
#include "Robotino.h"
#include "Robotino/RobotinoImpl.h"

namespace Robotino {

	// Robotino::RobotinoImplWrapper
		Robotino::RobotinoImplWrapper::RobotinoImplWrapper() {
			impl = new RobotinoImpl();
		}

		Robotino::RobotinoImplWrapper::~RobotinoImplWrapper() {
			delete impl;
		}

		RobotinoImpl* Robotino::RobotinoImplWrapper::get() {
			return impl;
		}
	// End Robotino::RobotinoImplWrapper





	Robotino::Robotino() {
		impl = std::make_unique<RobotinoImplWrapper>();
	}

	void Robotino::Connect(const std::string& ip) {
		impl->get()->Connect(ip);
	}

	void Robotino::Disconnect(bool silent) {
		impl->get()->Disconnect(silent);
	}

	void Robotino::DriveDirect(float x, float y, float omega) {
		impl->get()->DriveDirect(x, y, omega);
	}

	void Robotino::Stop() {
		impl->get()->Stop();
	}

	bool Robotino::GetBumper() {
		return impl->get()->GetBumper();
	}

	std::vector<double> Robotino::GetPose() {
		return impl->get()->GetPose();
	}

	Image Robotino::GetCamera() {
		return impl->get()->GetCamera();
	}

	float Robotino::GetDistanceSensor(int index) {
		return impl->get()->GetDistanceSensor(index);
	}

}
