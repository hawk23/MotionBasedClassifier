#define _USE_MATH_DEFINES

#include <opencv2\opencv.hpp>
#include <math.h>
#include <iostream>
#include <iomanip>

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
	void addMotionVector(Point a, Point b);

	float valueAt(int index);
	void normalize(float factor);
	void print();

private:
	float bins[13] = {0};
};

