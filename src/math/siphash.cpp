/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
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

// Sponsored in part by Digital Contract Design, LLC

#include <bitcoin/system/constants.hpp>
#include <bitcoin/system/math/siphash.hpp>
#include <bitcoin/system/utility/container_source.hpp>
#include <bitcoin/system/utility/endian.hpp>
#include <bitcoin/system/utility/istream_reader.hpp>

namespace libbitcoin {
namespace system {

BC_CONSTEXPR uint64_t finalization = 0x00000000000000ff;
BC_CONSTEXPR uint32_t max_encoded_byte_count = (1 << byte_bits);

// NOTE: C++20 provides std::rotl which could replace this function.
uint64_t inline rotate_left(uint64_t value, uint8_t shift)
{
    return (uint64_t)((value << shift) | (value >> (64 - shift)));
}

void inline sipround(uint64_t& v0, uint64_t& v1, uint64_t& v2, uint64_t& v3)
{
    v0 += v1;
    v2 += v3;
    v1 = rotate_left(v1, 13);
    v3 = rotate_left(v3, 16);
    v1 ^= v0;
    v3 ^= v2;

    v0 = rotate_left(v0, 32);

    v2 += v1;
    v0 += v3;
    v1 = rotate_left(v1, 17);
    v3 = rotate_left(v3, 21);
    v1 ^= v2;
    v3 ^= v0;

    v2 = rotate_left(v2, 32);
}

void inline compression_round(uint64_t& v0, uint64_t& v1, uint64_t& v2,
    uint64_t& v3, uint64_t word)
{
    v3 ^= word;
    sipround(v0, v1, v2, v3);
    sipround(v0, v1, v2, v3);
    v0 ^= word;
}

uint64_t siphash(const half_hash& hash, const data_slice& message)
{
    return siphash(to_siphash_key(hash), message);
}

uint64_t siphash(const siphash_key& key, const data_slice& message)
{
    uint64_t v0 = siphash_magic_0 ^ std::get<0>(key);
    uint64_t v1 = siphash_magic_1 ^ std::get<1>(key);
    uint64_t v2 = siphash_magic_2 ^ std::get<0>(key);
    uint64_t v3 = siphash_magic_3 ^ std::get<1>(key);

    uint64_t byte_count = message.size();
    stream_source<data_slice> istream(message);
    istream_reader source(istream);

    for (uint64_t index = 8; index <= byte_count; index += byte_bits)
    {
        uint64_t word = source.read_8_bytes_little_endian();
        compression_round(v0, v1, v2, v3, word);
    }

    uint64_t last_word = 0;

    if (byte_count % byte_bits > 0)
        last_word = source.read_8_bytes_little_endian();

    last_word ^= ((byte_count % max_encoded_byte_count) << 56);
    compression_round(v0, v1, v2, v3, last_word);

    v2 ^= finalization;
    sipround(v0, v1, v2, v3);
    sipround(v0, v1, v2, v3);
    sipround(v0, v1, v2, v3);
    sipround(v0, v1, v2, v3);

    return v0 ^ v1 ^ v2 ^ v3;
}

siphash_key to_siphash_key(const half_hash& hash)
{
    const auto upper = from_little_endian<uint64_t, half_hash::const_iterator>(
        hash.begin(), hash.begin() + (half_hash_size / 2));

    const auto lower = from_little_endian<uint64_t, half_hash::const_iterator>(
        hash.begin() + (half_hash_size / 2), hash.end());

    return std::make_tuple(upper, lower);
}

} // namespace system
} // namespace libbitcoin
