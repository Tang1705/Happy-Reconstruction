#include "Device.h"
#include <QDebug>
Device* Device::instance = nullptr;

Device::Device()
{
	vector<CameraInfo> cams = CameraPointGrey::getCameraList();
	if (cams.size() != 0)
	{
		hasCamera = true;
		camera = Camera::NewCamera(0, cams[0].busID, triggerModeSoftware);
		CameraSettings camSettings;
		camSettings.shutter = 25;
		camSettings.gain = 0.0;
		camera->setCameraSettings(camSettings);
		camera->startCapture();
	}

	projector = new ProjectorLC4500(0);
	if (projector->getIsRunning())hasProjector = true;
}

Device* Device::getInstance()
{
	if (instance == nullptr) instance = new Device();
	return instance;
}

Camera* Device::getCamera()
{
	return camera;
}

Projector* Device::getProjector()
{
	return projector;
}

bool Device::getHasCamera()
{
	return hasCamera;
}

bool Device::getHasProjector()
{
	return hasProjector;
}
