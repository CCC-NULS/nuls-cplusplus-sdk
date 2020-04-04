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
#ifndef LIBBITCOIN_SYSTEM_EC_SCALAR_HPP
#define LIBBITCOIN_SYSTEM_EC_SCALAR_HPP

#include <cstdint>
#include <memory>
#include <bitcoin/system/define.hpp>
#include <bitcoin/system/math/elliptic_curve.hpp>

namespace libbitcoin {
namespace system {

class BC_API ec_scalar
{
public:
    static const ec_scalar zero;

    /// Constructors.
    ec_scalar();
    ec_scalar(const ec_secret& secret);
    ec_scalar(const ec_scalar& scalar);
    ec_scalar(ec_scalar&& scalar);
    ec_scalar(uint64_t value);

    /// Operators.
    ec_scalar& operator=(const ec_secret& secret);
    ec_scalar& operator=(const ec_scalar& scalar);
    ec_scalar& operator=(ec_scalar&& scalar);
    ec_scalar& operator=(uint64_t value);

    ec_scalar operator-();
    ec_scalar& operator+=(const ec_scalar& scalar);
    ec_scalar& operator-=(const ec_scalar& scalar);
    ec_scalar& operator*=(const ec_scalar& scalar);

    /// Cast operators.
    operator bool() const;
    operator const ec_secret&() const;

    /// Accessors.
    const ec_secret& secret() const;

protected:
    friend ec_scalar operator+(const ec_scalar& left, const ec_scalar& right);
    friend ec_scalar operator-(const ec_scalar& left, const ec_scalar& right);
    friend ec_scalar operator*(const ec_scalar& left, const ec_scalar& right);

    std::shared_ptr<ec_secret> secret_;
};

bool operator==(const ec_scalar& left, const ec_scalar& right);
bool operator!=(const ec_scalar& left, const ec_scalar& right);
ec_scalar operator+(const ec_scalar& left, const ec_scalar& right);
ec_scalar operator-(const ec_scalar& left, const ec_scalar& right);
ec_scalar operator*(const ec_scalar& left, const ec_scalar& right);

} // namespace system
} // namespace libbitcoin

#endif

