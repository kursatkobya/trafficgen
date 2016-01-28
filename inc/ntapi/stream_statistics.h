// $Id: stream_statistics.h 26494 2013-11-01 13:53:15Z lm $
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
 *
 * This is the header file of the statistics stream interface
 */
#ifndef __STREAM_STATISTICS_H__
#define __STREAM_STATISTICS_H__

#if !defined(__NT_H__)
  #error: My interface file is 'nt.h'. Please include that via #include "nt.h" directly.
#endif

/** @addtogroup StatStream
 * @{
 *
 * The statistics stream is used to access statistics from the
 * system. The statistics stream is read only.
 *
 * Statistical information is retrieved using the @ref
 * NtStatisticsCmd_e::NT_STATISTICS_READ_CMD_QUERY_V2
 * "NT_STATISTICS_READ_CMD_QUERY_V2" command in a call to @ref NT_StatRead
 * on an open statistics stream.  This command will fill out the
 * supplied @ref NtStatistics_t structure with port and color based
 * statistics for all adapters in the system. The @ref
 * NtPortStatistics_v1_s::NtPortStatisticsValid_v1_s "NtPortStatisticsValid_v1_s" structure can
 * be used to check which returned part of the @ref NtPortStatistics_v1_s
 * structure is valid. This is useful since not all adapters support
 * all types of statistical information.
 *
 * \par Note:
 * Be aware that statistics from multiple adapters are only
 * synchronized if the time is synchronized.
 *
 * For an example on how to use the statistics stream see @ref
 * stat/stat.c "stat/stat.c".
 *
 * @section ColorStatistics Color Statistics
 * The color statistics for each color are found by adding up the counters
 * for all the hardware filters that has been given the specific color.\n
 * The counters for a hardware filter are not reset when the corresponding NTPL filter
 * (using a given color) is deleted. When another NTPL filter (using another color)
 * later uses the same hardware filter, this other color will start up with a
 * counter that is not zero - which is maybe not as expected.
 *
 * It is the responsibility of the application to handle this.
 *
 * It can be achieved by remembering the counter values for a given color
 * when it was first configured and then subsequently only showing the
 * delta compared to this initial value.
 * Another option is to set the clear flag in @ref NtStatisticsQuery_v2_s::clear
 * on the first call to @ref NT_StatRead. This will make the subsequent calls
 * to @ref NT_StatRead return only the delta compared to the first call.
 *
 * Be aware that setting this clear flag will clear all statistics counters.
 * If this is not desirable the application will have to handle it by itself.
 */
#include "ntapi/commontypes.h"

/**
 * Possible statistics read commands
 */
enum NtStatisticsCmd_e {
  NT_STATISTICS_READ_CMD_UNKNOWN=0,      //!< Unknown read command
  NT_STATISTICS_READ_CMD_COMPAT_0,       //!< Command for backward compatibility - defined in stream_statistics_compat.h
  NT_STATISTICS_READ_CMD_COMPAT_1,       //!< Command for backward compatibility - defined in stream_statistics_compat.h
  NT_STATISTICS_READ_CMD_QUERY_V2,       //!< Reads all the statistical information version 1 (including IPF table counters)
};

/**
 * RMON1 counters as defined in RFC 2819
 */
