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

float TRAIN_PCT = 0.8;
int numBins = 13; // HACK

int main(int argc, char **argv)
{
	// extract Features and create Shot objects holding MotionHistograms and additional info about the shot
	FeatureExtractor			extractor		= FeatureExtractor ();
	extractor.extract();

	// create datasets
	Mat							trainingData;
	Mat							trainingLabels;
	Mat							testData;
	Mat							testLabels;
	CrossValidationManager		cvManager		= CrossValidationManager (extractor);

	cvManager.getFold			(5, trainingData, testData, trainingLabels, testLabels);

	// create classifier
	SVMClassifier				classifier		= SVMClassifier ();

	classifier.train			(trainingData, trainingLabels);
	classifier.test				(testData, testLabels);

	return 0;
}