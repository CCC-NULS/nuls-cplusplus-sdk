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
#ifndef LIBNULS_SYSTEM_TRACK_HPP
#define LIBNULS_SYSTEM_TRACK_HPP

#include <atomic>
#include <cstddef>
#include <string>

// libnuls defines the log and tracking but does not use them.
// These are defined in bc so that they can be used in network and blockchain.

#define CONSTRUCT_TRACK(class_name) \
    track<class_name>(#class_name)

template <class Shared>
class track
{
public:
    static std::atomic<size_t> instances;

protected:
    track(const std::string& class_name);
    virtual ~track();

private:
    const std::string class_;
};

#include <nuls/system/impl/utility/track.ipp>

#endif
