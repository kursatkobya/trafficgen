// $Id: commontypes.h 23639 2013-05-08 14:54:48Z fc $
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
 * This file contains the common types that can be used by any interface
 */

#ifndef __COMMONTYPES_H__
#define __COMMONTYPES_H__

#include <limits.h>

/**
 * Define cross-platform NT_INLINE keyword for static inline functions
 */
#ifndef NT_INLINE
#ifdef WIN32
#define NT_INLINE __forceinline
#else //WIN32
#define NT_INLINE inline
#endif //WIN32
#endif //NT_INLINE

/**
 * Timestamp type.
 */
enum NtTimestampType_e {
  NT_TIMESTAMP_TYPE_NATIVE = 0,    //!< 64-bit 10 ns resolution timer from a base of 0
  NT_TIMESTAMP_TYPE_NATIVE_NDIS,   //!< 64-bit 10 ns resolution timer from a base of January 1, 1601
  NT_TIMESTAMP_TYPE_NATIVE_UNIX,   //!< 64-bit 10 ns resolution timer from a base of January 1, 1970
#ifndef DOXYGEN_INTERNAL_ONLY
  NT_TIMESTAMP_TYPE_NDIS,          //!< Depreciated
#endif
  /**
   * PCAP only supported for Rx, thus no in-line adapter support for these time stamps.
   */
  NT_TIMESTAMP_TYPE_PCAP,          //!< 32-bit seconds and 32-bit usecs from a base of January 1, 1970
  NT_TIMESTAMP_TYPE_PCAP_NANOTIME, //!< 32-bit seconds and 32-bit nsecs from a base of January 1, 1970
};


/**
 * Time stamp method
 */
enum NtTimestampMethod_e {
  NT_TIMESTAMP_METHOD_UNKNOWN = 0, //!< Time stamp method unknown
  NT_TIMESTAMP_METHOD_SOF,         //!< Time stamp at start of frame
  NT_TIMESTAMP_METHOD_EOF          //!< Time stamp at end of frame
};

/**
 * Time stamp inject offset
 */
enum NtTimestampInjectOffsetMode_e {
  NT_TIMESTAMP_INJECT_OFFSET_UNKNOWN = 0, //!< Time stamp inject offset mode unknown
  NT_TIMESTAMP_INJECT_OFFSET_UNSUPPORTED, //!< Time stamp inject offset mode is unsupported
  NT_TIMESTAMP_INJECT_OFFSET_SOF,         //!< Time stamp inject offset calculated from start of frame
  NT_TIMESTAMP_INJECT_OFFSET_EOF          //!< Time stamp inject offset calculated from end of frame
};

/**
 * Relative TX timing method
 */
enum NtTxTimingMethod_e {
  NT_TX_TIMING_UNSUPPORTED = 0, //!< Changing TX timing is unsupported
  NT_TX_TIMING_ABSOLUTE,        //!< TX is made relative (IFG based)
  NT_TX_TIMING_RELATIVE,        //!< TX is made absolut (time stamp based)
};

/**
 * WIS Mode bit mask
 */
enum NtWISMode_e {
  NT_WIS_MODE_DISABLED      = 0x00, //!< OC-192 WIS mode HW Support but disabled
  NT_WIS_MODE_ENABLED       = 0x01, //!< OC-192 WIS mode enabled
};

enum NtHighFrequencySampling_e {
  NT_HIGH_FREQUENCY_SAMPLING_DISABLE = 0, //!< High frequency sampling not used
  NT_HIGH_FREQUENCY_SAMPLING_ENABLE,      //!< High frequency sampling activated
};

enum NtOsTimeSyncFailover_e {
  NT_OS_TIMESYNC_FAILOVER_DISABLE = 0, //!< OS Timesync failover disabled
  NT_OS_TIMESYNC_FAILOVER_ENABLE,      //!< OS Timesync failover enabled
};

/**
 * Host buffer types.
 * Used to select between RX or TX host buffers.
 */
enum NtNetHostBufferType_e {
  NT_NET_HOSTBUFFER_TYPE_UNKNOWN=0, //!< Host buffer type is unknown
  NT_NET_HOSTBUFFER_TYPE_RX,        //!< Host buffer type is RX (ntservice.ini file tag: HostBufferRx)
  NT_NET_HOSTBUFFER_TYPE_TX,        //!< Host buffer type is TX (ntservice.ini file tag: HostBufferTx)
};

/**
 * The stream types supported.
 */
enum NtMsgEndpoint_e {
  NT_MSG_ENDPOINT_UNKNOWN=0,      //!< Unknown stream type
  NT_MSG_ENDPOINT_NET_STREAM,     //!< Network stream
  NT_MSG_ENDPOINT_CONFIG_STREAM,  //!< Configuration stream
  NT_MSG_ENDPOINT_STAT_STREAM,    //!< Statistics stream
  NT_MSG_ENDPOINT_EVENT_STREAM,   //!< Event stream
  NT_MSG_ENDPOINT_INFO_STREAM,    //!< Info stream
  NT_MSG_ENDPOINT_SYSTEM_STREAM,  //!< System-wide stream. @note This is vital and is automatically created in NT_Init() and must
                                  //!< only be created once per process. The reason is that when it closes we expect the process is
                                  //!< terminated and will perform system-wide cleanup for all resourced linked to that process.
  NT_MSG_ENDPOINT_NET_CMD,        //!< Network stream related command endpoint
};

/**
 * Adapter types
 */