struct NtRMON1Counters_s {
  uint64_t dropEvents;           //!< Number of events where packet(s) are dropped by the MAC because they are too small or the MAC has bandwidth issues
  uint64_t octets;               //!< Number of octets received by the port (good and bad)
  uint64_t pkts;                 //!< Number of packets received by the port (good and bad)
  uint64_t broadcastPkts;        //!< Number of broadcast packets including MAC control packets
  uint64_t multicastPkts;        //!< Number of multicast packets including MAC pause and MAC control packets
  uint64_t crcAlignErrors;       //!< Number of packets with CRC/Align errors
  uint64_t undersizePkts;        //!< Number of packets < 64 octets
  uint64_t oversizePkts;         //!< Number of packets > 1518 octets (and for NT adapters, packets > MAX and packets < 10000) If packets count here they do not count in the packet and octet counters.\n<b>Note:</b> This counter doesn't count in the TX direction for the following products: NT4E CAPTURE, NT4E-STD CAPTURE, NT20E CAPTURE, NT4E2-EL.
  uint64_t fragments;            //!< Number of packets < 64 octets with errors
  uint64_t jabbers;              //!< Number of packets > MAX with errors - if packets count here they do not count in the packets and octets counters
  uint64_t collisions;           //!< Number of collisions detected
  uint64_t pkts64Octets;         //!< Number of packets = 64 octets
  uint64_t pkts65to127Octets;    //!< Number of packets in the range 65 to 127 octets
  uint64_t pkts128to255Octets;   //!< Number of packets in the range 128 to 255 octets
  uint64_t pkts256to511Octets;   //!< Number of packets in the range 256 to  511 octets
  uint64_t pkts512to1023Octets;  //!< Number of packets in the range 512 to 1023 octets
  uint64_t pkts1024to1518Octets; //!< Number of packets in the range 1024 to 1518 octets
};

/**
 * Extended RMON - these counters are used to categorize packets not handled by RMON1
 */
struct NtExtendedRMONCounters_s {
  uint64_t pkts1519to2047Octets;   //!< Number of packets in the range 1519 to 2047 octets
  uint64_t pkts2048to4095Octets;   //!< Number of packets in the range 2048 to 4095 octets
  uint64_t pkts4096to8191Octets;   //!< Number of packets in the range 4096 to 8191 octets
  uint64_t pkts8192toMaxOctets;    //!< Number of packets in the range 8192 to MAX octets
  uint64_t pktsHardSlice;          //!< Number of packets in the range 10001 to 16383 octets
  uint64_t pktsHardSliceJabber;    //!< Number of bad packets in the range 10001 to 16383 octets and packets > 16383 octets
  uint64_t unicastPkts;            //!< Number of Unicast packets including MAC control packets
  // The following counters are also counted as a sum in @ref NtRMON1Counters_s::crcAlignErrors.
  uint64_t pktsCrc;               //!< Number of packets with CRC errors
  uint64_t pktsAlignment;         //!< Number of packets with alignment errors
  uint64_t pktsCodeViolation;     //!< Number of packets with code violation errors
};

/**
 * Checksum counters - these counters count packets with IP/TCP/UDP errors
 */
struct NtCheckSumCounters_s {
  uint64_t pktsIpChkSumError;  //!< Number of packets with IP checksum errors
  uint64_t pktsUdpChkSumError; //!< Number of packets with UDP checksum errors
  uint64_t pktsTcpChkSumError; //!< Number of packets with TCP checksum errors
} ;

/**
 * Packet decoding counters - these counters are available on adapters with a packet decoder
 */
struct NtDecodeCounters_s {
  uint64_t pktsGiantUndersize;    //!< Number of packets > 63 bytes including tags and =< 63 excluding tags
  uint64_t pktsBabyGiant;         //!< Number of packets > MAX including tags and =< MAX excluding tags
  uint64_t pktsNotIslVlanMpls;    //!< Number of packets without ISL, VLAN and MPLS
  uint64_t pktsIsl;               //!< Number of packets with ISL
  uint64_t pktsVlan;              //!< Number of packets with VLAN
  uint64_t pktsIslVlan;           //!< Number of packets with ISL and VLAN
  uint64_t pktsMpls;              //!< Number of packets with MPLS
  uint64_t pktsIslMpls;           //!< Number of packets with ISL and MPLS
  uint64_t pktsVlanMpls;          //!< Number of packets with VLAN and MPLS
  uint64_t pktsIslVlanMpls;       //!< Number of packets with ISL, VLAN and MPLS
};

/**
  * Extended drop counters - these counters will count the packets
  * dropped for various reasons
 */
struct NtExtendedDropCounters_s {
  uint64_t pktsMacBandwidth;  //!< Number of packets dropped by the MAC because of bandwidth issues and number of packets < 17 octets. This counter is also available in @ref NtRMON1Counters_s::dropEvents.

