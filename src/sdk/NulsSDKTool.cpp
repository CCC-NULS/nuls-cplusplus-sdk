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

#include <regex>

#include <nuls/system/sdk/NulsSDKTool.hpp>
#include <nuls/system/wallet/encrypted_keys.hpp>
#include <nuls/system/utility/pseudo_random.hpp>
#include <nuls/system/formats/base_58.hpp>

namespace libnuls {
namespace system {
namespace sdk {

uint8_t op_assign(char ch) { return static_cast<uint8_t>(ch); }

std::vector<model::account> NulsSDKTool::createOffLineAccount(int count, std::string prefix, std::string password)
{
    std::vector<model::account> list;

    if (!NulsSDKTool::validPassword(password))
    {
        return  list;
    }
    if (count < 1)
    {
        count = 1;
    }

    bool ret;
    wallet::encrypted_token token;
    std::transform(password.begin(), password.end(), token.begin(), op_assign);
    wallet::encrypted_private out_private;
    ec_compressed out_point;
    wallet::ek_seed seed;
    pseudo_random::fill(seed);

    for (int i = 0; i < count; i++) 
    {
        ret = wallet::create_key_pair(out_private, out_point, token, seed, 0);
        if (false == ret){
            break;
        }


#if 0
        Account account;
        if (StringUtils.isBlank(prefix))
        {
            account = AccountTool.createAccount(SDKContext.main_chain_id);
        }
        else
        {
            account = AccountTool.createAccount(SDKContext.main_chain_id, null, prefix);
        }
        if (StringUtils.isNotBlank(password))
        {
            account.encrypt(password);
        }
        AccountDto accountDto = new AccountDto();
        accountDto.setAddress(account.getAddress().toString());
        accountDto.setPubKey(HexUtil.encode(account.getPubKey()));
        if (account.isEncrypted())
        {
            accountDto.setPrikey("");
            accountDto.setEncryptedPrivateKey(HexUtil.encode(account.getEncryptedPriKey()));
        }
        else
        {
            accountDto.setPrikey(HexUtil.encode(account.getPriKey()));
            accountDto.setEncryptedPrivateKey("");
        }
        list.add(accountDto);
#endif        
    }

    return list;
}


bool NulsSDKTool::validPassword(std::string password)
{
    if (password.empty())
    {
        return false;
    }
    if (password.length() < 8 || password.length() > 20)
    {
        return false;
    }

    std::string str1("(.*)[a-zA-Z](.*)");
    std::string str2("(.*)\\d+(.*)");    
    std::string str3("(.*)\\s+(.*)");    
    std::string str4("(.*)[\u4e00-\u9fa5\u3000]+(.*)");

    std::regex pattern1(str1, std::regex::icase);
    std::regex pattern2(str2, std::regex::icase);
    std::regex pattern3(str3, std::regex::icase);    
    std::regex pattern4(str4, std::regex::icase);

    if (std::regex_match(password, pattern1) && 
        std::regex_match(password, pattern2)  && 
        !std::regex_match(password, pattern3)  && 
        !std::regex_match(password, pattern4) )
    {
        return true;
    }

    return false;
}

} // namespace sdk
} // namespace system
} // namespace libnuls


