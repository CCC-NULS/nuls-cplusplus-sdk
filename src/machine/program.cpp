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
#include <nuls/system/machine/program.hpp>

#include <cstddef>
#include <cstdint>
#include <utility>
#include <nuls/system/chain/script.hpp>
#include <nuls/system/chain/transaction.hpp>
#include <nuls/system/machine/interpreter.hpp>
#include <nuls/system/machine/script_version.hpp>
#include <nuls/system/utility/data.hpp>

namespace libnuls {
namespace system {
namespace machine {

using namespace nuls::system::chain;

static const chain::transaction default_tx_;
static const chain::script default_script_;

// Constructors.
//-----------------------------------------------------------------------------

program::program()
  : script_(default_script_),
    transaction_(default_tx_),
    input_index_(0),
    forks_(0),
    value_(0),
    version_(script_version::unversioned),
    negative_count_(0),
    operation_count_(0),
    jump_(script_.begin())
{
}

program::program(const script& script)
  : script_(script),
    transaction_(default_tx_),
    input_index_(0),
    forks_(0),
    value_(0),
    version_(script_version::unversioned),
    negative_count_(0),
    operation_count_(0),
    jump_(script_.begin())
{
}

program::program(const script& script, const chain::transaction& transaction,
    uint32_t input_index, uint32_t forks)
  : script_(script),
    transaction_(transaction),
    input_index_(input_index),
    forks_(forks),
    value_(max_uint64),
    version_(script_version::unversioned),
    negative_count_(0),
    operation_count_(0),
    jump_(script_.begin())
{
}

// Condition, alternate, jump and operation_count are not copied.
program::program(const script& script, const chain::transaction& transaction,
    uint32_t input_index, uint32_t forks, data_stack&& stack, uint64_t value,
    script_version version)
  : script_(script),
    transaction_(transaction),
    input_index_(input_index),
    forks_(forks),
    value_(value),
    version_(version),
    negative_count_(0),
    operation_count_(0),
    jump_(script_.begin()),
    primary_(std::move(stack))
{
}


// Condition, alternate, jump and operation_count are not copied.
program::program(const script& script, const program& other)
  : script_(script),
    transaction_(other.transaction_),
    input_index_(other.input_index_),
    forks_(other.forks_),
    value_(other.value_),
    version_(script_version::unversioned),
    negative_count_(0),
    operation_count_(0),
    jump_(script_.begin()),
    primary_(other.primary_)
{
}

// Condition, alternate, jump and operation_count are not moved.
program::program(const script& script, program&& other, bool)
  : script_(script),
    transaction_(other.transaction_),
    input_index_(other.input_index_),
    forks_(other.forks_),
    value_(other.value_),
    version_(script_version::unversioned),
    negative_count_(0),
    operation_count_(0),
    jump_(script_.begin()),
    primary_(std::move(other.primary_))
{
}

// Instructions.
//-----------------------------------------------------------------------------

code program::evaluate()
{
    return interpreter::run(*this);
}

code program::evaluate(const operation& op)
{
    return interpreter::run(op, *this);
}

} // namespace machine
} // namespace system
} // namespace libnuls
