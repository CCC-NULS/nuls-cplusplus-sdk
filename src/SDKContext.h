// Copyright © 2020 NULS.


#pragma once


#include <stdint.h>
#include <string>

namespace NULS {

class SDKContext {

public:
    static std::string DEFAULT_ENCODING;
    /**
     * 本链id
     */
    static int main_chain_id;
    /**
     * 本链主资产id
     */
    static const int main_asset_id;
    /**
     * NULS主网链id
     */
    static int nuls_chain_id;
    /**
     * NULS主资产id
     */
    static const int nuls_asset_id;
    /**
     * NULS主网默认转账交易手续费单价
     */
    static const int NULS_DEFAULT_NORMAL_TX_FEE_PRICE;
    /**
     * NULS主网默认业务交易手续费单价
     */
    static const int NULS_DEFAULT_OTHER_TX_FEE_PRICE;
    /**
     * 注销共识节点，保证金锁定时间
     */
    static const int STOP_AGENT_LOCK_TIME;
    /**
     * 访问钱包的http接口url地址
     */
    static std::string wallet_url;

};

std::string SDKContext::DEFAULT_ENCODING = "UTF-8";
int SDKContext::main_chain_id = 1;
const int SDKContext::main_asset_id = 1;
int SDKContext::nuls_chain_id = 1;
const int SDKContext::nuls_asset_id = 1;
const int SDKContext::NULS_DEFAULT_NORMAL_TX_FEE_PRICE = 100000;
const int SDKContext::NULS_DEFAULT_OTHER_TX_FEE_PRICE = 100000;
const int SDKContext::STOP_AGENT_LOCK_TIME = 259200;
std::string SDKContext::wallet_url = std::string("http://127.0.0.1:9898/");

}