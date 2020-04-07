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

#ifndef LIBNULS_SYSTEM_SIPHASH
#define LIBNULS_SYSTEM_SIPHASH

#include <cstdint>
#include <tuple>
#include <nuls/system/compat.hpp>
#include <nuls/system/define.hpp>
#include <nuls/system/math/hash.hpp>
#include <nuls/system/utility/data.hpp>

namespace libnuls {
namespace system {

typedef std::tuple<uint64_t, uint64_t> siphash_key;

siphash_key to_siphash_key(const half_hash& hash);
uint64_t siphash(const half_hash& hash, const data_slice& message);
uint64_t siphash(const siphash_key& key, const data_slice& message);

} // namespace system
} // namespace libnuls

#endif
