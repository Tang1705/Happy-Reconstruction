#pragma once

#include "Camera.h"
#include "CameraPointGrey.h"
#include "ProjectorLC4500.h"


class Device
{
public:
	static Device* instance;
	static Device* getInstance();
	Camera* getCamera();
	Projector* getProjector();
	bool getHasCamera();
	bool getHasProjector();

private:
	Device();
	
	Camera *camera;
	Projector *projector;
	// variable indicate whether the camera and projector
	// have been initialized or not
	bool hasCamera = false;
	bool hasProjector = false;
	
};