enum NtAdapterType_e {
  NT_ADAPTER_TYPE_UNKNOWN=0,   //!< Unknown adapter type
  NT_ADAPTER_TYPE_NT4E,        //!< NT4E network adapter
  NT_ADAPTER_TYPE_NT20E,       //!< NT20E network adapter
  NT_ADAPTER_TYPE_NT4E_STD,    //!< NT4E-STD network adapter
  NT_ADAPTER_TYPE_NT4E_PORT,   //!< NTPORT4E expansion adapter
  NT_ADAPTER_TYPE_NTBPE,       //!< NTBPE bypass adapter
  NT_ADAPTER_TYPE_NT20E2,      //!< NT20E2 network adapter
  NT_ADAPTER_TYPE_NT4E2_EL,    //!< Intel 82580 based adapter
  NT_ADAPTER_TYPE_NT20E2_EL,   //!< Intel 82599 based adapter
  NT_ADAPTER_TYPE_NT40E2_1,    //!< NT40E2-1 network adapter
  NT_ADAPTER_TYPE_NT40E2_4,    //!< NT40E2-4 network adapter
  NT_ADAPTER_TYPE_NT4E2_4T_BP, //!< NT4E2-4T-BP bypass network adapter
  NT_ADAPTER_TYPE_NT4E2_4_PTP,   //!< NT4E2-4 PTP network adapter with IEEE1588
  NT_ADAPTER_TYPE_NT20E2_PTP,   //!< NT20E2 PTP network adapter with IEEE1588
};

/**
 * Packet descriptor type
 */
enum NtPacketDescriptorType_e {
  NT_PACKET_DESCRIPTOR_TYPE_UNKNOWN,      //!< Unknown descriptor type
  NT_PACKET_DESCRIPTOR_TYPE_PCAP,         //!< Descriptor type is PCAP
  NT_PACKET_DESCRIPTOR_TYPE_NT,           //!< Descriptor type is NT
  NT_PACKET_DESCRIPTOR_TYPE_NT_EXTENDED,  //!< Descriptor type is NT extended
};

/**
 * Product types
 */
enum NtProductType_e {
  NT_PRODUCT_TYPE_UNKNOWN=0,      //!< Unknown product type
  NT_PRODUCT_TYPE_CAPTURE,        //!< Capture product type
  NT_PRODUCT_TYPE_INLINE,         //!< In-line product type
  NT_PRODUCT_TYPE_CAPTURE_REPLAY, //!< Capture-replay product type
  NT_PRODUCT_TYPE_TRAFFIC_GEN,    //!< Traffic generator product type
  NT_PRODUCT_TYPE_BYPASS,         //!< Bypass product type
};

/**
 * Profile types
 */
enum NtProfileType_e {
  NT_PROFILE_TYPE_UNKNOWN=0,           //!< Unknown profile type
  NT_PROFILE_TYPE_CAPTURE=1<<0,        //!< Capture profile type
  NT_PROFILE_TYPE_INLINE=1<<1,         //!< In-line profile type
  NT_PROFILE_TYPE_CAPTURE_REPLAY=1<<2, //!< Capture-replay profile type
  NT_PROFILE_TYPE_TRAFFIC_GEN=1<<3,    //!< Traffic generator profile type
};

/**
 * Product family
 */
enum NtProductFamily_e {
  NT_PRODUCT_FAMILY_UNKNOWN=0, //!< Unknown product family
  NT_PRODUCT_FAMILY_NT,        //!< NT adapter family
  NT_PRODUCT_FAMILY_NIC,       //!< Standard NIC product family
};

enum NtFeatureType_e {
  NT_FEATURE_TYPE_BYPASS=1<<0, //!< The adapter has support for bypass.
};

/**
 * SDRAM module sizes
 */
enum NtSdramSize_e {
  NT_SDRAM_SIZE_UNKNOWN=0,      //!< Unknown RAM size
  NT_SDRAM_SIZE_512M = 0x1,     //!< RAM size 512 megabytes
  NT_SDRAM_SIZE_1G = 0x2,       //!< RAM size 1 gigabyte
  NT_SDRAM_SIZE_2G = 0x4,       //!< RAM size 2 gigabytes
  NT_SDRAM_SIZE_4G = 0x8,       //!< RAM size 4 gigabytes
};

/**
 * SDRAM module type
 */
enum NtSdramType_e {
  NT_SDRAM_TYPE_UNKNOWN=0,       //!< Unknown RAM type
  NT_SDRAM_TYPE_DDR2 = 0x1,      //!< RAM is DDR2
  NT_SDRAM_TYPE_DDR3 = 0x2,      //!< RAM is DDR3
};

/**
 * Port types
 */
//ON_API_CHG:
//A NT_PORT_TYPE_NIM_NOT_PRESENT should replace all the individual _NOT_PRESENT values
enum NtPortType_e {
  NT_PORT_TYPE_NOT_AVAILABLE= 0,       //!< The interface is not available
  NT_PORT_TYPE_NOT_RECOGNISED,         //!< The interface type cannot be recognized
  NT_PORT_TYPE_RJ45,                   //!< RJ45 type
  NT_PORT_TYPE_SFP_NOT_PRESENT,        //!< SFP type but slot is empty
  NT_PORT_TYPE_SFP_SX,                 //!< SFP SX
  NT_PORT_TYPE_SFP_SX_DD,              //!< SFP SX digital diagnostic
  NT_PORT_TYPE_SFP_LX,                 //!< SFP LX
  NT_PORT_TYPE_SFP_LX_DD,              //!< SFP LX digital diagnostic
  NT_PORT_TYPE_SFP_ZX,                 //!< SFP ZX
  NT_PORT_TYPE_SFP_ZX_DD,              //!< SFP ZX digital diagnostic
  NT_PORT_TYPE_SFP_CU,                 //!< SFP copper
  NT_PORT_TYPE_SFP_CU_DD,              //!< SFP copper digital diagnostic
  NT_PORT_TYPE_SFP_NOT_RECOGNISED,     //!< SFP unknown
  NT_PORT_TYPE_XFP,                    //!< XFP
  NT_PORT_TYPE_XPAK,                   //!< XPAK
  NT_PORT_TYPE_SFP_CU_TRI_SPEED,       //!< SFP copper tri-speed
  NT_PORT_TYPE_SFP_CU_TRI_SPEED_DD,    //!< SFP copper tri-speed digital diagnostic
  NT_PORT_TYPE_SFP_PLUS,               //!< SFP+ type
  NT_PORT_TYPE_SFP_PLUS_NOT_PRESENT,   //!< SFP+ type but slot is empty
  NT_PORT_TYPE_XFP_NOT_PRESENT,        //!< XFP type but slot is empty
  NT_PORT_TYPE_QSFP_PLUS_NOT_PRESENT,  //!< QSFP type but slot is empty
  NT_PORT_TYPE_QSFP_PLUS,              //!< QSFP type
};

