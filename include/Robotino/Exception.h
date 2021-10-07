#pragma once

#include <exception>

namespace Robotino {

	class NotConnectedException : public std::exception {
	public:
		NotConnectedException() : std::exception("Robotino::NotConnectedException -> Connection may have been lost") {}
	};

}
