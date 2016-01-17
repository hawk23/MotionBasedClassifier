#include "stdafx.h"
#include "PerformanceMeasure.h"

float PerformanceMeasure::computeRecall(int correctResults, int missedResults)
{
	if (correctResults + missedResults > 0)
	{
		return (float)correctResults / ((float)correctResults + (float)missedResults);
	}
	else
	{
		return 0;
	}

}

float PerformanceMeasure::computePrecision(int correctResults, int falseResults)
{
	if (correctResults + falseResults > 0)
	{
		return (float)correctResults / ((float)correctResults + (float)falseResults);
	}
	else
	{
		return 0;
	}

}

float PerformanceMeasure::computeF1(int correctResults, int falseResults, int missedResults)
{
	float r = computeRecall(correctResults, missedResults);
	float p = computePrecision(correctResults, falseResults);

	if (p + r > 0)
	{
		return 2.0 * (p*r) / (p + r);
	}
	else
	{
		return 0;
	}
}