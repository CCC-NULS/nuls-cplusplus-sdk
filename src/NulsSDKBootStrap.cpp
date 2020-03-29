// Copyright © 2020 NULS.


#include "NulsSDKBootStrap.h"

using namespace NULS;

const std::string NulsSDKBootStrap::LANGUAGE = "en";
const std::string NulsSDKBootStrap::LANGUAGE_PATH = "languages";

void NulsSDKBootStrap::init(int chainId, std::string httpUrl) {
        initChainId(chainId);
        if (!endwithSlash(httpUrl)) {
            httpUrl += "/";
        }
        SDKContext::wallet_url = httpUrl;
}
void NulsSDKBootStrap::initMain(std::string httpUrl) {
        initChainId(1);
        if (!endwithSlash(httpUrl)) {
            httpUrl += "/";
        }
        SDKContext::wallet_url = httpUrl;
}

void NulsSDKBootStrap::initTest(std::string httpUrl) {
        initChainId(2);
        if (!endwithSlash(httpUrl)) {
            httpUrl += "/";
        }
        SDKContext::wallet_url = httpUrl;
}

void NulsSDKBootStrap::initChainId(int chainId) {
    if (chainId < 1 || chainId > 65535) {
        throw std::invalid_argument("[defaultChainId] is invalid");
    }
    SDKContext::main_chain_id = chainId;
    SDKContext::nuls_chain_id = chainId;
    //I18nUtils.loadLanguage(NulsSDKBootStrap.class, LANGUAGE_PATH, LANGUAGE);
}
bool NulsSDKBootStrap::endwithSlash(std::string url) {
    if (url.length() > 0) {
        std::size_t found = url.find_first_of("/");
        return found == url.length()-1;
    }
    return false;
}
