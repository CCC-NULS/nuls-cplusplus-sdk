// Copyright © 2020 NULS.


#include "HexCoding.h"

#include <tuple>

using namespace NULS;

static inline std::tuple<uint8_t, bool> value(uint8_t c) {
    if (c >= '0' && c <= '9')
        return std::make_tuple(c - '0', true);
    if (c >= 'a' && c <= 'z')
        return std::make_tuple(c - 'a' + 10, true);
    if (c >= 'A' && c <= 'Z')
        return std::make_tuple(c - 'A' + 10, true);

    // Invalid digit
    return std::make_tuple(0, false);
}

Data NULS::parse_hex(const std::string& string) {
    auto it = string.begin();

    // Skip `0x`
    if (string.size() >= 2 && string[0] == '0' && string[1] == 'x') {
        it += 2;
    }

    Data result;
    result.reserve((string.size() + 1) / 2);

    while (it != string.end()) {
        auto high = value(*it);
        if (!std::get<1>(high)) {
            return {};
        }
        it += 1;

        if (it == string.end()) {
            result.push_back(std::get<0>(high));
            break;
        }

        auto low = value(*it);
        if (!std::get<1>(low)) {
            return {};
        }
        it += 1;

        result.push_back((std::get<0>(high) << 4) | std::get<0>(low));
    }

    return result;
}
