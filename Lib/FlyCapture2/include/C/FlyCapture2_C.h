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

#ifndef FLIR_FC2_FLYCAPTURE2_C_H
#define FLIR_FC2_FLYCAPTURE2_C_H

//=============================================================================
// Global C header file for FlyCapture2.
//
// This file defines the C API for FlyCapture2
//=============================================================================

#include "FlyCapture2Platform_C.h"
#include "FlyCapture2Defs_C.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * Create a FC2 context for IIDC camera.
     * This call must be made before any other calls that use a context
     * will succeed.
     *
     * @see fc2DestroyContext()
     *
     * @param pContext A pointer to the fc2Context to be created.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2CreateContext(
                fc2Context* pContext );

    /**
     * Create a FC2 context for a GigE Vision camera.
     * This call must be made before any other calls that use a context
     * will succeed.
     *
     * @see fc2DestroyContext()
     *
     * @param pContext A pointer to the fc2Context to be created.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2CreateGigEContext(
                fc2Context* pContext );

    /**
     * Destroy the FC2 context. This must be called when the user is finished
     * with the context in order to prevent memory leaks.
     *
     * @see fc2CreateContext()
     *
     * @param context The context to be destroyed.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2DestroyContext(
                fc2Context context );

    /**
    * @defgroup CBusManager Bus Manager Operation
    *
    * @brief The functions in this section provide access to BusManager
    * operations
    */
    /*@{*/

    /**
     * Fire a bus reset. The actual bus reset is only fired for the
     * specified 1394 bus, but it will effectively cause a global bus
     * reset for the library.
     *
     * @param context The fc2Context to be used.
     * @param pGuid PGRGuid of the camera or the device to cause bus reset.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2FireBusReset(
                fc2Context context,
                fc2PGRGuid* pGuid);

    /**
     * Gets the number of cameras attached to the PC.
     *
     * @param context The fc2Context to be used.
     * @param pNumCameras Number of cameras detected.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetNumOfCameras(
                fc2Context context,
                unsigned int* pNumCameras );

    /**
    * Gets the PGRGuid for a camera with the specified IPv4 address.
    *
    * @param context The fc2Context to be used.
    * @param ipAddress IP address to get GUID for.
    * @param pGuid Unique PGRGuid for the camera.
    *
    * @return A fc2Error indicating the success or failure of the function.
    */
    FLYCAPTURE2_C_API fc2Error
        fc2GetCameraFromIPAddress(
            fc2Context context,
            fc2IPAddress ipAddress,
            fc2PGRGuid* pGuid);

    /**
    * Gets the PGRGuid for a camera on the PC. It uniquely identifies
    * the camera specified by the index and is used to identify the camera
    * during a fc2Connect() call.
    *
    * @param context The fc2Context to be used.
    * @param index Zero based index of camera.
    * @param pGuid Unique PGRGuid for the camera.
    *
    * @return A fc2Error indicating the success or failure of the function.
    */
    FLYCAPTURE2_C_API fc2Error
        fc2GetCameraFromIndex(
            fc2Context context,
            unsigned int index,
            fc2PGRGuid* pGuid);

    /**
     * Gets the PGRGuid for a camera on the PC. It uniquely identifies
     * the camera specified by the serial number and is used to identify the camera
     * during a fc2Connect() call.
     *
     * @param context The fc2Context to be used.
     * @param serialNumber Serial number of camera.
     * @param pGuid Unique PGRGuid for the camera.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetCameraFromSerialNumber(
                fc2Context context,
                unsigned int serialNumber,
                fc2PGRGuid* pGuid );

    /**
     * Gets the serial number of the camera with the specified index.
     *
     * @param context The fc2Context to be used.
     * @param index Zero based index of desired camera.
     * @param pSerialNumber Serial number of camera.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetCameraSerialNumberFromIndex(
                fc2Context context,
                unsigned int index,
                unsigned int* pSerialNumber );

    /**
     * Gets the interface type associated with a PGRGuid. This is useful
     * in situations where there is a need to enumerate all cameras
     * for a particular interface.
     *
     * @param context The fc2Context to be used.
     * @param pGuid The PGRGuid to get the interface for.
     * @param pInterfaceType The interface type of the PGRGuid.
     *
     * @return
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetInterfaceTypeFromGuid(
                fc2Context context,
                fc2PGRGuid *pGuid,
                fc2InterfaceType* pInterfaceType );

    /**
     * Gets the number of devices. This may include hubs, host controllers
     * and other hardware devices (including cameras).
     *
     * @param context The fc2Context to be used.
     * @param pNumDevices The number of devices found.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetNumOfDevices(
                fc2Context context,
                unsigned int* pNumDevices );

    /**
     * Gets the PGRGuid for a device. It uniquely identifies the device
     * specified by the index.
     *
     * @param context The fc2Context to be used.
     * @param index Zero based index of device.
     * @param pGuid Unique PGRGuid for the device.
     *
     * @see fc2GetNumOfDevices()
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetDeviceFromIndex(
                fc2Context context,
                unsigned int index,
                fc2PGRGuid*     pGuid );

    /**
        * Read a phy register on the specified device. The full address
        * to be read from is determined by the page, port and address.
        *
        * @param context The fc2Context to be used.
        * @param guid Unique PGRGuid for the device.
        * @param page Page to read from.
        * @param port Port to read from.
        * @param address Address to read from.
        * @param pValue Value read from the phy register.
        *
        * @return An Error indicating the success or failure of the function.
        */
    FLYCAPTURE2_C_API fc2Error
        fc2ReadPhyRegister(
            fc2Context context,
            fc2PGRGuid guid,
            unsigned int page,
            unsigned int port,
            unsigned int address,
            unsigned int* pValue );

    /**
     * Write a phy register on the specified device. The full address
     * to be written to is determined by the page, port and address.
     *
     * @param context The fc2Context to be used.
     * @param guid Unique PGRGuid for the device.
     * @param page Page to write to.
     * @param port Port to write to.
     * @param address Address to write to.
     * @param value Value to write to phy register.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2WritePhyRegister(
            fc2Context context,
            fc2PGRGuid guid,
            unsigned int page,
            unsigned int port,
            unsigned int address,
            unsigned int value );

    /**
     * Read usb link info for the port that the specified device is connected to.
     *
     * @param context The fc2Context to be used.
     * @param guid Unique PGRGuid for the device.
     * @param pValue Value read from the card register.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetUsbLinkInfo(
            fc2Context context,
            fc2PGRGuid guid,
            unsigned int* pValue );

    /**
     * Read usb port status for the port that the specified device is connected to.
     *
     * @param context The fc2Context to be used.
     * @param guid Unique PGRGuid for the device.
     * @param pValue Value read from the card register.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetUsbPortStatus(
            fc2Context context,
            fc2PGRGuid guid,
            unsigned int* pValue );

    /**
     * Gets the topology information for the PC.
     *
     * @param context The fc2Context to be used.
     * @param pTopologyNodeContext A Topology Node context that will contain
     *                             the topology information
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetTopology(
            fc2Context context,
            fc2TopologyNodeContext* pTopologyNodeContext );

    /**
     * Register a callback function that will be called when the
     * specified callback event occurs.
     *
     * @param context The fc2Context to be used.
     * @param enumCallback Pointer to function that will receive the callback.
     * @param callbackType Type of callback to register for.
     * @param pParameter Callback parameter to be passed to callback.
     * @param pCallbackHandle Unique callback handle used for unregistering
     *                        callback.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2RegisterCallback(
                fc2Context context,
                fc2BusEventCallback enumCallback,
                fc2BusCallbackType callbackType,
                void* pParameter,
                fc2CallbackHandle* pCallbackHandle );

    /**
     * Unregister a callback function.
     *
     * @param context The fc2Context to be used.
     * @param callbackHandle Unique callback handle.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2UnregisterCallback(
                fc2Context context,
                fc2CallbackHandle callbackHandle );

    /**
     * Force a rescan of the buses. This does not trigger a bus reset.
     * The camera objects will be invalidated only if the camera network
     * topology is changed (ie. a camera is disconnected or added)
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2RescanBus( fc2Context context);

    /**
     * Force the camera with the specific MAC address to the specified
     * IP address, subnet mask and default gateway. This is useful in
     * situations where a GigE Vision camera is using Persistent IP and the
     * application's subnet is different from the device subnet.
     *
     * @param context The fc2Context to be used.
     * @param macAddress MAC address of the camera.
     * @param ipAddress IP address to set on the camera.
     * @param subnetMask Subnet mask to set on the camera.
     * @param defaultGateway Default gateway to set on the camera.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2ForceIPAddressToCamera(
                fc2Context context,
                fc2MACAddress macAddress,
                fc2IPAddress ipAddress,
                fc2IPAddress subnetMask,
                fc2IPAddress defaultGateway );

    /**
     * Force all cameras on the network to be assigned sequential IP addresses
     * on the same subnet as the network adapters that they are connected to.
     * This is useful in situations where GigE Vision cameras are using
     * IP addresses in a subnet different from the host's subnet.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2ForceAllIPAddressesAutomatically();

    /**
     * Force cameras on the network to be assigned sequential IP addresses
     * on the same subnet as the network adapters that it is connected to.
     * This is useful in situations where GigE Vision cameras are using
     * IP addresses in a subnet different from the host's subnet.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2ForceIPAddressAutomatically(unsigned int serialNumber);

    /**
     * Discover all cameras connected to the network even if they reside
     * on a different subnet. This is useful in situations where a GigE
     * camera is using Persistent IP and the application's subnet is
     * different from the device subnet. After discovering the camera,
     * it is easy to use ForceIPAddressToCamera() to set a different IP
     * configuration.
     *
     * @param context The fc2Context to be used.
     * @param gigECameras Pointer to an array of CameraInfo structures.
     * @param arraySize Size of the array. Number of discovered cameras
     *                  is returned in the same value.
     *
     * @return An Error indicating the success or failure of the function.
     *         If the error is PGRERROR_BUFFER_TOO_SMALL then arraySize will
     *         contain the minimum size needed for gigECameras array.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2DiscoverGigECameras(
                fc2Context context,
                fc2CameraInfo* gigECameras,
                unsigned int* arraySize  );

    /**
    * Query whether a GigE camera is controllable.
    *
    * @param context The fc2Context to be used.
    * @param pGuid Unique PGRGuid for the camera.
    * @param pControllable True indicates camera is controllable
    *
    * @return A fc2Error indicating the success or failure of the function.
    */
    FLYCAPTURE2_C_API fc2Error
        fc2IsCameraControlable(
            fc2Context context,
            fc2PGRGuid* pGuid,
            BOOL* pControlable);
    /*@}*/

    /**
    * @defgroup CConnectionAndImage Connection and Image Retrieval
    *
    * @brief These functions deal with connections and image retrieval from
    * the camera.
    */
    /*@{*/

    /**
     * Connects the fc2Context to the camera specified by the GUID.
     *
     * Be aware that calling fc2CreateGUIContext() releases the CCP acquired
     * for GigE cameras in fc2Connect(). Consider calling fc2Connect() after
     * fc2CreateGUIContext().
     *
     * @param context The fc2Context to be used.
     * @param guid The unique identifier for a specific camera on the PC.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2Connect(
                fc2Context context,
                fc2PGRGuid* guid );

    /**
     * Disconnects the fc2Context from the camera. This allows another physical
     * camera specified by a GUID to be connected to the fc2Context.
     *
     * @see fc2Connect()
     *
     * @param context The fc2Context to be used.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2Disconnect(
                fc2Context context );

    /**
    * Checks if the fc2Context is connected to a physical camera
    * specified by a GUID.
    *
    * @see fc2Connect()
    * @see fc2Disconnect()
    *
    * @param context The fc2Context to be used.
    *
    * @return Whether fc2Connect() was called on the fc2Context.
    */
    FLYCAPTURE2_C_API BOOL
        fc2IsConnected(
                fc2Context context );

    /**
     * Sets the callback data to be used on completion of image transfer.
     * To clear the current stored callback data, pass in NULL for both
     * callback arguments.
     *
     * @see fc2StartCapture()
     *
     * @param context The fc2Context to be used.
     * @param pCallbackFn A function to be called when a new image is received.
     * @param pCallbackData A pointer to data that can be passed to the
     *                      callback function.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetCallback(
                fc2Context context,
                fc2ImageEventCallback pCallbackFn,
                void* pCallbackData);

    /**
     * Starts isochronous image capture. It will use either the current
     * video mode or the most recently set video mode of the camera.
     *
     * @see fc2RetrieveBuffer()
     * @see fc2StartSyncCapture()
     * @see fc2StopCapture()
     *
     * @param context The fc2Context to be used.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2StartCapture(
                fc2Context context );

    /**
     * Starts isochronous image capture. It will use either the current
     * video mode or the most recently set video mode of the camera. The callback
     * function is called when a new image is received from the camera.
     *
     * @see fc2RetrieveBuffer()
     * @see fc2StartSyncCapture()
     * @see fc2StopCapture()
     *
     * @param context The fc2Context to be used.
     * @param pCallbackFn A function to be called when a new image is received.
     * @param pCallbackData A pointer to data that can be passed to the
     *                      callback function. A NULL pointer is acceptable.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2StartCaptureCallback(
                fc2Context context,
                fc2ImageEventCallback pCallbackFn,
                void* pCallbackData);

    /**
     * Starts synchronized isochronous image capture on multiple cameras.
     * This function is only used for firewire cameras.
     *
     * @see fc2RetrieveBuffer()
     * @see fc2StartCapture()
     * @see fc2StopCapture()
     *
     * @param numCameras Number of fc2Contexts in the ppCameras array.
     * @param pContexts Array of fc2Contexts.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2StartSyncCapture(
                unsigned int numCameras,
                fc2Context *pContexts );

    /**
     * Starts synchronized isochronous image capture on multiple cameras.
     * This function is only used for firewire cameras.
     *
     * @see fc2RetrieveBuffer()
     * @see fc2StartCapture()
     * @see fc2StopCapture()
     *
     * @param numCameras Number of fc2Contexts in the ppCameras array.
     * @param pContexts Array of fc2Contexts.
     * @param pCallbackFns Array of callback functions for each camera.
     * @param pCallbackDataArray Array of callback data pointers.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2StartSyncCaptureCallback(
                unsigned int numCameras,
                fc2Context *pContexts,
                fc2ImageEventCallback* pCallbackFns,
                void** pCallbackDataArray);

    /**
     * Retrieves the next image object containing the next image.
     *
     * @see fc2StartCapture()
     * @see fc2StopCapture()
     *
     * @param context The fc2Context to be used.
     * @param pImage Pointer to fc2Image to store image data.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2RetrieveBuffer(
                fc2Context context,
                fc2Image* pImage );

    /**
     * Stops isochronous image transfer and cleans up all associated
     * resources.
     *
     * @see fc2StartCapture()
     * @see fc2RetrieveBuffer()
     *
     * @param context The fc2Context to be used.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2StopCapture(
                fc2Context context );

    /**
     * Retrieves the next image event containing the next part of the image.
     *
     * @see fc2StartCapture()
     * @see fc2RetrieveBuffer()
     * @see fc2StopCapture()
     *
     * @param context The fc2Context to be used.
     * @param pImage Pointer to fc2Image to store image data.
     * @param eventNumber The event number to wait for.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2WaitForBufferEvent(
            fc2Context context,
            fc2Image* pImage,
            unsigned int eventNumber );

    /**
     * Specify user allocated buffers to use as image data buffers.
     * To prevent image tearing, the size of each buffer should be equal to
     * ((unsigned int)(bufferSize + packetSize - 1)/packetSize) * packetSize.
     * The total size should be (size * numBuffers) or larger.
     * The packet Size that should be used differs between interfaces:
     *  Firewire:   Use the Format7 packet size.
     *  Usb2:       First round to Format7 packet size then round to 512 bytes.
     *  Usb3:       Use a packet size of 1024 bytes.
     *  GigE:       No need to do any rounding on GigE
     *
     * @see fc2StartCapture()
     * @see fc2RetrieveBuffer()
     * @see fc2StopCapture()
     *
     * @param context The fc2Context to be used.
     * @param ppMemBuffers Pointer to memory buffers to be written to. The
     *                     size of the data should be equal to
     *                     (size * numBuffers) or larger.
     * @param size The size of each buffer (in bytes).
     * @param nNumBuffers Number of buffers in the array.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetUserBuffers(
                fc2Context context,
                unsigned char* const ppMemBuffers,
                int size,
                int nNumBuffers );

    /**
     * Get the configuration associated with the camera.
     *
     * @see fc2SetConfiguration()
     *
     * @param context The fc2Context to be used.
     * @param config Pointer to the configuration structure to be filled.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetConfiguration(
                fc2Context context,
                fc2Config* config );

    /**
     * Set the configuration associated with the camera.
     *
     * @see fc2GetConfiguration()
     *
     * @param context The fc2Context to be used.
     * @param config Pointer to the configuration structure to be used.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetConfiguration(
                fc2Context context,
                fc2Config* config );
    /*@}*/

    /**
    * @defgroup CInformationProperties Information and Properties
    *
    * @brief These functions deal with information and properties can be
    * retrieved from the camera.
    */
    /*@{*/

    /**
     * Retrieves information from the camera such as serial number, model
     * name and other camera information.
     *
     * @param context The fc2Context to be used.
     * @param pCameraInfo Pointer to the camera information structure
     *                    to be filled.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetCameraInfo(
                fc2Context context,
                fc2CameraInfo* pCameraInfo );

    /**
     * Retrieves information about the specified camera property. The
     * property type must be specified in the fc2PropertyInfo structure
     * passed into the function in order for the function to succeed.
     *
     * @see fc2GetProperty()
     * @see fc2SetProperty()
     *
     * @param context The fc2Context to be used.
     * @param propInfo Pointer to the PropertyInfo structure to be filled.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetPropertyInfo(
                fc2Context context,
                fc2PropertyInfo* propInfo );

    /**
     * Reads the settings for the specified property from the camera. The
     * property type must be specified in the fc2Property structure passed
     * into the function in order for the function to succeed. If auto
     * is on, the integer and abs values returned may not be consistent
     * with each other.
     *
     * @see fc2GetPropertyInfo()
     * @see fc2SetProperty()
     *
     * @param context The fc2Context to be used.
     * @param prop Pointer to the Property structure to be filled.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetProperty(
                fc2Context context,
                fc2Property* prop );

    /**
     * Writes the settings for the specified property to the camera. The
     * property type must be specified in the Property structure passed
     * into the function in order for the function to succeed.
     * The absControl flag controls whether the absolute or integer value
     * is written to the camera. Use fc2GetPropertyInfo() to query which
     * options are available for a specific property.
     *
     * @see fc2GetPropertyInfo()
     * @see fc2GetProperty()
     *
     * @param context The fc2Context to be used.
     * @param prop Pointer to the Property structure to be used.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetProperty(
                fc2Context context,
                fc2Property* prop );

    /**
     * Writes the settings for the specified property to the camera. The
     * property type must be specified in the Property structure passed
     * into the function in order for the function to succeed.
     * The absControl flag controls whether the absolute or integer value
     * is written to the camera.
     *
     * @param context The fc2Context to be used.
     * @param prop Pointer to the Property structure to be used.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetPropertyBroadcast(
                fc2Context context,
                fc2Property* prop );
    /*@}*/

    /**
    * @defgroup CGeneralPurposeIO General Purpose Input / Output
    *
    * @brief These functions deal with general GPIO pin control on the camera.
    */
    /*@{*/

    /**
     * Get the GPIO pin direction for the specified pin. This is not a
     * required call when using the trigger or strobe functions as
     * the pin direction is set automatically internally.
     *
     * @see fc2SetGPIOPinDirection()
     * @see fc2SetGPIOPinDirectionBroadcast()
     *
     * @param context The fc2Context to be used.
     * @param pin Pin to get the direction for.
     * @param pDirection Direction of the pin. 0 for input, 1 for output.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetGPIOPinDirection(
                fc2Context context,
                unsigned int pin,
                unsigned int* pDirection );

    /**
     * Set the GPIO pin direction for the specified pin. This is useful if
     * there is a need to set the pin into an input pin (i.e. to read the
     * voltage) off the pin without setting it as a trigger source. This
     * is not a required call when using the trigger or strobe functions as
     * the pin direction is set automatically internally.
     *
     * @see fc2GetGPIOPinDirection()
     * @see fc2SetGPIOPinDirectionBroadcast()
     *
     * @param context The fc2Context to be used.
     * @param pin Pin to get the direction for.
     * @param direction Direction of the pin. 0 for input, 1 for output.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetGPIOPinDirection(
                fc2Context context,
                unsigned int pin,
                unsigned int direction);

    /**
     * Set the GPIO pin direction for the specified pin. This is useful if
     * there is a need to set the pin into an input pin (i.e. to read the
     * voltage) off the pin without setting it as a trigger source. This
     * is not a required call when using the trigger or strobe functions as
     * the pin direction is set automatically internally.
     *
     * @see fc2GetGPIOPinDirection()
     *
     * @param context The fc2Context to be used.
     * @param pin Pin to get the direction for.
     * @param direction Direction of the pin. 0 for input, 1 for output.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetGPIOPinDirectionBroadcast(
                fc2Context context,
                unsigned int pin,
                unsigned int direction);
    /*@}*/

    /**
    * @defgroup CTrigger Trigger
    *
    * @brief These functions deal with trigger control on the camera.
    */
    /*@{*/

    /**
     * Retrieve trigger information from the camera.
     *
     * @see fc2GetTriggerMode()
     * @see fc2SetTriggerMode()
     * @see fc2SetTriggerModeBroadcast()
     * @see fc2GetTriggerDelayInfo()
     * @see fc2GetTriggerDelay()
     * @see fc2SetTriggerDelay()
     *
     * @param context The fc2Context to be used.
     * @param triggerModeInfo Structure to receive trigger information.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetTriggerModeInfo(
                fc2Context context,
                fc2TriggerModeInfo* triggerModeInfo );

    /**
     * Retrieve current trigger settings from the camera.
     *
     * @see fc2GetTriggerModeInfo()
     * @see fc2SetTriggerMode()
     * @see fc2SetTriggerModeBroadcast()
     * @see fc2GetTriggerDelayInfo()
     * @see fc2GetTriggerDelay()
     * @see fc2SetTriggerDelay()
     *
     * @param context The fc2Context to be used.
     * @param triggerMode Structure to receive trigger mode settings.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetTriggerMode(
                fc2Context context,
                fc2TriggerMode* triggerMode );

    /**
     * Set the specified trigger settings to the camera.
     *
     * @see fc2GetTriggerModeInfo()
     * @see fc2GetTriggerMode()
     * @see fc2GetTriggerDelayInfo()
     * @see fc2GetTriggerDelay()
     * @see fc2SetTriggerDelay()
     * @see fc2SetTriggerModeBroadcast()
     *
     * @param context The fc2Context to be used.
     * @param triggerMode Structure providing trigger mode settings.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetTriggerMode(
                fc2Context context,
                fc2TriggerMode* triggerMode );

    /**
     * Set the specified trigger settings to the camera.
     *
     * @see fc2GetTriggerModeInfo()
     * @see fc2GetTriggerMode()
     * @see fc2GetTriggerDelayInfo()
     * @see fc2GetTriggerDelay()
     * @see fc2SetTriggerDelay()
     * @see fc2SetTriggerMode()
     *
     * @param context The fc2Context to be used.
     * @param triggerMode Structure providing trigger mode settings.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetTriggerModeBroadcast(
                fc2Context context,
                fc2TriggerMode* triggerMode );

    /**
     * Fire the software trigger according to the DCAM specifications.
     *
     * @param context The fc2Context to be used.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2FireSoftwareTrigger(
                fc2Context context );

    /**
     * Fire the software trigger according to the DCAM specifications.
     *
     * @param context The fc2Context to be used.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2FireSoftwareTriggerBroadcast(
                fc2Context context );

    /**
     * Retrieve trigger delay information from the camera.
     *
     * @see fc2GetTriggerModeInfo()
     * @see fc2GetTriggerMode()
     * @see fc2SetTriggerMode()
     * @see fc2GetTriggerDelay()
     * @see fc2SetTriggerDelay()
     * @see fc2SetTriggerDelayBroadcast()
     *
     * @param context The fc2Context to be used.
     * @param triggerDelayInfo Structure to receive trigger delay information.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetTriggerDelayInfo(
                fc2Context context,
                fc2TriggerDelayInfo* triggerDelayInfo );

    /**
     * Retrieve current trigger delay settings from the camera.
     *
     * @see fc2GetTriggerModeInfo()
     * @see fc2GetTriggerMode()
     * @see fc2SetTriggerMode()
     * @see fc2GetTriggerDelayInfo()
     * @see fc2SetTriggerDelay()
     * @see fc2SetTriggerDelayBroadcast()
     *
     * @param context The fc2Context to be used.
     * @param triggerDelay Structure to receive trigger delay settings.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetTriggerDelay(
                fc2Context context,
                fc2TriggerDelay* triggerDelay );

    /**
     * Set the specified trigger delay settings to the camera.
     *
     * @see fc2GetTriggerModeInfo()
     * @see fc2GetTriggerMode()
     * @see fc2SetTriggerMode()
     * @see fc2GetTriggerDelayInfo()
     * @see fc2GetTriggerDelay()
     * @see fc2SetTriggerDelayBroadcast()
     *
     * @param context The fc2Context to be used.
     * @param triggerDelay Structure providing trigger delay settings.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetTriggerDelay(
                fc2Context context,
                fc2TriggerDelay* triggerDelay );

    /**
     * Set the specified trigger delay settings to the camera.
     *
     * @see fc2GetTriggerModeInfo()
     * @see fc2GetTriggerMode()
     * @see fc2SetTriggerMode()
     * @see fc2GetTriggerDelayInfo()
     * @see fc2GetTriggerDelay()
     * @see fc2SetTriggerDelay()
     *
     * @param context The fc2Context to be used.
     * @param triggerDelay Structure providing trigger delay settings.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetTriggerDelayBroadcast(
                fc2Context context,
                fc2TriggerDelay* triggerDelay );
    /*@}*/

    /**
    * @defgroup CStrobe Strobe
    *
    * @brief These functions deal with strobe control on the camera.
    */
    /*@{*/

    /**
     * Retrieve strobe information from the camera.
     *
     * @see fc2GetStrobe()
     * @see fc2SetStrobe()
     * @see fc2SetStrobeBroadcast()
     *
     * @param context The fc2Context to be used.
     * @param strobeInfo Structure to receive strobe information.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetStrobeInfo(
                fc2Context context,
                fc2StrobeInfo* strobeInfo );

    /**
     * Retrieve current strobe settings from the camera. The strobe pin
     * must be specified in the structure before being passed in to
     * the function.
     *
     * @see fc2GetStrobeInfo()
     * @see fc2SetStrobe()
     * @see fc2SetStrobeBroadcast()
     *
     * @param context The fc2Context to be used.
     * @param strobeControl Structure to receive strobe settings.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetStrobe(
                fc2Context context,
                fc2StrobeControl* strobeControl );

    /**
     * Set current strobe settings to the camera. The strobe pin
     * must be specified in the structure before being passed in to
     * the function.
     *
     * @see fc2GetStrobeInfo()
     * @see fc2GetStrobe()
     * @see fc2SetStrobeBroadcast()
     *
     * @param context The fc2Context to be used.
     * @param strobeControl Structure providing strobe settings.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetStrobe(
                fc2Context context,
                fc2StrobeControl* strobeControl );

    /**
     * Set current strobe settings to the camera. The strobe pin
     * must be specified in the structure before being passed in to
     * the function.
     *
     * @see fc2GetStrobeInfo()
     * @see fc2GetStrobe()
     * @see fc2SetStrobe()
     *
     * @param context The fc2Context to be used.
     * @param strobeControl Structure providing strobe settings.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetStrobeBroadcast(
                fc2Context context,
                fc2StrobeControl* strobeControl );
    /*@}*/

    /**
    * @defgroup CLookUp Look Up Table
    *
    * @brief These functions deal with Look Up Table control on the camera.
    */
    /*@{*/

    /**
     * Query if LUT support is available on the camera. Note that some cameras
     * may report support for the LUT and return an inputBitDepth of 0. In these
     * cases use log2(numEntries) for the inputBitDepth.
     *
     * @see fc2EnableLUT()
     * @see fc2GetLUTChannel()
     * @see fc2SetLUTChannel()
     *
     * @param context The fc2Context to be used.
     * @param pData The LUT structure to be filled.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetLUTInfo(
                fc2Context context,
                fc2LUTData* pData );

    /**
     * Query the read/write status of a single LUT bank.
     *
     * @param context The fc2Context to be used.
     * @param bank The bank to query.
     * @param pReadSupported Whether reading from the bank is supported.
     * @param pWriteSupported Whether writing to the bank is supported.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetLUTBankInfo(
                fc2Context context,
                unsigned int bank,
                BOOL* pReadSupported,
                BOOL* pWriteSupported );

    /**
     * Get the LUT bank that is currently being used. For cameras with
     * PGR LUT, the active bank is always 0.
     *
     * @param context The fc2Context to be used.
     * @param pActiveBank The currently active bank.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetActiveLUTBank(
                fc2Context context,
                unsigned int* pActiveBank );

    /**
     * Set the LUT bank that will be used.
     *
     * @param context The fc2Context to be used.
     * @param activeBank The bank to be set as active.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetActiveLUTBank(
                fc2Context context,
                unsigned int activeBank );

    /**
     * Enable or disable LUT functionality on the camera.
     *
     * @see fc2GetLUTInfo()
     * @see fc2GetLUTChannel()
     * @see fc2SetLUTChannel()
     *
     * @param context The fc2Context to be used.
     * @param on Whether to enable or disable LUT.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2EnableLUT(
                fc2Context context,
                BOOL on );

    /**
     * Get the LUT channel settings from the camera.
     *
     * @see fc2GetLUTInfo()
     * @see fc2EnableLUT()
     * @see fc2SetLUTChannel()
     *
     * @param context The fc2Context to be used.
     * @param bank Bank to retrieve.
     * @param channel Channel to retrieve.
     * @param sizeEntries Number of entries in LUT table to read.
     * @param pEntries Array to store LUT entries.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetLUTChannel(
                fc2Context context,
                unsigned int bank,
                unsigned int channel,
                unsigned int sizeEntries,
                unsigned int* pEntries );

    /**
     * Set the LUT channel settings to the camera.
     *
     * @see fc2GetLUTInfo()
     * @see fc2EnableLUT()
     * @see fc2GetLUTChannel()
     *
     * @param context The fc2Context to be used.
     * @param bank Bank to set.
     * @param channel Channel to set.
     * @param sizeEntries Number of entries in LUT table to write. This must be the
     *                    same size as numEntries returned by GetLutInfo().
     * @param pEntries Array containing LUT entries to write.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetLUTChannel(
                fc2Context context,
                unsigned int bank,
                unsigned int channel,
                unsigned int sizeEntries,
                unsigned int* pEntries );
    /*@}*/

    /**
    * @defgroup CMemoryChannel Memory Channels
    *
    * @brief These functions deal with memory channel control on the camera.
    */
    /*@{*/

    /**
     * Retrieve the current memory channel from the camera.
     *
     * @see fc2SaveToMemoryChannel()
     * @see fc2RestoreFromMemoryChannel()
     * @see fc2GetMemoryChannelInfo()
     *
     * @param context The fc2Context to be used.
     * @param pCurrentChannel Current memory channel.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetMemoryChannel(
                fc2Context context,
                unsigned int* pCurrentChannel );

    /**
     * Save the current settings to the specified current memory channel.
     *
     * @see fc2GetMemoryChannel()
     * @see fc2RestoreFromMemoryChannel()
     * @see fc2GetMemoryChannelInfo()
     *
     * @param context The fc2Context to be used.
     * @param channel Memory channel to save to.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SaveToMemoryChannel(
                fc2Context context,
                unsigned int channel );

    /**
     * Restore the specified current memory channel.
     *
     * @see fc2GetMemoryChannel()
     * @see fc2SaveToMemoryChannel()
     * @see fc2GetMemoryChannelInfo()
     *
     * @param context The fc2Context to be used.
     * @param channel Memory channel to restore from.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2RestoreFromMemoryChannel(
                fc2Context context,
                unsigned int channel );

    /**
     * Query the camera for memory channel support. If the number of
     * channels are 0, then memory channel support is not available.
     *
     * @see fc2GetMemoryChannel()
     * @see fc2SaveToMemoryChannel()
     * @see fc2RestoreFromMemoryChannel()
     *
     * @param context The fc2Context to be used.
     * @param pNumChannels Number of memory channels supported.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetMemoryChannelInfo(
                fc2Context context,
                unsigned int* pNumChannels );

    /**
     * Get the current status of the embedded image information register,
     * as well as the availability of each embedded property.
     *
     * @see fc2SetEmbeddedImageInfo()
     *
     * @param context The fc2Context to be used.
     * @param pInfo Structure to be filled.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetEmbeddedImageInfo(
                fc2Context context,
                fc2EmbeddedImageInfo* pInfo );

    /**
     * Sets the on/off values of the embedded image information structure
     * to the camera.
     *
     * @see fc2GetEmbeddedImageInfo()
     *
     * @param context The fc2Context to be used.
     * @param pInfo Structure to be used.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetEmbeddedImageInfo(
                fc2Context context,
                fc2EmbeddedImageInfo* pInfo );
    /*@}*/

    /**
    * @defgroup CRegister Register Operation
    *
    * @brief These functions deal with register operation on the camera.
    */
    /*@{*/

    /**
     * Write to the specified register on the camera.
     *
     * @see fc2ReadRegister()
     *
     * @param context The fc2Context to be used.
     * @param address DCAM address to be written to.
     * @param value The value to be written.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2WriteRegister(
                fc2Context context,
                unsigned int address,
                unsigned int value);

    /**
     * Read the specified register from the camera.
     *
     * @see fc2WriteRegister()
     *
     * @param context The fc2Context to be used.
     * @param address DCAM address to be read from.
     * @param pValue The value that is read.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2ReadRegister(
                fc2Context context,
                unsigned int address,
                unsigned int* pValue );

    /**
     * Write to the specified register on the camera with broadcast.
     *
     * @see fc2ReadRegisterBlock()
     *
     * @param context The fc2Context to be used.
     * @param address DCAM address to be written to.
     * @param value The value to be written.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2WriteRegisterBroadcast(
                fc2Context context,
                unsigned int address,
                unsigned int value);

    /**
     * Write to the specified register block on the camera.
     *
     * @see fc2ReadRegisterBlock()
     *
     * @param context The fc2Context to be used.
     * @param addressHigh Top 16 bits of the 48-bit absolute address to write to.
     * @param addressLow Bottom 32 bits of the 48 bits absolute address to write to.
     * @param pBuffer Array containing data to be written.
     * @param length Size of array, in quadlets.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2WriteRegisterBlock(
                fc2Context context,
                unsigned short addressHigh,
                unsigned int addressLow,
                const unsigned int* pBuffer,
                unsigned int length );

    /**
     * Write to the specified register block on the camera.
     *
     * @see fc2WriteRegisterBlock()
     *
     * @param context The fc2Context to be used.
     * @param addressHigh Top 16 bits of the 48-bit absolute address to read from.
     * @param addressLow Bottom 32 bits of the 48 bits absolute address to read from.
     * @param pBuffer Array to store read data.
     * @param length Size of array, in quadlets.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2ReadRegisterBlock(
                fc2Context context,
                unsigned short addressHigh,
                unsigned int addressLow,
                unsigned int* pBuffer,
                unsigned int length );

    /**
     * Returns a text representation of the register value.
     *
     * @param registerVal The register value to query.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API const char*
        fc2GetRegisterString(
                unsigned int registerVal);
    /*@}*/

    /**
     * Get cycle time from camera
     *
     * @param context The fc2Context to be used.
     * @param Timestamp struct.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetCycleTime( fc2Context context, fc2TimeStamp* pTimeStamp );

    /**
     * Returns the camera diagnostic information.
     *
     * @param context The fc2Context to be used.
     * @param pCameraStats Pointer to the fc2CameraStats structure.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetStats( fc2Context context, fc2CameraStats* pCameraStats );

    /*
     * Reset the camera diagnostic information.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        ResetStats();

    /**
     * Register the camera to issue a custom callback function call for a
     * specific device event.
     *
     * @param context The fc2Context to be used.
     * @param pOpts Pointer to the EventOptions structure which defines the
     *              callback function to use, the event for which to register
     *              the device, and a pointer to user data (optional) to be
     *              passed to the callback function.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2RegisterEvent(
                fc2Context context,
                fc2EventOptions* pOpts );

    /**
     *De-register an event previously registered with the camera.
     *
     * @param context The fc2Context to be used.
     * @param pOpts Pointer to the EventOptions structure which defines the
     *              callback function to use, the event for which to register
     *              the device, and a pointer to user data (optional) to be
     *              passed to the callback function. The callback function and
     *              user data elements of the EventOptions structure are ignored
     *              in this call, and just the event name within the structure is
     *              used with this function call.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2DeregisterEvent(
                fc2Context context,
                fc2EventOptions* pOpts );

    /**
     * Register the camera to issue a custom callback function call for a
     * specific device event.
     *
     * @param context The fc2Context to be used.
     * @param pOpts Pointer to the EventOptions structure which defines the
     *              callback function to use, the event for which to register
     *              the device, and a pointer to user data (optional) to be
     *              passed to the callback function. The event name element of
     *              the structure is ignored with this function call. If a single
     *              event has already been registered via RegisterEvent(), this
     *              call will fail, as the user could accidentally change the
     *              the internal callback function pointer for a queued event.
     *              The user will need to de-register all registered events,
     *              then call this function again.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2RegisterAllEvents(
                fc2Context context,
                fc2EventOptions* pOpts );

    /*
     * De-register all events registered with the camera.
     *
     * @param context The fc2Context to be used.
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2DeregisterAllEvents(
                fc2Context context);

    /**
    * @defgroup CDCAMFormats DCAM Formats
    *
    * @brief These functions deal with DCAM video mode and frame rate
    *            on the camera. This is only used for firewire and usb2 cameras.
    */
    /*@{*/

    /**
     * Query the camera to determine if the specified video mode and
     * frame rate is supported.
     *
     * @param context The fc2Context to be used.
     * @param videoMode Video mode to check.
     * @param frameRate Frame rate to check.
     * @param pSupported Whether the video mode and frame rate is supported.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetVideoModeAndFrameRateInfo(
                fc2Context context,
                fc2VideoMode videoMode,
                fc2FrameRate frameRate,
                BOOL* pSupported);

    /**
     * Get the current video mode and frame rate from the camera. If
     * the camera is in Format7, the video mode will be VIDEOMODE_FORMAT7
     * and the frame rate will be FRAMERATE_FORMAT7.
     *
     * @param context The fc2Context to be used.
     * @param videoMode Current video mode.
     * @param frameRate Current frame rate.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetVideoModeAndFrameRate(
                fc2Context context,
                fc2VideoMode* videoMode,
                fc2FrameRate* frameRate );

    /**
     * Set the specified video mode and frame rate to the camera. It is
     * not possible to set the camera to VIDEOMODE_FORMAT7 or
     * FRAMERATE_FORMAT7. Use the Format7 functions to set the camera
     * into Format7.
     *
     * @param context The fc2Context to be used.
     * @param videoMode Video mode to set to camera.
     * @param frameRate Frame rate to set to camera.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetVideoModeAndFrameRate(
                fc2Context context,
                fc2VideoMode videoMode,
                fc2FrameRate frameRate );
    /*@}*/

    /**
    * @defgroup CFormat7 Format7
    *
    * @brief These functions deal with Format7 custom image control on the camera.
    */
    /*@{*/

    /**
     * Retrieve the availability of Format7 custom image mode and the
     * camera capabilities for the specified Format7 mode. The mode must
     * be specified in the Format7Info structure in order for the
     * function to succeed.
     *
     * @param context The fc2Context to be used.
     * @param info Structure to be filled with the capabilities of the specified
     *             mode and the current state in the specified mode.
     * @param pSupported Whether the specified mode is supported.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetFormat7Info(
                fc2Context context,
                fc2Format7Info* info,
                BOOL* pSupported );

    /**
     * Validates Format7ImageSettings structure and returns valid packet
     * size information if the image settings are valid. The current
     * image settings are cached while validation is taking place. The
     * cached settings are restored when validation is complete.
     *
     * @param context The fc2Context to be used.
     * @param imageSettings Structure containing the image settings.
     * @param settingsAreValid Whether the settings are valid.
     * @param packetInfo Packet size information that can be used to
     *                   determine a valid packet size.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2ValidateFormat7Settings(
                fc2Context context,
                fc2Format7ImageSettings* imageSettings,
                BOOL* settingsAreValid,
                fc2Format7PacketInfo* packetInfo );

    /**
     * Get the current Format7 configuration from the camera. This call
     * will only succeed if the camera is already in Format7.
     *
     * @param context The fc2Context to be used.
     * @param imageSettings Current image settings.
     * @param packetSize Current packet size.
     * @param percentage Current packet size as a percentage.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetFormat7Configuration(
                fc2Context context,
                fc2Format7ImageSettings* imageSettings,
                unsigned int* packetSize,
                float* percentage );

    /**
     * Set the current Format7 configuration to the camera.
     *
     * @param context The fc2Context to be used.
     * @param imageSettings Image settings to be written to the camera.
     * @param packetSize Packet size to be written to the camera.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetFormat7ConfigurationPacket(
                fc2Context context,
                fc2Format7ImageSettings* imageSettings,
                unsigned int packetSize );

    /**
     * Set the current Format7 configuration to the camera.
     *
     * @param context The fc2Context to be used.
     * @param imageSettings Image settings to be written to the camera.
     * @param percentSpeed Packet size as a percentage to be written to the camera.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetFormat7Configuration(
                fc2Context context,
                fc2Format7ImageSettings* imageSettings,
                float percentSpeed );
    /*@}*/

    /**
    * @defgroup CGVCPRegister GVCP Register Operation
    *
    * @brief These functions deal with GVCP register operation on the camera.
    */
    /*@{*/

    /**
     * Write a GVCP register.
     *
     * @param context The fc2Context to be used.
     * @param address GVCP address to be written to.
     * @param value The value to be written.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2WriteGVCPRegister(
                fc2Context context,
                unsigned int address,
                unsigned int value);

    /**
     * Write a GVCP register with broadcast
     *
     * @param context The fc2Context to be used.
     * @param address GVCP address to be written to.
     * @param value The value to be written.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2WriteGVCPRegisterBroadcast(
                fc2Context context,
                unsigned int address,
                unsigned int value);

    /**
     * Read a GVCP register.
     *
     * @param context The fc2Context to be used.
     * @param address GVCP address to be read from.
     * @param pValue The value that is read.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2ReadGVCPRegister(
                fc2Context context,
                unsigned int address,
                unsigned int* pValue );

    /**
     * Write a GVCP register block.
     *
     * @param context The fc2Context to be used.
     * @param address GVCP address to be write to.
     * @param pBuffer Array containing data to be written.
     * @param length Size of array, in quadlets.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2WriteGVCPRegisterBlock(
                fc2Context context,
                unsigned int address,
                const unsigned int* pBuffer,
                unsigned int length );

    /**
     * Read a GVCP register block.
     *
     * @param context The fc2Context to be used.
     * @param address GVCP address to be read from.
     * @param pBuffer Array containing data to be written.
     * @param length Size of array, in quadlets.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2ReadGVCPRegisterBlock(
                fc2Context context,
                unsigned int address,
                unsigned int* pBuffer,
                unsigned int length );

    /**
     * Write a GVCP memory block.
     *
     * @param context The fc2Context to be used.
     * @param address GVCP address to be write to.
     * @param pBuffer Array containing data to be written.
     * @param length Size of array, in quadlets.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2WriteGVCPMemory(
                fc2Context context,
                unsigned int address,
                const unsigned char* pBuffer,
                unsigned int length );

    /**
     * Read a GVCP memory block.
     *
     * @param context The fc2Context to be used.
     * @param address GVCP address to be read from.
     * @param pBuffer Array containing data to be written.
     * @param length Size of array, in quadlets.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2ReadGVCPMemory(
                fc2Context context,
                unsigned int address,
                unsigned char* pBuffer,
                unsigned int length );
    /*@}*/


    /**
    * @defgroup CGEVProperty GigE property manipulation
    *
    * @brief These functions deal with GigE properties.
    */
    /*@{*/

    /**
     * Get the specified GigEProperty. The GigEPropertyType field must
     * be set in order for this function to succeed.
     *
     * @param context The fc2Context to be used.
     * @param pGigEProp The GigE property to get.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetGigEProperty(
                fc2Context context,
                fc2GigEProperty* pGigEProp );

    /**
     * Set the specified GigEProperty. The GigEPropertyType field must
     * be set in order for this function to succeed.
     *
     * @param context The fc2Context to be used.
     * @param pGigEProp The GigE property to set.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetGigEProperty(
                fc2Context context,
                const fc2GigEProperty* pGigEProp );

    /**
     * Discover the largest packet size that works for the network link
     * between the PC and the camera. This is useful in cases where
     * there may be multiple links between the PC and the camera and
     * there is a possibility of a component not supporting the
     * recommended jumbo frame packet size of 9000.
     *
     * @param context The fc2Context to be used.
     * @param packetSize The maximum packet size supported by the link.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2DiscoverGigEPacketSize(
            fc2Context context,
            unsigned int* packetSize );
    /*@}*/

    /**
    * @defgroup CGEVImageSettings GigE image settings
    *
    * @brief These functions deal with GigE image setting.
    */
    /*@{*/

    /**
     * Check if the particular imaging mode is supported by the camera.
     *
     * @param context The fc2Context to be used.
     * @param mode The mode to check.
     * @param isSupported Whether the mode is supported.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2QueryGigEImagingMode(
                fc2Context context,
                fc2Mode mode,
                BOOL* isSupported );

    /**
     * Get the current imaging mode on the camera.
     *
     * @param context The fc2Context to be used.
     * @param mode Current imaging mode on the camera.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetGigEImagingMode(
                fc2Context context,
                fc2Mode* mode );

    /**
     * Set the current imaging mode to the camera. This should only be
     * done when the camera is not streaming images.
     *
     * @param context The fc2Context to be used.
     * @param mode Imaging mode to set to the camera.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetGigEImagingMode(
                fc2Context context,
                fc2Mode mode );

    /**
     * Get information about the image settings possible on the camera.
     *
     * @param context The fc2Context to be used.
     * @param pInfo Image settings information.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetGigEImageSettingsInfo(
                fc2Context context,
                fc2GigEImageSettingsInfo* pInfo );

    /**
     * Get the current image settings on the camera.
     *
     * @param context The fc2Context to be used.
     * @param pImageSettings Current image settings on camera.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetGigEImageSettings(
                fc2Context context,
                fc2GigEImageSettings* pImageSettings );

    /**
     * Set the image settings specified to the camera.
     *
     * @param context The fc2Context to be used.
     * @param pImageSettings Image settings to set to camera.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetGigEImageSettings(
                fc2Context context,
                const fc2GigEImageSettings* pImageSettings );
    /*@}*/

    /**
    * @defgroup CGEVImageBinningSettings GigE image binning settings
    *
    * @brief These functions deal with GigE image binning settings.
    */
    /*@{*/

    /**
     * Get the current binning settings on the camera.
     *
     * @param context The fc2Context to be used.
     * @param horzBinnningValue Current horizontal binning value.
     * @param vertBinnningValue Current vertical binning value.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetGigEImageBinningSettings(
                fc2Context context,
                unsigned int* horzBinnningValue,
                unsigned int* vertBinnningValue );

    /**
     * Set the specified binning values to the camera. It is recommended
     * that GetGigEImageSettingsInfo() be called after this function
     * succeeds to retrieve the new image settings information for
     * the new binning mode.
     *
     * @param context The fc2Context to be used.
     * @param horzBinnningValue Horizontal binning value.
     * @param vertBinnningValue Vertical binning value.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetGigEImageBinningSettings(
                fc2Context context,
                unsigned int horzBinnningValue,
                unsigned int vertBinnningValue );
    /*@}*/

    /**
    * @defgroup CGEVImageStreamConfig GigE image stream configuration
    *
    * @brief These functions deal with GigE image stream configuration.
    */
    /*@{*/

    /**
     * Get the number of stream channels present on the camera.
     *
     * @param context The fc2Context to be used.
     * @param numChannels Number of stream channels present.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetNumStreamChannels(
                fc2Context context,
                unsigned int* numChannels );

    /**
     * Get the stream channel information for the specified channel.
     *
     * @param context The fc2Context to be used.
     * @param channel Channel number to use.
     * @param pChannel Stream channel information for the specified channel.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetGigEStreamChannelInfo(
                fc2Context context,
                unsigned int channel,
                fc2GigEStreamChannel* pChannel );

    /**
     * Set the stream channel information for the specified channel.
     *
     * Note that the source UDP port of the stream channel is read-only.
     *
     * @param context The fc2Context to be used.
     * @param channel Channel number to use.
     * @param pChannel Stream channel information to use for the specified channel.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetGigEStreamChannelInfo(
                fc2Context context,
                unsigned int channel,
                fc2GigEStreamChannel* pChannel );

    /**
     * Get the current gige config on the camera.
     *
     * @param context The fc2Context to be used.
     * @param pGigEConfig Current configuration on camera.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetGigEConfig(
                fc2Context context,
                fc2GigEConfig* pConfig );

    /**
     * Set the gige config specified to the camera.
     *
     * @param context The fc2Context to be used.
     * @param pGigEConfig configuration to set to camera.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetGigEConfig(
                fc2Context context,
                const fc2GigEConfig* pConfig );
    /*@}*/

    /**
    * @defgroup CImage Image Operation
    *
    * @brief The Image operations are used to retrieve images from a camera,
    * convert between multiple pixel formats and save images to disk.
    * Operations on images are not guaranteed to be thread safe. It is
    * recommended that operations on images be protected by thread
    * synchronization constructs such as mutexes.
    */
    /*@{*/

    /**
     * Set the default color processing algorithm.  This method will be
     * used for any image with the DEFAULT algorithm set. The method used
     * is determined at the time of the Convert() call, therefore the most
     * recent execution of this function will take precedence. The default
     * setting is shared within the current process.
     *
     * @param defaultMethod The color processing algorithm to set.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetDefaultColorProcessing(
                fc2ColorProcessingAlgorithm defaultMethod );

    /**
     * Get the default color processing algorithm.
     *
     * @param pDefaultMethod The default color processing algorithm.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetDefaultColorProcessing(
                fc2ColorProcessingAlgorithm* pDefaultMethod );

    /**
     * Set the default output pixel format. This format will be used for any
     * call to Convert() that does not specify an output format. The format
     * used will be determined at the time of the Convert() call, therefore
     * the most recent execution of this function will take precedence.
     * The default is shared within the current process.
     *
     * @param format The output pixel format to set.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetDefaultOutputFormat(
                fc2PixelFormat format );

    /**
     * Get the default output pixel format.
     *
     * @param pFormat The default pixel format.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetDefaultOutputFormat(
                fc2PixelFormat* pFormat );

    /**
     * Calculate the bits per pixel for the specified pixel format.
     *
     * @param format The pixel format.
     * @param pBitsPerPixel The bits per pixel.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2DetermineBitsPerPixel(
                fc2PixelFormat format,
                unsigned int* pBitsPerPixel );

    /**
     * Create a fc2Image. If externally allocated memory is to be used for the
     * converted image, simply assigning the pData member of the fc2Image structure
     * is insufficient. fc2SetImageData() should be called in order to populate
     * the fc2Image structure correctly.
     *
     * @see fc2SetImageData()
     *
     * @param pImage Pointer to image to be created.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2CreateImage(
                fc2Image* pImage );

    /**
     * Destroy the fc2Image.
     *
     * @param image Pointer to image to be destroyed.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2DestroyImage(
                fc2Image* image );

    /**
     * Sets the dimensions of the image object.
     *
     * @param pImage The fc2Image to be used.
     * @param rows Number of rows to set.
     * @param cols Number of cols to set.
     * @param stride Stride to set.
     * @param pixelFormat Pixel format to set.
     * @param bayerFormat Bayer tile format to set.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetImageDimensions(
                fc2Image* pImage,
                unsigned int rows,
                unsigned int cols,
                unsigned int stride,
                fc2PixelFormat pixelFormat,
                fc2BayerTileFormat bayerFormat);

    /**
    * Get the image dimensions associated with the image object.
    *
    * @param pImage The fc2Image to be used.
    * @param pRows Number of rows.
    * @param pCols Number of columns.
    * @param pStride The stride.
    * @param pPixelFormat Pixel format.
    * @param pBayerFormat Bayer tile format.
    */
    FLYCAPTURE2_C_API fc2Error
        fc2GetImageDimensions(
                fc2Image* pImage,
                unsigned int* pRows,
                unsigned int* pCols,
                unsigned int* pStride,
                fc2PixelFormat* pPixelFormat,
                fc2BayerTileFormat* pBayerFormat);

    /**
     * Set the color processing algorithm. This should be set on the
     * input image object.
     *
     * @param pImage The fc2Image to be used.
     * @param colorProc The color processing algorithm to use.
     *
     * @see fc2GetColorProcessing()
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetImageColorProcessing(
                fc2Image* pImage,
                fc2ColorProcessingAlgorithm colorProc);

    /**
    * Get the current color processing algorithm.
    *
    * @param pImage The fc2Image to be used.
    *
    * @see fc2SetColorProcessing()
    *
    * @return The current color processing algorithm.
    */
    FLYCAPTURE2_C_API fc2Error
        fc2GetImageColorProcessing(
                fc2Image* pImage,
                fc2ColorProcessingAlgorithm* pColorProc);

    /**
     * Set the data of the Image object.
     * Ownership of the image buffer is not transferred to the Image object.
     * It is the user's responsibility to delete the buffer when it is
     * no longer in use.
     *
     * @param pImage The fc2Image to be used.
     * @param pData Pointer to the image buffer.
     * @param dataSize Size of the image buffer.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetImageData(
                fc2Image* pImage,
                const unsigned char* pData,
                unsigned int dataSize);

    /**
     * Get a pointer to the data associated with the image. This function
     * is considered unsafe. The pointer returned could be invalidated if
     * the buffer is resized or released. The pointer may also be
     * invalidated if the Image object is passed to fc2RetrieveBuffer().
     *
     * @param pImage The fc2Image to be used.
     * @param ppData A pointer to the image data.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetImageData(
                fc2Image* pImage,
                unsigned char** ppData);

    /**
     * Get the metadata associated with the image. This includes
     * embedded image information.
     *
     * @param pImage The fc2Image to be used.
     *
     * @return Metadata associated with the image.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetImageMetadata(
                fc2Image* pImage,
                fc2ImageMetadata* pImageMetaData);

    /**
     * Get the timestamp data associated with the image.
     *
     * @param pImage The fc2Image to be used.
     *
     * @return Timestamp data associated with the image.
     */
    FLYCAPTURE2_C_API fc2TimeStamp
        fc2GetImageTimeStamp(
                fc2Image* pImage);

    /**
     * Save the image to the specified file name with the file format
     * specified.
     *
     * @param pImage The fc2Image to be used.
     * @param pFilename Filename to save image with.
     * @param format File format to save in.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SaveImage(
                fc2Image* pImage,
                const char* pFilename,
                fc2ImageFileFormat format );

    /**
     * Save the image to the specified file name with the file format
     * specified.
     *
     * @param pImage The fc2Image to be used.
     * @param pFilename Filename to save image with.
     * @param format File format to save in.
     * @param pOption Options for saving image.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SaveImageWithOption(
                fc2Image* pImage,
                const char* pFilename,
                fc2ImageFileFormat format,
                void* pOption );

    /**
     *
     *
     * @param pImageIn
     * @param pImageOut
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2ConvertImage(
                fc2Image* pImageIn,
                fc2Image* pImageOut );

    /**
     * Converts the current image buffer to the specified output format and
     * stores the result in the specified image. The destination image
     * does not need to be configured in any way before the call is made.
     *
     * @param format Output format of the converted image.
     * @param pImageIn Input image.
     * @param pImageOut Output image.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2ConvertImageTo(
                fc2PixelFormat format,
                fc2Image* pImageIn,
                fc2Image* pImageOut );

    /**
     * Calculate statistics associated with the image. In order to collect
     * statistics for a particular channel, the enabled flag for the
     * channel must be set to true. Statistics can only be collected for
     * images in Mono8, Mono16, RGB, RGBU, BGR and BGRU.
     *
     * @param pImage The fc2Image to be used.
     * @param pImageStatisticsContext The fc2ImageStatisticsContext to hold the
     *                                statistics.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2CalculateImageStatistics(
                fc2Image* pImage,
                fc2ImageStatisticsContext* pImageStatisticsContext );
    /*@}*/

    /**
    * @defgroup CImageStatistics Image Statistics Operation
    *
    * @brief The Image Statistics operation provides the functionality for the user to collect
    * image channel statistics.
    */
    /*@{*/

    /**
     * Create a statistics context.
     *
     * @param pImageStatisticsContext A statistics context.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2CreateImageStatistics(
                fc2ImageStatisticsContext* pImageStatisticsContext );

    /**
     * Destroy a statistics context.
     *
     * @param imageStatisticsContext A statistics context.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2DestroyImageStatistics(
                fc2ImageStatisticsContext imageStatisticsContext );


    /**
     * Enable all channels.
     *
     * @param imageStatisticsContext A statistics context.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2ImageStatisticsEnableAll(
            fc2ImageStatisticsContext imageStatisticsContext );

    /**
     * Disable all channels.
     *
     * @param imageStatisticsContext A statistics context.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2ImageStatisticsDisableAll(
            fc2ImageStatisticsContext imageStatisticsContext );

    /**
     * Enable only the grey channel.
     *
     * @param imageStatisticsContext A statistics context.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2ImageStatisticsEnableGreyOnly(
            fc2ImageStatisticsContext imageStatisticsContext );

    /**
     * Enable only the RGB channels.
     *
     * @param imageStatisticsContext A statistics context.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2ImageStatisticsEnableRGBOnly(
            fc2ImageStatisticsContext imageStatisticsContext );

    /**
     * Enable only the HSL channels.
     *
     * @param imageStatisticsContext A statistics context.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2ImageStatisticsEnableHSLOnly(
            fc2ImageStatisticsContext imageStatisticsContext );

    /**
     * Get the status of a statistics channel.
     *
     * @see fc2SetChannelStatus()
     *
     * @param imageStatisticsContext A statistics context.
     * @param channel The statistics channel.
     * @param pEnabled Whether the channel is enabled.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetChannelStatus(
                fc2ImageStatisticsContext imageStatisticsContext,
                fc2StatisticsChannel channel,
                BOOL* pEnabled );

    /**
     * Set the status of a statistics channel.
     *
     * @see fc2GetChannelStatus()
     *
     * @param imageStatisticsContext A statistics context.
     * @param channel The statistics channel.
     * @param enabled Whether the channel should be enabled.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2SetChannelStatus(
                fc2ImageStatisticsContext imageStatisticsContext,
                fc2StatisticsChannel channel,
                BOOL enabled );

    /**
     * Get the range of a statistics channel. The values returned
     * are the maximum possible values for any given pixel in the image.
     * This is generally 0-255 for 8 bit images, and 0-65535 for
     * 16 bit images.
     *
     * @param imageStatisticsContext A statistics context.
     * @param channel The statistics channel.
     * @param pMin The minimum possible value.
     * @param pMax The maximum possible value.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetChannelRange(
            fc2ImageStatisticsContext imageStatisticsContext,
            fc2StatisticsChannel channel,
            unsigned int* pMin,
            unsigned int* pMax );

    /**
     * Get the range of a statistics channel. The values returned
     * are the maximum values recorded for all pixels in the image.
     *
     * @param imageStatisticsContext A statistics context.
     * @param channel The statistics channel.
     * @param pPixelValueMin The minimum pixel value.
     * @param pPixelValueMax The maximum pixel value.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetChannelPixelValueRange(
            fc2ImageStatisticsContext imageStatisticsContext,
            fc2StatisticsChannel channel,
            unsigned int* pPixelValueMin,
            unsigned int* pPixelValueMax );

    /**
     * Get the number of unique pixel values in the image.
     *
     * @param imageStatisticsContext A statistics context.
     * @param channel The statistics channel.
     * @param pNumPixelValues The number of unique pixel values.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetChannelNumPixelValues(
            fc2ImageStatisticsContext imageStatisticsContext,
            fc2StatisticsChannel channel,
            unsigned int* pNumPixelValues );

    /**
     * Get the mean of the image.
     *
     * @param imageStatisticsContext A statistics context.
     * @param channel The statistics channel.
     * @param pPixelValueMean The mean of the image.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetChannelMean(
            fc2ImageStatisticsContext imageStatisticsContext,
            fc2StatisticsChannel channel,
            float* pPixelValueMean );

    /**
     * Get the histogram for the image.
     *
     * @param imageStatisticsContext A statistics context.
     * @param channel The statistics channel.
     * @param ppHistogram Pointer to an array containing the histogram.
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetChannelHistogram(
            fc2ImageStatisticsContext imageStatisticsContext,
            fc2StatisticsChannel channel,
            int** ppHistogram );

    /**
     * Get all statistics for the image.
     *
     * @param imageStatisticsContext The statistics context.
     * @param channel The statistics channel.
     * @param pRangeMin The minimum possible value.
     * @param pRangeMax The maximum possible value.
     * @param pPixelValueMin The minimum pixel value.
     * @param pPixelValueMax The maximum pixel value.
     * @param pNumPixelValues The number of unique pixel values.
     * @param pPixelValueMean The mean of the image.
     * @param ppHistogram Pointer to an array containing the histogram.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetImageStatistics(
                fc2ImageStatisticsContext imageStatisticsContext,
                fc2StatisticsChannel channel,
                unsigned int* pRangeMin,
                unsigned int* pRangeMax,
                unsigned int* pPixelValueMin,
                unsigned int* pPixelValueMax,
                unsigned int* pNumPixelValues,
                float* pPixelValueMean,
                int** ppHistogram );

    /*@}*/

    /**
    * @defgroup CAVIRecorder AVI Recording Operation
    *
    * @brief The AVI recording operation provides the functionality for the user to record
     * images to an AVI file.
    */
    /*@{*/

    /**
     * Create a AVI context.
     *
     * @param pAVIContext A AVI context.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2CreateAVI(
                fc2AVIContext* pAVIContext );

    /**
     * Open an AVI file in preparation for writing Images to disk.
     * The size of AVI files is limited to 2GB. The filenames are
     * automatically generated using the filename specified.
     *
     * @param AVIContext The AVI context to use.
     * @param pFileName The filename of the AVI file.
     * @param pOption Options to apply to the AVI file.
     *
     * @see SetMaximumAVISize()
     * @see fc2AVIClose()
     * @see fc2AVIOption
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2AVIOpen(
                fc2AVIContext AVIContext,
                const char*  pFileName,
                fc2AVIOption* pOption );

    /**
     * Open an MJPEG file in preparation for writing Images to disk.
     * The size of AVI files is limited to 2GB. The filenames are
     * automatically generated using the filename specified.
     *
     * @param AVIContext The AVI context to use.
     * @param pFileName The filename of the AVI file.
     * @param pOption Options to apply to the AVI file.
     *
     * @see fc2AVIClose()
     * @see fc2MJPGOption
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2MJPGOpen(
                fc2AVIContext AVIContext,
                const char*  pFileName,
                fc2MJPGOption* pOption );

    /**
     * Open an H.264 video file in preparation for writing Images to disk.
     * If the file extension is not specified, MP4 will be used as the default
     * container. Consult ffmpeg documentation for a list of supported containers.
     *
     * @param pFileName The filename of the video file.
     * @param pOption H.264 options to apply to the video file.
     *
     * @see fc2AVIClose()
     * @see fc2H264Option
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2H264Open(
                fc2AVIContext AVIContext,
                const char*  pFileName,
                fc2H264Option* pOption );

    /**
     * Append an image to the AVI file.
     *
     * @param AVIContext The AVI context to use.
     * @param pImage The image to append.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2AVIAppend(
                fc2AVIContext AVIContext,
                fc2Image* pImage );

   /**
    * Set the maximum file size (in megabytes) of a AVI/MP4 file. A new AVI/MP4 file
    * is created automatically when file size limit is reached. Setting
    * a maximum size of 0 indicates no limit on file size.
    *
    * @param AVIContext The AVI context to use.
    * @param size The maximum AVI file size in MB.
    *
    * @return A fc2Error indicating the success or failure of the function.
    */
    FLYCAPTURE2_C_API fc2Error
        fc2AVISetMaximumSize(
            fc2AVIContext AVIContext,
            unsigned int size);

    /**
     * Close the AVI file.
     *
     * @param AVIContext The AVI context to use.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2AVIClose(
                fc2AVIContext AVIContext );

    /**
     * Destroy a AVI context.
     *
     * @param AVIContext A AVI context.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2DestroyAVI(
                fc2AVIContext AVIContext );

    /*@}*/

    /**
    * @defgroup CTopologyNode TopologyNode Operation
    *
    * @brief The TopologyNode operation provides the functionality for the user to
    * generate a tree structure of all cameras and devices connected to a computer.
    */
    /*@{*/

    /**
     * Create a TopologyNode context.
     *
     * @param pTopologyNodeContext A Topology Node context.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2CreateTopologyNode(
                fc2TopologyNodeContext* pTopologyNodeContext );

    /**
     * Get the PGRGuid associated with the node.
     *
     * @param TopologyNodeContext The Topology Node context to use.
     * @param pGuid The unique identifier associated with the node.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2TopologyNodeGetGuid(
                fc2TopologyNodeContext TopologyNodeContext,
                fc2PGRGuid* pGuid);

    /**
     * Get the device ID associated with the node.
     *
     * @param TopologyNodeContext The Topology Node context to use.
     * @param pID Device ID of the node.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2TopologyNodeGetDeviceId(
                fc2TopologyNodeContext TopologyNodeContext,
                int* pID);

    /**
     * Get the node type associated with the node.
     *
     * @param TopologyNodeContext The Topology Node context to use.
     * @param pNodeType Node type of the node.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2TopologyNodeGetNodeType(
                fc2TopologyNodeContext TopologyNodeContext,
                fc2NodeType* pNodeType);

    /**
     * Get the interface type associated with the node.
     *
     * @param TopologyNodeContext The Topology Node context to use.
     * @param pInterfaceType Interface type of the node.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2TopologyNodeGetInterfaceType(
                fc2TopologyNodeContext TopologyNodeContext,
                fc2InterfaceType* pInterfaceType);

    /**
     * Get the number of child nodes.
     *
     * @param TopologyNodeContext The Topology Node context to use.
     * @param pNumChildNodes Number of child nodes.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2TopologyNodeGetNumChildren(
                fc2TopologyNodeContext TopologyNodeContext,
                unsigned int* pNumChildNodes);

    /**
     * Get child node located at the specified position.
     *
     * @param TopologyNodeContext The Topology Node context to use.
     * @param position Position of the child node.
     * @param pChildTopologyNodeContext The Topology Node context the contains
     *                                  information on the child topology
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2TopologyNodeGetChild(
                fc2TopologyNodeContext TopologyNodeContext,
                unsigned int position,
                fc2TopologyNodeContext* pChildTopologyNodeContext);

    /**
     * Add the specified TopologyNode as a child of the node.
     *
     * @param TopologyNodeContext The Topology Node context to use.
     * @param TopologyNodeChildContext The TopologyNode child context to add.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2TopologyNodeAddChild(
                fc2TopologyNodeContext TopologyNodeContext,
                fc2TopologyNodeContext TopologyNodeChildContext);

    /**
     * Get the number of ports.
     *
     * @param TopologyNodeContext The Topology Node context to use.
     * @param pNumPorts Number of ports.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2TopologyNodeGetNumPorts(
                fc2TopologyNodeContext TopologyNodeContext,
                unsigned int* pNumPorts);

    /**
     * Get type of port located at the specified position.
     *
     * @param TopologyNodeContext The Topology Node context to use.
     * @param position Position of the port.
     * @param pPortType PortType at the specified position.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2TopologyNodeGetPortType(
                fc2TopologyNodeContext TopologyNodeContext,
                unsigned int position,
                fc2PortType* pPortType);

    /**
     * Add the specified PortType as a port of the node.
     *
     * @param TopologyNodeContext The Topology Node context to use.
     * @param portType childPort The port to add.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2TopologyNodeAddPortType(
                fc2TopologyNodeContext TopologyNodeContext,
                fc2PortType portType);

    /**
     * Assign a PGRGuid and device ID to the node.
     *
     * @param TopologyNodeContext The Topology Node context to use.
     * @param guid PGRGuid to be assigned.
     * @param deviceId Device ID to be assigned.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API BOOL
        fc2TopologyNodeAssignGuidToNode(
                fc2TopologyNodeContext TopologyNodeContext,
                fc2PGRGuid guid,
                int deviceId);

    /**
     * Assign a PGRGuid, device ID and nodeType to the node.
     *
     * @param TopologyNodeContext The Topology Node context to use.
     * @param guid PGRGuid to be assigned.
     * @param deviceId Device ID to be assigned.
     * @param nodeType NodeType to be assigned
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API BOOL
        fc2TopologyNodeAssignGuidToNodeEx(
                fc2TopologyNodeContext TopologyNodeContext,
                fc2PGRGuid guid,
                int deviceId,
                fc2NodeType nodeType);

    /**
     * Destroy a TopologyNode context.
     *
     * @param TopologyNodeContext A Topology Node context.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2DestroyTopologyNode(
                fc2TopologyNodeContext TopologyNodeContext );

    /*@}*/

    /**
    * @defgroup CUtilities Utilities
    *
    * @brief The utility operations are used to query for general system
    * information such as operating system, available memory etc.
    * It can also be used to launch browsers, CHM viewers or terminal commands.
    */
    /*@{*/

    /**
     * Check for driver compatibility for the given camera guid.
     *
     * @param pGuid The PGRGuid of the device to check.
     *
     * @return FC2_ERROR_OK if the library is compatible with the currently
     *         loaded driver, otherwise an error indicating the type of failure.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2CheckDriver( const fc2PGRGuid* pGuid);

    /**
     * Get the driver's name for a device
     *
     * @param pGuid The PGRGuid of the device to check.
     * @param pDeviceName The device name will be returned in this string
     * @param pDeviceNameLength The length of the device name string returned
     *
     * @return An Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetDriverDeviceName(
            const fc2PGRGuid* pGuid,
            char* pDeviceName,
            size_t* deviceNameLength);

    /**
     * Get system information.
     *
     * @param pSystemInfo Structure to receive system information.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetSystemInfo( fc2SystemInfo* pSystemInfo);

    /**
     * Get library version.
     *
     * @param pVersion Structure to receive the library version.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2GetLibraryVersion( fc2Version* pVersion);

    /**
     * Launch a URL in the system default browser.
     *
     * @param pAddress URL to open in browser.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2LaunchBrowser( const char* pAddress);

    /**
     * Open a CHM file in the system default CHM viewer.
     *
     * @param pFileName Filename of CHM file to open.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2LaunchHelp( const char* pFileName);

    /**
     * Execute a command in the terminal. This is a blocking call that
     * will return when the command completes.
     *
     * @param pCommand Command to execute.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2LaunchCommand( const char* pCommand);

    /**
     * Execute a command in the terminal. This is a non-blocking call that
     * will return immediately. The return value of the command can be
     * retrieved in the callback.
     *
     * @param pCommand Command to execute.
     * @param pCallback Callback to fire when command is complete.
     * @param pUserData Data pointer to pass to callback.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API fc2Error
        fc2LaunchCommandAsync(
                const char* pCommand,
                fc2AsyncCommandCallback pCallback,
                void* pUserData );

    /**
     * Get a string representation of an error.
     *
     * @param error Error to be parsed.
     *
     * @return A fc2Error indicating the success or failure of the function.
     */
    FLYCAPTURE2_C_API const char*
        fc2ErrorToDescription(
                fc2Error error);

    /*@}*/

#ifdef __cplusplus
};
#endif

#endif // FLIR_FC2_FLYCAPTURE2_C_H