typedef enum NtPortType_e NtPortType_t, *NtPortType_p;

/**
 * Link state.\n
 * Just after start of ntservice the link state might be unknown since the
 * monitoring routine is busy reading NIM state and NIM data. This might also
 * be the case after a NIM is plugged into an interface.
 * The error state indicates a HW reading error.
 */
enum NtLinkState_e {
  NT_LINK_STATE_UNKNOWN = 0, //!< The link state has not been read yet
  NT_LINK_STATE_DOWN    = 1, //!< The link state is DOWN
  NT_LINK_STATE_UP      = 2, //!< The link state is UP
  NT_LINK_STATE_ERROR   = 3  //!< The link state could not be read
};

typedef enum NtLinkState_e NtLinkState_t, *NtLinkState_p;

/**
 * Link speed.
 * Note this is a bitmask.
 */
enum NtLinkSpeed_e {
  NT_LINK_SPEED_UNKNOWN=0,
  NT_LINK_SPEED_10M =0x01, //!< 10 Mbps
  NT_LINK_SPEED_100M=0x02, //!< 100 Mbps
  NT_LINK_SPEED_1G  =0x04, //!< 1 Gbps  (Autoneg only)
  NT_LINK_SPEED_10G =0x08, //!< 10 Gbps (Autoneg only)
  NT_LINK_SPEED_40G =0x10, //!< 40 Gbps (Autoneg only)
};

typedef enum NtLinkSpeed_e NtLinkSpeed_t;

/**
 * Link duplex mode
 */
enum NtLinkDuplex_e {
  NT_LINK_DUPLEX_UNKNOWN=0,
  NT_LINK_DUPLEX_HALF = 0x01, //!< Half duplex
  NT_LINK_DUPLEX_FULL = 0x02, //!< Full duplex
};

typedef enum NtLinkDuplex_e NtLinkDuplex_t;

/**
 * Link MDI mode
 */
enum NtLinkMDI_e {
  NT_LINK_MDI_AUTO = 0x01,  //!< MDI auto
  NT_LINK_MDI_MDI  = 0x02,  //!< MDI mode
  NT_LINK_MDI_MDIX = 0x04,  //!< MDIX mode
};

typedef enum NtLinkMDI_e NtLinkMDI_t;

/**
 * Link Auto/Manual mode
 */
enum NtLinkAutoNeg_e {
  NT_LINK_AUTONEG_MANUAL = 0x01, //!< Manual link
  NT_LINK_AUTONEG_AUTO   = 0x02, //!< Auto link
};

typedef enum NtLinkAutoNeg_e NtLinkAutoNeg_t;

/**
 * TX laser power mode
 */
enum NtTxPower_e {
  NT_TX_POWER_UNKNOWN=0, //!< Illegal value - should newer be read or written
  NT_TX_POWER_NA,        //!< Reading: Changing TX Power is not supported.\n Writing: Not valid for writing.
  NT_TX_POWER_ON,        //!< Reading: TX power is on.\n Writing: Turns on the TX power
  NT_TX_POWER_OFF        //!< Reading: TX power is off.\n Writing: Turns off the TX power
};


/**
 *
 */
enum NtBypassTrigger_e {
  NT_BYPASS_TRIGGER_NONE = 0x00,        //!< TODO:
  NT_BYPASS_TRIGGER_PWRFAIL = 0x01,     //!< TODO:
};

/**
 *
 */
enum NtBypassPortState_e {
  NT_BYPASS_PORT_STATE_UNKNOWN=0,  //!< NT_BYPASS_PORT_STATE_UNKNOWN should be used when reading
  NT_BYPASS_PORT_STATE_IGNORE=0,   //!< NT_BYPASS_PORT_STATE_IGNORE should be used when writing
  NT_BYPASS_PORT_STATE_NORMAL=1,   //!< TODO:
  NT_BYPASS_PORT_STATE_BYPASS=2,   //!< TODO:
};

/**
 *
 */
enum NtOperationReadWrite_e {
  NT_OPERATION_UNKNOWN = 0,        //!< TODO:
  NT_OPERATION_READ = 1,           //!< TODO:
  NT_OPERATION_WRITE = 2,          //!< TODO:
};



/**
 * Time sync protocol
 */
enum NtTimeSyncProtocol_e {
  NT_TIMESYNC_PROTOCOL_NT=0,      //!< Time sync set to NT time sync
  NT_TIMESYNC_PROTOCOL_OS,        //!< Time sync set to OS time sync
  NT_TIMESYNC_PROTOCOL_PPS_REL,   //!< Time sync set to PPS time sync with no external time source
  NT_TIMESYNC_PROTOCOL_PPS_ABS,   //!< Time sync set to PPS time sync with external time source
  NT_TIMESYNC_PROTOCOL_FREE,      //!< Time sync set to free running
};

/**
 * Time sync PPS actions
 */
