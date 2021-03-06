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

#ifndef LIBNULS_SYSTEM_BIT_READER_HPP
#define LIBNULS_SYSTEM_BIT_READER_HPP

#include <cstdint>
#include <nuls/system/utility/reader.hpp>

namespace libnuls {
namespace system {

/// Reader interface.
class BC_API bit_reader
  : public reader
{
public:
    /// Read bit.
    virtual bool read_bit() = 0;

    virtual uint64_t read_variable_bits_big_endian(
        uint8_t least_significant_bits) = 0;
};

} // namespace system
} // namespace libnuls

#endif
