#pragma once

#include "Robotino/RobotinoApi2.h"

namespace Robotino {

	class RobotinoImpl : private api2::Com {

		// Core utilities
		std::string hostname;
		bool wasConnected = false;

		// Sensors and actuators
		api2::OmniDrive omniDrive;
		api2::Bumper bumper;
		api2::DistanceSensor sensors[9];
		api2::Pose pose;

	public:
		RobotinoImpl();
		~RobotinoImpl();

		void Connect(const std::string& ip);
		void Disconnect(bool silent = false);

		void DriveDirect(float x, float y, float omega);
		void Stop();
		bool GetBumper();
		std::vector<double> GetPose();

		float GetDistanceSensor(int index);

	};

}
