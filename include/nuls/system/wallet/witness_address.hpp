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
#ifndef LIBNULS_SYSTEM_WALLET_WITNESS_ADDRESS_HPP
#define LIBNULS_SYSTEM_WALLET_WITNESS_ADDRESS_HPP

#include <nuls/system/math/hash.hpp>
#include <nuls/system/wallet/payment_address.hpp>

namespace libnuls {
namespace system {
namespace wallet {

/// A class for working with standard witness payment addresses.
class BC_API witness_address
  : public payment_address
{
  public:
    enum class address_format: uint8_t
    {
        witness_pubkey_hash,
        witness_script_hash
    };

    static const std::string mainnet_prefix;
    static const std::string testnet_prefix;

    typedef std::vector<witness_address> list;
    typedef std::shared_ptr<witness_address> ptr;

    /// Constructors.
    witness_address();
    witness_address(witness_address&& other);
    witness_address(const witness_address& other);
    witness_address(const std::string& address,
        address_format format=address_format::witness_pubkey_hash);
    witness_address(short_hash&& hash,
        address_format format=address_format::witness_pubkey_hash,
        uint8_t witness_version=0, const std::string& prefix=mainnet_prefix);
    witness_address(const short_hash& hash,
        address_format format=address_format::witness_pubkey_hash,
        uint8_t witness_version=0, const std::string& prefix=mainnet_prefix);
    witness_address(hash_digest&& hash,
        address_format format=address_format::witness_pubkey_hash,
        uint8_t witness_version=0, const std::string& prefix=mainnet_prefix);
    witness_address(const hash_digest& hash,
        address_format format=address_format::witness_pubkey_hash,
        uint8_t witness_version=0, const std::string& prefix=mainnet_prefix);
    witness_address(const chain::script& script,
        address_format format=address_format::witness_pubkey_hash,
        const std::string& prefix=mainnet_prefix);
    witness_address(const ec_private& secret,
        address_format format=address_format::witness_pubkey_hash,
        const std::string& prefix=mainnet_prefix);
    witness_address(const ec_public& point,
        address_format format=address_format::witness_pubkey_hash,
        const std::string& prefix=mainnet_prefix);

    /// Operators.
    bool operator<(const witness_address& other) const;
    bool operator==(const witness_address& other) const;
    bool operator!=(const witness_address& other) const;
    witness_address& operator=(const witness_address& other);
    friend std::istream& operator>>(std::istream& in,
        witness_address& to);
    friend std::ostream& operator<<(std::ostream& out,
        const witness_address& of);

    /// Cast operators.
    operator bool() const;

    /// Serializer.
    std::string encoded() const;

    /// Accessors.
    uint8_t witness_version() const;
    const hash_digest& witness_hash() const;
    chain::script output_script() const;

protected:
    /// Protected for unit testing.
    static data_chunk convert_bits(uint32_t from_bits, uint32_t to_bits,
        bool pad, const data_chunk& in, size_t in_offset);

private:
    /// Validators.
    static bool is_address(data_slice decoded);

    /// Factories.
    static witness_address from_string(const std::string& address,
        address_format format=address_format::witness_pubkey_hash,
        const std::string& prefix=mainnet_prefix);
    static witness_address from_script(const chain::script& script,
        address_format format=address_format::witness_pubkey_hash,
        const std::string& prefix=mainnet_prefix);
    static witness_address from_private(const ec_private& secret,
        address_format format=address_format::witness_pubkey_hash,
        const std::string& prefix=mainnet_prefix);
    static witness_address from_public(const ec_public& point,
        address_format format=address_format::witness_pubkey_hash,
        const std::string& prefix=mainnet_prefix);

    std::string prefix_;
    address_format format_;
    uint8_t witness_version_;
    hash_digest witness_hash_;
};

} // namespace wallet
} // namespace system
} // namespace libnuls

// Allow witness_address to be in indexed in std::*map classes.
namespace std
{
template <>
struct hash<nuls::system::wallet::witness_address>
{
    size_t operator()(const nuls::system::wallet::witness_address& address) const
    {
        return address.witness_hash() == nuls::system::null_hash ?
            std::hash<nuls::system::short_hash>()(address.hash()) :
            std::hash<nuls::system::hash_digest>()(address.witness_hash());
    }
};

} // namespace std

#endif
