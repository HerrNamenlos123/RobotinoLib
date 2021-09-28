#pragma once

#ifndef DISABLE_LOGGING
#include "Robotino/Log.h"
#endif

#include "Robotino/Exception.h"
#include "Robotino/Image.h"
#include <string>
#include <vector>
#include <memory>

namespace Robotino {

	class RobotinoImpl;

	class Robotino {

		class RobotinoImplWrapper {
			RobotinoImpl* impl = nullptr;
		public:
			RobotinoImplWrapper();
			~RobotinoImplWrapper();
			RobotinoImpl* get();

			RobotinoImplWrapper& operator=(const RobotinoImplWrapper&) = delete;
			RobotinoImplWrapper(const RobotinoImplWrapper&) = delete;
		};

		std::unique_ptr<RobotinoImplWrapper> impl;

	public:
		Robotino();

		void Connect(const std::string& ip);
		void Disconnect(bool silent = false);

		void DriveDirect(float x, float y, float omega);
		void Stop();
		bool GetBumper();
		std::vector<double> GetPose();
		Image GetCamera();

		float GetDistanceSensor(int index);

	};

}
