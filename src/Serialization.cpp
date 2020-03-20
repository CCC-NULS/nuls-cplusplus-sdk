// Copyright © 2020 NULS.


#include "Serialization.h"


#include "Address.h"
#include "Signer.h"

using namespace NULS;

static inline std::string addressString(const std::string& bytes) {
    auto data = std::vector<uint8_t>(bytes.begin(), bytes.end());
    auto address = Address(Address::binanceHRP, data);
    return address.encode();
}

std::string NULS::signaturePreimage(const Signer& signer) {
    std::string null;
    return null;
}
