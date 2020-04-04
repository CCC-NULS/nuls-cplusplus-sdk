/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
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

#include <bitcoin/system/message/get_compact_filter_headers.hpp>

#include <initializer_list>
#include <bitcoin/system/math/limits.hpp>
#include <bitcoin/system/message/messages.hpp>
#include <bitcoin/system/message/version.hpp>
#include <bitcoin/system/utility/container_sink.hpp>
#include <bitcoin/system/utility/container_source.hpp>
#include <bitcoin/system/utility/istream_reader.hpp>
#include <bitcoin/system/utility/ostream_writer.hpp>

namespace libbitcoin {
namespace system {
namespace message {

const std::string get_compact_filter_headers::command = "getcfheaders";
const uint32_t get_compact_filter_headers::version_minimum = version::level::minimum;
const uint32_t get_compact_filter_headers::version_maximum = version::level::maximum;

get_compact_filter_headers get_compact_filter_headers::factory(
    uint32_t version, const data_chunk& data)
{
    get_compact_filter_headers instance;
    instance.from_data(version, data);
    return instance;
}

get_compact_filter_headers get_compact_filter_headers::factory(
    uint32_t version, std::istream& stream)
{
    get_compact_filter_headers instance;
    instance.from_data(version, stream);
    return instance;
}

get_compact_filter_headers get_compact_filter_headers::factory(
    uint32_t version, reader& source)
{
    get_compact_filter_headers instance;
    instance.from_data(version, source);
    return instance;
}

get_compact_filter_headers::get_compact_filter_headers()
  : filter_type_(0u), start_height_(0u), stop_hash_(null_hash)
{
}

get_compact_filter_headers::get_compact_filter_headers(uint8_t filter_type,
    uint32_t start_height, const hash_digest& stop_hash)
  : filter_type_(filter_type),
    start_height_(start_height),
    stop_hash_(stop_hash)
{
}

get_compact_filter_headers::get_compact_filter_headers(uint8_t filter_type,
    uint32_t start_height, hash_digest&& stop_hash)
  : filter_type_(filter_type),
    start_height_(start_height),
    stop_hash_(std::move(stop_hash))
{
}

get_compact_filter_headers::get_compact_filter_headers(
    const get_compact_filter_headers& other)
  : get_compact_filter_headers(other.filter_type_, other.start_height_,
      other.stop_hash_)
{
}

get_compact_filter_headers::get_compact_filter_headers(
    get_compact_filter_headers&& other)
  : get_compact_filter_headers(other.filter_type_, other.start_height_,
      std::move(other.stop_hash_))
{
}

bool get_compact_filter_headers::is_valid() const
{
    return !(stop_hash_ == null_hash);
}

void get_compact_filter_headers::reset()
{
    filter_type_ = 0u;
    start_height_ = 0u;
    stop_hash_.fill(0);
}

bool get_compact_filter_headers::from_data(uint32_t version,
    const data_chunk& data)
{
    data_source istream(data);
    return from_data(version, istream);
}

bool get_compact_filter_headers::from_data(uint32_t version,
    std::istream& stream)
{
    istream_reader source(stream);
    return from_data(version, source);
}

bool get_compact_filter_headers::from_data(uint32_t version, reader& source)
{
    reset();

    filter_type_ = source.read_byte();
    start_height_ = source.read_4_bytes_little_endian();
    stop_hash_ = source.read_hash();

    if (version < get_compact_filter_headers::version_minimum)
        source.invalidate();

    if (!source)
        reset();

    return source;
}

data_chunk get_compact_filter_headers::to_data(uint32_t version) const
{
    data_chunk data;
    const auto size = serialized_size(version);
    data.reserve(size);
    data_sink ostream(data);
    to_data(version, ostream);
    ostream.flush();
    BITCOIN_ASSERT(data.size() == size);
    return data;
}

void get_compact_filter_headers::to_data(uint32_t version,
    std::ostream& stream) const
{
    ostream_writer sink(stream);
    to_data(version, sink);
}

void get_compact_filter_headers::to_data(uint32_t , writer& sink) const
{
    sink.write_byte(filter_type_);
    sink.write_4_bytes_little_endian(start_height_);
    sink.write_hash(stop_hash_);
}

size_t get_compact_filter_headers::satoshi_fixed_size()
{
    return sizeof(filter_type_) + sizeof(start_height_) + hash_size;
}

size_t get_compact_filter_headers::serialized_size(uint32_t ) const
{
    return satoshi_fixed_size();
}

uint8_t get_compact_filter_headers::filter_type() const
{
    return filter_type_;
}

void get_compact_filter_headers::set_filter_type(uint8_t value)
{
    filter_type_ = value;
}

uint32_t get_compact_filter_headers::start_height() const
{
    return start_height_;
}

void get_compact_filter_headers::set_start_height(uint32_t value)
{
    start_height_ = value;
}

hash_digest& get_compact_filter_headers::stop_hash()
{
    return stop_hash_;
}

const hash_digest& get_compact_filter_headers::stop_hash() const
{
    return stop_hash_;
}

void get_compact_filter_headers::set_stop_hash(const hash_digest& value)
{
    stop_hash_ = value;
}

void get_compact_filter_headers::set_stop_hash(hash_digest&& value)
{
    stop_hash_ = std::move(value);
}

get_compact_filter_headers& get_compact_filter_headers::operator=(
    get_compact_filter_headers&& other)
{
    filter_type_ = other.filter_type_;
    start_height_ = other.start_height_;
    stop_hash_ = std::move(other.stop_hash_);
    return *this;
}

bool get_compact_filter_headers::operator==(
    const get_compact_filter_headers& other) const
{
    return (filter_type_ == other.filter_type_)
        && (start_height_ == other.start_height_)
        && (stop_hash_ == other.stop_hash_);
}

bool get_compact_filter_headers::operator!=(
    const get_compact_filter_headers& other) const
{
    return !(*this == other);
}

} // namespace message
} // namespace system
} // namespace libbitcoin
