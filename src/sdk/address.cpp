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
#include <nuls/system/sdk/address.hpp>

#include <algorithm>
#include <cstdint>
#include <string>
#include <utility>
#include <boost/program_options.hpp>
#include <nuls/system/formats/base_32.hpp>
#include <nuls/system/formats/base_58.hpp>
#include <nuls/system/math/checksum.hpp>
#include <nuls/system/math/elliptic_curve.hpp>
#include <nuls/system/math/hash.hpp>
#include <nuls/system/wallet/ec_private.hpp>
#include <nuls/system/wallet/ec_public.hpp>

namespace libnuls {
namespace system {
namespace sdk {

using namespace nuls::system::machine;

const std::string address::mainnet_prefix = "NULS";
const std::string address::testnet_prefix = "tNULS";
const std::string LENGTHPREFIX[] =  {"", "a", "b", "c", "d", "e"};
 
address::address(int chainId, std::string prefix, uint8_t addressType, short_hash hash160)
  : chainId(chainId), prefix(prefix), addressType(addressType), hash160(hash160)
{
    addressBytes[0] = (uint16_t)chainId | 0xff;
    addressBytes[1] = ((uint16_t)chainId >> 8)| 0xff;
    addressBytes[2] = addressType;
    std::copy(hash160.begin(), hash160.end(), addressBytes.begin() + 3);
}
std::string address::to_string()
{
    std::string addstr;
    if (!prefix.empty())
    {
        addstr.append(prefix);
        addstr.append(LENGTHPREFIX[prefix.length()]);
    }
    byte_array<ADDRESS_LENGTH + 1> addressBytesWithXor;
    std::copy(addressBytes.begin(), addressBytes.end(), addressBytesWithXor.begin());
    addressBytesWithXor[ADDRESS_LENGTH] = get_xor(addressBytes);
    addstr.append(encode_base58(addressBytesWithXor));
    return addressStr;
}
uint8_t address::get_xor(byte_array<ADDRESS_LENGTH> body) 
{
    uint8_t ret = 0;
    for (int i = 0; i < body.size(); i++)
    {
        ret ^= body[i];
    }
    return ret;
}


} // namespace sdk
} // namespace system
} // namespace libnuls
