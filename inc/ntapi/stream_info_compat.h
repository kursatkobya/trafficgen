// $Id: stream_info_compat.h 26768 2013-11-14 12:57:36Z ps $
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
 * This is the header file of the STREAMTYPE_INFO interface containing
 * included for backward compatibility structures.
 *
 */
#ifndef __STREAM_INFO_COMPAT_H__
#define __STREAM_INFO_COMPAT_H__

#if !defined(_NT_NTAPI_NO_COMPAT)

/***********************************************************************************************/
/*                               Adapter info version 0                                        */
/***********************************************************************************************/
#define NT_INFO_CMD_READ_ADAPTER NT_INFO_CMD_READ_COMPAT_0 //!< Adapter info - the number of sensors, ports, PCI ID and bus ID
/**
 * This structure will return the adapter specific info
 */
struct NtInfoAdapter_s {
  uint8_t numSensors;                      //!< The number of sensors on this adapter
  uint8_t Reserved1[3];
  uint8_t numLevel1Sensors;                //!< The number of level 1 sensors on this adapter
  uint8_t Reserved2[3];
  uint8_t portOffset;                      //!< The port numbers of this adapter start at this port offset
  uint8_t Reserved3[3];
  uint8_t numPorts;                        //!< The number of ports on this adapter
  uint8_t Reserved4[3];
  uint8_t numPhysicalAdapters;             //!< The number of physical adapters grouped in this virtual adapter
  uint8_t Reserved5[3];
  uint32_t numHostBuffersRx;               //!< The number of RX host buffers on this adapter
  uint32_t numHostBuffersTx;               //!< The number of TX host buffers on this adapter
  uint32_t numTsConnectors;                //!< The number of time sync connectors on this adapter
  enum NtAdapterType_e adapterType;        //!< The adapter type
  enum NtProductType_e productType;        //!< The product line type
  enum NtProfileType_e profile;            //!< The profile the adapter is using
  enum NtProductFamily_e productFamily;    //!< The product family
  char name[128];                          //!< The adapter name
  char serialNo[50];                       //!< The adapter serial number
  /**
   * AVR version for Gen2 adapters:
   *   avr[0] = Main board AVR,
   *   avr[1] = Front board AVR
   */
  struct NtversionAvr_s avr;
  /**
   * The bus ID is read as:
   *   32-bit value,
   *   4 x 8-bit values defining
   *      function,
   *      device,
   *      bus and
   *      slot
   */
  union Ntbusid_u {
    struct Ntbusid_s {
      uint32_t function:8; //!< The PCI function number
      uint32_t device:8;   //!< The PCI device number
      uint32_t bus:8;      //!< The PCI bus number
      uint32_t slot:8;     //!< The PCI slot number
    }s;
    uint32_t value;        //!< The slot, bus, device and function as a 32-bit value
  } busid;  

  /**
   * PCI  ID is read as:
   *   32-bit value,
   *   2 x 16-bit values defining
   *      device ID and
   *      vendor ID
   */
  union Ntpciid_u pciid;
  /**
   * The FPGA ID of the image currently running on the adapter.
   * The format is: item-product-version-revision-build.
   * For example, 200-9114-40-01-1023.
   */
  union Ntfpgaid_u fpgaid;
  uint32_t extendedDescriptor;                  //!< Is the adapter running with extended descriptors
  enum NtPacketDescriptorType_e descriptorType; //!< The descriptor type used
  enum NtTimestampType_e timestampType;         //!< The timestamp type used by the adapter
  enum NtTimestampMethod_e timestampMethod;     //!< The timestamp method (SOF/EOF) used by the adapter
};

/**
 * NT_INFO_CMD_READ_ADAPTER specific data.
 * The adapterNo must be initialized for the relevant adapter.
 */
struct NtInfoCmdAdapter_s {
  uint8_t adapterNo;           //!< The adapter to query
  uint8_t Reserved1[3];
  struct NtInfoAdapter_s data; //!< The adapter data
};

/***********************************************************************************************/
/*                               Adapter info version 1                                        */
/***********************************************************************************************/
#define NT_INFO_CMD_READ_ADAPTER_V1 NT_INFO_CMD_READ_COMPAT_5 //!< Adapter info - the number of sensors, ports, PCI ID and bus ID
/**
 * This structure will return the adapter specific info
 */
