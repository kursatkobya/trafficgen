// $Id: pktdescr.h 26788 2013-11-15 10:22:11Z bk $
/*
 * Copyright 2013 Napatech A/S. All rights reserved.
 * CONFIDENTIAL INFORMATION.
 * 
 * 1. Copying, modification, and distribution of this file, or executable
 * versions of the file, is governed by the terms of the agreement (such
 * as an SCLA or NDA) under which the file was made available. If no such
 * agreement is currently in force between You and Napatech A/S, you may
 * not copy, modify, or distribute this file.
 * 
 * 2. This source code is confidential information of Napatech A/S, and
 * as such, may not be distributed, except to or within Napatech A/S
 * customers under a current, executed NDA or equivalent confidentiality
 * agreement governing the distribution of confidential information.
 * 
 * 3. Redistributions of source code must retain this copyright notice,
 * list of conditions and the following disclaimer.
 * 
 * THIS SOFTWARE IS PROVIDED BY NAPATECH A/S ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NAPATECH A/S OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * This source file contains the packet macros available.\n
 * See the @ref PacketMacros for details.
 */

#ifndef __PKT_DESCR_H__
#define __PKT_DESCR_H__

#ifndef DOXYGEN_INTERNAL_ONLY

/* In debug mode add assert to all general RX macros */
#ifdef NDEBUG
#define _NT_NET_ASSERT(x) (x)
#else
#define _NT_NET_ASSERT(x) (assert(!"macro argument: unsupported descriptor type"),x)
#endif

#include "pktdescr_std0.h"
#include "pktdescr_ext7.h"
#include "pktdescr_ext8.h"
#include "pktdescr_ext9.h"

// Ensure that the following is packed.
#pragma pack(push, 1)

typedef union {
  NtStd0Descr_t std0; //!< Standard descriptor v0
  NtExt7Descr_t ext7; //!< Only valid for extended descriptor format 7
  NtExt8Descr_t ext8; //!< Only valid for extended descriptor format 8
  NtExt9Descr_t ext9; //!< Only valid for extended descriptor format 9
} NtPktDescr_t;

// Disable 1-byte packing
#pragma pack(pop)

#endif // DOXYGEN_INTERNAL_ONLY

/** @addtogroup DataMacros
 * @{
 */

/** @defgroup PacketMacros Packet macros
 * @{
 * The following is only possible on packet-based streams.
 *
 * Unless specified otherwise, the NT_NET_GET_PKT_XYZ macros will return
 * integer type values.
 *
 * In debug mode all packet macros contain an assert which asserts
 * that the macros is supported for a given macro. Define the macro
 * NDEBUG to remove the assert or use the build option -DNDEBUG. When
 * the assert is removed the unsupported macros returns -1.
 */

/** @defgroup BasicDescriptorMacros Basic descriptor macros
 * @{
 * The following macros are always available.
 */

/** @def NT_NET_GET_PKT_DESCRIPTOR_TYPE
 *  @brief Returns @ref NtPacketDescriptorType_e
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_DESCRIPTOR_TYPE(_hNetBuf_)       _NT_NET_GET_PKT_DESCRIPTOR_TYPE(_hNetBuf_)

/** @def NT_NET_GET_PKT_DESCRIPTOR_FORMAT
 *  @brief Returns the descriptor format, e.g. 7 for EXT7, 8 for EXT8 and 9 for EXT9
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)     _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)

/** @def NT_NET_GET_PKT_DESCR_PTR
 *  @brief A pointer to the packet descriptor
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_DESCR_PTR(_hNetBuf_)             _NT_NET_GET_PKT_DESCR_PTR(_hNetBuf_)
#if !defined(_NT_NTAPI_NO_COMPAT)
#define NT_NET_GET_PKT_DESCR(_hNetBuf_)                 _NT_NET_GET_PKT_DESCR_PTR(_hNetBuf_)
#endif

/** @def NT_NET_GET_PKT_DESCR_LENGTH
 *  @brief The length of the packet descriptor
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_DESCR_LENGTH(_hNetBuf_)          _NT_NET_GET_PKT_DESCR_LENGTH(_hNetBuf_)

/** @def NT_NET_GET_PKT_TIMESTAMP
 *  @brief The time when the packet was captured as an 64bit unsigned value
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_TIMESTAMP(_hNetBuf_)             _NT_NET_GET_PKT_TIMESTAMP(_hNetBuf_)

/** @def NT_NET_GET_PKT_TIMESTAMP_TYPE
 *  @brief The packet time stamp type. See @ref NtTimestampType_e
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_TIMESTAMP_TYPE(_hNetBuf_)        _NT_NET_GET_PKT_TIMESTAMP_TYPE(_hNetBuf_)

/** @def NT_NET_GET_PKT_CAP_LENGTH
 *  @brief The packet capture length
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_CAP_LENGTH(_hNetBuf_)            _NT_NET_GET_PKT_CAP_LENGTH(_hNetBuf_)

/** @def NT_NET_GET_PKT_WIRE_LENGTH
 *  @brief The packet wire length
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_WIRE_LENGTH(_hNetBuf_)           _NT_NET_GET_PKT_WIRE_LENGTH(_hNetBuf_)

/** @def NT_NET_GET_PKT_L2_PTR
 *  @brief A pointer to the L2 packet data. If an ISL header is present it will point to the ISL header.
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_L2_PTR(_hNetBuf_)                _NT_NET_GET_PKT_L2_PTR(_hNetBuf_)

/** @def NT_NET_UPDATE_PKT_L2_PTR
 *  @brief When creating packets within a segment it is required to update the L2 pointer using this macro after applying the descriptor info
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_UPDATE_PKT_L2_PTR(_hNetBuf_)             _NT_NET_UPDATE_PKT_L2_PTR(_hNetBuf_)

/** @def NT_DESCR_NT_LENGTH
 *  @brief Length of the NT standard descriptor
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_DESCR_NT_LENGTH    (sizeof(NtStd0Descr_t))

/** @def NT_DESCR_EXT7_LENGTH
 *  @brief Length of the NT Extended 7 descriptor
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_DESCR_EXT7_LENGTH  (sizeof(NtExt7Descr_t))

/** @def NT_DESCR_EXT8_LENGTH
 *  @brief Length of the NT Extended 8 descriptor
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_DESCR_EXT8_LENGTH  (sizeof(NtExt8Descr_t))

/** @def NT_DESCR_EXT9_LENGTH
 *  @brief Length of the NT Extended 9 descriptor
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_DESCR_EXT9_LENGTH  (sizeof(NtExt9Descr_t))

/** @} */

