#include "MotionHistogram.h"

#pragma once
class Shot
{
public:
	Shot(int start, int end, int jumpOff);
	~Shot();

	void set_histogram(MotionHistogram histogram);
	MotionHistogram& get_histogram();
	int get_end();
	int get_start();
	int get_jumpOff();

private:
	int start;
	int end;
	int jumpOff;
	MotionHistogram histogram;
};

