#pragma once

#include <exception>

// A very simple exception indicating that the connection to the robotino was lost
class ConnectionLostException : public std::exception {
public:
	ConnectionLostException() {
	}
};
