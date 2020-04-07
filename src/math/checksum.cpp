/**
 * Copyright (c) 2011-2019 libnuls developers (see AUTHORS)
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
#include <nuls/system/math/checksum.hpp>

#include <nuls/system/math/hash.hpp>
#include <nuls/system/utility/endian.hpp>
#include <nuls/system/utility/deserializer.hpp>

namespace libnuls {
namespace system {

void append_checksum(data_chunk& data)
{
    const auto checksum = bitcoin_checksum(data);
    extend_data(data, to_little_endian(checksum));
}

uint32_t bitcoin_checksum(const data_slice& data)
{
    const auto hash = bitcoin_hash(data);
    return from_little_endian_unsafe<uint32_t>(hash.begin());
}

bool verify_checksum(const data_slice& data)
{
    if (data.size() < checksum_size)
        return false;

    // TODO: create a bitcoin_checksum overload that can accept begin/end.
    const auto checksum_begin = data.end() - checksum_size;
    auto checksum = from_little_endian_unsafe<uint32_t>(checksum_begin);
    return bitcoin_checksum({ data.begin(), checksum_begin }) == checksum;
}

} // namespace system
} // namespace libnuls

