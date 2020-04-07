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
#ifndef LIBNULS_SYSTEM_SEQUENCER_HPP
#define LIBNULS_SYSTEM_SEQUENCER_HPP

#include <functional>
#include <memory>
#include <queue>
#include <nuls/system/utility/asio.hpp>
#include <nuls/system/utility/enable_shared_from_base.hpp>
#include <nuls/system/utility/thread.hpp>
////#include <nuls/system/utility/track.hpp>

namespace libnuls {
namespace system {

class sequencer
  : public enable_shared_from_base<sequencer>
    /*, track<sequencer>*/
{
public:
    typedef std::shared_ptr<sequencer> ptr;
    typedef std::function<void()> action;

    sequencer(asio::service& service);
    virtual ~sequencer();

    void lock(action&& handler);
    void unlock();

private:
    // This is thread safe.
    asio::service& service_;

    // These are protected by mutex.
    bool executing_;
    std::queue<action> actions_;
    mutable shared_mutex mutex_;
};

} // namespace system
} // namespace libnuls

#endif