/** @defgroup NtDescriptorMacros NT descriptor macros
 * @{

 * The following is only available if "PacketDescriptor = NT or Ext7 or Ext8 or Ext9" has been selected in the ntservice.ini file
 * and if @ref NT_NET_GET_PKT_DESCRIPTOR_TYPE returns @ref NT_PACKET_DESCRIPTOR_TYPE_NT || @ref NT_PACKET_DESCRIPTOR_TYPE_NT_EXTENDED.
 * The following macros constitute the collection extracting data from the "NT" descriptor.
 */

/** @def NT_NET_GET_PKT_CRC_ERROR
 *  @brief Returns 1 if the packet has a L2 CRC error - If no L2 CRC error this is 0.
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_CRC_ERROR(_hNetBuf_)             _NT_NET_GET_PKT_CRC_ERROR(_hNetBuf_)

/** @def NT_NET_GET_PKT_TCP_CSUM_OK
 *  @brief Returns 1 if the packet has a valid TCP checksum - if not a TCP packet this is 0
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_TCP_CSUM_OK(_hNetBuf_)           _NT_NET_GET_PKT_TCP_CSUM_OK(_hNetBuf_)

/** @def NT_NET_GET_PKT_UDP_CSUM_OK
 *  @brief Returns 1 if the packet has a valid UDP checksum - if not a UDP packet this is 0
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_UDP_CSUM_OK(_hNetBuf_)           _NT_NET_GET_PKT_UDP_CSUM_OK(_hNetBuf_)

/** @def NT_NET_GET_PKT_IP_CSUM_OK
 *  @brief Returns 1 if the packet has a valid IP checksum - if not an IP packet this is 0
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_IP_CSUM_OK(_hNetBuf_)            _NT_NET_GET_PKT_IP_CSUM_OK(_hNetBuf_)

/** @def NT_NET_GET_PKT_CV_ERROR
 *  @brief Returns 1 if the packet has coding violations - If no coding violations this is 0.
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_CV_ERROR(_hNetBuf_)              _NT_NET_GET_PKT_CV_ERROR(_hNetBuf_)

/** @def NT_NET_GET_PKT_SLICED
 *  @brief Returns 1 if the packet has been sliced - If no slicing has occured this is 0
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_SLICED(_hNetBuf_)                _NT_NET_GET_PKT_SLICED(_hNetBuf_)

/** @def NT_NET_GET_PKT_HARD_SLICED
 *  @brief Returns 1 if the packet has been hard sliced - If no hard slicing has occured this is 0
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_HARD_SLICED(_hNetBuf_)           _NT_NET_GET_PKT_HARD_SLICED(_hNetBuf_)

/** @def NT_NET_GET_PKT_RXPORT
 *  @brief The port that received this packet
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_RXPORT(_hNetBuf_)                _NT_NET_GET_PKT_RXPORT(_hNetBuf_)

/** @def NT_NET_GET_PKT_IS_TCP
 *  @brief Returns 1 if the packet has a TCP header - returns 0 if the packet does not have a TCP header
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_IS_TCP(_hNetBuf_)                _NT_NET_GET_PKT_IS_TCP(_hNetBuf_)

/** @def NT_NET_GET_PKT_IS_UDP
 *  @brief Returns 1 if the packet has an UDP header - returns 0 if the packet does not have an UDP header
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_IS_UDP(_hNetBuf_)                _NT_NET_GET_PKT_IS_UDP(_hNetBuf_)

/** @def NT_NET_GET_PKT_IS_IP
 *  @brief Returns 1 if the packet has an IP header - returns 0 if the packet does not have an IP header
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_IS_IP(_hNetBuf_)                 _NT_NET_GET_PKT_IS_IP(_hNetBuf_)

/** @def NT_NET_GET_PKT_TXPORT
 *  @brief The port this packet is to be transmitted on
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_TXPORT(_hNetBuf_)                _NT_NET_GET_PKT_TXPORT(_hNetBuf_)

/** @def NT_NET_GET_PKT_RECALC_L2_CRC
 *  @brief Returns 1 if the packet has L2 CRC recalc/override set - Returns 0 if L2 CRC recalc/override is not set
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_RECALC_L2_CRC(_hNetBuf_)         _NT_NET_GET_PKT_RECALC_L2_CRC(_hNetBuf_)
#if !defined(_NT_NTAPI_NO_COMPAT)
#define NT_NET_GET_PKT_CALC_L2_CRC(_hNetBuf_)           _NT_NET_GET_PKT_RECALC_L2_CRC(_hNetBuf_)
#endif

/** @def NT_NET_GET_PKT_TXNOW
 *  @brief Returns 1 if the packet has TxNow set - Returns 0 if TxNow is not set
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_TXNOW(_hNetBuf_)                 _NT_NET_GET_PKT_TXNOW(_hNetBuf_)

/** @def NT_NET_GET_PKT_TXIGNORE
 *  @brief Returns 1 if the packet has TxIgnore set - Returns 0 if TxIgnore is not set
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_TXIGNORE(_hNetBuf_)              _NT_NET_GET_PKT_TXIGNORE(_hNetBuf_)

/** @} */

