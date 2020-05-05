#include "Camera.h"
#include <iostream>


#include "CameraPointGrey.h"

// Global camera enumerator
std::vector< std::vector<CameraInfo> > Camera::GetInterfaceCameraList(){
    std::vector< std::vector<CameraInfo> > ret;

#ifdef WITH_CAMERAPOINTGREY
    std::vector<CameraInfo> ptgreycameras = CameraPointGrey::getCameraList();
    ret.push_back(ptgreycameras);
#endif

    return ret;
}

// Camera factory
Camera* Camera::NewCamera(unsigned int interfaceNum , unsigned int camNum , CameraTriggerMode triggerMode){

	std::cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" << std::endl;
	
    if(interfaceNum == 0)
        return new CameraPointGrey(camNum , triggerMode);

    return (Camera*)NULL;
}
