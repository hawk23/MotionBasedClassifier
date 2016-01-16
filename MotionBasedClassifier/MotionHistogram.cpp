#include "stdafx.h"
#include "MotionHistogram.h"

MotionHistogram::MotionHistogram()
{
}


MotionHistogram::~MotionHistogram()
{
}

void MotionHistogram::addMotionVector(Point2f a, Point2f b)
{
	float x = b.x - a.x;
	float y = a.y - b.y;

	float angle = atan2(y, x);
	int degree = (int) (angle * 180.0 / M_PI);

	// avoid negative degree. only 0 to 360 allowed
	if (degree < 0)
	{
		degree += 360;
	}

	// add motion vector to bin
	if (degree == 0)
	{
		bins[0]++;
	}
	else
	{
		// one bin has 30°
		int bin = ((int) (degree+15) / 30) + 1;

		if (bin > 12)
		{
			bin -= 12;
		}

		bins[bin]++;
	}
}

int MotionHistogram::valueAt(int index)
{
	// TODO: check bounds

	return bins[index];
}