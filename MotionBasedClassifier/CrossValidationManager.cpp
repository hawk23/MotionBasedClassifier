#include "stdafx.h"
#include "CrossValidationManager.h"

CrossValidationManager::CrossValidationManager(FeatureExtractor &extractor) : extractor(extractor)
{
}

CrossValidationManager::~CrossValidationManager()
{
}

/*
builds data sets for the n-th fold of a 5-fold cross validation procedure
*/
void CrossValidationManager::getFold(int number, Mat &trainingData, Mat &testData, Mat &trainingLabels, Mat &testLabels)
{
	vector<Shot> shots		= extractor.get_data();

	int numBins				= 13; // HACK!

	int sampleCount			= shots.size();
	int testSampleCount		= sampleCount / 5;

	int testStartIndex		= testSampleCount * (number - 1);
	int testEndIndex		= testStartIndex + testSampleCount - 1;

	int trainIndex			= 0;
	int testIndex			= 0;

	// create Mat objects
	trainingData			= Mat(sampleCount - testSampleCount,	numBins,	CV_32FC1);
	trainingLabels			= Mat(sampleCount - testSampleCount,	1,			CV_32SC1);
	testData				= Mat(testSampleCount,					numBins,	CV_32FC1);
	testLabels				= Mat(testSampleCount,					1,			CV_32SC1);

	// copy data to Mat objects
	for (int i = 0; i < sampleCount; i++)
	{
		// test data
		if (i >= testStartIndex && i <= testEndIndex)
		{
			for (int k = 0; k < numBins; k++)
			{
				float value = shots[i].get_histogram().valueAt(k);
				testData.at<float>(testIndex, k) = value;
			}

			int label = shots[i].get_jumpOff();
			testLabels.at<int>(testIndex) = label;

			testIndex++;
		}
		// training data
		else
		{
			for (int k = 0; k < numBins; k++)
			{
				float value = shots[i].get_histogram().valueAt(k);
				trainingData.at<float>(trainIndex, k) = value;
			}

			int label = shots[i].get_jumpOff();
			trainingLabels.at<int>(trainIndex) = label;

			trainIndex++;
		}
	}
}
