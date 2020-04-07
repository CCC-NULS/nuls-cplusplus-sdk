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
#ifndef LIBNULS_SYSTEM_LOG_SINK_HPP
#define LIBNULS_SYSTEM_LOG_SINK_HPP

#include <iostream>
#include <boost/smart_ptr.hpp>
#include <nuls/system/define.hpp>
#include <nuls/system/log/rotable_file.hpp>
#include <nuls/system/log/severity.hpp>
#include <nuls/system/unicode/ofstream.hpp>

namespace libnuls {
namespace system {
namespace log {

typedef boost::shared_ptr<ofstream> file;

/// Initializes null (as opposed to default) logging sinks.
void initialize();

/// Initializes default non-rotable libnuls logging sinks and formats.
void initialize(log::file& debug_file, log::file& error_file,
    log::stream& output_stream, log::stream& error_stream, bool verbose);

/// Initializes default rotable libnuls logging sinks and formats.
void initialize(const rotable_file& debug_file, const rotable_file& error_file,
    log::stream& output_stream, log::stream& error_stream, bool verbose);

/// Log stream operator.
formatter& operator<<(formatter& stream, severity value);

} // namespace log
} // namespace system
} // namespace libnuls

#endif