enum NtTimeSyncPpsAction_e {
  NT_TIMESYNC_PPS_ACTION_REFERENCE_TIME=0,  //!< Send reference TOD to driver
  NT_TIMESYNC_PPS_ACTION_ENABLE,            //!< Enable PPS clock synchronization
  NT_TIMESYNC_PPS_ACTION_DISABLE,           //!< Disable PPS clock synchronization
};

/**
 * Time sync connectors
 */
enum NtTimeSyncConnector_e {
  NT_TIMESYNC_CONNECTOR_NONE = 0,      //!< Time sync connector unused
  NT_TIMESYNC_CONNECTOR_EXT  = 0x01,   //!< Bit mask for external time sync connnector
  NT_TIMESYNC_CONNECTOR_INT1 = 0x02,   //!< Bit mask for internal 1 time sync connnector
  NT_TIMESYNC_CONNECTOR_INT2 = 0x04,   //!< Bit mask for internal 2 time sync connnector
};


/**
 * Time sync PPS current clock synchonization mode
 */
enum NtTimeSyncPpsSyncMode_e {
  NT_TIMESYNC_PPS_MODE_NOT_SYNCING = 0,  //!< Currently not using PPS synchronization
  NT_TIMESYNC_PPS_MODE_PHASE_SYNCING,    //!< Currently using phase synchronization method
  NT_TIMESYNC_PPS_MODE_TIME_SYNCING      //!< Currently using time synchronization
};


/**
 * Time sync connector settings
 */
enum NtTimeSyncConnectorSetting_e {
  NT_TIMESYNC_CONNECTOR_SETTING_NONE = 0,          //!< Connector set to None. Connector not used
  NT_TIMESYNC_CONNECTOR_SETTING_NTTS_IN = 1,       //!< Connector set to NttsIn (NT-TS input)
  NT_TIMESYNC_CONNECTOR_SETTING_PPS_IN = 2,        //!< Connector set to PpsIn (PPS input)
  NT_TIMESYNC_CONNECTOR_SETTING_10MPPS_IN = 3,     //!< 10MPPS - Frequency reference input (not yet supported)
  NT_TIMESYNC_CONNECTOR_SETTING_NTTS_OUT = 4,      //!< Connector set to NttsOut (NT-TS output)
  NT_TIMESYNC_CONNECTOR_SETTING_PPS_OUT = 5,       //!< Connector set to PpsOut (PPS output)
  NT_TIMESYNC_CONNECTOR_SETTING_10MPPS_OUT = 6,    //!< 10MPPS - Frequency output  (not yet supported)
  NT_TIMESYNC_CONNECTOR_SETTING_REPEAT_INT1 = 7,   //!< Connector set to repeat connector Int1
  NT_TIMESYNC_CONNECTOR_SETTING_REPEAT_INT2 = 8,   //!< Connector set to repeat connector Int2
  NT_TIMESYNC_CONNECTOR_SETTING_REPEAT_EXT1 = 9,   //!< Connector set to repeat connector Ext1
};


/**
 * Time sync connector status
 */
enum NtTimeSyncConStatus_e {
  NT_TIMESYNC_CONNECTOR_STATUS_NONE = 0,         //!< Time sync status not applicable (current TS ref is not a connector)
  NT_TIMESYNC_CONNECTOR_STATUS_SIGNAL_LOST,      //!< Time sync signal lost (NT and PPS)
  NT_TIMESYNC_CONNECTOR_STATUS_SIGNAL_PRESENT,   //!< Time sync signal present (NT and PPS)
};

/**
 * Time sync in-sync status
 *
 * This is set according to the configured parameters
 * TimeSyncOSInSyncLimit, TimeSyncPTPInSyncLimit,
 * TimeSyncPPSInSyncLimit and TimeSyncNTTSInSyncLimit
 */
enum NtTimeSyncInSyncStatus_e {
  NT_TIMESYNC_INSYNC_STATUS_NONE = 0,     //!< Time sync in-sync status not applicable i.e. free running.
  NT_TIMESYNC_INSYNC_STATUS_IN_SYNC,      //!< Time sync in-sync status is in-sync.
  NT_TIMESYNC_INSYNC_STATUS_NOT_IN_SYNC   //!< Time sync in-sync status is not in-sync.
};

/**
 * Time sync PPS status
 */
enum NtTimeSyncPpsStatus_e {
  NT_TIMESYNC_PPS_STATUS_NONE = 0,        //!< PPS clock synchronization status invalid
  NT_TIMESYNC_PPS_STATUS_ENABLED = 0x01,  //!< PPS clock synchronization status enabled by app
  NT_TIMESYNC_PPS_STATUS_DISABLED = 0x02, //!< //!< PPS clock sunchronization status disabled
};

/**
 * Time sync reference priority
 */
enum NtTimeSyncReference_e {
  NT_TIMESYNC_REFERENCE_INVALID      = 0,  //!< Time Sync reference id invalid
  NT_TIMESYNC_REFERENCE_FREE_RUN     = 1,  //!< Time Sync reference id for free running
  NT_TIMESYNC_REFERENCE_PTP          = 2,  //!< Time Sync reference id for PTP
  NT_TIMESYNC_REFERENCE_INT1         = 3,  //!< Time Sync reference id for connector internal 1
  NT_TIMESYNC_REFERENCE_INT2         = 4,  //!< Time Sync reference id for connector internal 2
  NT_TIMESYNC_REFERENCE_EXT1         = 5,  //!< Time Sync reference id for connector external 1
  NT_TIMESYNC_REFERENCE_OSTIME       = 6,  //!< Time Sync reference id for OS Time
};

/**
 * Time sync frequency reference priority
 */