struct NtInfoAdapter_v1_s {
  uint8_t numSensors;                      //!< The number of sensors on this adapter
  uint8_t Reserved1[3];
  uint8_t numLevel1Sensors;                //!< The number of level 1 sensors on this adapter
  uint8_t Reserved2[3];
  uint8_t portOffset;                      //!< The port numbers of this adapter start at this port offset
  uint8_t Reserved3[3];
  uint8_t numPorts;                        //!< The number of ports on this adapter
  uint8_t Reserved4[3];
  uint8_t numPhysicalAdapters;             //!< The number of physical adapters grouped in this virtual adapter
  uint8_t Reserved5[3];
  uint32_t numHostBuffersRx;               //!< The number of RX host buffers on this adapter
  uint32_t numHostBuffersTx;               //!< The number of TX host buffers on this adapter
  uint32_t numTsConnectors;                //!< The number of time sync connectors on this adapter
  enum NtAdapterType_e adapterType;        //!< The adapter type
  enum NtProductType_e productType;        //!< The product line type
  enum NtProfileType_e profile;            //!< The profile the adapter is using
  uint32_t supportedProfilesBitmask;       //!< The profiles supported by the adapter - the value is represented as a bitmask of @ref NtProfileType_e values
  enum NtProductFamily_e productFamily;    //!< The product family
  char name[128];                          //!< The adapter name
  char serialNo[50];                       //!< The adapter serial number
  /**
   * AVR version for Gen2 adapters:
   *   avr[0] = Main board AVR,
   *   avr[1] = Front board AVR
   */
  struct NtversionAvr_s avr;
  /**
   * The bus ID is read as:
   *   32-bit value,
   *   4 x 8-bit values defining
   *      function,
   *      device,
   *      bus and
   *      slot
   */
  union Ntbusid_v1_u {
    struct Ntbusid_v1_s {
      uint32_t function:8; //!< The PCI function number
      uint32_t device:8;   //!< The PCI device number
      uint32_t bus:8;      //!< The PCI bus number
      uint32_t slot:8;     //!< The PCI domain number
    }s;
    uint32_t value;        //!< The domain, bus, device and function as a 32-bit value
  } busid;  
  /**
   * PCI  ID is read as:
   *   32-bit value,
   *   2 x 16-bit values defining
   *      device ID and
   *      vendor ID
   */
  union Ntpciid_u pciid;
  /**
   * The FPGA ID of the image currently running on the adapter.
   * The format is: item-product-version-revision-build.
   * For example, 200-9114-40-01-1023.
   */
  union Ntfpgaid_u fpgaid;
  uint32_t extendedDescriptor; //!< The extended descriptor in use by RX - if 0 then no extended is used
  uint32_t supportedExtendedDescriptorsBitmask; //!< Bitmask of supported extended descriptors, for example, if bit 7 is set then extended descriptor 7 is supported, and if bit 8 it set then extended descriptor 8 is supported
  enum NtPacketDescriptorType_e descriptorType; //!< The descriptor type used
  enum NtTimestampType_e timestampType;         //!< The time stamp type used by the adapter
  enum NtTimestampMethod_e timestampMethod;     //!< The time stamp method (SOF/EOF) used by the adapter

  enum NtTxTimingMethod_e txTiming;             //!< The TX timing
  struct NtInfoWis_s wisMode;
  enum NtTimestampInjectOffsetMode_e tsInjectModeOffset; //!< Time stamp injection offset mode
  struct NtInfoGlobalSync_s globalSync;         //!< Global sync status
};

/**
 * NT_INFO_CMD_READ_ADAPTER_V1 specific data.
 * The adapterNo must be initialized for the relevant adapter.
 */
struct NtInfoCmdAdapter_v1_s {
  uint8_t adapterNo;              //!< The adapter to query
  uint8_t Reserved1[3];
  struct NtInfoAdapter_v1_s data; //!< The adapter data
};

