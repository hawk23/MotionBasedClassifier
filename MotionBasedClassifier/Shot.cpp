#include "stdafx.h"
#include "Shot.h"

Shot::Shot(int start, int end, int jumpOff) : start(start), end(end), jumpOff(jumpOff)
{
	
}

Shot::~Shot()
{
}

void Shot::set_histogram(MotionHistogram histogram)
{
	this->histogram = histogram;
}

int Shot::get_end()
{
	return this->end;
}

int Shot::get_start()
{
	return this->start;
}

MotionHistogram& Shot::get_histogram()
{
	return this->histogram;
}

int Shot::get_jumpOff()
{
	return this->jumpOff;
}