enum NtTimeSyncFreqReference_e {
  NT_TIMESYNC_FREQ_REFERENCE_INVALID   = 0,  //!< Time Sync frequency reference id invalid
  NT_TIMESYNC_FREQ_REFERENCE_FREE_RUN  = 1,  //!< Time Sync frequency reference id for free running oscillator
  NT_TIMESYNC_FREQ_REFERENCE_SYNC_E    = 2,  //!< Time Sync frequency reference id for PTP port Rx recovered clock (SyncE)
};

/**
 * Time sync sampling source identifier
 */
enum NtTimeSyncSamplingSrc_e {
  NT_TIMESYNC_SAMPLING_EXT1 = 0,    //!< Sampling source is External1 connector
  NT_TIMESYNC_SAMPLING_INT1 = 1,    //!< Sampling source is Internal1 connector
  NT_TIMESYNC_SAMPLING_INT2 = 2,    //!< Sampling source is Internal2 connector
  /* 3,4,5 - for future use */
  NT_TIMESYNC_SAMPLING_PTP  = 6,    //!< Sampling source is PTP clock PPS output.
  NT_TIMESYNC_SAMPLING_CNT
};

/**
 * Time sync sampling source status
 */
enum NtTimeSyncSamplingSrcStatus_e {
  NT_TIMESYNC_SAMPLING_STATUS_INVALID     = 0,   //!< Time sync sampling source status unused
  NT_TIMESYNC_SAMPLING_STATUS_NOT_PRESENT = 1,   //!< Time sync sampling source status not present (no signal/undefined)
  NT_TIMESYNC_SAMPLING_STATUS_PRESENT     = 2    //!< Time sync sampling source status present
};



/**
 * IEEE 1588 PTP port state identifier
 */
enum NtPTPPortState_e {
  NT_PTP_PORT_STATE_NA           = 0,   //!< Invalid
  NT_PTP_PORT_STATE_INIT         = 1,   //!< Initializing
  NT_PTP_PORT_STATE_FAULTY       = 2,   //!< Faulty
  NT_PTP_PORT_STATE_DISABLED     = 3,   //!< Disabled
  NT_PTP_PORT_STATE_LISTENING    = 4,   //!< Listening
  NT_PTP_PORT_STATE_PRE_MASTER   = 5,   //!< Pre Master
  NT_PTP_PORT_STATE_MASTER       = 6,   //!< Master
  NT_PTP_PORT_STATE_PASSIVE      = 7,   //!< Passive
  NT_PTP_PORT_STATE_UNCALIBRATED = 8,   //!< Uncalibrated
  NT_PTP_PORT_STATE_SLAVE        = 9,   //!< Slave
  NT_PTP_PORT_STATE_INACTIVE     = 127, //!< PTP protocol engine inactive
};


/**
 * Sensor types
 */
enum NtSensorType_e {
  NT_SENSOR_TYPE_UNKNOWN      = 0,
  NT_SENSOR_TYPE_TEMPERATURE  = 1, //!< Unit: 0.1 degree Celsius
  NT_SENSOR_TYPE_VOLTAGE      = 2, //!< Unit: 10 mV
  NT_SENSOR_TYPE_CURRENT      = 3, //!< Unit: 1 uA
  NT_SENSOR_TYPE_POWER        = 4, //!< Unit: 0.1 uW
  NT_SENSOR_TYPE_FAN          = 5, //!< Unit: 1 RPM (Revolutions Per Minute)
  NT_SENSOR_TYPE_HIGH_POWER   = 6, //!< Unit: 1 W
};

typedef enum NtSensorType_e NtSensorType_t;

/**
 * Sensor subtypes
 */
enum NtSensorSubType_e {
  NT_SENSOR_SUBTYPE_NA = 0,
  NT_SENSOR_SUBTYPE_POWER_OMA,    //!< Subtype for NT_SENSOR_TYPE_POWER type on optical modules (optical modulation amplitude measured)
  NT_SENSOR_SUBTYPE_POWER_AVERAGE //!< Subtype for NT_SENSOR_TYPE_POWER type on optical modules (average power measured)
};

typedef enum NtSensorSubType_e NtSensorSubType_t;

/**
 * Sensor source
 */
enum NtSensorSource_e {
  NT_SENSOR_SOURCE_UNKNOWN        = 0x00,  //!< Unknown source
  NT_SENSOR_SOURCE_PORT           = 0x01,  //!< Sensors located in NIMs
  NT_SENSOR_SOURCE_LEVEL1_PORT    = 0x02,  //!< Level 1 sensors located in NIMs
#ifndef DOXYGEN_INTERNAL_ONLY
  NT_SENSOR_SOURCE_LEVEL2_PORT    = 0x04,  //!< Level 2 sensors located in NIMs
#endif
  NT_SENSOR_SOURCE_ADAPTER        = 0x08,  //!< Sensors mounted on the adapter
  NT_SENSOR_SOURCE_LEVEL1_ADAPTER = 0x10,  //!< Level 1 sensors mounted on the adapter
#ifndef DOXYGEN_INTERNAL_ONLY
  NT_SENSOR_SOURCE_LEVEL2_ADAPTER = 0x20,  //!< Level 2 sensors mounted on the adapter
#endif
};

/**
 * Sensor state
 */
enum NtSensorState_e {
  NT_SENSOR_STATE_UNKNOWN      = 0, //!< Unknown state
  NT_SENSOR_STATE_INITIALIZING = 1, //!< The sensor is initializing
  NT_SENSOR_STATE_NORMAL       = 2, //!< Sensor values are within range
  NT_SENSOR_STATE_ALARM        = 3, //!< Sensor values are out of range
  NT_SENSOR_STATE_NOT_PRESENT  = 4  //!< The sensor is not present, for example, SFP without diagnostics
};

typedef enum NtSensorState_e NtSensorState_t;

