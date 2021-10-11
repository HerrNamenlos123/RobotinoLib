#pragma once

#include <exception>

namespace Robotino {

	class NotConnectedException : public std::logic_error {
	public:
		NotConnectedException() : std::logic_error("Robotino::NotConnectedException -> Connection may have been lost") {}
	};

}