/***********************************************************************************************/
/*                               Adapter info version 2                                        */
/***********************************************************************************************/
#define NT_INFO_CMD_READ_ADAPTER_V2 NT_INFO_CMD_READ_COMPAT_7 //!< Adapter info - the number of sensors, ports, PCI ID and bus ID
/**
 * This structure will return the adapter specific info version 2.
 * Must be a mirror of NtInfoAdapter_s with version 2 variables added
 * to the bottom.
 */
struct NtInfoAdapter_v2_s {
  uint8_t numSensors;                      //!< The number of sensors on this adapter
  uint8_t Reserved1[3];
  uint8_t numLevel1Sensors;                //!< The number of level 1 sensors on this adapter
  uint8_t Reserved2[3];
  uint8_t portOffset;                      //!< The port numbers of this adapter start at this port offset
  uint8_t Reserved3[3];
  uint8_t numPorts;                        //!< The number of ports on this adapter
  uint8_t Reserved4[3];
  uint8_t numPhysicalAdapters;             //!< The number of physical adapters grouped in this virtual adapter
  uint8_t Reserved5[3];
  uint32_t numHostBuffersRx;               //!< The number of RX host buffers on this adapter
  uint32_t numHostBuffersTx;               //!< The number of TX host buffers on this adapter
  uint32_t numTsConnectors;                //!< The number of time sync connectors on this adapter
  enum NtAdapterType_e adapterType;        //!< The adapter type
  enum NtProductType_e productType;        //!< The product line type
  enum NtProfileType_e profile;            //!< The profile the adapter is using
  uint32_t supportedProfilesBitmask;       //!< The profiles supported by the adapter - the value is represented as a bitmask of @ref NtProfileType_e values
  uint32_t adapterFeatures;                //!< The features supported by the adapter - the value is represented as a bitmask of @ref NtFeatureType_e values
  enum NtProductFamily_e productFamily;    //!< The product family
  char name[128];                          //!< The adapter name
  char serialNo[50];                       //!< The adapter serial number
  /**
   * AVR version for Gen2 adapters:
   *   avr[0] = Main board AVR,
   *   avr[1] = Front board AVR
   */
  struct NtversionAvr_s avr;

  /**
   * The bus ID is read as:
   *   32-bit value,
   *   4 x 8-bit values defining
   *      function,
   *      device,
   *      bus and
   *      slot
   */
  union Ntbusid_v2_u {
    struct Ntbusid_v2_s {
      uint32_t function:8; //!< The PCI function number
      uint32_t device:8;   //!< The PCI device number
      uint32_t bus:8;      //!< The PCI bus number
      uint32_t slot:8;     //!< The PCI slot number
    }s;
    uint32_t value;        //!< The slot, bus, device and function as a 32-bit value
  } busid;  
  /**
   * PCI  ID is read as:
   *   32-bit value,
   *   2 x 16-bit values defining
   *      device ID and
   *      vendor ID
   */
  union Ntpciid_u pciid;
  struct NtInfoPCIeInfo_s pciInfo;              //!< Information about the PCI bus.
  /**
   * The FPGA ID of the image currently running on the adapter.
   * The format is: item-product-version-revision-build.
   * For example, 200-9114-40-01-1023.
   */
  union Ntfpgaid_u fpgaid;
  struct NtInfoSDRAMInfo_s sdramInfo;           //!< The SDRAM information
  uint32_t extendedDescriptor; //!< The extended descriptor in use by RX - if 0 then no extended is used
  uint32_t supportedExtendedDescriptorsBitmask; //!< Bitmask of supported extended descriptors, for example, if bit 7 is set then extended descriptor 7 is supported, and if bit 8 it set then extended descriptor 8 is supported
  enum NtPacketDescriptorType_e descriptorType; //!< The descriptor type used
  enum NtTimestampType_e timestampType;         //!< The time stamp type used by the adapter
  enum NtTimestampMethod_e timestampMethod;     //!< The time stamp method (SOF/EOF) used by the adapter
  enum NtTxTimingMethod_e txTiming;             //!< The TX timing
  struct NtInfoWis_s wisMode;
  enum NtTimestampInjectOffsetMode_e tsInjectModeOffset; //!< Time stamp injection offset mode
  struct NtInfoGlobalSync_s globalSync;         //!< Global sync status
};

