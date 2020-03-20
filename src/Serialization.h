// Copyright © 2020 NULS.
//


#pragma once

#include <string>

namespace NULS {

class Signer;

std::string signaturePreimage(const Signer& signer);


} // namespace
