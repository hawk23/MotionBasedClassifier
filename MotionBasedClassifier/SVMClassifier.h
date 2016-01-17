#include <opencv2\opencv.hpp>
#include <iostream>
#include <iomanip>
#include "TestResult.h"
#include "PerformanceMeasure.h"

using namespace std;
using namespace cv;
using namespace cv::ml;

#pragma once
class SVMClassifier
{
public:
	SVMClassifier();
	~SVMClassifier();

	void train(Mat trainingData, Mat trainingLabels);
	void test(Mat testData, Mat testLabels);
	void printPerformance(int foldNumber);

private:
	Ptr<SVM> svm;
	TestResult testResult;
};

