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

// Sponsored in part by Digital Contract Design, LLC

#ifndef LIBNULS_SYSTEM_OSTREAM_BIT_WRITER_IPP
#define LIBNULS_SYSTEM_OSTREAM_BIT_WRITER_IPP

#include <cstddef>
#include <nuls/system/utility/data.hpp>
#include <nuls/system/utility/endian.hpp>

namespace libnuls {
namespace system {

template <size_t Size>
void ostream_bit_writer::write_forward(const byte_array<Size>& value)
{
	// write_bytes(value.data(), Size);
    for (unsigned index = 0; index < Size; index++)
        write_byte(value[index]);
}

template <size_t Size>
void ostream_bit_writer::write_reverse(const byte_array<Size>& value)
{
    for (unsigned index = 0; index < Size; index++)
        write_byte(value[Size - (index + 1)]);
}

template <typename Integer>
void ostream_bit_writer::write_big_endian(Integer value)
{
    byte_array<sizeof(Integer)> bytes = to_big_endian(value);
    write_forward<sizeof(Integer)>(bytes);
}

template <typename Integer>
void ostream_bit_writer::write_little_endian(Integer value)
{
    byte_array<sizeof(Integer)> bytes = to_little_endian(value);
    write_forward<sizeof(Integer)>(bytes);
}

} // namespace system
} // namespace libnuls

#endif
