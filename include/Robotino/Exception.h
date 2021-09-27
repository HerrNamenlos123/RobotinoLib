#pragma once

#include <exception>

namespace Robotino {

	class NotConnectedException : public std::exception {
	public:
		NotConnectedException() {}
	};

}