/**
 * NT_INFO_CMD_READ_ADAPTER_V2 specific data.
 * The adapterNo must be initialized for the relevant adapter.
 */
struct NtInfoCmdAdapter_v2_s {
  uint8_t adapterNo;              //!< The adapter to query
  uint8_t Reserved1[3];
  struct NtInfoAdapter_v2_s data; //!< The adapter data
};

/***********************************************************************************************/
/*                               Port info version 0                                           */
/***********************************************************************************************/
#define NT_INFO_CMD_READ_PORT NT_INFO_CMD_READ_COMPAT_1  //!< Port info - the port state, speed and duplex
/**
 * This structure will return the port specific information
 */
typedef struct NtInfoPort_s {
  enum NtPortType_e type;     //!< The interface type
  enum NtLinkState_e state;   //!< The port up or down
  enum NtLinkSpeed_e speed;   //!< The interface speed
  enum NtLinkDuplex_e duplex; //!< The duplex mode
  int32_t flow;               //!< 0 = No flow control, 1 = Flow control
  enum NtLinkMDI_e mdi;       //!< 0 = auto, 1 = MDI, 2 = MDIX
  uint8_t macAddress[6];      //!< The MAC address of the interface
  uint16_t maxFrameSize;      //!< The current maximum frame size
  /**
   * Capabilities reflect what the port is capable of, that is what speed/duplex is possible. For example,
   * if only 100 M full duplex is available, the capabilities would
   * show:
   * halfDuplexMask=0.
   * fullDuplexMask=NT_LINK_SPEED_100M.
   * Other capabilities are min/max transmit sizes.
   */
  struct NtLinkCapabilities_s capabilities; //!< The link capabilities
  uint8_t adapterNo;             //!< The adapter that has the port
  uint8_t Reserved1[3];
  uint8_t numSensors;            //!< The number of sensors on this port
  uint8_t Reserved2[3];
  uint8_t numLevel1Sensors;      //!< Number of level 1 sensors on this port
  uint8_t Reserved3[3];
  uint8_t numLevel2Sensors;      //!< Number of level 2 sensors on this port
  uint8_t Reserved4[3];

  /**
   *  NIM model information
   */
  enum NtNimIdentifier_e nim_id; //!< NIM identifier
  uint8_t vendor_name[17];       //!< NIM Vendor name
  uint8_t product_no[17];        //!< NIM product number
  uint8_t serial_no[17];         //!< NIM serial number
  uint8_t date[9];               //!< NIM vendors manufacturing date
  uint8_t revision[5];           //!< NIM vendor revision
  uint8_t power_level_req;       //!< NIM required power level
  uint8_t power_level_curr;      //!< NIM current power level
  struct NtNIMLinkLength_s link_length;
} NtInfoPort_t;

/**
 * NT_INFO_CMD_READ_PORT specific data.
 * The portNo must be initialized for the relevant port.
 */
struct NtInfoCmdPort_s {
  uint8_t portNo;           //!< The port to query
  uint8_t Reserved1[3];
  struct NtInfoPort_s data; //!< The port data
};
/***********************************************************************************************/
/*                               Port info version 1                                           */
/***********************************************************************************************/
#define NT_INFO_CMD_READ_PORT_V1 NT_INFO_CMD_READ_COMPAT_6  //!< Port info - the port state, speed and duplex
/**
 * This structure will return the port specific information version 1.
 * Must be a mirror of NtInfoPort_s with version 1 variables added
 * to the bottom.
 */