  uint64_t pktsOverflow;      //!< Number of packets dropped because the port buffer is full
  uint64_t octetsOverflow;    //!< Number of octets dropped because the port buffer is full

  uint64_t pktsDedup;         //!< Number of packets dropped because of deduplication
  uint64_t octetsDedup;       //!< Number of octets dropped because of deduplication

  uint64_t pktsNoFilter;      //!< Number of packets dropped because they do not match a filter
  uint64_t octetsNoFilter;    //!< Number of octets dropped because they do not match a filter
};


/**
 * Color counters
 */
struct NtColorStatistics_s {
  uint64_t pkts;   //!< Number of packets
  uint64_t octets; //!< Number of octets
};

/**
 * Statistics info group for color statistics
 */
struct NtStatGroupColor_s {
  int supported;                          //!< Set if color statistics is supported
  struct NtColorStatistics_s aColor[64];  //!< The color statistics
  uint64_t ts;                            //!< Color counter sample time stamp
  enum NtTimestampType_e tsType;          //!< Time stamp type
};

/**
 * Statistics info group for adapter statistics
 */
struct NtStatGroupAdapter_s {
  struct NtStatGroupColor_s color;
};

/**
 * Statistics info for IPF table
 */
struct NtIpFragTableCounters_s {
  uint64_t ipFragTableFirstHit;     //!< Counts all IPv4/IPv6 first-fragment hits in FPGA IPF-table
  uint64_t ipFragTableFirstNoHit;   //!< Counts all IPv4/IPv6 first-fragment misses in FPGA IPF-table
  uint64_t ipFragTableMidHit;       //!< Counts all IPv4/IPv6 mid-fragment hits in FPGA IPF-table
  uint64_t ipFragTableMidNoHit;     //!< Counts all IPv4/IPv6 mid-fragment misses in FPGA IPF-table
  uint64_t ipFragTableLastHit;      //!< Counts all IPv4/IPv6 last-fragment hits in FPGA IPF-table
  uint64_t ipFragTableLastNoHit;    //!< Counts all IPv4/IPv6 last-fragment misses in FPGA IPF-table
};

/**
 * Statistics for each port
 */
struct NtPortStatistics_v1_s {
  /**
   * Valid indicators - these indicate which counters are supported by the port
   */
  struct NtPortStatisticsValid_v1_s {
    int RMON1;   //!< Is set if RMON1 counters are supported
    int extRMON; //!< Is set if extended RMON counters are supported
    int chksum;  //!< Is set if IP/TCP/UDP checksum counters are supported
    int decode;  //!< Is set if packet decode counters are supported
    int extDrop; //!< Is set if extended drop counters are supported
    int ipf;     //!< Is set if IP fragment table counters are supported
  } valid;

  struct NtRMON1Counters_s RMON1;          //!< RMON1 counters
  struct NtExtendedRMONCounters_s extRMON; //!< Extended RMON counters
  struct NtCheckSumCounters_s chksum;      //!< Checksum error counters
  struct NtDecodeCounters_s decode;        //!< Packets decoded by onboard packet decoder
  struct NtExtendedDropCounters_s extDrop; //!< Extended drop counters
  struct NtIpFragTableCounters_s  ipf;     //!< IP fragment table counters (when using IPFMode)
};

/**
 * Statistics info group for port statistics
 */
struct NtStatGroupport_v1_s {
  struct NtPortStatistics_v1_s rx;   //!< Counters based on RX ports
  struct NtPortStatistics_v1_s tx;   //!< Counters based on TX ports
  uint64_t linkDownCounter;       //!< Counts number of link downs
  uint64_t ts;                    //!< Port counter sample time stamp
  enum NtTimestampType_e tsType;  //!< Time stamp type
};

/**
 * Statistics info group for stream statistics
 */
