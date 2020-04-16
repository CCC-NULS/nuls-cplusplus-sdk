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
#ifndef LIBNULS_SYSTEM_TEST_OVERLOADS_HPP
#define LIBNULS_SYSTEM_TEST_OVERLOADS_HPP

#include <nuls/system.hpp>

#include <ostream>

namespace std {

template <size_t Size>
std::ostream& operator<<(std::ostream& stream,
    const nuls::system::byte_array<Size>& bytes)
{
    stream << nuls::system::encode_base16(bytes);
    return stream;
}

std::ostream& operator<<(std::ostream& stream,
    const nuls::system::hash_digest& hash);

std::ostream& operator<<(std::ostream& stream,
    const nuls::system::data_chunk& data);

} // namespace std

#endif