/**
 * Sensor value
 */
#define NT_SENSOR_NAN (int)0x80000000 //!< Indicates that sensor value or sensor limit is not valid (Not a Number)

/**
 * Master/Slave
 */
enum NtBondingType_e {
  NT_BONDING_UNKNOWN,       //!< Unknown bonding type
  NT_BONDING_MASTER,        //!< Adapter is master in the bonding
  NT_BONDING_SLAVE,         //!< Adapter is slave in the bonding
};

/**
 * Maximum name length for streams
 */
#define NT_MAX_STREAM_NAME_LENGTH 20


/**
 * NT20E2 Adapter sensors
 *
 * When reading sensors using the @ref InfoStream @ref NtInfoSensor_t
 * the source must be @ref NtSensorSource_e::NT_SENSOR_SOURCE_ADAPTER to
 * read the public sensors or @ref NtSensorSource_e::NT_SENSOR_SOURCE_LEVEL1_ADAPTER
 * to read the Diagnostic sensors.
 */
enum NtSensorsAdapterNT20E2_e {
  // Public sensors
  NT_SENSOR_NT20E2_FPGA,              //!< FPGA temperature sensor
  NT_SENSOR_NT20E2_FAN,               //!< FAN speed sensor
  NT_SENSOR_NT20E2_MAIN_EXAR1_TEMP,   //!< Mainboard power supply 1 temperature sensor
  NT_SENSOR_NT20E2_MAIN_EXAR2_TEMP,   //!< Mainboard power supply 2 temperature sensor
  NT_SENSOR_NT20E2_FRONT_EXAR_TEMP,   //!< Front board power supply temperature sensor
  NT_SENSOR_NT20E2_FRONT_TEMP_PBA,    //!< Front board PBA temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT20E2_NT20E2_POWER,      //!< Total power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT20E2_FPGA_POWER,        //!< FPGA power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT20E2_DDR3_POWER,        //!< DDR3 RAM power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT20E2_PHY_POWER,         //!< PHY power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT20E2_SFP_0_POWER,       //!< SFP 0 power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT20E2_SFP_1_POWER,       //!< SFP 1 power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT20E2_ADAPTER_MAX,       //!< Number of NT20E2 adapter sensors
};

enum NtSensorsPortNT20E2_e {
  // Public sensors
  NT_SENSOR_NT20E2_NIM,               //!< SFP temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT20E2_SUPPLY,            //!< SFP supply voltage sensor - does not generate alarms
  NT_SENSOR_NT20E2_TX_BIAS,           //!< SFP TX bias current sensor - does not generate alarms
  NT_SENSOR_NT20E2_TX,                //!< SFP TX power sensor - does not generate alarms
  NT_SENSOR_NT20E2_RX,                //!< SFP RX power sensor - does not generate alarms
  NT_SENSOR_NT20E2_PORT_MAX,          //!< Number of NT20E2 port sensors
};

/**
 * NT40E2_4 Adapter sensors
 *
 * When reading sensors using the @ref InfoStream @ref NtInfoSensor_t
 * the source must be @ref NtSensorSource_e::NT_SENSOR_SOURCE_ADAPTER to
 * read the public sensors or @ref NtSensorSource_e::NT_SENSOR_SOURCE_LEVEL1_ADAPTER
 * to read the Diagnostic sensors.
 */
enum NtSensorsAdapterNT40E2_4_e {
  // Public sensors
  NT_SENSOR_NT40E2_4_FPGA = NT_SENSOR_NT20E2_FPGA,                         //!< FPGA temperature sensor
  NT_SENSOR_NT40E2_4_FAN = NT_SENSOR_NT20E2_FAN,                           //!< FAN speed sensor
  NT_SENSOR_NT40E2_4_MAIN_EXAR1_TEMP = NT_SENSOR_NT20E2_MAIN_EXAR1_TEMP,   //!< Mainboard power supply 1 temperature sensor
  NT_SENSOR_NT40E2_4_MAIN_EXAR2_TEMP = NT_SENSOR_NT20E2_MAIN_EXAR2_TEMP,   //!< Mainboard power supply 2 temperature sensor
  NT_SENSOR_NT40E2_4_FRONT_EXAR_TEMP = NT_SENSOR_NT20E2_FRONT_EXAR_TEMP,   //!< Front board power supply temperature sensor
  NT_SENSOR_NT40E2_4_FRONT_TEMP_PBA = NT_SENSOR_NT20E2_FRONT_TEMP_PBA,     //!< Front board PBA temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT40E2_4_NT40E2_4_POWER = NT_SENSOR_NT20E2_NT20E2_POWER,       //!< Total power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT40E2_4_FPGA_POWER = NT_SENSOR_NT20E2_FPGA_POWER,             //!< FPGA power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT40E2_4_DDR3_POWER = NT_SENSOR_NT20E2_DDR3_POWER,             //!< DDR3 RAM power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT40E2_4_PHY_POWER = NT_SENSOR_NT20E2_PHY_POWER,               //!< PHY power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT40E2_4_SFP_0_POWER = NT_SENSOR_NT20E2_SFP_0_POWER,           //!< SFP 0 power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT40E2_4_SFP_1_POWER = NT_SENSOR_NT20E2_SFP_1_POWER,           //!< SFP 1 power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT40E2_4_ADAPTER_MAX = NT_SENSOR_NT20E2_ADAPTER_MAX,           //!< Number of NT40E2_4 adapter sensors
};

