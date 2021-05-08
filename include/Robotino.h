#pragma once

#include "RobotinoDeps.h"
#include "Exception.h"
#include <string>

class Robotino : public Com {

	// Core utilities
	std::string hostname;
	bool wasConnected = false;

	// Sensors and actuators
	OmniDrive omniDrive;
	Bumper bumper;
	DistanceSensor sensors[9];

public:
	Robotino();
	~Robotino();

	bool Connect(const std::string& ip);
	void Disconnect(bool silent = false);

	void DriveDirect(float x, float y, float omega);
	void Stop();
	bool GetBumper();
	
	float GetDistanceSensor(int index);

};
