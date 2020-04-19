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
#ifndef LIBNULS_SYSTEM_SDK_ADDRESS_HPP
#define LIBNULS_SYSTEM_SDK_ADDRESS_HPP

#include <nuls/system/math/hash.hpp>
#include <nuls/system/wallet/payment_address.hpp>
#include <nuls/system/wallet/ec_private.hpp>
#include <nuls/system/wallet/ec_public.hpp>


namespace libnuls {
namespace system {
namespace sdk {

/// A class for working with standard witness payment addresses.
class BC_API address  //: public wallet::payment_address
{
public:
  static const std::string mainnet_prefix;
  static const std::string testnet_prefix;
  static const int ADDRESS_LENGTH = 23;

  address(int chainId, std::string prefix, uint8_t addressType, short_hash hash160);
  std::string to_string();

private:
    static uint8_t get_xor(byte_array<ADDRESS_LENGTH> body);  
    static const std::string LENGTHPREFIX[];

    std::string prefix;
    int chainId;
    std::string addressStr;
    uint8_t addressType;
    short_hash hash160;
    byte_array<ADDRESS_LENGTH> addressBytes;


};

} // namespace sdk
} // namespace system
} // namespace libnuls


#endif