struct NtInfoPort_v1_s {
  enum NtPortType_e type;     //!< The interface type
  enum NtLinkState_e state;   //!< The port up or down
  enum NtLinkSpeed_e speed;   //!< The interface speed
  enum NtLinkDuplex_e duplex; //!< The duplex mode
  int32_t flow;               //!< 0 = no flow control, 1 = flow control
  enum NtLinkMDI_e mdi;       //!< 1 = auto, 2 = MDI, 4 = MDIX
  uint8_t macAddress[6];      //!< The MAC address of the interface
  uint16_t maxFrameSize;      //!< The current maximum frame size
  /**
   * Capabilities reflect what the port is capable of, that is, what speed/duplex is possible. For example,
   * if only 100 M full duplex is available, the capabilities would
   * show:
   * halfDuplexMask=0.
   * fullDuplexMask=NT_LINK_SPEED_100M.
   * Other capabilities are min/max transmit sizes.
   */
  struct NtLinkCapabilities_s capabilities; //!< The link capabilities
  uint8_t adapterNo;             //!< The adapter that has the port
  uint8_t Reserved1[3];
  uint8_t numSensors;            //!< The number of sensors on this port
  uint8_t Reserved2[3];
  uint8_t numLevel1Sensors;      //!< Number of level 1 sensors on this port
  uint8_t Reserved3[3];
  uint8_t numLevel2Sensors;      //!< Number of level 2 sensors on this port
  uint8_t Reserved4[3];

  /**
   *  NIM model information
   */
  enum NtNimIdentifier_e nim_id; //!< NIM identifier
  uint8_t vendor_name[17];       //!< NIM Vendor name
  uint8_t product_no[17];        //!< NIM product number
  uint8_t serial_no[17];         //!< NIM serial number
  uint8_t date[9];               //!< NIM vendors manufacturing date
  uint8_t revision[5];           //!< NIM vendor revision
  uint8_t power_level_req;       //!< NIM required power level
  uint8_t power_level_curr;      //!< NIM current power level
  struct NtNIMLinkLength_s link_length;

  /**
   *  Adapter information
   */
  struct NtInfoAdapter_v1_s adapterInfo; // Adapter information
  /**
   * Bypass port information
   */
  struct NtBypassPortInfo_s bypass;   // Bypass port information
};

/**
 * NT_INFO_CMD_READ_PORT_V1 specific data.
 * The portNo must be initialized for the relevant port.
 */
struct NtInfoCmdPort_v1_s {
  uint8_t portNo;              //!< The port to query
  uint8_t Reserved1[3];
  struct NtInfoPort_v1_s data; //!< The port data
};


/***********************************************************************************************/
/*                               Port info version 2                                           */
/***********************************************************************************************/
#define NT_INFO_CMD_READ_PORT_V2 NT_INFO_CMD_READ_COMPAT_8  //!< Port info - the port state, speed and duplex
/**
 * This structure will return the port specific information version 2.
 * Must be a mirror of NtInfoPort_s with version 1 variables added
 * to the bottom.
 */
struct NtInfoPort_v2_s {
  enum NtPortType_e type;     //!< The interface type
  enum NtLinkState_e state;   //!< The port up or down
  enum NtLinkSpeed_e speed;   //!< The interface speed
  enum NtLinkDuplex_e duplex; //!< The duplex mode
  int32_t flow;               //!< 0 = no flow control, 1 = flow control
  enum NtLinkMDI_e mdi;       //!< 1 = auto, 2 = MDI, 4 = MDIX
  uint8_t macAddress[6];      //!< The MAC address of the interface
  uint16_t maxFrameSize;      //!< The current maximum frame size
  /**
   * Capabilities reflect what the port is capable of, that is, what speed/duplex is possible. For example,
   * if only 100 M full duplex is available, the capabilities would
   * show:
   * halfDuplexMask=0.
   * fullDuplexMask=NT_LINK_SPEED_100M.
   * Other capabilities are min/max transmit sizes.
   */
  struct NtLinkCapabilities_s capabilities; //!< The link capabilities
  uint8_t adapterNo;             //!< The adapter that has the port
  uint8_t Reserved1[3];
  uint8_t numSensors;            //!< The number of sensors on this port
  uint8_t Reserved2[3];
  uint8_t numLevel1Sensors;      //!< Number of level 1 sensors on this port
  uint8_t Reserved3[3];
  uint8_t numLevel2Sensors;      //!< Number of level 2 sensors on this port
  uint8_t Reserved4[3];

