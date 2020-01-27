//=============================================================================
// Copyright © 2017 FLIR Integrated Imaging Solutions, Inc. All Rights Reserved.
//
// This software is the confidential and proprietary information of FLIR
// Integrated Imaging Solutions, Inc. ("Confidential Information"). You
// shall not disclose such Confidential Information and shall use it only in
// accordance with the terms of the license agreement you entered into
// with FLIR Integrated Imaging Solutions, Inc. (FLIR).
//
// FLIR MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT. FLIR SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================
//=============================================================================
// $Id: FlyCapture2Defs_C.h,v 1.74 2010-12-13 23:58:00 mgara Exp $
//=============================================================================

#ifndef PGR_FC2_FLYCAPTURE2DEFS_C_H
#define PGR_FC2_FLYCAPTURE2DEFS_C_H

#include <stdlib.h>

//=============================================================================
// Definitions header file for FlyCapture2 C API.
//
// Holds enumerations, typedefs and structures that are used across the
// FlyCapture2 C API wrapper.
//
// Please see FlyCapture2Defs.h or the API documentation for full details
// of the various enumerations and structures.
//=============================================================================

#ifdef __cplusplus
extern "C"
{
#endif

	/**
	 * @defgroup CTypeDefs TypeDefs
	 */

	/*@{*/

	typedef int BOOL;

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

#ifndef FULL_32BIT_VALUE
#define FULL_32BIT_VALUE 0x7FFFFFFF
#endif

#define MAX_STRING_LENGTH   512

	/**
	 * A context to the FlyCapture2 C library. It must be created before
	 * performing any calls to the library.
	 */
	typedef void* fc2Context;

	/**
	 * A context to the FlyCapture2 C GUI library. It must be created before
	 * performing any calls to the library.
	 */
	typedef void* fc2GuiContext;

	/**
	 * An internal pointer used in the fc2Image structure.
	 */
	typedef void* fc2ImageImpl;

	/**
	 * A context referring to the AVI recorder object.
	 */
	typedef void* fc2AVIContext;

	/**
	 * A context referring to the ImageStatistics object.
	 */
	typedef void* fc2ImageStatisticsContext;

	/**
	 * A context referring to the TopologyNode object.
	 */
	typedef void* fc2TopologyNodeContext;

	/**
	 * A GUID to the camera.  It is used to uniquely identify a camera.
	 */
	typedef struct _fc2PGRGuid
	{
		unsigned int value[4];

	} fc2PGRGuid;

	/*@}*/

	/**
	 * @defgroup CEnumerations Enumerations
	 */

	/*@{*/

	/** The error types returned by functions. */
	typedef enum _fc2Error
	{
		FC2_ERROR_UNDEFINED = -1, /**< Undefined */
		FC2_ERROR_OK, /**< Function returned with no errors. */
		FC2_ERROR_FAILED, /**< General failure. */
		FC2_ERROR_NOT_IMPLEMENTED, /**< Function has not been implemented. */
		FC2_ERROR_FAILED_BUS_MASTER_CONNECTION, /**< Could not connect to Bus Master. */
		FC2_ERROR_NOT_CONNECTED, /**< Camera has not been connected. */
		FC2_ERROR_INIT_FAILED, /**< Initialization failed. */
		FC2_ERROR_NOT_INTITIALIZED, /**< Camera has not been initialized. */
		FC2_ERROR_INVALID_PARAMETER, /**< Invalid parameter passed to function. */
		FC2_ERROR_INVALID_SETTINGS, /**< Setting set to camera is invalid. */
		FC2_ERROR_INVALID_BUS_MANAGER, /**< Invalid Bus Manager object. */
		FC2_ERROR_MEMORY_ALLOCATION_FAILED, /**< Could not allocate memory. */
		FC2_ERROR_LOW_LEVEL_FAILURE, /**< Low level error. */
		FC2_ERROR_NOT_FOUND, /**< Device not found. */
		FC2_ERROR_FAILED_GUID, /**< GUID failure. */
		FC2_ERROR_INVALID_PACKET_SIZE, /**< Packet size set to camera is invalid. */
		FC2_ERROR_INVALID_MODE, /**< Invalid mode has been passed to function. */
		FC2_ERROR_NOT_IN_FORMAT7, /**< Error due to not being in Format7. */
		FC2_ERROR_NOT_SUPPORTED, /**< This feature is unsupported. */
		FC2_ERROR_TIMEOUT, /**< Timeout error. */
		FC2_ERROR_BUS_MASTER_FAILED, /**< Bus Master Failure. */
		FC2_ERROR_INVALID_GENERATION, /**< Generation Count Mismatch. */
		FC2_ERROR_LUT_FAILED, /**< Look Up Table failure. */
		FC2_ERROR_IIDC_FAILED, /**< IIDC failure. */
		FC2_ERROR_STROBE_FAILED, /**< Strobe failure. */
		FC2_ERROR_TRIGGER_FAILED, /**< Trigger failure. */
		FC2_ERROR_PROPERTY_FAILED, /**< Property failure. */
		FC2_ERROR_PROPERTY_NOT_PRESENT, /**< Property is not present. */
		FC2_ERROR_REGISTER_FAILED, /**< Register access failed. */
		FC2_ERROR_READ_REGISTER_FAILED, /**< Register read failed. */
		FC2_ERROR_WRITE_REGISTER_FAILED, /**< Register write failed. */
		FC2_ERROR_ISOCH_FAILED, /**< Isochronous failure. */
		FC2_ERROR_ISOCH_ALREADY_STARTED, /**< Isochronous transfer has already been started. */
		FC2_ERROR_ISOCH_NOT_STARTED, /**< Isochronous transfer has not been started. */
		FC2_ERROR_ISOCH_START_FAILED, /**< Isochronous start failed. */
		FC2_ERROR_ISOCH_RETRIEVE_BUFFER_FAILED, /**< Isochronous retrieve buffer failed. */
		FC2_ERROR_ISOCH_STOP_FAILED, /**< Isochronous stop failed. */
		FC2_ERROR_ISOCH_SYNC_FAILED, /**< Isochronous image synchronization failed. */
		FC2_ERROR_ISOCH_BANDWIDTH_EXCEEDED, /**< Isochronous bandwidth exceeded. */
		FC2_ERROR_IMAGE_CONVERSION_FAILED, /**< Image conversion failed. */
		FC2_ERROR_IMAGE_LIBRARY_FAILURE, /**< Image library failure. */
		FC2_ERROR_BUFFER_TOO_SMALL, /**< Buffer is too small. */
		FC2_ERROR_IMAGE_CONSISTENCY_ERROR, /**< There is an image consistency error. */
		FC2_ERROR_INCOMPATIBLE_DRIVER, /**< The installed driver is not compatible with the library. */
		FC2_ERROR_FORCE_32BITS = FULL_32BIT_VALUE

	} fc2Error;

	/** The type of bus callback to register a callback function for. */
	typedef enum _fc2BusCallbackType
	{
		FC2_BUS_RESET, /**< Register for all bus events. */
		FC2_ARRIVAL, /**< Register for arrivals only. */
		FC2_REMOVAL, /**< Register for removals only. */
		FC2_CALLBACK_TYPE_FORCE_32BITS = FULL_32BIT_VALUE

	} fc2BusCallbackType;

	/**
	 * The grab strategy employed during image transfer. This type controls
	 * how images that stream off the camera accumulate in a user buffer
	 * for handling.
	 */
	/*
	   @remark Unlike earlier versions of the FlyCapture SDK, it is no longer
	 * necessary to explicitly start the image grabbing process before
	 * specifying an image grabbing mode.
	 */
	typedef enum _fc2GrabMode
	{
		/**
		 * Grabs the newest image in the user buffer each time the
		 * RetrieveBuffer() function is called. Older images are dropped
		 * instead of accumulating in the user buffer. Grabbing blocks if the
		 * camera has not finished transmitting the next available image. If
		 * the camera is transmitting images faster than the application can
		 * grab them, images may be dropped and only the most recent image
		 * is stored for grabbing. Note that this mode is the equivalent of
		 * flycaptureLockLatest in earlier versions of the FlyCapture SDK.
		 */
		FC2_DROP_FRAMES,

		/**
		 * Images accumulate in the user buffer, and the oldest image is
		 * grabbed for handling before being discarded. This member can be
		 * used to guarantee that each image is seen. However, image processing
		 * time must not exceed transmission time from the camera to the
		 * buffer. Grabbing blocks if the camera has not finished transmitting
		 * the next available image. The buffer size is controlled by the
		 * numBuffers parameter in the FC2Config struct. Note that this mode is
		 * the equivalent of flycaptureLockNext in earlier versions of the
		 * FlyCapture SDK.
		 */
		FC2_BUFFER_FRAMES,

		/**
		 * Unspecified grab mode.
		 */
		FC2_UNSPECIFIED_GRAB_MODE,
		FC2_GRAB_MODE_FORCE_32BITS = FULL_32BIT_VALUE

	} fc2GrabMode;

	/** Timeout options for grabbing images. */
	typedef enum _fc2GrabTimeout
	{
		FC2_TIMEOUT_NONE = 0, /**< Non-blocking wait. */
		FC2_TIMEOUT_INFINITE = -1, /**< Wait indefinitely. */
		FC2_TIMEOUT_UNSPECIFIED = -2, /**< Unspecified timeout setting. */
		FC2_GRAB_TIMEOUT_FORCE_32BITS = FULL_32BIT_VALUE

	} fc2GrabTimeout;

	/** Bandwidth allocation options for 1394 devices. */
	typedef enum _fc2BandwidthAllocation
	{
		/** Do not allocate bandwidth. */
		FC2_BANDWIDTH_ALLOCATION_OFF = 0,
		/** Allocate bandwidth. This is the default setting. */
		FC2_BANDWIDTH_ALLOCATION_ON = 1,
		/**
		 * Bandwidth allocation is not supported by either the camera or
		 * operating system.
		 */
		FC2_BANDWIDTH_ALLOCATION_UNSUPPORTED = 2,
		/** Not specified. This leaves the current setting unchanged. */
		FC2_BANDWIDTH_ALLOCATION_UNSPECIFIED = 3,
		FC2_BANDWIDTH_ALLOCATION_FORCE_32BITS = FULL_32BIT_VALUE

	}fc2BandwidthAllocation;

	/** Interfaces that a camera may use to communicate with a host. */
	typedef enum _fc2InterfaceType
	{
		FC2_INTERFACE_IEEE1394, /**< IEEE-1394 (Includes 1394a and 1394b). */
		FC2_INTERFACE_USB_2, /**< USB 2.0. */
		FC2_INTERFACE_USB_3, /**< USB 3.0. */
		FC2_INTERFACE_GIGE, /**< GigE. */
		FC2_INTERFACE_UNKNOWN, /**< Unknown interface. */
		FC2_INTERFACE_TYPE_FORCE_32BITS = FULL_32BIT_VALUE

	} fc2InterfaceType;

	/**
	 * Camera properties. Not all properties may be supported, depending
	 * on the camera model.
	 */
	typedef enum _fc2PropertyType
	{
		FC2_BRIGHTNESS,
		FC2_AUTO_EXPOSURE,
		FC2_SHARPNESS,
		FC2_WHITE_BALANCE,
		FC2_HUE,
		FC2_SATURATION,
		FC2_GAMMA,
		FC2_IRIS,
		FC2_FOCUS,
		FC2_ZOOM,
		FC2_PAN,
		FC2_TILT,
		FC2_SHUTTER,
		FC2_GAIN,
		FC2_TRIGGER_MODE,
		FC2_TRIGGER_DELAY,
		FC2_FRAME_RATE,
		FC2_TEMPERATURE,
		FC2_UNSPECIFIED_PROPERTY_TYPE,
		FC2_PROPERTY_TYPE_FORCE_32BITS = FULL_32BIT_VALUE

	} fc2PropertyType;

	/** Frame rates in frames per second. */
	typedef enum _fc2FrameRate
	{
		FC2_FRAMERATE_1_875, /**< 1.875 fps. */
		FC2_FRAMERATE_3_75, /**< 3.75 fps. */
		FC2_FRAMERATE_7_5, /**< 7.5 fps. */
		FC2_FRAMERATE_15, /**< 15 fps. */
		FC2_FRAMERATE_30, /**< 30 fps. */
		FC2_FRAMERATE_60, /**< 60 fps. */
		FC2_FRAMERATE_120, /**< 120 fps. */
		FC2_FRAMERATE_240, /**< 240 fps. */
		FC2_FRAMERATE_FORMAT7, /**< Custom frame rate for Format7 functionality. */
		FC2_NUM_FRAMERATES, /**< Number of possible camera frame rates. */
		FC2_FRAMERATE_FORCE_32BITS = FULL_32BIT_VALUE

	} fc2FrameRate;

	/** DCAM video modes. */
	typedef enum _fc2VideoMode
	{
		FC2_VIDEOMODE_160x120YUV444, /**< 160x120 YUV444. */
		FC2_VIDEOMODE_320x240YUV422, /**< 320x240 YUV422. */
		FC2_VIDEOMODE_640x480YUV411, /**< 640x480 YUV411. */
		FC2_VIDEOMODE_640x480YUV422, /**< 640x480 YUV422. */
		FC2_VIDEOMODE_640x480RGB, /**< 640x480 24-bit RGB. */
		FC2_VIDEOMODE_640x480Y8, /**< 640x480 8-bit. */
		FC2_VIDEOMODE_640x480Y16, /**< 640x480 16-bit. */
		FC2_VIDEOMODE_800x600YUV422, /**< 800x600 YUV422. */
		FC2_VIDEOMODE_800x600RGB, /**< 800x600 RGB. */
		FC2_VIDEOMODE_800x600Y8, /**< 800x600 8-bit. */
		FC2_VIDEOMODE_800x600Y16, /**< 800x600 16-bit. */
		FC2_VIDEOMODE_1024x768YUV422, /**< 1024x768 YUV422. */
		FC2_VIDEOMODE_1024x768RGB, /**< 1024x768 RGB. */
		FC2_VIDEOMODE_1024x768Y8, /**< 1024x768 8-bit. */
		FC2_VIDEOMODE_1024x768Y16, /**< 1024x768 16-bit. */
		FC2_VIDEOMODE_1280x960YUV422, /**< 1280x960 YUV422. */
		FC2_VIDEOMODE_1280x960RGB, /**< 1280x960 RGB. */
		FC2_VIDEOMODE_1280x960Y8, /**< 1280x960 8-bit. */
		FC2_VIDEOMODE_1280x960Y16, /**< 1280x960 16-bit. */
		FC2_VIDEOMODE_1600x1200YUV422, /**< 1600x1200 YUV422. */
		FC2_VIDEOMODE_1600x1200RGB, /**< 1600x1200 RGB. */
		FC2_VIDEOMODE_1600x1200Y8, /**< 1600x1200 8-bit. */
		FC2_VIDEOMODE_1600x1200Y16, /**< 1600x1200 16-bit. */
		FC2_VIDEOMODE_FORMAT7, /**< Custom video mode for Format7 functionality. */
		FC2_NUM_VIDEOMODES, /**< Number of possible video modes. */
		FC2_VIDEOMODE_FORCE_32BITS = FULL_32BIT_VALUE

	} fc2VideoMode;

	/** Camera modes for DCAM formats as well as Format7. */
	typedef enum _fc2Mode
	{
		FC2_MODE_0 = 0,
		FC2_MODE_1,
		FC2_MODE_2,
		FC2_MODE_3,
		FC2_MODE_4,
		FC2_MODE_5,
		FC2_MODE_6,
		FC2_MODE_7,
		FC2_MODE_8,
		FC2_MODE_9,
		FC2_MODE_10,
		FC2_MODE_11,
		FC2_MODE_12,
		FC2_MODE_13,
		FC2_MODE_14,
		FC2_MODE_15,
		FC2_MODE_16,
		FC2_MODE_17,
		FC2_MODE_18,
		FC2_MODE_19,
		FC2_MODE_20,
		FC2_MODE_21,
		FC2_MODE_22,
		FC2_MODE_23,
		FC2_MODE_24,
		FC2_MODE_25,
		FC2_MODE_26,
		FC2_MODE_27,
		FC2_MODE_28,
		FC2_MODE_29,
		FC2_MODE_30,
		FC2_MODE_31,
		FC2_NUM_MODES, /**< Number of modes */
		FC2_MODE_FORCE_32BITS = FULL_32BIT_VALUE

	} fc2Mode;

	/** Pixel formats available for Format7 modes. */
	typedef enum _fc2PixelFormat
	{
		FC2_PIXEL_FORMAT_MONO8			= 0x80000000, /**< 8 bits of mono information. */
		FC2_PIXEL_FORMAT_411YUV8		= 0x40000000, /**< YUV 4:1:1. */
		FC2_PIXEL_FORMAT_422YUV8		= 0x20000000, /**< YUV 4:2:2. */
		FC2_PIXEL_FORMAT_444YUV8		= 0x10000000, /**< YUV 4:4:4. */
		FC2_PIXEL_FORMAT_RGB8			= 0x08000000, /**< R = G = B = 8 bits. */
		FC2_PIXEL_FORMAT_MONO16			= 0x04000000, /**< 16 bits of mono information. */
		FC2_PIXEL_FORMAT_RGB16			= 0x02000000, /**< R = G = B = 16 bits. */
		FC2_PIXEL_FORMAT_S_MONO16		= 0x01000000, /**< 16 bits of signed mono information. */
		FC2_PIXEL_FORMAT_S_RGB16		= 0x00800000, /**< R = G = B = 16 bits signed. */
		FC2_PIXEL_FORMAT_RAW8			= 0x00400000, /**< 8 bit raw data output of sensor. */
		FC2_PIXEL_FORMAT_RAW16			= 0x00200000, /**< 16 bit raw data output of sensor. */
		FC2_PIXEL_FORMAT_MONO12			= 0x00100000, /**< 12 bits of mono information. */
		FC2_PIXEL_FORMAT_RAW12			= 0x00080000, /**< 12 bit raw data output of sensor. */
		FC2_PIXEL_FORMAT_BGR			= 0x80000008, /**< 24 bit BGR. */
		FC2_PIXEL_FORMAT_BGRU			= 0x40000008, /**< 32 bit BGRU. */
		FC2_PIXEL_FORMAT_RGB			= FC2_PIXEL_FORMAT_RGB8, /**< 24 bit RGB. */
		FC2_PIXEL_FORMAT_RGBU			= 0x40000002, /**< 32 bit RGBU. */
		FC2_PIXEL_FORMAT_BGR16			= 0x02000001, /**< R = G = B = 16 bits. */
		FC2_PIXEL_FORMAT_BGRU16			= 0x02000002, /**< 64 bit BGRU. */
		FC2_PIXEL_FORMAT_422YUV8_JPEG	= 0x40000001, /**< JPEG compressed stream. */
		FC2_NUM_PIXEL_FORMATS			=  20, /**< Number of pixel formats. */
		FC2_UNSPECIFIED_PIXEL_FORMAT	= 0 /**< Unspecified pixel format. */

	} fc2PixelFormat;

	/** Bus speeds. */
	typedef enum _fc2BusSpeed
	{
		FC2_BUSSPEED_S100, /**< 100Mbits/sec. */
		FC2_BUSSPEED_S200, /**< 200Mbits/sec. */
		FC2_BUSSPEED_S400, /**< 400Mbits/sec. */
		FC2_BUSSPEED_S480, /**< 480Mbits/sec. Only for USB2 cameras. */
		FC2_BUSSPEED_S800, /**< 800Mbits/sec. */
		FC2_BUSSPEED_S1600, /**< 1600Mbits/sec. */
		FC2_BUSSPEED_S3200, /**< 3200Mbits/sec. */
		FC2_BUSSPEED_S5000, /**< 5000Mbits/sec. Only for USB3 cameras. */
		FC2_BUSSPEED_10BASE_T, /**< 10Base-T. Only for GigE cameras. */
		FC2_BUSSPEED_100BASE_T, /**< 100Base-T.  Only for GigE cameras.*/
		FC2_BUSSPEED_1000BASE_T, /**< 1000Base-T (Gigabit Ethernet).  Only for GigE cameras. */
		FC2_BUSSPEED_10000BASE_T, /**< 10000Base-T.  Only for GigE cameras. */
		FC2_BUSSPEED_S_FASTEST, /**< The fastest speed available. */
		FC2_BUSSPEED_ANY, /**< Any speed that is available. */
		FC2_BUSSPEED_SPEED_UNKNOWN = -1, /**< Unknown bus speed. */
		FC2_BUSSPEED_FORCE_32BITS = FULL_32BIT_VALUE

	} fc2BusSpeed;

	typedef enum _fc2PCIeBusSpeed
	{
		FC2_PCIE_BUSSPEED_2_5, /** 2.5 Gb/s */
		FC2_PCIE_BUSSPEED_5_0, /** 5.0 Gb/s */
		FC2_PCIE_BUSSPEED_UNKNOWN = -1, /** Speed is unknown */
		FC2_PCIE_BUSSPEED_FORCE_32BITS = FULL_32BIT_VALUE
	} fc2PCIeBusSpeed;

	/** Types of low level drivers that FlyCapture uses. */
	typedef enum _fc2DriverType
	{
		FC2_DRIVER_1394_CAM, /**< PGRCam.sys. */
		FC2_DRIVER_1394_PRO, /**< PGR1394.sys. */
		FC2_DRIVER_1394_JUJU, /**< firewire_core. */
		FC2_DRIVER_1394_VIDEO1394, /**< video1394. */
		FC2_DRIVER_1394_RAW1394, /**< raw1394. */
		FC2_DRIVER_USB_NONE, /**< No usb driver used just BSD stack. (Linux only) */
		FC2_DRIVER_USB_CAM, /**< PGRUsbCam.sys. */
		FC2_DRIVER_USB3_PRO, /**< PGRXHCI.sys. */
		FC2_DRIVER_GIGE_NONE, /**< no GigE drivers used, MS/BSD stack. */
		FC2_DRIVER_GIGE_FILTER, /**< PGRGigE.sys. */
		FC2_DRIVER_GIGE_PRO, /**< PGRGigEPro.sys. */
		FC2_DRIVER_GIGE_LWF, /**< PgrLwf.sys. */
		FC2_DRIVER_UNKNOWN = -1, /**< Unknown driver type. */
		FC2_DRIVER_FORCE_32BITS = FULL_32BIT_VALUE
	} fc2DriverType;

	/**
	 * Color processing algorithms. Please refer to our knowledge base at
	 * article at http://www.ptgrey.com/support/kb/index.asp?a=4&q=33 for
	 * complete details for each algorithm.
	 */
	typedef enum _fc2ColorProcessingAlgorithm
	{
		/** Default method. */
		FC2_DEFAULT,
		/** No color processing. */
		FC2_NO_COLOR_PROCESSING,
		/**
		 * Fastest but lowest quality. Equivalent to
		 * FLYCAPTURE_NEAREST_NEIGHBOR_FAST in FlyCapture.
		 */
		FC2_NEAREST_NEIGHBOR_FAST,
		/** Weights surrounding pixels based on localized edge orientation. */
		FC2_EDGE_SENSING,
		/** Well-balanced speed and quality. */
		FC2_HQ_LINEAR,
		/** Slowest but produces good results. */
		FC2_RIGOROUS,
		/** Multithreaded with similar results to edge sensing. */
		FC2_IPP,
		/** Best quality but much faster than rigorous. */
		FC2_DIRECTIONAL,
		/** Weighted pixel average from different directions*/
		FC2_WEIGHTED_DIRECTIONAL,
		FC2_COLOR_PROCESSING_ALGORITHM_FORCE_32BITS = FULL_32BIT_VALUE

	} fc2ColorProcessingAlgorithm;

	/** Bayer tile formats. */
	typedef enum _fc2BayerTileFormat
	{
		FC2_BT_NONE, /**< No bayer tile format. */
		FC2_BT_RGGB, /**< Red-Green-Green-Blue. */
		FC2_BT_GRBG, /**< Green-Red-Blue-Green. */
		FC2_BT_GBRG, /**< Green-Blue-Red-Green. */
		FC2_BT_BGGR, /**< Blue-Green-Green-Red. */
		FC2_BT_FORCE_32BITS = FULL_32BIT_VALUE

	} fc2BayerTileFormat;

	/** File formats to be used for saving images to disk. */
	typedef enum _fc2ImageFileFormat
	{
		FC2_FROM_FILE_EXT = -1, /**< Determine file format from file extension. */
		FC2_PGM, /**< Portable gray map. */
		FC2_PPM, /**< Portable pixmap. */
		FC2_BMP, /**< Bitmap. */
		FC2_JPEG, /**< JPEG. */
		FC2_JPEG2000, /**< JPEG 2000. */
		FC2_TIFF, /**< Tagged image file format. */
		FC2_PNG, /**< Portable network graphics. */
		FC2_RAW, /**< Raw data. */
		FC2_IMAGE_FILE_FORMAT_FORCE_32BITS = FULL_32BIT_VALUE

	} fc2ImageFileFormat;

	/*@}*/

	/**
	 * @defgroup CGigEEnums GigE specific enumerations
	 *
	 * These enumerations are specific to GigE camera operation only.
	 */

	/*@{*/

	/** Possible properties that can be queried from the camera. */
	typedef enum _fc2GigEPropertyType
	{
		FC2_HEARTBEAT,
		FC2_HEARTBEAT_TIMEOUT,
		PACKET_SIZE,
		PACKET_DELAY

	} fc2GigEPropertyType;

	/*@}*/

	/**
	 * Channels that allow statistics to be calculated.
	 */
	typedef enum _fc2StatisticsChannel
	{
		FC2_STATISTICS_GREY,
		FC2_STATISTICS_RED,
		FC2_STATISTICS_GREEN,
		FC2_STATISTICS_BLUE,
		FC2_STATISTICS_HUE,
		FC2_STATISTICS_SATURATION,
		FC2_STATISTICS_LIGHTNESS,
		FC2_STATISTICS_FORCE_32BITS = FULL_32BIT_VALUE
	} fc2StatisticsChannel;

	/** Possible operating systems. */
	typedef enum _fc2OSType
	{
		FC2_WINDOWS_X86, /**< All Windows 32-bit variants. */
		FC2_WINDOWS_X64, /**< All Windows 64-bit variants. */
		FC2_LINUX_X86, /**< All Linux 32-bit variants. */
		FC2_LINUX_X64, /**< All Linux 32-bit variants. */
		FC2_MAC, /**< Mac OSX. */
		FC2_UNKNOWN_OS, /**< Unknown operating system. */
		FC2_OSTYPE_FORCE_32BITS = FULL_32BIT_VALUE
	} fc2OSType;

	/** Possible byte orders. */
	typedef enum _fc2ByteOrder
	{
		FC2_BYTE_ORDER_LITTLE_ENDIAN,
		FC2_BYTE_ORDER_BIG_ENDIAN,
		FC2_BYTE_ORDER_FORCE_32BITS = FULL_32BIT_VALUE
	} fc2ByteOrder;

	/**
	 * Possible states of a port on a node.
	 */
	typedef enum _fc2PortType
	{
		NOT_CONNECTED = 1,
		CONNECTED_TO_PARENT,
		CONNECTED_TO_CHILD
	} fc2PortType;

	/**
	 * Type of node.
	 */
	typedef enum _fc2NodeType
	{
		COMPUTER,
		BUS,
		CAMERA,
		NODE
	} fc2NodeType;

	/**
	 * @defgroup CStructures Structures
	 */

	/*@{*/

	//
	// Description:
	//	 An image. It is comparable to the Image class in the C++ library.
	//   The fields in this structure should be considered read only.
	//
	typedef struct _fc2Image
	{
		unsigned int rows;
		unsigned int cols;
		unsigned int stride;
		unsigned char* pData;
		unsigned int dataSize;
		unsigned int receivedDataSize;
		fc2PixelFormat format;
		fc2BayerTileFormat bayerFormat;

		fc2ImageImpl imageImpl;

	} fc2Image;

	/** Description of the system. */
	typedef struct _fc2SystemInfo
	{
		/** Operating system type as described by OSType. */
		fc2OSType osType;

		/** Detailed description of the operating system. */
		char osDescription[ MAX_STRING_LENGTH];

		/** Byte order of the system. */
		fc2ByteOrder byteOrder;

		/** Amount of memory available on the system. */
		size_t	sysMemSize;

		/** Detailed description of the CPU. */
		char cpuDescription[ MAX_STRING_LENGTH];

		/** Number of cores on all CPUs on the system. */
		size_t	numCpuCores;

		/** List of drivers used. */
		char driverList[ MAX_STRING_LENGTH];

		/** List of libraries used. */
		char libraryList[ MAX_STRING_LENGTH];

		/** Detailed description of the GPU. */
		char gpuDescription[ MAX_STRING_LENGTH];

		/** Screen resolution width in pixels. */
		size_t screenWidth;

		/** Screen resolution height in pixels. */
		size_t screenHeight;

		/** Reserved for future use. */
		unsigned int reserved[16];

	} fc2SystemInfo;

	/** The current version of the library. */
	typedef struct _fc2Version
	{
		unsigned int major; /**< Major version number. */
		unsigned int minor; /**< Minor version number. */
		unsigned int type; /**< Type version number. */
		unsigned int build; /**< Build version number. */
	} fc2Version;

	/**
	 * @defgroup CGigEStructures GigE specific structures
	 *
	 * These structures are specific to GigE camera operation only.
	 */

	/*@{*/

	/** IPv4 address. */
	typedef struct _fc2IPAddress
	{
		unsigned char octets[4];
	} fc2IPAddress;

	/** MAC address. */
	typedef struct _fc2MACAddress
	{
		unsigned char octets[6];
	} fc2MACAddress;

	/** A GigE property. */
	typedef struct _fc2GigEProperty
	{
		/** The type of property. */
		fc2GigEPropertyType propType;
		/**
		 * Whether the property is readable. If this is false, then
		 * no other value in this structure is valid.
		 */
		BOOL isReadable;
		/** Whether the property is writable. */
		BOOL isWritable;
		/** Minimum value. */
		unsigned int min;
		/** Maximum value. */
		unsigned int max;
		/** Current value. */
		unsigned int value;

		unsigned int reserved[8];
	} fc2GigEProperty;

	/** Information about a single GigE stream channel. */
	typedef struct _fc2GigEStreamChannel
	{
		/** Network interface index used (or to use). */
		unsigned int networkInterfaceIndex;
		/** Host port on the PC where the camera will send the data stream. */
		unsigned int hostPort;
		/** Disable IP fragmentation of packets. */
		BOOL doNotFragment;
		/** Packet size, in bytes. */
		unsigned int packetSize;
		/** Inter packet delay, in timestamp counter units. */
		unsigned int interPacketDelay;
		/** Destination IP address. It can be a multicast or unicast address. */
		fc2IPAddress destinationIpAddress;
		/** Source UDP port of the stream channel. Read only. */
		unsigned int sourcePort;

		unsigned int reserved[8];
	} fc2GigEStreamChannel;

	/**
	 * Configuration for a GigE camera.  These options are options that are
	 * generally should be set before starting isochronous transfer.
	 */
	typedef struct _fc2GigEConfig
	{
		/** Turn on/off packet resend functionality */
		BOOL enablePacketResend;

		/**
		 * Number of retries to perform when a register read/write timeout
		 * is received by the library. The default value is 0.
		 */
		unsigned int registerTimeoutRetries;

		/**
		 * Register read/write timeout value, in microseconds.
		 * The default value is dependent on the interface type.
		 */
		unsigned int registerTimeout;

		unsigned int reserved[8];
	} fc2GigEConfig;

	/** Format 7 information for a single mode. */
	typedef struct _fc2GigEImageSettingsInfo
	{
		/** Maximum image width. */
		unsigned int maxWidth;
		/** Maximum image height. */
		unsigned int maxHeight;
		/** Horizontal step size for the offset. */
		unsigned int offsetHStepSize;
		/** Vertical step size for the offset. */
		unsigned int offsetVStepSize;
		/** Horizontal step size for the image. */
		unsigned int imageHStepSize;
		/** Vertical step size for the image. */
		unsigned int imageVStepSize;
		/** Supported pixel formats in a bit field. */
		unsigned int pixelFormatBitField;
		/** Vendor unique pixel formats in a bit field. */
		unsigned int vendorPixelFormatBitField;
		/** Reserved for future use. */
		unsigned int reserved[16];
	} fc2GigEImageSettingsInfo;

	/** Image settings for a GigE camera. */
	typedef struct _fc2GigEImageSettings
	{
		/** Horizontal image offset. */
		unsigned int offsetX;
		/** Vertical image offset. */
		unsigned int offsetY;
		/** Width of image. */
		unsigned int width;
		/** Height of image. */
		unsigned int height;
		/** Pixel format of image. */
		fc2PixelFormat pixelFormat;
		/** Reserved for future use. */
		unsigned int reserved[8];
	} fc2GigEImageSettings;

	/*@}*/

	/**
	 * @defgroup CIIDCStructures IIDC specific structures
	 *
	 * These structures are specific to IIDC camera operation only.
	 */

	/*@{*/

	/** Format 7 image settings. */
	typedef struct _fc2Format7ImageSettings
	{
		/** Format 7 mode. */
		fc2Mode mode;
		/** Horizontal image offset. */
		unsigned int offsetX;
		/** Vertical image offset. */
		unsigned int offsetY;
		/** Width of image. */
		unsigned int width;
		/** Height of image. */
		unsigned int height;
		/** Pixel format of image. */
		fc2PixelFormat pixelFormat;
		/** Reserved for future use. */
		unsigned int reserved[8];

	} fc2Format7ImageSettings;

	/** Format 7 information for a single mode. */
	typedef struct _fc2Format7Info
	{
		/** Format 7 mode. */
		fc2Mode         mode;

		/** Maximum image width. */
		unsigned int maxWidth;
		/** Maximum image height. */
		unsigned int maxHeight;
		/** Horizontal step size for the offset. */
		unsigned int offsetHStepSize;
		/** Vertical step size for the offset. */
		unsigned int offsetVStepSize;
		/** Horizontal step size for the image. */
		unsigned int imageHStepSize;
		/** Vertical step size for the image. */
		unsigned int imageVStepSize;
		/** Supported pixel formats in a bit field. */
		unsigned int pixelFormatBitField;
		/** Vendor unique pixel formats in a bit field. */
		unsigned int vendorPixelFormatBitField;
		/** Current packet size in bytes. */
		unsigned int packetSize;
		/** Minimum packet size in bytes for current mode. */
		unsigned int minPacketSize;
		/** Maximum packet size in bytes for current mode. */
		unsigned int maxPacketSize;
		/** Current packet size as a percentage of maximum packet size. */
		float percentage;
		/** Reserved for future use. */
		unsigned int reserved[16];

	} fc2Format7Info;

	/** Format 7 packet information. */
	typedef struct _fc2Format7PacketInfo
	{
		/** Recommended bytes per packet. */
		unsigned int recommendedBytesPerPacket;
		/** Maximum bytes per packet. */
		unsigned int maxBytesPerPacket;
		/** Minimum bytes per packet. */
		unsigned int unitBytesPerPacket;
		/** Reserved for future use. */
		unsigned int reserved[8];

	} fc2Format7PacketInfo;

	/*@}*/

	/**
	 * Configuration for a camera. These options are options that are
	 * generally should be set before starting isochronous transfer.
	 */
	typedef struct _fc2Config
	{
		/** Number of buffers used by the FlyCapture2 library to grab images. */
		unsigned int numBuffers;

		/**
		 * Number of notifications per image. This value should only be set
		 * after the image settings to be used is set to the camera.
		 * The default number of notifications is 1.
		 *
		 * There are 4 general scenarios:
		 * - 1 notification - End of image
		 * - 2 notifications - After first packet and end of image
		 * - 3 notifications - After first packet, middle of image, end of image
		 * - x notifications - After first packet, (x -2) spread evenly, end of image
		 *
		 * Specifying zero for the number of notifications will be ignored (the current value
		 * will not be modified).
		 *
		 * Note that the event numbers start at 0. Ex. when 3 notifications are
		 * used, the three events will be 0, 1 and 2.
		 */
		unsigned int numImageNotifications;

		/**
		 *  Minimum number of notifications needed for the current image
		 *  settings on the camera. Read-only value.
		 */
		unsigned int minNumImageNotifications;

		/**
		 * Time in milliseconds that RetrieveBuffer() and WaitForBufferEvent()
		 * will wait for an image before timing out and returning.
		 */
		int grabTimeout;

		/** Grab mode for the camera. The default is DROP_FRAMES. */
		fc2GrabMode grabMode;

		/** This parameter enables RetrieveBuffer to run in high
		 *	performance mode.  This means that any interaction
		 *  with the camera, other than grabbing the image is disabled.
		 *	Currently Retrieve buffer reads registers on the camera to
		 *	determine which embedded image information settings have been
		 *	enabled, and it reads what the bayer tile is currently set to.
		 *	When High Performance mode is on, these reads are disabled.  This
		 *	means that any changes to the Bayer Tile or to the Embedded image
		 *	info after StartCapture() will not be tracked when made using
		 *	direct register writes.  If the corresponding SetEmbededImageInfo()
		 *	and GetEmbededImageInfo() calls are used then the changes will be
		 *	appropriately reflected.  This also means that changes to embedded
		 *	image info from other processes will not be updated either. */
		BOOL highPerformanceRetrieveBuffer;

		/** Isochronous bus speed. */
		fc2BusSpeed isochBusSpeed;

		/** Asynchronous bus speed. */
		fc2BusSpeed asyncBusSpeed;

		/**
		 * Bandwidth allocation flag that tells the camera the bandwidth
		 * allocation strategy to employ.
		 */
		fc2BandwidthAllocation bandwidthAllocation;

		/**
		 * Number of retries to perform when a register read/write timeout
		 * is received by the library. The default value is 0.
		 */
		unsigned int registerTimeoutRetries;

		/**
		 * Register read/write timeout value, in microseconds.
		 * The default value is dependent on the interface type.
		 */
		unsigned int registerTimeout;

		/** Reserved for future use */
		unsigned int reserved[16];

	} fc2Config;

	/**
	 * Information about a specific camera property. This structure is also
	 * also used as the TriggerDelayInfo structure.
	 */
	typedef struct _fc2PropertyInfo
	{
		/** Property info type. */
		fc2PropertyType type;
		/** Flag indicating if the property is present. */
		BOOL present;
		/** Flag indicating if auto is supported. */
		BOOL autoSupported;
		/** Flag indicating if manual is supported. */
		BOOL manualSupported;
		/** Flag indicating if on/off is supported. */
		BOOL onOffSupported;
		/** Flag indicating if one push is supported. */
		BOOL onePushSupported;
		/** Flag indicating if absolute mode is supported. */
		BOOL absValSupported;
		/** Flag indicating if property value can be read out. */
		BOOL readOutSupported;
		/** Minimum value (as an integer). */
		unsigned int min;
		/** Maximum value (as an integer). */
		unsigned int max;
		/** Minimum value (as a floating point value). */
		float absMin;
		/** Maximum value (as a floating point value). */
		float absMax;
		/** Textual description of units. */
		char pUnits[MAX_STRING_LENGTH];
		/** Abbreviated textual description of units. */
		char pUnitAbbr[MAX_STRING_LENGTH];
		/** Reserved for future use. */
		unsigned int reserved[8];

	} fc2PropertyInfo, fc2TriggerDelayInfo;

	/**
	 * A specific camera property. \n
	 * For example, to set the gain to 12dB, set the following values:
	 * - \a type - \c GAIN
	 * - \a absControl - \c true
	 * - \a onePush - \c false
	 * - \a onOff - \c true
	 * - \a autoManualMode - \c false
	 * - \a absValue - \c 12.0
	 */
	typedef struct _Property
	{
		/** Property info type. */
		fc2PropertyType   type;
		/** Flag indicating if the property is present. */
		BOOL present;
		/**
         * Flag controlling absolute mode (real world units)
         * or non-absolute mode (camera internal units).
         */
		BOOL absControl;
		/** Flag controlling one push. */
		BOOL onePush;
		/** Flag controlling on/off. */
		BOOL onOff;
		/** Flag controlling auto. */
		BOOL autoManualMode;
		/**
         * Value A (integer).
         * Used to configure properties in non-absolute mode.
         */
		unsigned int valueA;
		/**
         * Value B (integer). For white balance, value B applies to the blue value and
         * value A applies to the red value.
         */
		unsigned int valueB;
		/**
		* Floating point value.
		* Used to configure properties in absolute mode.
		*/
		float absValue;
		/** Reserved for future use. */
		unsigned int reserved[8];

		// For convenience, trigger delay is the same structure
		// used in a separate function along with trigger mode.

	} fc2Property, fc2TriggerDelay;

	/** Information about a camera trigger property. */
	typedef struct _fc2TriggerModeInfo
	{
		/** Presence of trigger mode. */
		BOOL present;
		/** Flag indicating if trigger value can be read out. */
		BOOL readOutSupported;
		/** Flag indicating if on/off is supported. */
		BOOL onOffSupported;
		/** Flag indicating if polarity is supported. */
		BOOL polaritySupported;
		/** Flag indicating if the value is readable. */
		BOOL valueReadable;
		/** Source mask. */
		unsigned int sourceMask;
		/** Flag indicating if software trigger is supported. */
		BOOL softwareTriggerSupported;
		/** Mode mask. */
		unsigned int modeMask;
		/** Reserved for future use. */
		unsigned int reserved[8];

	} fc2TriggerModeInfo;

	/** A camera trigger. */
	typedef struct _fc2TriggerMode
	{
		/** Flag controlling on/off. */
		BOOL onOff;
		/** Polarity value. */
		unsigned int polarity;
		/** Source value. */
		unsigned int source;
		/** Mode value. */
		unsigned int mode;
		/** Parameter value. */
		unsigned int parameter;
		/** Reserved for future use. */
		unsigned int reserved[8];

	} fc2TriggerMode;

	/** A camera strobe property. */
	typedef struct _fc2StrobeInfo
	{
		/** Source value. */
		unsigned int source;
		/** Presence of strobe. */
		BOOL present;
		/** Flag indicating if strobe value can be read out. */
		BOOL readOutSupported;
		/** Flag indicating if on/off is supported. */
		BOOL onOffSupported;
		/** Flag indicating if polarity is supported. */
		BOOL polaritySupported;
		/** Minimum value. */
		float minValue;
		/** Maximum value. */
		float maxValue;
		/** Reserved for future use. */
		unsigned int reserved[8];

	} fc2StrobeInfo;

	/** A camera strobe. */
	typedef struct _fc2StrobeControl
	{
		/** Source value. */
		unsigned int source;
		/** Flag controlling on/off. */
		BOOL onOff;
		/** Signal polarity. */
		unsigned int polarity;
		/** Signal delay (in ms). */
		float delay;
		/** Signal duration (in ms). */
		float duration;
		/** Reserved for future use. */
		unsigned int reserved[8];

	} fc2StrobeControl;

	/** Timestamp information. */
	typedef struct _fc2TimeStamp
	{
		/** Seconds. */
		long long seconds;
		/** Microseconds. */
		unsigned int microSeconds;
		/** 1394 cycle time seconds. */
		unsigned int cycleSeconds;
		/** 1394 cycle time count. */
		unsigned int cycleCount;
		/** 1394 cycle time offset. */
		unsigned int cycleOffset;
		/** Reserved for future use. */
		unsigned int reserved[8];

	} fc2TimeStamp;

	/** Camera configuration ROM. */
	typedef struct _fc2ConfigROM
	{
		/** Vendor ID of a node. */
		unsigned int nodeVendorId;
		/** Chip ID (high part). */
		unsigned int chipIdHi;
		/** Chip ID (low part). */
		unsigned int chipIdLo;
		/** Unit Spec ID, usually 0xa02d. */
		unsigned int unitSpecId;
		/** Unit software version. */
		unsigned int unitSWVer;
		/** Unit sub software version. */
		unsigned int unitSubSWVer;
		/** Vendor unique info 0. */
		unsigned int vendorUniqueInfo_0;
		/** Vendor unique info 1. */
		unsigned int vendorUniqueInfo_1;
		/** Vendor unique info 2. */
		unsigned int vendorUniqueInfo_2;
		/** Vendor unique info 3. */
		unsigned int vendorUniqueInfo_3;
		/** Keyword. */
		char pszKeyword[ MAX_STRING_LENGTH ];
		/** Reserved for future use. */
		unsigned int reserved[16];

	} fc2ConfigROM;

	/** Camera information. */
	typedef struct _fc2CameraInfo
	{
		/** Device serial number. */
		unsigned int serialNumber;
		/** Interface type. */
		fc2InterfaceType interfaceType;
		/** Driver type. */
		fc2DriverType driverType;
		/** Flag indicating if this is a color camera. */
		BOOL isColorCamera;
		/** Device model name. */
		char modelName[ MAX_STRING_LENGTH];
		/** Device vendor name. */
		char vendorName[ MAX_STRING_LENGTH];
		/** String detailing the sensor information. */
		char sensorInfo[ MAX_STRING_LENGTH];
		/** String providing the sensor resolution. */
		char sensorResolution[ MAX_STRING_LENGTH];
		/** Driver name of driver being used. */
		char driverName[ MAX_STRING_LENGTH];
		/** Firmware version of camera. */
		char firmwareVersion[ MAX_STRING_LENGTH];
		/** Firmware build time. */
		char firmwareBuildTime[ MAX_STRING_LENGTH];
		/** Maximum bus speed. */
		fc2BusSpeed maximumBusSpeed;
		/** Bayer tile format. */
		fc2BayerTileFormat bayerTileFormat;
		/** Bus number, set to 0 for GigE and USB cameras **/
		fc2PCIeBusSpeed pcieBusSpeed;
		/** ieee1394 Node number, set to 0 for GigE and USB cameras **/
		unsigned short nodeNumber;
		/** PCIe Bus Speed, set to PCIE_BUSSPEED_UNKNOWN for unsupported drivers **/
		unsigned short busNumber;

		/** @name IIDC specific information */
		/*@{*/
		/** DCAM version. */
		unsigned int iidcVer;
		/** Configuration ROM data. */
		fc2ConfigROM configROM;
		/*@}*/

		/** @name GigE specific information */
		/*@{*/
		/** GigE Vision version. */
		unsigned int gigEMajorVersion;
		/** GigE Vision minor version. */
		unsigned int gigEMinorVersion;
		/** User defined name. */
		char userDefinedName[ MAX_STRING_LENGTH];
		/** XML URL 1. */
		char xmlURL1[ MAX_STRING_LENGTH];
		/** XML URL 2. */
		char xmlURL2[ MAX_STRING_LENGTH];
		/** MAC address */
		fc2MACAddress macAddress;
		/** IP address. */
		fc2IPAddress ipAddress;
		/** Subnet mask. */
		fc2IPAddress subnetMask;
		/** Default gateway. */
		fc2IPAddress defaultGateway;
		/** Status/Content of CCP register */
		unsigned int ccpStatus;
		/** Local Application IP Address. */
		unsigned int applicationIPAddress;
		/** Local Application port. */
		unsigned int applicationPort;
		/*@}*/

		/** Reserved for future use. */
		unsigned int reserved[16];

	} fc2CameraInfo;

	/** Properties of a single embedded image info property. */
	typedef struct _fc2EmbeddedImageInfoProperty
	{
		/** Whether this property is available. */
		BOOL available;
		/** Whether this property is on or off. */
		BOOL onOff;

	} fc2EmbeddedImageInfoProperty;

	/** Properties of the possible embedded image information. */
	typedef struct _fc2EmbeddedImageInfo
	{
		fc2EmbeddedImageInfoProperty timestamp;
		fc2EmbeddedImageInfoProperty gain;
		fc2EmbeddedImageInfoProperty shutter;
		fc2EmbeddedImageInfoProperty brightness;
		fc2EmbeddedImageInfoProperty exposure;
		fc2EmbeddedImageInfoProperty whiteBalance;
		fc2EmbeddedImageInfoProperty frameCounter;
		fc2EmbeddedImageInfoProperty strobePattern;
		fc2EmbeddedImageInfoProperty GPIOPinState;
		fc2EmbeddedImageInfoProperty ROIPosition;

	} fc2EmbeddedImageInfo;

	/** Metadata related to an image. */
	typedef struct _fc2ImageMetadata
	{
		/** Embedded timestamp. */
		unsigned int embeddedTimeStamp;
		/** Embedded gain. */
		unsigned int embeddedGain;
		/** Embedded shutter. */
		unsigned int embeddedShutter;
		/** Embedded brightness. */
		unsigned int embeddedBrightness;
		/** Embedded exposure. */
		unsigned int embeddedExposure;
		/** Embedded white balance. */
		unsigned int embeddedWhiteBalance;
		/** Embedded frame counter. */
		unsigned int embeddedFrameCounter;
		/** Embedded strobe pattern. */
		unsigned int embeddedStrobePattern;
		/** Embedded GPIO pin state. */
		unsigned int embeddedGPIOPinState;
		/** Embedded ROI position. */
		unsigned int embeddedROIPosition;
		/** Reserved for future use. */
		unsigned int reserved[31];

	} fc2ImageMetadata;

	/** Information about the camera's look up table. */
	typedef struct _fc2LUTData
	{
		/** Flag indicating if LUT is supported. */
		BOOL supported;
		/** Flag indicating if LUT is enabled. */
		BOOL enabled;
		/** The number of LUT banks available (Always 1 for PGR LUT). */
		unsigned int numBanks;
		/** The number of LUT channels per bank available. */
		unsigned int numChannels;
		/** The input bit depth of the LUT. */
		unsigned int inputBitDepth;
		/** The output bit depth of the LUT. */
		unsigned int outputBitDepth;
		/** The number of entries in the LUT. */
		unsigned int numEntries;
		/** Reserved for future use. */
		unsigned int reserved[8];

	} fc2LUTData;

	/** Camera diagnostic information. */
	typedef struct _fc2CameraStats
	{
		/* Number of dropped images in DROP_IMAGE mode */
		unsigned int imageDropped;
		/* Number of corrupt images, such as missing packet, zero packet */
		unsigned int imageCorrupt;
		/* Number of transmissions failed of camera */
		unsigned int imageXmitFailed;
		/* Number of images dropped in driver */
		unsigned int imageDriverDropped;
		/* Errors of register reading */
		unsigned int regReadFailed;
		/* Errors of register writing */
		unsigned int regWriteFailed;
		/* Port errors */
		unsigned int portErrors;

		/* The value of the camera power register.
		 * false: Camera is powered down.
		 * true: Camera is powered up.
		 */
		BOOL cameraPowerUp;

		/* The voltage values of the various voltage registers
		 * supported by the camera.
		 */
		float cameraVoltages[8];

		/** The number of voltage registers available.
		 * 0: the values in cameraVoltages[] are invalid.
		 */
		unsigned int numVoltages;

		/* The current values of the various current registers
		 * supported by the camera.
		 */
		float cameraCurrents[8];

		/** The number of current registers available.
		 * 0: the values in cameraCurrents[] are invalid.
		 */
		unsigned int numCurrents;

		/* The temperature of the camera board-level components. The value is
		 * in kelvins (0°C = 273.15K) and are in one-tenths (0.1) of a kelvin.
		 */
		unsigned int temperature;

		/* Time in seconds since the camera was initialized. */
		unsigned int timeSinceInitialization;
		/* Time in seconds since the camera detected a bus reset. */
		unsigned int timeSinceBusReset;
		/* Time stamp */
		fc2TimeStamp timeStamp;
		/* Number of packets requested for resend */
		unsigned int numResendPacketsRequested;
		/* Number of packet-resend packets received */
		unsigned int numResendPacketsReceived;
		/** Reserved for future use. */
		unsigned int reserved[16];

	} fc2CameraStats;

	/**
	 * @defgroup CImageSaveStructures Image saving structures.
	 *
	 * These structures define various parameters used for saving images.
	 */

	/*@{*/

	/** Options for saving PNG images. */
	typedef struct _fc2PNGOption
	{
		/** Whether to save the PNG as interlaced. */
		BOOL interlaced;
		/** Compression level (0-9). 0 is no compression, 9 is best compression. */
		unsigned int compressionLevel;
		/** Reserved for future use. */
		unsigned int reserved[16];

	} fc2PNGOption;

	/** Options for saving PPM images. */
	typedef struct _fc2PPMOption
	{
		/** Whether to save the PPM as a binary file. */
		BOOL binaryFile;
		/** Reserved for future use. */
		unsigned int reserved[16];

	} fc2PPMOption ;

	/** Options for saving PGM images. */
	typedef struct _fc2PGMOption
	{
		/** Whether to save the PPM as a binary file. */
		BOOL binaryFile;
		/** Reserved for future use. */
		unsigned int reserved[16];

	} fc2PGMOption;

	typedef enum _fc2TIFFCompressionMethod
	{
		FC2_TIFF_NONE = 1, /**< Save without any compression. */
		FC2_TIFF_PACKBITS, /**< Save using PACKBITS compression. */
		FC2_TIFF_DEFLATE, /**< Save using DEFLATE compression (ZLIB compression). */
		FC2_TIFF_ADOBE_DEFLATE, /**< Save using ADOBE DEFLATE compression */
		/**
		 * Save using CCITT Group 3 fax encoding. This is only valid for
		 * 1-bit images only. Default to LZW for other bit depths.
		 */
		FC2_TIFF_CCITTFAX3,
		/**
		 * Save using CCITT Group 4 fax encoding. This is only valid for
		 * 1-bit images only. Default to LZW for other bit depths.
		 */
		FC2_TIFF_CCITTFAX4,
		FC2_TIFF_LZW, /**< Save using LZW compression. */
		/**
		 * Save using JPEG compression. This is only valid for 8-bit
		 * greyscale and 24-bit only. Default to LZW for other bit depths.
		 */
		FC2_TIFF_JPEG,
	} fc2TIFFCompressionMethod;

	/** Options for saving TIFF images. */
	typedef struct _fc2TIFFOption
	{
		/** Compression method to use for encoding TIFF images. */
		fc2TIFFCompressionMethod compression;
		/** Reserved for future use. */
		unsigned int reserved[16];

	} fc2TIFFOption;

	/** Options for saving JPEG image. */
	typedef struct _fc2JPEGOption
	{
		/** Whether to save as a progressive JPEG file. */
		BOOL progressive;
		/**
		 * JPEG image quality in range (0-100).
		 * - 100 - Superb quality.
		 * - 75  - Good quality.
		 * - 50  - Normal quality.
		 * - 10  - Poor quality.
		 */
		unsigned int quality;
		/** Reserved for future use. */
		unsigned int reserved[16];

	} fc2JPEGOption;

	/** Options for saving JPEG2000 image. */
	typedef struct _fc2JPG2Option
	{
		/** JPEG saving quality in range (1-512). */
		unsigned int quality;
		/** Reserved for future use. */
		unsigned int reserved[16];
	} fc2JPG2Option;

	/** Options for saving Bitmap image. */
	typedef struct _fc2BMPOption
	{
		BOOL indexedColor_8bit;
		/** Reserved for future use. */
		unsigned int reserved[16];
	} fc2BMPOption;

	/** Options for saving MJPG files. */
	typedef struct _fc2MJPGOption
	{
		/** Frame rate of the stream */
		float frameRate;
		/** Image quality (1-100) */
		unsigned int quality;
		unsigned int reserved[256];

	} fc2MJPGOption;

	/** Options for saving H264 files. */
	typedef struct _fc2H264Option
	{
		/** Frame rate of the stream */
		float frameRate;
		/** Width of source image */
		unsigned int width;
		/** Height of source image */
		unsigned int height;
		/** Bitrate to encode at */
		unsigned int bitrate;
		/** Reserved for future use */
		unsigned int reserved[256];

	} fc2H264Option;

	/** Options for saving AVI files. */
	typedef struct _fc2AVIOption
	{
		/** Frame rate of the stream */
		float frameRate;
		/** Reserved for future use */
		unsigned int reserved[256];
	} fc2AVIOption;

	//=============================================================================
	// Callbacks
	//=============================================================================

	typedef void* fc2CallbackHandle;
	typedef void (*fc2BusEventCallback)( void* pParameter, unsigned int serialNumber );
	typedef void (*fc2ImageEventCallback)( fc2Image* image, void* pCallbackData );
	typedef void (*fc2AsyncCommandCallback)( fc2Error retError, void* pUserData );
	typedef void (*fc2CameraEventCallback)( void* pCallbackData );

	/*******************************************************************************
	 * Camera event data types
	 ******************************************************************************/
	/** Options for enabling device event registration. */
	typedef struct _fc2EventOptions
	{
		/** Callback function pointer */
		fc2CameraEventCallback EventCallbackFcn;

		/** Event name to register */
		const char* EventName;

		/** Pointer to callback data to be passed to the callback function */
		const void* EventUserData;

		/** Size of the underlying struct passed as eventCallbackData for sanity checks */
		size_t EventUserDataSize;
	} fc2EventOptions;


	/* Callback data passed to the callback function provided when using
	 * RegisterEvent() or RegisterAllEvents().
	 */
	typedef struct _fc2EventCallbackData
	{
		/** Pointer to the user-supplied data struct */
		void* EventUserData;

		/** Size of the user data supplied to the RegisterEvent()
		 * function.
		 */
		size_t EventUserDataSize;

		/** The event name used to register the event. Provided so the user
		 * knows which event triggered the callback.
		 */
		const char* EventName;

		/** The device register which EventName maps to. Provides an alternate
		 * means of indexing into different event types.
		 */
		unsigned long long EventID;

		/** Timestamp indicated the time (as reported by the camera) at which
		 * the camera exposure operation completed. This can be compared with
		 * image timestamps if there is a need to map event timestamps to
		 * specific images, if applicable.
		 */
		unsigned long long EventTimestamp;

		/** A pointer to additional data pertaining to the event which just
		 * trigger the callback function. The data may be of difference sizes
		 * or may not even be allocated, depending on the type of event which
		 * triggered the callback.
		 */
		void* EventData;

		/** The size of the structure pointed to by EventData. This value should
		 * be checked, especially if there are events which can trigger variable-
		 * length event data to be returned to the user when the callback function
		 * is issued.
		 */
		size_t EventDataSize;
	} fc2EventCallbackData;

	/*@}*/

	/*@}*/

#ifdef __cplusplus
};
#endif

#endif // PGR_FC2_FLYCAPTURE2DEFS_C_H