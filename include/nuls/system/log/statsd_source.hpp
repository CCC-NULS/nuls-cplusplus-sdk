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
#ifndef LIBNULS_SYSTEM_LOG_STATSD_SOURCE_HPP
#define LIBNULS_SYSTEM_LOG_STATSD_SOURCE_HPP

#include <chrono>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/features.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/threading_models.hpp>
#include <nuls/system/define.hpp>
#include <nuls/system/log/features/counter.hpp>
#include <nuls/system/log/features/gauge.hpp>
#include <nuls/system/log/features/metric.hpp>
#include <nuls/system/log/features/rate.hpp>
#include <nuls/system/log/features/timer.hpp>

namespace libnuls {
namespace system {
namespace log {

class BC_API statsd_source
  : public boost::log::sources::basic_composite_logger<char, statsd_source,
        boost::log::sources::multi_thread_model<boost::log::aux::light_rw_mutex>,
        boost::log::sources::features<features::metric, features::counter,
            features::gauge, features::timer, features::rate>>
{
    BOOST_LOG_FORWARD_LOGGER_MEMBERS(statsd_source)
};

BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(stats, statsd_source)

#define BC_STATS_SIMPLE(name, sequence) \
    BOOST_LOG_WITH_PARAMS(nuls::system::log::stats::get(), \
        (nuls::system::log::keywords::metric = (name))sequence)

#define BC_STATS_WITH_RATE(name, rate, sequence) \
    BOOST_LOG_WITH_PARAMS(nuls::system::log::stats::get(), \
        (nuls::system::log::keywords::metric = (name)) \
        (nuls::system::log::keywords::rate = (rate))sequence)

#define BC_STATS_COUNTER(name, value) \
    BC_STATS_SIMPLE(name, (nuls::system::log::keywords::counter = (value)))

#define BC_STATS_COUNTER_RATE(name, value, rate) \
    BC_STATS_WITH_RATE(name, rate, \
    (nuls::system::log::keywords::counter = (value)))

#define BC_STATS_GAUGE(name, value) \
    BC_STATS_SIMPLE(name, (nuls::system::log::keywords::gauge = (value)))

#define BC_STATS_GAUGE_RATE(name, value, rate) \
    BC_STATS_WITH_RATE(name, rate, \
    (nuls::system::log::keywords::gauge = (value)))

#define BC_STATS_TIMER(name, value) \
    BC_STATS_SIMPLE(name, (nuls::system::log::keywords::timer = (value)))

#define BC_STATS_TIMER_RATE(name, value, rate) \
    BC_STATS_WITH_RATE(name, rate, \
    (nuls::system::log::keywords::timer = (value)))

} // namespace log
} // namespace system
} // namespace libnuls

#endif
