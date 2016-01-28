// $Id: pktdescr_std0.h 26520 2013-11-03 07:01:31Z lm $
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
 * This source file contains the standard packet descriptor.\n
 * It is <b>not</b> to be used directly but via the @ref PacketMacros.
 */

#ifndef DOXYGEN_INTERNAL_ONLY

#ifndef __PKT_DESCR_STD_H__
#define __PKT_DESCR_STD_H__

// Ensure that the following is packed.
#pragma pack(push, 1)

/**
 * This descriptor is placed in front of all packets being received by the adapter when
 * the adapter is operating in STANDARD or EXTENDED mode.
 * Note: The descriptor is used for both RX and TX segments but not all fields apply
 *       in both directions.
 */
#define _NT_DESCR_STD0_FIELDS                                                                                                    \
  /* Offset 0x00. */                                                                                                             \
  uint64_t timestamp;         /* RX & TX - 64 Bit time stamp */                                                                  \
  /* Offset 0x08. */                                                                                                             \
  uint32_t storedLength:16;   /* RX & TX - length of stored data incl. padding */                                                \
  uint32_t crcError:1;        /* RX & TX - Ethernet CRC Error */                                                                 \
  uint32_t TCPCsumOk:1;       /* RX & TX - indicates TCP checksum is correct */                                                  \
  uint32_t UDPCsumOk:1;       /* RX & TX - indicates UDP checksum is correct */                                                  \
  uint32_t IPCsumOk:1;        /* RX & TX - indicates IP checksum is correct  */                                                  \
  uint32_t txCrcOverride:1;   /* RX & TX - recalculate the MAC frame CRC */                                                      \
  uint32_t cvError:1;         /* RX & TX - indicates that this frame had a code violation */                                     \
  uint32_t txSetClock:1;      /* TX      - Set the FPGA transmission clock equal to the time stamp of this packet */             \
  uint32_t frameSliced:1;     /* RX & TX - indicates that the current frame has been sliced (either soft or hard) */             \
  uint32_t rxPort:5;          /* RX only - the adapter port that received the current frame */                                   \
  uint32_t hardSlice:1;       /* RX & TX - the packet length is longer than the hardware can handle and has been hard sliced */  \
  uint32_t txNow:1;           /* TX only - 0 = preserve original IFG between frames, 1 = transmit not preserving original IFG */ \
  uint32_t txIgnore:1;        /* TX only - setting this bit to 1 will prevent the frame from being transmitted */                \
  /* Offset 0x0C. */                                                                                                             \
  uint32_t wireLength:16;     /* RX & TX - length of frame on the wire */                                                        \
  uint32_t txPort:5;          /* RX & TX - the adapter port that should transmit the frame */                                    \
  uint32_t TCPFrame:1;        /* RX only - indicates the current frame is TCP */                                                 \
  uint32_t UDPFrame:1;        /* RX only - indicates the current frame is UDP */                                                 \
  uint32_t IPFrame:1;         /* RX only - indicates the current frame is IP */                                                  \
  uint32_t descriptorType:1;  /* RX & TX - 0 = PCAP or 1 = STANDARD/EXTENDED, must be 1 for TX */                                \
  uint32_t extensionLength:3; /* RX & TX - extended header length in 8 byte units, must be 0 or 2 for TX */                      \
  uint32_t extensionFormat:4; /* RX & TX - extension format type */

typedef struct NtStd0Descr_s {
  _NT_DESCR_STD0_FIELDS
} NtStd0Descr_t;

// Disable 1-byte packing
#pragma pack(pop)

#define _NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)      ((NtStd0Descr_t*)(_hNetBuf_)->hHdr)

#define _NT_NET_GET_PKT_DESCRIPTOR_TYPE(_hNetBuf_)    ((_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->descriptorType == 0) ? \
                                                       NT_PACKET_DESCRIPTOR_TYPE_PCAP : \
                                                       ((_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->extensionFormat == 0 ? \
                                                         NT_PACKET_DESCRIPTOR_TYPE_NT : NT_PACKET_DESCRIPTOR_TYPE_NT_EXTENDED)))
#define _NT_NET_GET_PKT_DESCRIPTOR_FORMAT(_hNetBuf_)  (_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->extensionFormat)

#define _NT_NET_GET_PKT_DESCR_PTR(_hNetBuf_)          ((NtPktDescr_t*)(_hNetBuf_)->hHdr)
#define _NT_NET_GET_PKT_DESCR_LENGTH(_hNetBuf_)       ((uint8_t)sizeof(NtStd0Descr_t)+(_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->extensionLength<<3))
#define _NT_NET_GET_PKT_TIMESTAMP(_hNetBuf_)          (_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->timestamp)
#define _NT_NET_GET_PKT_TIMESTAMP_TYPE(_hNetBuf_)     ((_hNetBuf_)->tsType)
#define _NT_NET_GET_PKT_CAP_LENGTH(_hNetBuf_)         (_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->storedLength)
#define _NT_NET_GET_PKT_WIRE_LENGTH(_hNetBuf_)        (_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->wireLength)
#define _NT_NET_GET_PKT_L2_PTR(_hNetBuf_)             ((void*)(_hNetBuf_)->hPkt)
#define _NT_NET_UPDATE_PKT_L2_PTR(_hNetBuf_)          (((_hNetBuf_)->hPkt)=(void*)((uint8_t*)((_hNetBuf_)->hHdr)+_NT_NET_GET_PKT_DESCR_LENGTH(_hNetBuf_)))

