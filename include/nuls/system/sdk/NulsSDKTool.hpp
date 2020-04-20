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

#ifndef LIBNULS_SYSTEM_SDK_NULSSDKTOOL_HPP
#define LIBNULS_SYSTEM_SDK_NULSSDKTOOL_HPP

#include <algorithm>
#include <iostream>
#include <cstdint>
#include <memory>
#include <string>
#include <cstddef>
#include <vector>
#include <nuls/system/define.hpp>
#include <nuls/system/model/account.hpp>

namespace libnuls {
namespace system {
namespace sdk {

class BC_API NulsSDKTool {

public:
    static std::vector<model::account> createOffLineAccount(int count, std::string prefix, std::string password);
    static std::vector<model::account> createOffLineAccount(int count, std::string password);
    

private:

    static bool validPassword(std::string password);       
};
} // namespace model
} // namespace system
} // namespace libnuls


#endif