#define _USE_MATH_DEFINES

#include <opencv2\opencv.hpp>
#include <math.h>


using namespace cv;
using namespace std;

#pragma once
class MotionHistogram
{
public:
	MotionHistogram();
	~MotionHistogram();

	// methods

	/*
	add a motion vector
	x: x component of the vector
	y: y component of the vector
	*/
	void addMotionVector(Point2f a, Point2f b);

	int valueAt(int index);

private:
	int bins[13] = {0};
};