#if !defined(_NTAPI_EXTDESCR_7_) && !defined(_NTAPI_EXTDESCR_8_) && !defined(_NTAPI_EXTDESCR_9_)

/** @defgroup ExtendedNtDescriptorMacros Extended NT descriptor macros
 * @{
 * The following is only available if "PacketDescriptor = Ext7, Ext8 or Ext9" has been set in the ntservice.ini
 * file and if @ref NT_NET_GET_PKT_DESCRIPTOR_TYPE returns @ref NT_PACKET_DESCRIPTOR_TYPE_NT_EXTENDED
 */

/** @def NT_NET_GET_PKT_HASH
 *  @brief The packet hash value
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_HASH(_hNetBuf_)                                  \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_HASH_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_HASH_TYPE
 *  @brief The packet hash type
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_HASH_TYPE(_hNetBuf_)                             \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_HASH_TYPE_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_HASH_VALID
 *  @brief Returns 1 if the hash value/type is valid - Returns 0 if the hash value/type is invalid
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_HASH_VALID(_hNetBuf_)                            \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_HASH_VALID_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_JUMBO
 *  @brief Returns 1 if the packet has a jumbo frame - Returns 0 if the packet does not have a jumbo frame
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_JUMBO(_hNetBuf_)                                 \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_JUMBO_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_BROADCAST
 *  @brief Returns 1 if the destination MAC is a broadcast address - Returns 0 if the destination MAC is not a broadcast address
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_BROADCAST(_hNetBuf_)                             \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_BROADCAST_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_L4_PORT_TYPE
 *  @brief The L4 port type - see @ref NtL4PortType_e
 *  When using extended descriptor 9 it is advised to use @ref NT_NET_GET_PKT_TUNNEL_TYPE instead.
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_L4_PORT_TYPE(_hNetBuf_)                          \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8) ? _NT_NET_GET_PKT_L4_PORT_TYPE_EXT7(_hNetBuf_) : \
   ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ? _NT_NET_GET_PKT_L4_PORT_TYPE_EXT9(_hNetBuf_) : _NT_NET_ASSERT(~0)))

/** @def NT_NET_GET_PKT_L4_FRAME_TYPE
 *  @brief The L4 frame type - see @ref NtL4FrameType_e
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_L4_FRAME_TYPE(_hNetBuf_)                         \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_L4_FRAME_TYPE_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_L3_FRAME_TYPE
 *  @brief The L3 frame type - see @ref NtL3FrameType_e
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_L3_FRAME_TYPE(_hNetBuf_)                         \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_L3_FRAME_TYPE_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_L2_FRAME_TYPE
 *  @brief The L2 frame type - see @ref NtL2FrameType_e
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_L2_FRAME_TYPE(_hNetBuf_)                         \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_L2_FRAME_TYPE_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_L4_LENGTH
 *  @brief The L4 header length in units of 32 bits (valid for L4 = TCP only)
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_L4_LENGTH(_hNetBuf_)                             \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_L4_LENGTH_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_L3_LENGTH
 *  @brief The L3 header length in units of 32 bits (valid for L3 = IPv4/IPv6 only)
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_L3_LENGTH(_hNetBuf_)                             \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_L3_LENGTH_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_MPLS_COUNT
 *  @brief The number of MPLS shim labels present
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_MPLS_COUNT(_hNetBuf_)                            \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_MPLS_COUNT_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_VLAN_COUNT
 *  @brief The number of VLANs present
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_VLAN_COUNT(_hNetBuf_)                            \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_VLAN_COUNT_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_ISL
 *  @brief Returns 1 if ISL encapsulation is present - Returns 0 if ISL encapsulation is not present
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_ISL(_hNetBuf_)                                   \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_ISL_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_DECODE_ERROR
 *  @brief Returns 1 if the frame could not be decoded correctly - Returns 0 otherwise
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_DECODE_ERROR(_hNetBuf_)                          \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_DECODE_ERROR_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0))
#if !defined(_NT_NTAPI_NO_COMPAT)
#define NT_NET_GET_PKT_PROT_SMALL(_hNetBuf_) NT_NET_GET_PKT_DECODE_ERROR(_hNetBuf_)
#endif


/** @def NT_NET_GET_PKT_FRAME_LARGE
 *  @brief Large frame - Returns 1 when PktSz > MaxFrameSize. MaxFrameSize is set in ntservice.ini. Returns 0 when PktSz <= MaxFrameSize
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_FRAME_LARGE(_hNetBuf_)                           \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_FRAME_LARGE_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_FRAME_SMALL
 *  @brief Small frame - Returns 1 when PktSz < 64 (+ISL and/or VLAN) - Returns 0 when PktSz >= 64
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_FRAME_SMALL(_hNetBuf_)                           \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_FRAME_SMALL_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_IPV6_FR_HEADER
 *  @brief Returns 1 if IPv6 fragment header is present - Returns 0 if no IPv6 fragment header is present
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_IPV6_FR_HEADER(_hNetBuf_)                        \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_IPV6_FR_HEADER_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_IPV6_RT_HEADER
 *  @brief Returns 1 if IPv6 routing header is present - Returns 0 if no IPv6 routing header is present
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_IPV6_RT_HEADER(_hNetBuf_)                        \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_IPV6_RT_HEADER_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_L4_PROTOCOL_NUM
 *  @brief L4 protocol number (TCP, UDP, SCTP etc.) - if not an IP packet this is 0
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_L4_PROTOCOL_NUM(_hNetBuf_)                       \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_L4_PROTOCOL_NUM_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_L3_FRAGMENTED
 *  @brief L3 fragmented frame (only valid for IPv4 if more fragments bit = 1 or fragment offset not equal to 0)
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_L3_FRAGMENTED(_hNetBuf_)                         \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_L3_FRAGMENTED_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_L3_FIRST_FRAG
 *  @brief L3 First fragment (offset = 0) Note: Only valid for IPv4 - always set on IPv6 so use IPV6_FR_HEADER instead
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_L3_FIRST_FRAG(_hNetBuf_)                         \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_L3_FIRST_FRAG_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_COLOR
 *  @brief The color of the packet
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_COLOR(_hNetBuf_)                                 \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_COLOR_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_L5_OFFSET
 *  @brief Offset from L2 pointer to where L5 starts
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_L5_OFFSET(_hNetBuf_)                             \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_L5_OFFSET_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_L4_OFFSET
 *  @brief Offset from L2 pointer to where L4 starts
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_L4_OFFSET(_hNetBuf_)                             \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_L4_OFFSET_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_L3_OFFSET
 *  @brief Offset from L2 pointer to where L3 starts
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_L3_OFFSET(_hNetBuf_)                             \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_L3_OFFSET_EXT7(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_DEDUPLICATION_CRC
 *  @brief The packet deduplication CRC value. Only available on extended descriptor 9.
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_DEDUPLICATION_CRC(_hNetBuf_)                     \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_DEDUPLICATION_CRC_EXT9(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @} */

