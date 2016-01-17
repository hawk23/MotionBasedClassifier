#pragma once
class TestResult
{
public:
	TestResult();
	~TestResult();

	int truePositive;
	int falsePositive;
	int trueNegative;
	int falseNegative;
};

