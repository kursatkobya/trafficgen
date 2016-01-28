// $Id: stream_statistics_compat.h 22854 2013-03-15 15:27:56Z bk $
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
 * This is the header file of the statistics stream interface containing
 * included for backward compatibility structures.
 *
 */

#ifndef __STREAM_STATISTICS_COMPAT_H__
#define __STREAM_STATISTICS_COMPAT_H__

#if !defined(_NT_NTAPI_NO_COMPAT)

/********************************************************************************/
/*       Statistics data defines for NT_STATISTICS_READ_CMD_QUERY               */
/********************************************************************************/
#define NT_STATISTICS_READ_CMD_QUERY  NT_STATISTICS_READ_CMD_COMPAT_0

/**
 * Statistics for each port
 */
struct NtPortStatistics_s {
  /**
   * Valid indicators. These indicate which counters are supported by the port.
   */
  struct NtPortStatisticsValid_s {
    int RMON1;   //!< Is set if RMON1 counters are supported
    int extRMON; //!< Is set if extended RMON counters are supported
    int chksum;  //!< Is set if IP/TCP/UDP checksum counters are supported
    int decode;  //!< Is set if packet decode counters are supported
    int extDrop; //!< Is set if extended drop counters are supported
  } valid;

  struct NtRMON1Counters_s RMON1;          //!< RMON1 counters
  struct NtExtendedRMONCounters_s extRMON; //!< Extended RMON counters
  struct NtCheckSumCounters_s chksum;      //!< Checksum error counters
  struct NtDecodeCounters_s decode;        //!< Packets decoded by onboard packet decoder
  struct NtExtendedDropCounters_s extDrop; //!< Extended drop counters
};

/**
 * Statistics info group for port statistics
 */
struct NtStatGroupPort_s {
  struct NtPortStatistics_s rx;   //!< Counters based on RX ports
  struct NtPortStatistics_s tx;   //!< Counters based on TX ports
  uint64_t linkDownCounter;       //!< Counts number of link downs

  uint64_t ts;                    //!< Port counter sample time stamp
  enum NtTimestampType_e tsType;  //!< Time stamp type
};

struct NtStatisticsQuery_s {
  int poll; //!< Gets the current statistical information or waits for a new update
  int clear; //!< Clears the statistical information after it has been read. All statistics counters for the current stream will be cleared. Other statistics streams will remain untouched.
  /**
   * Data section holding the statistic counters
   */
  struct NtStatisticsQueryResult_s {
    /**
     * Port specific statistics
     */
    struct NtStatisticsQueryPortResult_s {
      uint8_t numPorts;                     //!< Number of ports in @ref aPorts
      uint8_t Reserved1[3];
      struct NtStatGroupPort_s aPorts[64];  //!< Array of port statistic structures in the system
    } port;
    /**
     * Adapter specific statistics
     */
    struct NtStatisticsQueryAdapterResult_s {
      uint8_t numAdapters;                        //!< Number of adapters in @ref aAdapters
      uint8_t Reserved1[3];
      struct NtStatGroupAdapter_s aAdapters[10];  //!< Array of adapter statistic structures
    } adapter;
  } data;                               //!< Structure for statistic results
};

/********************************************************************************/
/*       Statistics data defines for NT_STATISTICS_READ_CMD_QUERY_V1            */
/********************************************************************************/
#define NT_STATISTICS_READ_CMD_QUERY_V1 NT_STATISTICS_READ_CMD_COMPAT_1

struct NtStatisticsQuery_v1_s {
  int poll; //!< Gets the current statistical information or waits for a new update
  int clear; //!< Clears the statistical information after it has been read. All statistics counters for the current stream will be cleared. Other statistics streams will remain untouched.
  /**
   * Data section holding the statistic counters
   */
  struct NtStatisticsQueryResult_v1_s {
    /**
     * Port specific statistics
     */
    struct NtStatisticsQueryPortResult_v1_s {
      uint8_t numPorts;                    //!< Number of ports in @ref aPorts
      uint8_t Reserved1[3];
      struct NtStatGroupport_v1_s aPorts[64];  //!< Array of port statistic structures in the system
    } port;
    /**
     * Adapter specific statistics
     */
    struct NtStatisticsQueryAdapterResult_v1_s {
      uint8_t numAdapters;                       //!< Number of adapters in @ref aAdapters
      uint8_t Reserved1[3];
      struct NtStatGroupAdapter_s aAdapters[10];  //!< Array of adapter statistic structures
    } adapter;
  } data;                               //!< Structure for statistic results
};


#endif /* _NT_NTAPI_NO_COMPAT */
#endif /* __STREAM_STATISTICS_COMPAT_H__ */
