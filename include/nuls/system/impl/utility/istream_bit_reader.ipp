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
 
// Sponsored in part by Digital Contract Design, LLC

#ifndef LIBNULS_SYSTEM_ISTREAM_BIT_READER_IPP
#define LIBNULS_SYSTEM_ISTREAM_BIT_READER_IPP

#include <nuls/system/utility/data.hpp>
#include <nuls/system/utility/endian.hpp>

namespace libnuls {
namespace system {

#define VERIFY_UNSIGNED(T) static_assert(std::is_unsigned<T>::value, \
    "The endian functions only work on unsigned types")

template <size_t Size>
byte_array<Size> istream_bit_reader::read_forward()
{
	auto data = reader_.read_bytes(Size);
	byte_array<Size> out = to_array<Size>(data);
    return out;
}

template <size_t Size>
byte_array<Size> istream_bit_reader::read_reverse()
{
    byte_array<Size> out;

    for (size_t index = 0; index < Size; index++)
        out[Size - (index + 1)] = read_byte();

    return out;
}

template <typename Integer>
Integer istream_bit_reader::read_big_endian()
{
    VERIFY_UNSIGNED(Integer);
    Integer out = 0;

    for (size_t index = sizeof(Integer); (index > 0) && !empty(); index--)
    {
        uint8_t value = read_byte();
        out |= static_cast<Integer>(value) << (8 * (index - 1));
    }

    return out;
}

template <typename Integer>
Integer istream_bit_reader::read_little_endian()
{
    VERIFY_UNSIGNED(Integer);
    Integer out = 0;

    for (size_t index = 0; (index < sizeof(Integer)) && !empty(); index++)
    {
        uint8_t value = read_byte();
        out |= static_cast<Integer>(value) << (8 * index);
    }

    return out;
}

} // namespace system
} // namespace libnuls

#endif