  /**
   *  NIM model information
   */
  enum NtNimIdentifier_e nim_id; //!< NIM identifier
  uint8_t vendor_name[17];       //!< NIM Vendor name
  uint8_t product_no[17];        //!< NIM product number
  uint8_t serial_no[17];         //!< NIM serial number
  uint8_t date[9];               //!< NIM vendors manufacturing date
  uint8_t revision[5];           //!< NIM vendor revision
  uint8_t power_level_req;       //!< NIM required power level
  uint8_t power_level_curr;      //!< NIM current power level
  struct NtNIMLinkLength_s link_length;

  /**
   *  Adapter information
   */
  struct NtInfoAdapter_v2_s adapterInfo; // Adapter information
  /**
   * Bypass port information
   */
  struct NtBypassPortInfo_s bypass;   // Bypass port information
};

/**
 * NT_INFO_CMD_READ_PORT_V2 specific data.
 * The portNo must be initialized for the relevant port.
 */
struct NtInfoCmdPort_v2_s {
  uint8_t portNo;              //!< The port to query
  uint8_t Reserved1[3];
  struct NtInfoPort_v2_s data; //!< The port data
};

/***********************************************************************************************/
/* Time sync version 0                                                                         */
/***********************************************************************************************/
#define NT_INFO_CMD_READ_TIMESYNC NT_INFO_CMD_READ_COMPAT_2      //!< Time sync info - the time sync connector and time sync data

struct NtInfoTimeSync_s {
  uint32_t timeSyncSupported;         //!< Is the time sync supported by this adapter
  uint32_t timeSyncProtocol;          //!< The time sync protocol
  uint32_t timeSyncPpsEnable;         //!< The time sync PPS enable
  uint32_t timeSyncConnectorIn;       //!< The time sync input connector
  uint32_t timeSyncConnectorOut;      //!< The time sync output connectors
  uint32_t timeSyncConnectorRepeat;   //!< The time sync repeater connectors
  uint32_t timeSyncTimeJumpThreshold; //!< The time sync time jump threshold in seconds
  uint32_t timeSyncTimeOffset;        //!< The time sync offset in nanoseconds
  uint64_t timeSyncPpsSampled;        //!< The sampled PPS time (0 if not applicable)
  int64_t timeSyncTimeSkew;           //!< The time skew
  uint32_t timeSyncStatus;            //!< The time sync status
};

/**
 * NT_INFO_CMD_READ_TIMESYNC specific data.
 * The adapterNo must be initialized for the relevant adapter.
 */
struct NtInfoCmdTimeSync_s {
  uint8_t adapterNo;            //!< The adapter to query
  uint8_t Reserved1[3];
  struct NtInfoTimeSync_s data; //!< The time sync data
};

#define NT_INFO_CMD_READ_TIMESYNC_V1 NT_INFO_CMD_READ_COMPAT_4      //!< Time sync info - the time sync connector and time sync data

/**
 * Time sync status
 */
enum NtTimeSyncStatus_e {
  NT_TIMESYNC_STATUS_NONE = 0,         //!< Time sync status unused
  NT_TIMESYNC_STATUS_SIGNAL_LOST,      //!< Time sync signal lost (NT and PPS)
  NT_TIMESYNC_STATUS_SIGNAL_PRESENT,   //!< Time sync signal present (NT and PPS)
  NT_TIMESYNC_STATUS_OS_SYNCING,       //!< OS time sync synching (OS only)
  NT_TIMESYNC_STATUS_OS_IN_SYNC,       //!< OS time sync in synchronization (OS only)
};

/**
 * Time sync OS Failover status
 */
enum NtTimeSyncOSFailoverStatus_e {
  NT_TIMESYNC_OS_FAILOVER_STATUS_DISABLED = 0,
  NT_TIMESYNC_OS_FAILOVER_STATUS_INIT     = 1,
  NT_TIMESYNC_OS_FAILOVER_STATUS_WAITING  = 2,
  NT_TIMESYNC_OS_FAILOVER_STATUS_ACTIVE   = 3,
};

/**
 * Time sync specific info V1
 */
