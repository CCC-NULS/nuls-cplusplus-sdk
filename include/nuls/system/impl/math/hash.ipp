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
#ifndef LIBNULS_SYSTEM_HASH_IPP
#define LIBNULS_SYSTEM_HASH_IPP

#include <algorithm>
#include <cstddef>
#include <nuls/system/utility/data.hpp>

namespace libnuls {
namespace system {

template<size_t Size>
byte_array<Size> scrypt(const data_slice& data, const data_slice& salt, uint64_t N,
    uint32_t p, uint32_t r)
{
    const auto out = scrypt(data, salt, N, r, p, Size);
    return to_array<Size>({ out });
}

} // namespace system
} // namespace libnuls

#endif
