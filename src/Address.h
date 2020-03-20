// Copyright © 2020 NULS.


#pragma once

#include "Data.h"

#include <stdint.h>
#include <string>

namespace NULS {

class Address {
public:
    static constexpr auto binanceHRP = "bnb";
    static constexpr auto binanceTestHRP = "tbnb";

public:
    /// Human-readable part.
    ///
    /// \see https://github.com/satoshilabs/slips/blob/master/slip-0173.md
    std::string hrp;

    /// Public key hash.
    Data keyHash;

    /// Determines whether a string makes a valid Tendermint address.
    static bool isValid(const std::string& string);

    /// Initializes an address with a key hash.
    Address(const std::string& hrp, const Data& keyHash) : hrp(hrp), keyHash(keyHash) {}

    /// Initializes an address with a key hash.
    Address(const std::string& hrp, Data&& keyHash) : hrp(hrp), keyHash(keyHash) {}

    /// Decodes an address.
    ///
    /// \returns a pair with the address and a success flag.
    static std::pair<Address, bool> decode(const std::string& addr);

    /// Encodes the address.
    ///
    /// \returns encoded address string, or empty string on failure.
    std::string encode() const;

    bool operator==(const Address& rhs) const {
        return hrp == rhs.hrp && keyHash == rhs.keyHash;
    }

private:
    Address() = default;
};

} // namespace
