#include "stdafx.h"
#include "MotionHistogram.h"

MotionHistogram::MotionHistogram()
{
}


MotionHistogram::~MotionHistogram()
{
}

void MotionHistogram::addMotionVector(Point a, Point b)
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

float MotionHistogram::valueAt(int index)
{
	// TODO: check bounds

	return bins[index];
}

void MotionHistogram::normalize(float factor)
{
	if (factor > 0)
	{
		// HACK: hardcoded value
		for (int i = 0; i < 13; i++)
		{
			bins[i] = (float) bins[i] / factor;
		}
	}
}

void MotionHistogram::print()
{
	cout << "[ ";

	for (int i = 0; i < 13; i++)
	{
		cout << setprecision(4) << bins[i] << " ";
	}

	cout << "]" << endl;
}