/**
 * Copyright (c) 2011-2019 libnuls developers (see AUTHORS)
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
#ifndef LIBNULS_SYSTEM_MESSAGE_MESSAGES_HPP
#define LIBNULS_SYSTEM_MESSAGE_MESSAGES_HPP

#include <algorithm>
#include <cstdint>
#include <cstddef>
#include <nuls/system/math/limits.hpp>
#include <nuls/system/message/address.hpp>
#include <nuls/system/message/alert.hpp>
#include <nuls/system/message/alert_payload.hpp>
#include <nuls/system/message/block.hpp>
#include <nuls/system/message/block_transactions.hpp>
#include <nuls/system/message/compact_block.hpp>
#include <nuls/system/message/compact_filter.hpp>
#include <nuls/system/message/compact_filter_checkpoint.hpp>
#include <nuls/system/message/compact_filter_headers.hpp>
#include <nuls/system/message/fee_filter.hpp>
#include <nuls/system/message/filter_add.hpp>
#include <nuls/system/message/filter_clear.hpp>
#include <nuls/system/message/filter_load.hpp>
#include <nuls/system/message/get_address.hpp>
#include <nuls/system/message/get_block_transactions.hpp>
#include <nuls/system/message/get_blocks.hpp>
#include <nuls/system/message/get_compact_filter_checkpoint.hpp>
#include <nuls/system/message/get_compact_filter_headers.hpp>
#include <nuls/system/message/get_compact_filters.hpp>
#include <nuls/system/message/get_data.hpp>
#include <nuls/system/message/get_headers.hpp>
#include <nuls/system/message/headers.hpp>
#include <nuls/system/message/heading.hpp>
#include <nuls/system/message/inventory.hpp>
#include <nuls/system/message/inventory_vector.hpp>
#include <nuls/system/message/memory_pool.hpp>
#include <nuls/system/message/merkle_block.hpp>
#include <nuls/system/message/network_address.hpp>
#include <nuls/system/message/not_found.hpp>
#include <nuls/system/message/ping.hpp>
#include <nuls/system/message/pong.hpp>
#include <nuls/system/message/reject.hpp>
#include <nuls/system/message/send_compact.hpp>
#include <nuls/system/message/send_headers.hpp>
#include <nuls/system/message/transaction.hpp>
#include <nuls/system/message/verack.hpp>
#include <nuls/system/message/version.hpp>
#include <nuls/system/utility/container_sink.hpp>
#include <nuls/system/utility/data.hpp>

// Minimum current libnuls protocol version:     31402
// Minimum current satoshi client protocol version: 31800

// libnuls-network
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// version      v2      70001           added relay field
// verack       v1
// getaddr      v1
// addr         v1
// ping         v1
// ping         v2      60001   BIP031  added nonce field
// pong         v1      60001   BIP031
// reject       v3      70002   BIP061
// ----------------------------------------------------------------------------
// alert        --                      no intent to support
// checkorder   --                      obsolete
// reply        --                      obsolete
// submitorder  --                      obsolete
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// libnuls-node
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// getblocks    v1
// inv          v1
// getdata      v1
// getdata      v3      70001   BIP037  allows filtered_block flag
// block        v1
// tx           v1
// notfound     v2      70001
// getheaders   v3      31800
// headers      v3      31800
// mempool      --      60002   BIP035
// mempool      v3      70002           allow multiple inv messages in reply
// sendheaders  v3      70012   BIP130
// feefilter    v3      70013   BIP133
// blocktxn     v3      70014   BIP152
// cmpctblock   v3      70014   BIP152
// getblocktxn  v3      70014   BIP152
// sendcmpct    v3      70014   BIP152
// merkleblock  v3      70001   BIP037  no bloom filters so unfiltered only
// ----------------------------------------------------------------------------
// filterload   --      70001   BIP037  no intent to support, see BIP111
// filteradd    --      70001   BIP037  no intent to support, see BIP111
// filterclear  --      70001   BIP037  no intent to support, see BIP111
// ----------------------------------------------------------------------------
// cfilter      --      70015   BIP157
// getcfilters  --      70015   BIP157
// cfcheckpt    --      70015   BIP157
// getcfcheckpt --      70015   BIP157
// cfheaders    --      70015   BIP157
// getcfheaders --      70015   BIP157
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

namespace libnuls {
namespace system {

#define DECLARE_MESSAGE_POINTER_TYPES(type) \
typedef message::type::ptr type##_ptr; \
typedef message::type::const_ptr type##_const_ptr

#define DECLARE_MESSAGE_POINTER_LIST_POINTER_TYPES(type) \
typedef message::type::ptr_list type##_ptr_list; \
typedef message::type::const_ptr_list type##_const_ptr_list; \
typedef message::type::const_ptr_list_ptr type##_const_ptr_list_ptr; \
typedef message::type::const_ptr_list_const_ptr type##_const_ptr_list_const_ptr

// HACK: declare these in bc namespace to reduce length.
DECLARE_MESSAGE_POINTER_TYPES(address);
DECLARE_MESSAGE_POINTER_TYPES(block);
DECLARE_MESSAGE_POINTER_TYPES(compact_block);
DECLARE_MESSAGE_POINTER_TYPES(compact_filter);
DECLARE_MESSAGE_POINTER_TYPES(compact_filter_checkpoint);
DECLARE_MESSAGE_POINTER_TYPES(compact_filter_headers);
DECLARE_MESSAGE_POINTER_TYPES(get_address);
DECLARE_MESSAGE_POINTER_TYPES(fee_filter);
DECLARE_MESSAGE_POINTER_TYPES(get_blocks);
DECLARE_MESSAGE_POINTER_TYPES(get_compact_filter_checkpoint);
DECLARE_MESSAGE_POINTER_TYPES(get_compact_filter_headers);
DECLARE_MESSAGE_POINTER_TYPES(get_compact_filters);
DECLARE_MESSAGE_POINTER_TYPES(get_data);
DECLARE_MESSAGE_POINTER_TYPES(get_headers);
DECLARE_MESSAGE_POINTER_TYPES(header);
DECLARE_MESSAGE_POINTER_TYPES(headers);
DECLARE_MESSAGE_POINTER_TYPES(inventory);
DECLARE_MESSAGE_POINTER_TYPES(memory_pool);
DECLARE_MESSAGE_POINTER_TYPES(merkle_block);
DECLARE_MESSAGE_POINTER_TYPES(not_found);
DECLARE_MESSAGE_POINTER_TYPES(ping);
DECLARE_MESSAGE_POINTER_TYPES(pong);
DECLARE_MESSAGE_POINTER_TYPES(reject);
DECLARE_MESSAGE_POINTER_TYPES(send_compact);
DECLARE_MESSAGE_POINTER_TYPES(send_headers);
DECLARE_MESSAGE_POINTER_TYPES(transaction);
DECLARE_MESSAGE_POINTER_TYPES(verack);
DECLARE_MESSAGE_POINTER_TYPES(version);
DECLARE_MESSAGE_POINTER_LIST_POINTER_TYPES(block);
DECLARE_MESSAGE_POINTER_LIST_POINTER_TYPES(header);
DECLARE_MESSAGE_POINTER_LIST_POINTER_TYPES(transaction);

#undef DECLARE_MESSAGE_POINTER_TYPES
#undef DECLARE_MESSAGE_POINTER_LIST_POINTER_TYPES

namespace message {

/// Serialize a message object to the Bitcoin wire protocol encoding.
template <typename Message>
data_chunk serialize(uint32_t version, const Message& packet,
    uint32_t magic)
{
    const auto heading_size = heading::satoshi_fixed_size();
    const auto payload_size = packet.serialized_size(version);
    const auto message_size = heading_size + payload_size;

    // Unfortunately data_sink doesn't support seek, so this is a little ugly.
    // The header requires payload size and checksum but prepends the payload.
    // Use a stream to prevent unnecessary copying of the payload.
    data_chunk data;

    // Reserve memory for the full message.
    data.reserve(message_size);

    // Size the vector for the heading so that payload insertion will follow.
    data.resize(heading_size);

    // Insert the payload after the heading and into the reservation.
    data_sink ostream(data);
    packet.to_data(version, ostream);
    ostream.flush();
    BITCOIN_ASSERT(data.size() == message_size);

    // Create the payload checksum without copying the buffer.
    const data_slice slice(data.data() + heading_size, data.data() + message_size);
    const auto check = bitcoin_checksum(slice);
    const auto payload_size32 = safe_unsigned<uint32_t>(payload_size);

    // Create and serialize the heading to a temporary variable (12 bytes).
    heading head(magic, Message::command, payload_size32, check);
    auto heading = head.to_data();

    // Move the heading into the allocated beginning of the message buffer.
    std::move(heading.begin(), heading.end(), data.begin());
    return data;
}

BC_API size_t variable_uint_size(uint64_t value);

} // namespace message
} // namespace system
} // namespace libnuls

#endif
