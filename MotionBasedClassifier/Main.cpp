// MotionBasedClassifier.cpp : Defines the entry point for the console application.
// 

#include "stdafx.h"
#include <iostream>
#include <opencv2\opencv.hpp>
#include <opencv2\video.hpp>
#include <opencv2\imgproc.hpp>
#include <set>
#include <iterator>
#include <iomanip>
#include <fstream>
#include "FeatureExtractor.h"
#include "SVMClassifier.h"
#include "CrossValidationManager.h"

using namespace std;
using namespace cv;
using namespace cv::ml;

int main(int argc, char **argv)
{
	// extract Features and create Shot objects holding MotionHistograms and additional info about the shot
	FeatureExtractor			extractor		= FeatureExtractor ();
	extractor.extract();

	// create datasets
	Mat							trainingData, trainingLabels, testData, testLabels;
	CrossValidationManager		cvManager		= CrossValidationManager (extractor);

	/**
	 * start 5-fold cross validation of our feature extractor and classifier
	 */

	for (int foldNumber = 1; foldNumber <= 5; foldNumber++)
	{
		cvManager.getFold(foldNumber, trainingData, testData, trainingLabels, testLabels);

		// create classifier
		SVMClassifier				classifier = SVMClassifier();

		classifier.train(trainingData, trainingLabels);
		classifier.test(testData, testLabels);
		classifier.printPerformance(foldNumber);
	}

	return 0;
}