#include "Precision.h"

namespace rtc {


	bool approxEqual(double a, double b, double relEpsilon) {
		// Return true if the numbers are close to each other and difference is lower than EPSILON.
		double diff{ std::abs(a - b) };
		if (diff <= EPSILON)
			return true;
		// Return true if the difference between a and b is within epsilon % of the larger of a and b (Knuth).
		return (diff <= (std::max(std::abs(a), std::abs(b)) * relEpsilon));
	}

}