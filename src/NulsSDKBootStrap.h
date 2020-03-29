// Copyright © 2020 NULS.

#pragma once

#include "SDKContext.h"

namespace NULS {
class NulsSDKBootStrap {

public:
    /**
     * NULS-SDK工具初始化
     * 设置对接的链的ID和钱包NULS-SDK-Provider模块的url访问地址
     *
     * @param chainId 链ID
     * @param httpUrl 钱包url访问地址(ip + port)
     */
    static void init(int chainId, std::string httpUrl);

    /**
     * NULS-SDK工具连接NULS主网钱包初始化
     * 设置主网钱包NULS-SDK-Provider模块的url访问地址
     *
     * @param httpUrl 钱包url访问地址(ip + port)
     */
    static void initMain(std::string httpUrl);

    /**
     * NULS-SDK工具连接NULS测试网钱包初始化
     * 设置测试网钱包NULS-SDK-Provider模块的url访问地址
     *
     * @param httpUrl 钱包url访问地址(ip + port)
     */
    static void initTest(std::string httpUrl);

private:
    static const std::string LANGUAGE;
    static const std::string LANGUAGE_PATH;

    /**
     * nuls sdk init
     *
     * @param chainId 运行链的id
     */
    static void initChainId(int chainId);

    static bool endwithSlash(std::string url);
};

}