/** @defgroup ExtendedNtDescriptorIPFMacros Extended NT descriptor IPF macros
 * @{
 * The following are used to help collect IP fragmented data. With theses
 * macros it is possible to de-fragment IP fragmented data in a
 * multi-processing application using 5-tuple hashing. It is only available if
 * "PacketDescriptor" in the ntservice.ini file has been set to "Ext8" or
 * "Ext9" and if @ref NT_NET_GET_PKT_DESCRIPTOR_TYPE returns @ref
 * NT_PACKET_DESCRIPTOR_TYPE_NT_EXTENDED @note: These macros do not return
 * valid values if the IPF engine is not turned on see @ref NtplIPFMode
 */

/** @def NT_NET_GET_PKT_IPF_UNMATCHED_STREAMID
 *  @brief Stream ID where unmatched fragments are stored
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_IPF_UNMATCHED_STREAMID(_hNetBuf_)                \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_IPF_UNMATCHED_STREAMID_EXT8(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_IPF_UNMATCHED_FLAG
 *  @brief Unmatched fragment flag
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_IPF_UNMATCHED_FLAG(_hNetBuf_)                    \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_IPF_UNMATCHED_FLAG_EXT8(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_IPF_LAST_FRAGMENT
 *  @brief Last fragment flag (More fragment bit = 0 && offset != 0)
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_IPF_LAST_FRAGMENT(_hNetBuf_)                     \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||                  \
    _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_IPF_LAST_FRAGMENT_EXT8(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @} */

/** @defgroup ExtendedNtDescriptorTunnelMacros Extended NT descriptor Tunneling macros
 * @{
 *
 * The following are used to help accessing GTPv1 and IP-in-IP tunneled
 * data. With theses macros it is possible to determine the tunnel type,
 * retrieve the frame types and get direct offsets to the layers 3, 4 and 5
 * inside the tunnel. Only the first tunnel is decoded, hence a tunnel inside
 * a tunnel is not decoded. The following macros are only available if
 * "PacketDescriptor" in the ntservice.ini file has been set to "Ext9".
 */

