#include "stdafx.h"
#include "PerformanceMeasure.h"

float PerformanceMeasure::computeRecall(int truePositive, int falseNegative)
{
	if (truePositive + falseNegative > 0)
	{
		return (float)truePositive / ((float)truePositive + (float)falseNegative);
	}
	else
	{
		return 0;
	}

}

float PerformanceMeasure::computePrecision(int truePositive, int falsePositive)
{
	if (truePositive + falsePositive > 0)
	{
		return (float)truePositive / ((float)truePositive + (float)falsePositive);
	}
	else
	{
		return 0;
	}

}

float PerformanceMeasure::computeF1(int truePositive, int falsePositive, int falseNegative)
{
	float r = computeRecall(truePositive, falseNegative);
	float p = computePrecision(truePositive, falsePositive);

	if (p + r > 0)
	{
		return 2.0 * (p*r) / (p + r);
	}
	else
	{
		return 0;
	}
}

float PerformanceMeasure::computeAccuracy(int truePositive, int falsePositive, int trueNegative, int falseNegative)
{
	return (float) (truePositive + trueNegative) / (float) (truePositive + trueNegative + falsePositive + falseNegative);
}