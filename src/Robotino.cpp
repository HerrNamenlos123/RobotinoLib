
#include "Log.h"
#include "Robotino.h"

#include <iostream>

#define CHECK_COM() \
if (!isConnected()) { \
	if (wasConnected) { \
		LOG_CORE_CRITICAL("Connection lost! Robotino is not connected anymore!"); wasConnected = false; \
		throw ConnectionLostException(); \
	} else { \
		LOG_CORE_CRITICAL("Robotino is not connected!"); \
		throw ConnectionLostException(); \
	} \
}

// Main Robotino class

Robotino::Robotino() {

}

Robotino::~Robotino() {
	Disconnect(true);
	rec::robotino::api2::shutdown();
}

bool Robotino::Connect(const std::string& ip) {

	// First, disconnect
	if (isConnected()) {
		if (hostname == ip) {	// Same ip, stay connected
			LOG_CORE_DEBUG("Already connected to {}", address());
			return true;
		}
		else {
			Disconnect();		// Different ip, disconnect and reconnect
		}
	}

	hostname = ip;
	wasConnected = false;

	// Connect
	LOG_CORE_DEBUG("Connecting to address {}", hostname.c_str());
	setAddress(hostname.c_str());

	try {
		connectToServer(true);
	}
	catch (const rec::robotino::api2::RobotinoException& e) {
		LOG_CORE_ERROR("Failed to connect to address {}: {}", address(), e.what());
		return false;
	}

	if (!isConnected()) {
		LOG_CORE_ERROR("Failed to connect to address {}: Connection is not active anymore");
		return false;
	}

	LOG_CORE_INFO("Connection Established");
	wasConnected = true;
	return true;
}

void Robotino::Disconnect(bool silent) {

	if (isConnected()) {
		Stop();
		disconnectFromServer();
		LOG_CORE_INFO("Connection closed");
	}
	else {
		if (wasConnected) {
			LOG_CORE_WARN("Connection was not active anymore at the time of disconnecting, may have been lost");
		}
		else if (!silent) {
			LOG_CORE_DEBUG("Connection wasn't active");
		}
	}
	wasConnected = false;
}



// Simple Drive functions and sensor interfaces

void Robotino::DriveDirect(float x, float y, float omega) {
	CHECK_COM();

	omniDrive.setVelocity(x, y, omega);
}

void Robotino::Stop() {
	CHECK_COM();

	omniDrive.setVelocity(0, 0, 0);
}

bool Robotino::GetBumper() {
	CHECK_COM();

	return bumper.value();
}

std::vector<double> Robotino::GetPose() {
	CHECK_COM();

	double x, y, phi;
	pose.readings(&x, &y, &phi);

	return { x, y, phi };
}

float Robotino::GetDistanceSensor(int index) {
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
