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
#include <nuls/system/utility/scope_lock.hpp>

#include <memory>
#include <nuls/system/utility/thread.hpp>

namespace libnuls {
namespace system {

scope_lock::scope_lock(shared_mutex& mutex)
  : mutex_(mutex)
{
    mutex_.lock();
}

scope_lock::~scope_lock()
{
    mutex_.unlock();
}

} // namespace system
} // namespace libnuls
