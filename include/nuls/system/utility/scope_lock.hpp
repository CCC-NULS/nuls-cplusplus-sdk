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
#ifndef LIBNULS_SYSTEM_SCOPE_LOCK_HPP
#define LIBNULS_SYSTEM_SCOPE_LOCK_HPP

#include <memory>
#include <nuls/system/define.hpp>
#include <nuls/system/utility/thread.hpp>

namespace libnuls {
namespace system {

/// This class is thread safe.
/// Reserve exclusive access to a resource while this object is in scope.
class BC_API scope_lock
{
public:
    typedef std::shared_ptr<scope_lock> ptr;

    /// Lock using the specified mutex reference.
    scope_lock(shared_mutex& mutex);

    /// Unlock.
    virtual ~scope_lock();

private:
    shared_mutex& mutex_;
};

} // namespace system
} // namespace libnuls

#endif
