#include "Helper_Functions.h"

double toRadians(double degrees)
{
	return degrees * PI / 180;
}

double CalculateAbsDistance(const POINT& p1, const POINT& p2)
{
	return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}