/** @def NT_NET_GET_PKT_INNER_L3_OFFSET
 *  @brief Offset from L2 pointer to where inner tunnel L3 starts
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_INNER_L3_OFFSET(_hNetBuf_)                       \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_INNER_L3_OFFSET_EXT9(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_INNER_L4_OFFSET
 *  @brief  Offset from L2 pointer to where inner tunnel L4 starts
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_INNER_L4_OFFSET(_hNetBuf_)                       \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_INNER_L4_OFFSET_EXT9(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_INNER_L5_OFFSET
 *  @brief  Offset from L2 pointer to where inner tunnel L5 starts
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_INNER_L5_OFFSET(_hNetBuf_)                       \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_INNER_L5_OFFSET_EXT9(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_INNER_L3_FRAME_TYPE
 *  @brief The inner tunnel L3 frame type - see @ref NtL3FrameType_e
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_INNER_L3_FRAME_TYPE(_hNetBuf_)                   \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_INNER_L3_FRAME_TYPE_EXT9(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_INNER_L4_FRAME_TYPE
 *  @brief The inner tunnel L4 frame type - see @ref NtL4FrameType_e
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_INNER_L4_FRAME_TYPE(_hNetBuf_)                   \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_INNER_L4_FRAME_TYPE_EXT9(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_INNER_L3_FRAGMENT_TYPE
 *  @brief The inner L3 fragment type - see @ref NtL3FragmentType_e
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_INNER_L3_FRAGMENT_TYPE(_hNetBuf_)                \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_INNER_L3_FRAGMENT_TYPE_EXT9(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_TUNNEL_TYPE
 *  @brief The tunnel type - see @ref NtTunnelType_e
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_TUNNEL_TYPE(_hNetBuf_)                           \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_TUNNEL_TYPE_EXT9(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_TUNNEL_HDR_LENGTH
 *  @brief The tunnel header length in units of 32 bits
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_TUNNEL_HDR_LENGTH(_hNetBuf_)                     \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_TUNNEL_HDR_LENGTH_EXT9(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @def NT_NET_GET_PKT_INNER_DECODE_ERROR
 *  @brief Inner tunnel decode error
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_GET_PKT_INNER_DECODE_ERROR(_hNetBuf_)                    \
  ((_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9) ?                  \
   _NT_NET_GET_PKT_INNER_DECODE_ERROR_EXT9(_hNetBuf_) : _NT_NET_ASSERT(~0))

/** @} */

#endif /* !defined(_NTAPI_EXTDESCR_7_) && !defined(_NTAPI_EXTDESCR_8_) && !defined(_NTAPI_EXTDESCR_9_) */

/** @defgroup TxMacros TX macros
 * @{
 * The following can only be used on TX or in-line based streams
 *
 */

/** @def NT_NET_SET_PKT_CLEAR_DESCR_NT
 *  @brief Clears the NT descriptor
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_CLEAR_DESCR_NT(_hNetBuf_)       do{ memset((_hNetBuf_)->hHdr, 0, sizeof(NtStd0Descr_t)); } while(0)

/** @def NT_NET_SET_PKT_DESCR_TYPE_NT
 *  @brief Sets the packet descriptor type to NT
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_DESCR_TYPE_NT(_hNetBuf_)        do{ _NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->descriptorType = 1; } while(0)

/** @def NT_NET_SET_PKT_CLEAR_DESCR_EXT7
 *  @brief Clears the EXT7 descriptor
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_CLEAR_DESCR_EXT7(_hNetBuf_)     do{ memset((_hNetBuf_)->hHdr, 0, sizeof(NtExt7Descr_t)); } while(0)

/** @def NT_NET_SET_PKT_DESCR_TYPE_EXT7
 *  @brief Sets the packet descriptor type to EXT7
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#ifndef DOXYGEN_INTERNAL_ONLY
#define NT_EXTENDED_DESCRIPTOR_07_LENGTH 2
#define NT_EXTENDED_DESCRIPTOR_07_TYPE   7
#endif // DOXYGEN_INTERNAL_ONLY
#define NT_NET_SET_PKT_DESCR_TYPE_EXT7(_hNetBuf_) \
  do{ _NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->descriptorType = 1;    \
    _NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->extensionFormat = NT_EXTENDED_DESCRIPTOR_07_TYPE; \
    _NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->extensionLength = NT_EXTENDED_DESCRIPTOR_07_LENGTH; } while(0)

/** @def NT_NET_SET_PKT_CLEAR_DESCR_EXT8
 *  @brief Clears the EXT8 descriptor
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_CLEAR_DESCR_EXT8(_hNetBuf_)     do{ memset((_hNetBuf_)->hHdr, 0, sizeof(NtExt8Descr_t)); } while(0)

/** @def NT_NET_SET_PKT_DESCR_TYPE_EXT8
 *  @brief Sets the packet descriptor type to EXT8
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#ifndef DOXYGEN_INTERNAL_ONLY
#define NT_EXTENDED_DESCRIPTOR_08_LENGTH 2
#define NT_EXTENDED_DESCRIPTOR_08_TYPE   8
#endif // DOXYGEN_INTERNAL_ONLY
#define NT_NET_SET_PKT_DESCR_TYPE_EXT8(_hNetBuf_) \
  do{ _NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->descriptorType = 1;    \
    _NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->extensionFormat = NT_EXTENDED_DESCRIPTOR_08_TYPE; \
    _NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->extensionLength = NT_EXTENDED_DESCRIPTOR_08_LENGTH; } while(0)

/** @def NT_NET_SET_PKT_CLEAR_DESCR_EXT9
 *  @brief Clears the EXT9 descriptor
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_CLEAR_DESCR_EXT9(_hNetBuf_)     do{ memset((_hNetBuf_)->hHdr, 0, sizeof(NtExt9Descr_t)); } while(0)

/** @def NT_NET_SET_PKT_DESCR_TYPE_EXT9
 *  @brief Sets the packet descriptor type to EXT9
 *  @param[in] _hNetBuf_ Packet container reference
 *  @hideinitializer
 */