struct NtStatGroupStream_s {
  struct {
    struct NtColorStatistics_s forward;   //!< Number of forwarded packets/bytes
    struct NtColorStatistics_s flush;     //!< Number of flushed packets/bytes. Received while the stream-id is inactive
    struct NtColorStatistics_s drop;      //!< Number of dropped packets/bytes
  } streamid[256];                        //!< Statistic for an assigned stream-id.
  struct {
    struct NtColorStatistics_s forward;   //!< Number of forwarded packets/bytes
    struct NtColorStatistics_s flush;     //!< Number of flushed packets/bytes. Received while the stream-id is inactive
    struct NtColorStatistics_s drop;      //!< Number of dropped packets/bytes
  } Unassigned;                           //!< Statistic for traffic received in a host buffer before it has been assigned to a stream-id.
  uint64_t ts;
};

struct NtStatisticsQuery_v2_s {
  int poll; //!< Gets the current statistical information or waits for a new update
  int clear; //!< Clears the statistical information after it has been read. All statistics counters for the current stream will be cleared. Other statistics streams will remain untouched.
  /**
   * Data section holding the statistic counters
   */
  struct NtStatisticsQueryResult_v2_s {
    /**
     * Port specific statistics
     */
    struct NtStatisticsQueryPortResult_v2_s {
      uint8_t numPorts;                    //!< Number of ports in @ref aPorts
      uint8_t Reserved1[3];
      struct NtStatGroupport_v1_s aPorts[64];  //!< Array of port statistic structures in the system
    } port;
    /**
     * Adapter specific statistics
     */
    struct NtStatisticsQueryAdapterResult_v2_s {
      uint8_t numAdapters;                       //!< Number of adapters in @ref aAdapters
      uint8_t Reserved1[3];
      struct NtStatGroupAdapter_s aAdapters[10];  //!< Array of adapter statistic structures
    } adapter;
    /**
     * Stream specific statistics
     */
    struct NtStatGroupStream_s stream;
  } data;                                        //!< Structure for statistic results
};

/* Include commands for backwards compatibility */
#if !defined(_NT_NTAPI_NO_COMPAT)
#include "stream_statistics_compat.h"
#endif

/**
 * Statistics
 */
typedef struct NtStatistics_s {
  enum NtStatisticsCmd_e cmd;             //!< Statistics command
  /**
   * Statistics data
   */
  union NtStatistics_u {
    struct NtStatisticsQuery_v2_s query_v2;     //!< The structure to use for @ref NtStatistics_s::cmd==NT_STATISTICS_READ_CMD_QUERY_V2
#if !defined(_NT_NTAPI_NO_COMPAT)
    /* Commands for backwards compatibility */
    struct NtStatisticsQuery_v1_s query_v1;     //!< The structure to use for @ref NtStatistics_s::cmd==NT_STATISTICS_READ_CMD_QUERY_V1
    struct NtStatisticsQuery_s  query;          //!< The structure to use for @ref NtStatistics_s::cmd==NT_STATISTICS_READ_CMD_QUERY
#endif
  }u;                                           //!< Union for statistic structures
} NtStatistics_t;

/**
 * Statistics stream handle
 */
typedef struct NtStatStream_s* NtStatStream_t;

/**
 * @brief Opens a statistics stream
 *
 * This function is called to retrieve a handle to a statistics stream
 *
 * @param[out] hStatStream      Reference to a NtStatStream_t stream pointer
 * @param[in]  name             Stream friendly name - used in, for example, logging statements
 *
 * @retval  0    Success
 * @retval !=0   Error
 */
int NT_StatOpen(NtStatStream_t *hStatStream, const char *name);

/**
 * @brief Reads statistics
 *
 * Returns statistical information from the system
 *
 * @param[in]  hStatStream       NtStatStream_t handle
 * @param[in]  stat              Return buffer for statistics
 *
 * @retval  0    Success
 * @retval !=0   Error
 */
int NT_StatRead(NtStatStream_t hStatStream, NtStatistics_t *stat);

/**
 * @brief Closes a statistics stream
 *
 * This function is called to close a statistics stream
 *
 * @param[in] hStatStream        Reference to a NtStatStream_t stream pointer
 *
 * @retval  0    Success
 * @retval !=0   Error
 */
int NT_StatClose(NtStatStream_t hStatStream);

/** @} */

#endif // __STREAM_STATISTICS_H__
