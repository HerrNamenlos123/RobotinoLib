#pragma once

// Suppress warnings from Robotino API
#pragma warning( push )
#pragma warning( disable : 4018 )	// Suppress signed/unsigned mismatch
#pragma warning( disable : 4996 )	// Suppress deprecation warning

#include <rec/robotino/api2/all.h>
using namespace rec::robotino;

#pragma warning( pop )	// But only in these headers