struct NtInfoTimeSync_v1_s {
  uint32_t timeSyncSupported;                   //!< Is the time sync supported by this adapter
  enum NtTimeSyncProtocol_e timeSyncProtocol;   //!< The time sync protocol
  enum NtTimeSyncPpsStatus_e timeSyncPpsEnable; //!< The time sync PPS enable
  uint32_t timeSyncConnectorIn;                 //!< The time sync input connector
  uint32_t timeSyncConnectorOut;                //!< The time sync output connectors
  uint32_t timeSyncConnectorRepeat;             //!< The time sync repeater connectors
  uint32_t timeSyncTimeJumpThreshold;           //!< The time sync time jump threshold in seconds
  uint32_t timeSyncTimeOffset;                  //!< The time sync offset in nanoseconds
  uint64_t timeSyncPpsSampled;                  //!< The sampled PPS time (0 if not applicable)
  int64_t  timeSyncTimeSkew;                    //!< The time skew
  enum NtTimeSyncStatus_e timeSyncStatus;       //!< The time sync status
  uint32_t osTimeSyncFailoverEnable;            //!< The OS time sync failover enable
  uint32_t osTimeSyncFailoverStatus;            //!< The OS time sync failover status
  uint32_t highFrequencySampling;               //!< The high frequency sampling status
  uint64_t adapterTime;                         //!< The sampled adapter time
  uint64_t externalTime;                        //!< The sampled external time
  uint32_t timeSyncConnectorPpsOut;             //!< The time sync PPS out connector
};
/**
 * NT_INFO_CMD_READ_TIMESYNC_V1 specific data.
 * The adapterNo must be initialized for the relevant adapter.
 */
struct NtInfoCmdTimeSync_v1_s {
  uint8_t adapterNo;               //!< The adapter to query
  uint8_t Reserved1[3];
  struct NtInfoTimeSync_v1_s data; //!< The time sync data
};




/***********************************************************************************************/
/* Hostbuffer info version 0                                                                   */
/***********************************************************************************************/
#define NT_INFO_CMD_READ_HOSTBUFFER NT_INFO_CMD_READ_COMPAT_3  //!< Host buffer info - the NUMA node, size and feed
/**
 * NT_INFO_CMD_READ_PORT_V1 specific data.
 * The portNo must be initialized for the relevant port.
 */
struct NtInfoHostBuffer_s {
  uint8_t numaNode;  //!< The NUMA node on which the host buffer resides
  uint8_t Reserved1[3];
  uint32_t size;     //!< The size of the host buffer in bytes
  uint32_t feed;     //!< The feed index per adapter and type
};

/**
 * NT_INFO_CMD_READ_HOSTBUFFER specific data.
 * The adapterNo, hostBufferNo and hostBufferType must be initialized for the relevant adapter, host buffer number and host buffer type.
 */
struct NtInfoCmdHostBuffer_s {
  uint8_t adapterNo;                         //!< The adapter to query
  uint8_t Reserved1[3];
  uint32_t hostBufferNo;                     //!< The host buffer to query
  enum NtNetHostBufferType_e hostBufferType; //!< The host buffer type, that is, CAPTURE or TX
  struct NtInfoHostBuffer_s data;            //!< The host buffer data
};

/***********************************************************************************************/



/***********************************************************************************************/
/* PTP info version 0                                                                          */
/***********************************************************************************************/
#define NT_INFO_CMD_READ_PTP  NT_INFO_CMD_READ_COMPAT_9

struct NtInfoPTP_s {
  bool                    enabled;     //!< Is PTP stack configured to be used (slave, master or ptp pps sampling)
  struct NtPTPTimestamp_s ts;          //!< Timestamp at this info retrieval
  struct NtPTPPort_s      ptpPort;     //!< PTP port information structure
  struct NtPTPDataSets_s  ptpDataSets; //!< PTP data sets (according to IEEE1588-2008 spec.)
  struct NtPTPPortStat_s  ptpPortStat; //!< PTP ethernet port statistics
  struct NtPTPSyncStat_s  stat;        //!< In slave mode, stat holds the timesync statistics
};
/**
 * NT_INFO_CMD_READ_PTP specific data.
 */
struct NtInfoCmdPTP_s {
  uint8_t adapterNo;               //!< The adapter to query
  uint8_t Reserved1[2];
  struct NtInfoPTP_s data;         //!< Query PTP information structure
};



#endif /* _NT_NTAPI_NO_COMPAT */
#endif /* __STREAM_INFO_COMPAT_H__ */


