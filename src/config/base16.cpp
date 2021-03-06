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
#include <nuls/system/config/base16.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <nuls/system/formats/base_16.hpp>
#include <nuls/system/utility/data.hpp>

namespace libnuls {
namespace system {
namespace config {

base16::base16()
{
}

base16::base16(const std::string& hexcode)
{
    std::stringstream(hexcode) >> *this;
}

base16::base16(const data_chunk& value)
  : value_(value)
{
}

base16::base16(const base16& other)
  : base16(other.value_)
{
}

base16::operator const data_chunk&() const
{
    return value_;
}

base16::operator data_slice() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, base16& argument)
{
    std::string hexcode;
    input >> hexcode;

    if (!decode_base16(argument.value_, hexcode))
    {
        using namespace boost::program_options;
        BOOST_THROW_EXCEPTION(invalid_option_value(hexcode));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const base16& argument)
{
    output << encode_base16(argument.value_);
    return output;
}

} // namespace config
} // namespace system
} // namespace libnuls
