#pragma once

#include "Robotino/RobotinoApi2.h"
#include "Robotino/Image.h"

namespace Robotino {

	class Camera : public api2::Camera {
	public:
		Image image;

		Camera() {}

		void imageReceivedEvent(const unsigned char* data, unsigned int dataSize, unsigned int width, unsigned int height, unsigned int step) {
			image.load(data, dataSize, width, height, step);
		}
	};

	class RobotinoImpl : private api2::Com {

		// Core utilities
		std::string hostname;
		bool wasConnected = false;

		// Sensors and actuators
		api2::OmniDrive omniDrive;
		api2::Bumper bumper;
		api2::DistanceSensor sensors[9];
		api2::Pose pose;
		Camera camera;

	public:
		RobotinoImpl();
		~RobotinoImpl();

		void Connect(const std::string& ip);
		void Disconnect(bool silent = false);

		void DriveDirect(float x, float y, float omega);
		void Stop();
		bool GetBumper();
		std::vector<double> GetPose();
		Image GetCamera();

		float GetDistanceSensor(int index);

	//private:
		//void CameraImageReceived();

	};

}
