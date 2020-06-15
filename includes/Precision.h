/*
* Interface file for code that changes the Ray Tracer precision.
*
*
* This file contains the definitions for Ray Tracer project precision,
* in order to change it easily from a single header file.
*
*/

#ifndef RTC_PRECISION_H
#define RTC_PRECISION_H
#define PI 3.14159265


#include <algorithm>
#include <cmath>

namespace rtc {

	/*
	Defines a real number precision. RTC can be compiled in
	single or double pricision, just by changing the typedef.
	*/

	typedef float real;

	// Test for floating point numbers for equivalence.
	constexpr double EPSILON{ 0.00001 };
	bool approxEqual(double a, double b, double relEpsilon);

}

#endif // RTC_PRECISION_H
