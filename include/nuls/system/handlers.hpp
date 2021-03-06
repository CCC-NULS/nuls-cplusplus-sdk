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
#ifndef LIBNULS_SYSTEM_HANDLERS_HPP
#define LIBNULS_SYSTEM_HANDLERS_HPP

#include <functional>
#include <nuls/system/error.hpp>

namespace libnuls {
namespace system {

typedef std::function<void(const code&)> handle0;

template <typename Type>
using handle1 = std::function<void(const code&, const Type&)>;

template <typename Type1, typename Type2>
using handle2 = std::function<void(const code&, const Type1&,
    const Type2&)>;

template <typename Type1, typename Type2, typename Type3>
using handle3 = std::function<void(const code&, const Type1&,
    const Type2&, const Type3&)>;

} // namespace system
} // namespace libnuls

#endif