#ifndef DOXYGEN_INTERNAL_ONLY
#define NT_EXTENDED_DESCRIPTOR_09_LENGTH 3
#define NT_EXTENDED_DESCRIPTOR_09_TYPE   9
#endif // DOXYGEN_INTERNAL_ONLY
#define NT_NET_SET_PKT_DESCR_TYPE_EXT9(_hNetBuf_) \
  do{ _NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->descriptorType = 1;    \
    _NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->extensionFormat = NT_EXTENDED_DESCRIPTOR_09_TYPE; \
    _NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->extensionLength = NT_EXTENDED_DESCRIPTOR_09_LENGTH; } while(0)

/** @def NT_NET_SET_PKT_CAP_LENGTH
 *  @brief Calculates and sets the packet capture length. Input is wire length. Capture length is calculated from the value.
 *  @param[in] _hNetBuf_ Packet container reference
 *  @param[in] _Length_ The length value
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_CAP_LENGTH(_hNetBuf_, _Length_)   _NT_NET_SET_PKT_CAP_LENGTH(_hNetBuf_, _Length_)

/** @def NT_NET_SET_PKT_WIRE_LENGTH
 *  @brief Sets the packet wire length
 *  @param[in] _hNetBuf_ Packet container reference
 *  @param[in] _Length_ The length value
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_WIRE_LENGTH(_hNetBuf_, _Length_)  _NT_NET_SET_PKT_WIRE_LENGTH(_hNetBuf_, _Length_)

/** @def NT_NET_SET_PKT_RECALC_L2_CRC
 *  @brief Asks the adapter to re-generate the CRC
 *  @param[in] _hNetBuf_ Packet container reference
 *  @param[in] _bval_ Set to 1 if CRC should be re-generated, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_RECALC_L2_CRC(_hNetBuf_, _bval_)  _NT_NET_SET_PKT_RECALC_L2_CRC(_hNetBuf_, _bval_)
#if !defined(_NT_NTAPI_NO_COMPAT)
#define NT_NET_SET_PKT_CALC_L2_CRC(_hNetBuf_, _bval_)    NT_NET_SET_PKT_RECALC_L2_CRC(_hNetBuf_, _bval_)
#endif

/** @def NT_NET_SET_PKT_TIMESTAMP
 *  @brief Sets the packet time stamp - useful when controlling the traffic rate
 *  @param[in] _hNetBuf_ Packet container reference
 *  @param[in] _ts_ The timestamp value
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_TIMESTAMP(_hNetBuf_, _ts_)      _NT_NET_SET_PKT_TIMESTAMP(_hNetBuf_, _ts_)

/** @def NT_NET_SET_PKT_TXNOW
 *  @brief If set the IPG is ignored - this will result in line rate TX
 *  @param[in] _hNetBuf_ Packet container reference
 *  @param[in] _bval_ Set to 1 if line rate, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_TXNOW(_hNetBuf_, _bval_)        _NT_NET_SET_PKT_TXNOW(_hNetBuf_, _bval_)

/** @def NT_NET_SET_PKT_TXSETCLOCK
 *  @brief Sets the FPGA transmission clock equal to the time stamp of this packet
 *  @param[in] _hNetBuf_ Packet container reference
 *  @param[in] _bval_ Set to 1 if the FPGA transmission clock should equal to the time stamp of this packet, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_TXSETCLOCK(_hNetBuf_, _bval_)   _NT_NET_SET_PKT_TXSETCLOCK(_hNetBuf_, _bval_)

/** @def NT_NET_SET_PKT_TXIGNORE
 *  @brief Marks the packet not to be sent - useful in in-line scenarios where some packets should not be retransmitted
 *  @param[in] _hNetBuf_ Packet container reference
 *  @param[in] _bval_ Set to 1 to not transmit the packet, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_TXIGNORE(_hNetBuf_, _bval_)     _NT_NET_SET_PKT_TXIGNORE(_hNetBuf_, _bval_)

/** @def NT_NET_SET_PKT_IS_IP
 *  @brief Sets if the packet is IP
 *  @param[in] _hNetBuf_ Packet container reference
 *  @param[in] _bval_ Set to 1 if IP packet, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_IS_IP(_hNetBuf_, _bval_)        _NT_NET_SET_PKT_IS_IP(_hNetBuf_, _bval_)

/** @def NT_NET_SET_PKT_IS_UDP
 *  @brief Sets if the packet is UDP
 *  @param[in] _hNetBuf_ Packet container reference
 *  @param[in] _bval_ Set to 1 if UDP packet, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_IS_UDP(_hNetBuf_, _bval_)       _NT_NET_SET_PKT_IS_UDP(_hNetBuf_, _bval_)

/** @def NT_NET_SET_PKT_IS_TCP
 *  @brief Sets if the packet is TCP
 *  @param[in] _hNetBuf_ Packet container reference
 *  @param[in] _bval_ Set to 1 if TCP packet, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_IS_TCP(_hNetBuf_, _bval_)       _NT_NET_SET_PKT_IS_TCP(_hNetBuf_, _bval_)

/** @def NT_NET_SET_PKT_CRC_ERROR
 *  @brief Sets if the packet has a CRC error
 *  @param[in] _hNetBuf_ Packet container reference
 *  @param[in] _bval_ Set to 1 if packet has a CRC error, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_CRC_ERROR(_hNetBuf_, _bval_)    _NT_NET_SET_PKT_CRC_ERROR(_hNetBuf_, _bval_)

/** @def NT_NET_SET_PKT_IP_CSUM_OK
 *  @brief Sets if the packet has an OK IP checksum
 *  @param[in] _hNetBuf_ Packet container reference
 *  @param[in] _bval_ Set to 1 if packet packet has an OK IP checksum, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_IP_CSUM_OK(_hNetBuf_, _bval_)   _NT_NET_SET_PKT_IP_CSUM_OK(_hNetBuf_, _bval_)

/** @def NT_NET_SET_PKT_TCP_CSUM_OK
 *  @brief Sets if the packet has an OK TCP checksum
 *  @param[in] _hNetBuf_ Packet container reference
 *  @param[in] _bval_ Set to 1 if packet packet has an OK TCP checksum, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_TCP_CSUM_OK(_hNetBuf_, _bval_)  _NT_NET_SET_PKT_TCP_CSUM_OK(_hNetBuf_, _bval_)

/** @def NT_NET_SET_PKT_UDP_CSUM_OK
 *  @brief Sets if the packet has an OK UDP checksum
 *  @param[in] _hNetBuf_ Packet container reference
 *  @param[in] _bval_ Set to 1 if packet packet has an OK UDP checksum, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_UDP_CSUM_OK(_hNetBuf_, _bval_)  _NT_NET_SET_PKT_UDP_CSUM_OK(_hNetBuf_, _bval_)

/** @def NT_NET_SET_PKT_TXPORT
 *  @brief Sets the packet port where the packets should be transmitted @note This feature only works on the CaptureReplay profile and the TX port can only be within the range of one adapter
 *  @param[in] _hNetBuf_ Packet container reference
 *  @param[in] _Port_ Port number
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_TXPORT(_hNetBuf_, _Port_)        _NT_NET_SET_PKT_TXPORT(_hNetBuf_, _Port_)

#if !defined(_NTAPI_EXTDESCR_7_) && !defined(_NTAPI_EXTDESCR_8_) && !defined(_NTAPI_EXTDESCR_9_)

/** @defgroup ExtendedTxMacros Extended TX macros
 * @{
 * The following can only be used if the TX buffer has an extended NT descriptor
 */