enum NtSensorsPortNT40E2_4_e {
  // Public sensors
  NT_SENSOR_NT40E2_4_NIM = NT_SENSOR_NT20E2_NIM,              //!< SFP temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT40E2_4_SUPPLY = NT_SENSOR_NT20E2_SUPPLY,        //!< SFP supply voltage sensor - does not generate alarms
  NT_SENSOR_NT40E2_4_TX_BIAS = NT_SENSOR_NT20E2_TX_BIAS,           //!< SFP TX bias current sensor - does not generate alarms
  NT_SENSOR_NT40E2_4_TX = NT_SENSOR_NT20E2_TX,                //!< SFP TX power sensor - does not generate alarms
  NT_SENSOR_NT40E2_4_RX = NT_SENSOR_NT20E2_RX,                //!< SFP RX power sensor - does not generate alarms
  NT_SENSOR_NT40E2_4_PORT_MAX = NT_SENSOR_NT20E2_PORT_MAX,    //!< Number of NT20E2 port sensors
};

/**
 * NT40E2_1 Adapter sensors
 *
 * When reading sensors using the @ref InfoStream @ref NtInfoSensor_t
 * the source must be @ref NtSensorSource_e::NT_SENSOR_SOURCE_ADAPTER to
 * read the public sensors or @ref NtSensorSource_e::NT_SENSOR_SOURCE_LEVEL1_ADAPTER
 * to read the Diagnostic sensors.
 */
enum NtSensorsAdapterNT40E2_e {
  // Public sensors
  NT_SENSOR_NT40E2_FPGA,              //!< FPGA temperature sensor
  NT_SENSOR_NT40E2_FAN,               //!< FAN speed sensor
  NT_SENSOR_NT40E2_MAIN_EXAR1_TEMP,   //!< Mainboard power supply 1 temperature sensor
  NT_SENSOR_NT40E2_MAIN_EXAR2_TEMP,   //!< Mainboard power supply 2 temperature sensor
  NT_SENSOR_NT40E2_FRONT_EXAR_TEMP,   //!< Front board power supply temperature sensor
  NT_SENSOR_NT40E2_FRONT_TEMP_PBA,    //!< Front board PBA temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT40E2_NT40E2_POWER,      //!< Total power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT40E2_FPGA_POWER,        //!< FPGA power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT40E2_DDR3_POWER,        //!< DDR3 RAM power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT40E2_PHY_POWER,         //!< PHY power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT40E2_QSFP_POWER,        //!< QSFP power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT40E2_ADAPTER_MAX,       //!< Number of NT40E2 adapter sensors
};

enum NtSensorsPortNT40E2_e {
  // Public sensors
  NT_SENSOR_NT40E2_NIM,               //!< SFP temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT40E2_SUPPLY,            //!< QSFP+ supply voltage sensor
  NT_SENSOR_NT40E2_TX_BIAS1,          //!< QSFP+ TX bias line 0 current sensor
  NT_SENSOR_NT40E2_TX_BIAS2,          //!< QSFP+ TX bias line 1 current sensor
  NT_SENSOR_NT40E2_TX_BIAS3,          //!< QSFP+ TX bias line 2 current sensor
  NT_SENSOR_NT40E2_TX_BIAS4,          //!< QSFP+ TX bias line 3 current sensor
  NT_SENSOR_NT40E2_RX1,               //!< QSFP+ RX line 0 power sensor
  NT_SENSOR_NT40E2_RX2,               //!< QSFP+ RX line 1 power sensor
  NT_SENSOR_NT40E2_RX3,               //!< QSFP+ RX line 2 power sensor
  NT_SENSOR_NT40E2_RX4,               //!< QSFP+ RX line 3 power sensor
  NT_SENSOR_NT40E2_TX1,               //!< QSFP+ TX line 0 power sensor
  NT_SENSOR_NT40E2_TX2,               //!< QSFP+ TX line 1 power sensor
  NT_SENSOR_NT40E2_TX3,               //!< QSFP+ TX line 2 power sensor
  NT_SENSOR_NT40E2_TX4,               //!< QSFP+ TX line 3 power sensor
  NT_SENSOR_NT40E2_PORT_MAX,          //!< Number of NT40E2 port sensors
};

enum NtSensorsAdapterNT20E_e {
  // Public sensors
  NT_SENSOR_NT20E_FPGA,               //!< FPGA temperature sensor (junction temperature)
  NT_SENSOR_NT20E_PBA,                //!< PCB temperature sensor (PCB temperature)
  NT_SENSOR_NT20E_ADAPTER_MAX,        //!< Number of NT20E adapter sensors
};

enum NtSensorsPortNT20E_e {
  // Public sensors
  NT_SENSOR_NT20E_XFP,               //!< XFP temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT20E_TX_BIAS,           //!< XFP TX bias current sensor - does not generate alarms
  NT_SENSOR_NT20E_TX,                //!< XFP TX power sensor - does not generate alarms
  NT_SENSOR_NT20E_RX,                //!< XFP RX power sensor - does not generate alarms
  NT_SENSOR_NT20E_PORT_MAX,          //!< Number of NT20E port sensors
};

enum NtSensorsAdapterNT4E_e {
  // Public sensors
  NT_SENSOR_NT4E_FPGA,               //!< FPGA temperature sensor (junction temperature)
  NT_SENSOR_NT4E_PBA,                //!< PCB temperature sensor (PCB temperature)
  NT_SENSOR_NT4E_ADAPTER_MAX,        //!< Number of NT4E adapter sensors
};

enum NtSensorsPortNT4E_e {
  // Public sensors
  NT_SENSOR_NT4E_SFP,                //!< SFP temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT4E_SUPPLY,             //!< SFP supply voltage sensor - does not generate alarms
  NT_SENSOR_NT4E_TX_BIAS,            //!< SFP TX bias current sensor - does not generate alarms
  NT_SENSOR_NT4E_TX,                 //!< SFP TX power sensor - does not generate alarms
  NT_SENSOR_NT4E_RX,                 //!< SFP RX power sensor - does not generate alarms
  NT_SENSOR_NT4E_PORT_MAX,           //!< Number NT4E of port sensors
};

