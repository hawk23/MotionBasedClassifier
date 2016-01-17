#include <opencv2\opencv.hpp>
#include <iostream>
#include <iomanip>
#include "FeatureExtractor.h"

using namespace std;
using namespace cv;
using namespace cv::ml;


#pragma once

/*
Implements Helper methods to perform 5-fold cross validation
on a given dataset
*/
class CrossValidationManager
{
public:
	CrossValidationManager(FeatureExtractor &extractor);
	~CrossValidationManager();

	void getFold (int number, Mat &trainingData, Mat &testData, Mat &trainingLabels, Mat &testLabels);

private:
	FeatureExtractor &extractor;
};