/** @def NT_NET_SET_PKT_INJECT_TIMESTAMP
 *  @brief Injects a time stamp on TX
 *
 *  The time stamp is injected into the payload at the offset
 *  provided. Offset range: 0-512. See @ref TimeStampInject "Time Stamp Injection"
 *  for further information
 *  @param[in] _hNetBuf_ Packet container reference
 *  @param[in] _offset_ Offset to inject timestamp at
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_INJECT_TIMESTAMP(_hNetBuf_, _offset_)            \
    do { if(_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||          \
            _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||          \
            _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9)            \
           _NT_NET_SET_PKT_INJECT_TIMESTAMP_EXT7(_hNetBuf_, _offset_);  \
         else assert(0); } while(0)

/** @def NT_NET_SET_PKT_ISL
 *  @brief Sets if the frame is ISL encapsulated
 *  @param[in] _hNetBuf_ Packet container reference
 *  @param[in] _bval_ Set 1 if ISL encapsulated, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_ISL(_hNetBuf_, _bval_)                           \
    do { if(_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||          \
            _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||          \
            _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9)            \
           _NT_NET_SET_PKT_ISL_EXT7(_hNetBuf_, _bval_);                 \
         else assert(0); } while(0)

/** @def NT_NET_SET_PKT_VLAN_COUNT
 *  @brief Sets the number of VLAN tags
 *  @param[in] _hNetBuf_ Packet container reference
 *  @param[in] _count_ The VLAN tag count
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_VLAN_COUNT(_hNetBuf_, _count_)                   \
  do { if(_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||            \
          _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||            \
          _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9)              \
         _NT_NET_SET_PKT_VLAN_COUNT_EXT7(_hNetBuf_, _count_);           \
       else assert(0); } while(0)

/** @def NT_NET_SET_PKT_MPLS_COUNT
 *  @brief Sets the number of MPLS shim labels
 *  @param[in] _hNetBuf_ Packet container reference
 *  @param[in] _count_ The MPLS shim labels count
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_MPLS_COUNT(_hNetBuf_, _count_)                   \
  do { if(_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||            \
          _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||            \
          _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9)              \
         _NT_NET_SET_PKT_MPLS_COUNT_EXT7(_hNetBuf_, _count_);           \
       else assert(0); } while(0)

/** @def NT_NET_SET_PKT_L2_FRAME_TYPE
 *  @brief Sets the L2 frame type, see @ref NtL2FrameType_e
 *  @param[in] _hNetBuf_ Packet container reference
 *  @param[in] _type_ The L2 frame type
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_L2_FRAME_TYPE(_hNetBuf_, _type_)                 \
  do { if(_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||            \
          _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||            \
          _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9)              \
         _NT_NET_SET_PKT_L2_FRAME_TYPE_EXT7(_hNetBuf_, _type_);         \
       else assert(0); } while(0)

/** @def NT_NET_SET_PKT_L3_FRAME_TYPE
 *  @brief Sets the L3 frame type, see @ref NtL3FrameType_e
 *  @param[in] _hNetBuf_ Packet container reference
 *  @param[in] _type_ The L3 frame type
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_L3_FRAME_TYPE(_hNetBuf_, _type_)                 \
  do { if(_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||            \
          _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||            \
          _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9)              \
         _NT_NET_SET_PKT_L3_FRAME_TYPE_EXT7(_hNetBuf_, _type_);         \
       else assert(0); } while(0)

/** @def NT_NET_SET_PKT_L4_FRAME_TYPE
 *  @brief Sets the L4 frame type, see @ref NtL4FrameType_e
 *  @param[in] _hNetBuf_ Packet container reference
 *  @param[in] _type_ The L4 frame type
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_L4_FRAME_TYPE(_hNetBuf_, _type_)                 \
  do { if(_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||            \
          _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||            \
          _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9)              \
         _NT_NET_SET_PKT_L4_FRAME_TYPE_EXT7(_hNetBuf_, _type_);         \
       else assert(0); } while(0)

/** @def NT_NET_SET_PKT_L3_LENGTH
 *  @brief L3 length in 32-bit units
 *  @param[in] _hNetBuf_ Packet container reference
 *  @param[in] _u32len_ The L3 length in 32-bit units
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_L3_LENGTH(_hNetBuf_, _u32len_)                   \
  do { if(_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||            \
          _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||            \
          _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9)              \
         _NT_NET_SET_PKT_L3_LENGTH_EXT7(_hNetBuf_, _u32len_);           \
       else assert(0); } while(0)

/** @def NT_NET_SET_PKT_L4_LENGTH
 *  @brief L4 length in 32-bit units
 *  @param[in] _hNetBuf_ Packet container reference
 *  @param[in] _u32len_ The L4 length in 32-bit units
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_L4_LENGTH(_hNetBuf_, _u32len_)                   \
  do { if(_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||            \
          _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||            \
          _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9)              \
         _NT_NET_SET_PKT_L4_LENGTH_EXT7(_hNetBuf_, _u32len_);           \
       else assert(0); } while(0)

/** @def NT_NET_SET_PKT_CALC_L3_CHECKSUM
 *  @brief If set, the adapter will calculate an IPv4 checksum on transmit
 *  @param[in] _hNetBuf_ Packet container reference
 *  @param[in] _bval_ Set to 1 calculate an IPv4 checksum on transmit, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_CALC_L3_CHECKSUM(_hNetBuf_, _bval_)              \
  do { if(_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||            \
          _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||            \
          _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9)              \
         _NT_NET_SET_PKT_CALC_L3_CHECKSUM_EXT7(_hNetBuf_, _bval_);      \
       else assert(0); } while(0)

/** @def NT_NET_SET_PKT_CALC_L4_CHECKSUM
 *  @brief If set, the adapter will calculate an TCP/UDP checksum on transmit
 *  @param[in] _hNetBuf_ Packet container reference
 *  @param[in] _bval_ Set to 1 calculate an TCP/UDP checksum on transmit, 0 otherwise
 *  @hideinitializer
 */
#define NT_NET_SET_PKT_CALC_L4_CHECKSUM(_hNetBuf_, _bval_)              \
  do { if(_NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==7 ||            \
          _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==8 ||            \
          _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)==9)              \
         _NT_NET_SET_PKT_CALC_L4_CHECKSUM_EXT7(_hNetBuf_, _bval_);      \
       else assert(0); } while(0)

#if !defined(_NT_NTAPI_NO_COMPAT)
#define NT_NET_SET_PKT_L3_OFFSET(_hNetBuf_, _offset_)
#define NT_NET_SET_PKT_L4_OFFSET(_hNetBuf_, _offset_)
#endif

/** @} */

#endif /* !defined(_NTAPI_EXTDESCR_7_) && !defined(_NTAPI_EXTDESCR_8_) && !defined(_NTAPI_EXTDESCR_9_) */

/** @} */
/** @} */
/** @} */

#endif /* __PKT_DESCR_H__ */
