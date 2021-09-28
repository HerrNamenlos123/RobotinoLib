
#include "Robotino/Log.h"
#include "Robotino/RobotinoImpl.h"
#include "Robotino/Exception.h"

#include <iostream>

#define CHECK_COM() \
if (!isConnected()) { \
	if (wasConnected) { \
		wasConnected = false; \
		throw Robotino::NotConnectedException(); \
	} else { \
		throw Robotino::NotConnectedException(); \
	} \
}

namespace Robotino {

	// Main Robotino class

	RobotinoImpl::RobotinoImpl() {

	}

	RobotinoImpl::~RobotinoImpl() {
		Disconnect(true);
		//rec::robotino::api2::shutdown();
	}

	void RobotinoImpl::Connect(const std::string& ip) {

		// Check if we're already connected
		if (isConnected()) {
			if (hostname == ip) {	// Same ip, stay connected
				LOG_CORE_WARN("Already connected to '{}'", address());
				return;
			}
			else {
				Disconnect();		// Different ip, disconnect and reconnect
			}
		}

		hostname = ip;
		wasConnected = false;

		// Connect
		LOG_CORE_INFO("Connecting...");
		setAddress(hostname.c_str());

		try {
			connectToServer(true);
		}
		catch (const rec::robotino::api2::RobotinoException& e) {
			LOG_CORE_ERROR("Connection to '{}' failed: {}", address(), e.what());
			throw Robotino::NotConnectedException();
		}

		LOG_CORE_INFO("Connected to '{}'", hostname.c_str());
		wasConnected = true;
	}

	void RobotinoImpl::Disconnect(bool silent) {

		if (isConnected()) {
			Stop();
			disconnectFromServer();
			if (!silent) {
				LOG_CORE_INFO("Connection closed");
			}
		}
		else {
			if (!silent) {
				if (wasConnected) {
					LOG_CORE_WARN("Can't disconnect, connection has been lost");
				}
				else {
					LOG_CORE_DEBUG("Can't disconnect, wasn't connected");
				}
			}
		}
		wasConnected = false;
	}



	// Simple Drive functions and sensor interfaces

	void RobotinoImpl::DriveDirect(float x, float y, float omega) {
		CHECK_COM();
		omniDrive.setVelocity(x, y, omega);
	}

	void RobotinoImpl::Stop() {
		CHECK_COM();
		omniDrive.setVelocity(0, 0, 0);
	}

	bool RobotinoImpl::GetBumper() {
		CHECK_COM();
		return bumper.value();
	}

	std::vector<double> RobotinoImpl::GetPose() {
		CHECK_COM();

		double x, y, phi;
		unsigned int id;
		processEvents();
		pose.readings(&x, &y, &phi, nullptr, nullptr, nullptr, &id);
		LOG_CORE_WARN("{}", id);

		return { x, y, phi };
	}

	Image RobotinoImpl::GetCamera() {
		CHECK_COM();
		processEvents();
		return camera.image;
	}

	float RobotinoImpl::GetDistanceSensor(int index) {
		CHECK_COM();

		if (index < 0 || index >= 9) {
			throw std::out_of_range("Sensor index out of range");
		}

		return sensors[index].distance() * 1000.0f;
	}












	/*
	void Robotino::UpdateDigitalInputs() {

		CHECK_COM();

		try {
			digitalInputArray.values(digitalInputs);
		}
		catch (const rec::robotino::api2::RobotinoException& e) {

			std::cout << "Can't update digital inputs, com is invalid! Exception message '" << e.what() << "'" << std::endl;
			return;
		}
	}

	bool Robotino::GetDigitalInput(size_t index) {

		CHECK_COM_0();

		updateDigitalInputs();

		if (index >= numberOfDigitalInputs) {
			std::cout << "Can't get digital input: Invalid index!" << std::endl;
			return false;
		}

		return digitalInputs[index];
	}

	void Robotino::UpdateAnalogInputs() {

		CHECK_COM();

		try {
			analogInputArray.values(analogInputs);
		}
		catch (const rec::robotino::api2::RobotinoException& e) {

			std::cout << "Can't update analog inputs, com is invalid! Exception message '" << e.what() << "'" << std::endl;
			return;
		}
	}

	bool Robotino::GetAnalogInput(size_t index) {

		CHECK_COM_0();

		updateAnalogInputs();

		if (index >= numberOfAnalogInputs) {
			std::cout << "Can't get analog input: Invalid index!" << std::endl;
			return false;
		}

		return analogInputs[index];
	}

	void Robotino::UpdateDigitalOutputs() {

		CHECK_COM();

		try {
			digitalOutputArray.setValues(digitalOutputs, (unsigned int)numberOfDigitalOutputs);
		}
		catch (const rec::robotino::api2::RobotinoException& e) {

			std::cout << "Can't update digital outputs, com is invalid! Exception message '" << e.what() << "'" << std::endl;
			return;
		}
	}

	void Robotino::SetDigitalOutput(size_t index, bool value) {

		CHECK_COM();

		if (index >= numberOfDigitalOutputs) {
			std::cout << "Can't set digital output: Invalid index!" << std::endl;
			return;
		}

		digitalOutputs[index] = value;

		updateDigitalOutputs();
	}

	*/
}