enum NtSensorsAdapterNT4E2_e {
  // Public sensors
  NT_SENSOR_NT4E2_FPGA,              //!< FPGA temperature sensor
  NT_SENSOR_NT4E2_FAN,               //!< FAN speed sensor
  NT_SENSOR_NT4E2_MAIN_EXAR1_TEMP,   //!< Mainboard power supply 1 temperature sensor
  NT_SENSOR_NT4E2_MAIN_EXAR2_TEMP,   //!< Mainboard power supply 2 temperature sensor
  NT_SENSOR_NT4E2_FRONT_EXAR_TEMP,   //!< Front board power supply temperature sensor
  NT_SENSOR_NT4E2_FRONT_TEMP_PBA,    //!< Front board PBA temperature sensor
  NT_SENSOR_NT4E2_FRONT_TEMP_PHY,    //!< Front board PHY temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT4E2_NT4E2_POWER,       //!< Total power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT4E2_FPGA_POWER,        //!< FPGA power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT4E2_DDR3_POWER,        //!< DDR3 RAM power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT4E2_FRONT_POWER,       //!< FRONT power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT4E2_ADAPTER_MAX,       //!< Number of NT4E2 adapter sensors
};

enum NtSensorsAdapterNT4E2_PTP_e {
  // Public sensors
  NT_SENSOR_NT4E2_PTP_FPGA,            //!< FPGA temperature sensor
  NT_SENSOR_NT4E2_PTP_FAN,             //!< FAN speed sensor
  NT_SENSOR_NT4E2_PTP_MAIN_EXAR1_TEMP, //!< Mainboard power supply 1 temperature sensor
  NT_SENSOR_NT4E2_PTP_MAIN_EXAR2_TEMP, //!< Mainboard power supply 2 temperature sensor
  NT_SENSOR_NT4E2_PTP_FRONT_EXAR_TEMP, //!< Front board power supply temperature sensor
  NT_SENSOR_NT4E2_PTP_FRONT_TEMP_PBA,  //!< Front board PBA temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT4E2_PTP_NT4E2_POWER,     //!< Total power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT4E2_PTP_FPGA_POWER,      //!< FPGA power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT4E2_PTP_DDR3_POWER,      //!< DDR3 RAM power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT4E2_PTP_FRONT_POWER,     //!< FRONT power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT4E2_PTP_SFP_0_POWER,     //!< SFP 0 power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT4E2_PTP_SFP_1_POWER,     //!< SFP 1 power consumption (calculated value) - does not generate alarms
  NT_SENSOR_NT4E2_PTP_ADAPTER_MAX,     //!< Number of NT4E2 adapter sensors
};

enum NtSensorsPortNT4E2_PTP_e {
  // Public sensors
  NT_SENSOR_NT4E2_PTP_SFP,             //!< SFP temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT4E2_PTP_SUPPLY,          //!< SFP supply voltage sensor - does not generate alarms
  NT_SENSOR_NT4E2_PTP_TX_BIAS,         //!< SFP TX bias current sensor - does not generate alarms
  NT_SENSOR_NT4E2_PTP_TX,              //!< SFP TX power sensor - does not generate alarms
  NT_SENSOR_NT4E2_PTP_RX,              //!< SFP RX power sensor - does not generate alarms
  NT_SENSOR_NT4E2_PTP_PORT_MAX,        //!< Number NT4E of port sensors
};

enum NtSensorsPortNT20E2_EL_e {
  // Public sensors
  NT_SENSOR_NT20E2_EL_NIM,             //!< SFP temperature sensor

  // Diagnostic sensors (Level 1)
  NT_SENSOR_NT20E2_EL_SUPPLY,          //!< SFP supply voltage sensor - does not generate alarms
  NT_SENSOR_NT20E2_EL_TX_BIAS,         //!< SFP TX bias current sensor - does not generate alarms
  NT_SENSOR_NT20E2_EL_TX,              //!< SFP TX power sensor - does not generate alarms
  NT_SENSOR_NT20E2_EL_RX,              //!< SFP RX power sensor - does not generate alarms
  NT_SENSOR_NT20E2_EL_PORT_MAX,        //!< Number of NT20E2 port sensors
};

enum NtPTPProfile_e {
  NT_PTP_PROFILE_DEFAULT = 0,          //!< PTP Default E2E Profile according to IEEE1588-2008
  NT_PTP_PROFILE_TELECOM,              //!< PTP Telecom Profile (ITU G.8265.1)
  NT_PTP_PROFILE_POWER,                //!< PTP Power Profile (IEEE C37.238)
  NT_PTP_PROFILE_COUNT
};

/**
 * Host loopback position.\n
 * The available loopback positions are adapter dependent and undocumented but
 * for each adapter a default host loopback position has been defined.
 * Therefore only the following values should be used.
 */
typedef enum NtHostLoopback_e {
  NT_HOST_LOOPBACK_NONE = 0,           //!< No host loopback
  NT_HOST_LOOPBACK_DEFAULT = INT_MAX,  //!< Default host loopback.
} NtHostLoopback_t;

/**
 * Stream-id state.
 * When a stream-id is in the active state traffic is forwarded to the stream-id by the adapter
 * When a stream-id is in the inactive state traffic is discarded by the adapter
 */
enum NtStreamIdState_e {
  NT_STREAM_ID_STATE_UNKNOWN,       //!< Unknown stream-id state
  NT_STREAM_ID_STATE_ACTIVE,        //!< Traffic is forwarded to the stream-id
  NT_STREAM_ID_STATE_INACTIVE,      //!< Traffic is dropped
};

#endif //__COMMONTYPES_H__