#define _NT_NET_GET_PKT_CRC_ERROR(_hNetBuf_)          (_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->crcError)
#define _NT_NET_GET_PKT_TCP_CSUM_OK(_hNetBuf_)        (_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->TCPCsumOk)
#define _NT_NET_GET_PKT_UDP_CSUM_OK(_hNetBuf_)        (_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->UDPCsumOk)
#define _NT_NET_GET_PKT_IP_CSUM_OK(_hNetBuf_)         (_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->IPCsumOk)
#define _NT_NET_GET_PKT_CV_ERROR(_hNetBuf_)           (_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->cvError)
#define _NT_NET_GET_PKT_SLICED(_hNetBuf_)             (_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->frameSliced)
#define _NT_NET_GET_PKT_HARD_SLICED(_hNetBuf_)        (_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->hardSlice)
#define _NT_NET_GET_PKT_RXPORT(_hNetBuf_)             ((_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->rxPort+(_hNetBuf_)->portOffset))
#define _NT_NET_GET_PKT_RECALC_L2_CRC(_hNetBuf_)      (_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->txCrcOverride)
#define _NT_NET_GET_PKT_TXNOW(_hNetBuf_)              (_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->txNow)
#define _NT_NET_GET_PKT_TXIGNORE(_hNetBuf_)           (_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->txIgnore)
#define _NT_NET_GET_PKT_IS_TCP(_hNetBuf_)             (_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->TCPFrame)
#define _NT_NET_GET_PKT_IS_UDP(_hNetBuf_)             (_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->UDPFrame)
#define _NT_NET_GET_PKT_IS_IP(_hNetBuf_)              (_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->IPFrame)

#define _NT_NET_GET_PKT_TXPORT(_hNetBuf_) \
  ((_hNetBuf_)->egressPort == -1 ? \
   (_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->txPort + (_hNetBuf_)->portOffset) : (_hNetBuf_)->egressPort)

#define _NT_NET_SET_PKT_CAP_LENGTH(_hNetBuf_,_Length_)  do{ _NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->storedLength = \
                                                            (uint16_t) (((_Length_)+(_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->extensionLength<<3) + \
                                                            sizeof(struct NtStd0Descr_s)+7)&~7); } while(0)
#define _NT_NET_SET_PKT_WIRE_LENGTH(_hNetBuf_,_Length_) do{_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->wireLength=(_Length_);}while(0)
#define _NT_NET_SET_PKT_TXPORT(_hNetBuf_,_Port_)        do{_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->txPort=(uint8_t)(((_Port_)-(_hNetBuf_)->portOffset)&0x1F);}while(0)

#define _NT_NET_SET_PKT_RECALC_L2_CRC(_hNetBuf_, _bval_) do{_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->txCrcOverride=(_bval_);}while(0)
#define _NT_NET_SET_PKT_TIMESTAMP(_hNetBuf_, _ts_)       do{_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->timestamp=(_ts_);}while(0)
#define _NT_NET_SET_PKT_TXNOW(_hNetBuf_, _bval_)         do{_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->txNow=(_bval_);}while(0)
#define _NT_NET_SET_PKT_TXSETCLOCK(_hNetBuf_, _bval_)    do{_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->txSetClock=(_bval_);}while(0)
#define _NT_NET_SET_PKT_TXIGNORE(_hNetBuf_, _bval_)      do{_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->txIgnore=(_bval_);}while(0)
#define _NT_NET_SET_PKT_IS_IP(_hNetBuf_, _bval_)         do{_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->IPFrame=(_bval_);}while(0)
#define _NT_NET_SET_PKT_IS_UDP(_hNetBuf_, _bval_)        do{_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->UDPFrame=(_bval_);}while(0)
#define _NT_NET_SET_PKT_IS_TCP(_hNetBuf_, _bval_)        do{_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->TCPFrame=(_bval_);}while(0)
#define _NT_NET_SET_PKT_CRC_ERROR(_hNetBuf_, _bval_)     do{_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->crcError=(_bval_);}while(0)
#define _NT_NET_SET_PKT_TCP_CSUM_OK(_hNetBuf_, _bval_)   do{_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->TCPCsumOk=(_bval_);}while(0)
#define _NT_NET_SET_PKT_UDP_CSUM_OK(_hNetBuf_, _bval_)   do{_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->UDPCsumOk=(_bval_);}while(0)
#define _NT_NET_SET_PKT_IP_CSUM_OK(_hNetBuf_, _bval_)    do{_NT_NET_GET_PKT_DESCR_PTR_STD0(_hNetBuf_)->IPCsumOk=(_bval_);}while(0)

#endif /* __PKT_DESCR_STD_H__ */

#endif // DOXYGEN_INTERNAL_ONLY
