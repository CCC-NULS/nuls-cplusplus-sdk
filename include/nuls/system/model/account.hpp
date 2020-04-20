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

#ifndef LIBNULS_SYSTEM_MODEL_ACCOUNT_HPP
#define LIBNULS_SYSTEM_MODEL_ACCOUNT_HPP

#include <algorithm>
#include <iostream>
#include <cstdint>
#include <memory>
#include <string>
#include <nuls/system/define.hpp>

namespace libnuls {
namespace system {
namespace model {

class BC_API account {

private:
    std::string address;
    std::string pubKey;
    std::string prikey;
    std::string encryptedPrivateKey;

public:
    account(std::string address, std::string pubKey, std::string prikey, std::string encryptedPrivateKey)
    {
        setAddress(address);
        setEncryptedPrivateKey(encryptedPrivateKey);
        setPubKey(pubKey);
        setPrikey(prikey);
    }
    
    std::string getAddress()
    {
        return address;
    }

    void setAddress(std::string& other)
    {
        address = other;
    }

    std::string getPubKey()
    {
        return pubKey;
    }

    void setPubKey(std::string& other)
    {
        pubKey = other;
    }

    std::string getPrikey()
    {
        return prikey;
    }

    void setPrikey(std::string& other)
    {
        prikey = other;
    }

    std::string getEncryptedPrivateKey()
    {
        return encryptedPrivateKey;
    }

    void setEncryptedPrivateKey(std::string& other)
    {
        encryptedPrivateKey = other;
    }

};
} // namespace model
} // namespace system
} // namespace libnuls


#endif