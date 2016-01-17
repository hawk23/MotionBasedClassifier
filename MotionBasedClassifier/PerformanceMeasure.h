#pragma once
class PerformanceMeasure
{
public:
	static float computeRecall(int correctResults, int missedResults);
	static float computePrecision(int correctResults, int falseResults);
	static float computeF1(int correctResults, int falseResults, int missedResults);
	static float computeAccuracy(int truePositive, int falsePositive, int trueNegative, int falseNegative);
};

