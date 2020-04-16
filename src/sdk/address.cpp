/**
 * Copyright (c) 2020 libnuls developers (see AUTHORS)
 *
 * This file is part of libnuls.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <nuls/system/sdk/address.hpp>

#include <algorithm>
#include <cstdint>
#include <string>
#include <utility>
#include <boost/program_options.hpp>
#include <nuls/system/formats/base_32.hpp>
#include <nuls/system/formats/base_58.hpp>
#include <nuls/system/math/checksum.hpp>
#include <nuls/system/math/elliptic_curve.hpp>
#include <nuls/system/math/hash.hpp>
#include <nuls/system/wallet/ec_private.hpp>
#include <nuls/system/wallet/ec_public.hpp>

namespace libnuls {
namespace system {
namespace sdk {

using namespace nuls::system::machine;

const std::string address::mainnet_prefix = "NULS";
const std::string address::testnet_prefix = "tNULS";

const size_t bech32_contracted_bit_size = 5;
const size_t bech32_expanded_bit_size = 8;

address::address()
  : payment_address(),
    witness_version_(0),
    witness_hash_(null_hash)
{
}

address::address(address&& other)
  : payment_address(other),
    prefix_(other.prefix_),
    format_(other.format_),
    witness_version_(other.witness_version_),
    witness_hash_(std::move(other.witness_hash_))
{
}

address::address(const address& other)
  : payment_address(other),
    prefix_(other.prefix_),
    format_(other.format_),
    witness_hash_(other.witness_hash_)
{
}

address::address(const std::string& addr,
    address_format format)
  : address(from_string(addr, format))
{
}

address::address(const wallet::ec_private& secret,
    address_format format, const std::string& prefix)
  : address(from_private(secret, format, prefix))
{
}

address::address(const wallet::ec_public& point, address_format format,
    const std::string& prefix)
  : address(from_public(point, format, prefix))
{
}

address::address(const chain::script& script,
    address_format format, const std::string& prefix)
  : address(from_script(script, format, prefix))
{
}

address::address(short_hash&& hash, address_format format,
    uint8_t witness_version, const std::string& prefix)
  : payment_address(std::move(hash)),
    prefix_(prefix),
    format_(format),
    witness_version_(witness_version),
    witness_hash_(null_hash)
{
}

address::address(const short_hash& hash, address_format format,
    uint8_t witness_version, const std::string& prefix)
  : payment_address(hash),
    prefix_(prefix),
    format_(format),
    witness_version_(witness_version),
    witness_hash_(null_hash)
{
}

address::address(hash_digest&& hash, address_format format,
    uint8_t witness_version, const std::string& prefix)
  : payment_address(null_short_hash),
    prefix_(prefix),
    format_(format),
    witness_version_(witness_version),
    witness_hash_(std::move(hash))
{
}

address::address(const hash_digest& hash, address_format format,
    uint8_t witness_version, const std::string& prefix)
  : payment_address(null_short_hash),
    prefix_(prefix),
    format_(format),
    witness_version_(witness_version),
    witness_hash_(hash)
{
}

// Factories.
// ----------------------------------------------------------------------------
// static
address address::from_string(const std::string& addr,
    address_format format, const std::string& prefix)
{
    // BIP 141 constants
    static constexpr size_t witness_program_min_size = 2;
    static constexpr size_t witness_program_max_size = 40;

    // BIP 173 witness version 0 constants
    static constexpr size_t witness_pubkey_hash_size = 42;
    static constexpr size_t witness_script_hash_size = 62;
    static constexpr size_t bech32_address_min_size = 14;
    static constexpr size_t bech32_address_max_size = 74;
    static constexpr size_t bech32_address_size_modulo = 8;
    static constexpr size_t bech32_address_modulo_invalid_1 = 0;
    static constexpr size_t bech32_address_modulo_invalid_2 = 3;
    static constexpr size_t bech32_address_modulo_invalid_3 = 5;

    // Attempt to decode BIP 173 address format.
    base32 bech32_decoded;
    if (!decode_base32(bech32_decoded, addr))
        return {};

    const uint8_t witness_version = bech32_decoded.payload.front();

    // Checks specific to witness version 0.
    if (witness_version == 0 && (addr.size() < witness_pubkey_hash_size ||
        addr.size() > witness_script_hash_size))
        return {};

    // Verify witness version is valid (only version 0 is
    // currently supported).
    if (witness_version != 0)
        return {};

    // Verify additional properties (BIP173 decoding).
    if (addr.size() < bech32_address_min_size ||
        addr.size() > bech32_address_max_size)
        return {};

    const auto address_mod = addr.size() % bech32_address_size_modulo;
    if (address_mod == bech32_address_modulo_invalid_1 ||
        address_mod == bech32_address_modulo_invalid_2 ||
        address_mod == bech32_address_modulo_invalid_3)
        return {};

    const auto converted = convert_bits(bech32_contracted_bit_size,
        bech32_expanded_bit_size, false, bech32_decoded.payload, 1);
    if (converted.size() < witness_program_min_size ||
        converted.size() > witness_program_max_size)
        return {};

    if (converted.size() == hash_size)
    {
        auto hash = to_array<hash_size>(converted);
        return { std::move(hash), format, witness_version, prefix };
    }

    BITCOIN_ASSERT(converted.size() == short_hash_size);
    auto hash = to_array<short_hash_size>(converted);
    return { std::move(hash), format, witness_version, prefix };
}

// static
address address::from_private(const wallet::ec_private& secret,
    address_format format, const std::string& prefix)
{
    return secret ? address(secret.to_public(), format, prefix)
        : address{};
}

// static
address address::from_public(const wallet::ec_public& point,
    address_format format, const std::string& prefix)
{
    if (!point)
        return {};

    data_chunk data;
    if (!point.to_data(data))
        return {};

    // Witness version.
    const uint8_t version = 0;

    return format == address_format::witness_pubkey_hash ?
        address(bitcoin_short_hash(data), format, version, prefix) :
        address(bitcoin_hash(data), format, version, prefix);
}

// static
address address::from_script(const chain::script& script,
    address_format format, const std::string& prefix)
{
    // Witness version.
    const uint8_t version = 0;
    const auto key = script.to_payments_key();

    return format == address_format::witness_pubkey_hash ?
        address(ripemd160_hash(key), format, version, prefix) :
        address(key, format, version, prefix);
}

// Cast operators.
// ----------------------------------------------------------------------------

address::operator bool() const
{
    return valid_;
}

// Serializer.
// ----------------------------------------------------------------------------

// Returns the bech32 encoded witness address.
std::string address::encoded() const
{
    const size_t conversion_offset = 0;

    base32 bech32;
    bech32.prefix = prefix_;
    bech32.payload = build_chunk(
    {
        to_chunk(witness_version_),
        witness_hash_ == null_hash ?
            convert_bits(bech32_expanded_bit_size, bech32_contracted_bit_size,
                true, to_chunk(hash_), conversion_offset) :
            convert_bits(bech32_expanded_bit_size, bech32_contracted_bit_size,
                true, to_chunk(witness_hash_), conversion_offset)
    });

    return encode_base32(bech32);
}

// Accessors.
// ----------------------------------------------------------------------------

uint8_t address::witness_version() const
{
    return witness_version_;
}

const hash_digest& address::witness_hash() const
{
    return witness_hash_;
}

chain::script address::output_script() const
{
    return format_ == address_format::witness_pubkey_hash ?
        chain::script::to_pay_witness_key_hash_pattern(hash_) :
        chain::script::to_pay_witness_script_hash_pattern(witness_hash_);
}

// Operators.
// ----------------------------------------------------------------------------

address& address::operator=(const address& other)
{
    valid_ = other.valid_;
    hash_ = other.hash_;
    prefix_ = other.prefix_;
    format_ = other.format_;
    witness_version_ = other.witness_version_;
    witness_hash_ = other.witness_hash_;
    return *this;
}

bool address::operator<(const address& other) const
{
    return encoded() < other.encoded();
}

bool address::operator==(const address& other) const
{
    return valid_ == other.valid_
        && version_ == other.version_
        && prefix_ == other.prefix_
        && format_ == other.format_
        && witness_version_ == other.witness_version_
        && hash_ == other.hash_
        && witness_hash_ == other.witness_hash_;
}

bool address::operator!=(const address& other) const
{
    return !(*this == other);
}

std::istream& operator>>(std::istream& in, address& to)
{
    std::string value;
    in >> value;
    to = address(value);

    if (!to)
    {
        using namespace boost::program_options;
        BOOST_THROW_EXCEPTION(invalid_option_value(value));
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const address& of)
{
    out << of.encoded();
    return out;
}

// static
data_chunk address::convert_bits(uint32_t from_bits, uint32_t to_bits,
    bool pad, const data_chunk& in, size_t in_offset)
{
    const uint32_t maximum = (1 << to_bits) - 1;
    const uint32_t maximum_accumulator = (1 << (from_bits + to_bits - 1)) - 1;

    size_t offset = 0;
    uint32_t bit_count = 0;
    uint32_t accumulator = 0;

    data_chunk out;
    for (const auto value: in)
    {
        if (offset++ < in_offset)
            continue;

        accumulator = ((accumulator << from_bits) | value);
        accumulator &= maximum_accumulator;

        bit_count += from_bits;
        while (bit_count >= to_bits)
        {
            bit_count -= to_bits;
            out.push_back((accumulator >> bit_count) & maximum);
        }
    }

    if (pad && bit_count > 0)
        out.push_back((accumulator << (to_bits - bit_count)) & maximum);
    else if (!pad && (bit_count >= from_bits ||
        ((accumulator << (to_bits - bit_count)) & maximum)))
        return {};

    return out;
}

} // namespace sdk
} // namespace system
} // namespace libnuls
