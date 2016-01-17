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

using namespace std;
using namespace cv;
using namespace cv::ml;

float TRAIN_PCT = 0.8;
int numBins = 13; // HACK

int main(int argc, char **argv)
{
	// extract Features and create Shot objects holding MotionHistograms and additional info about the shot
	FeatureExtractor extractor = FeatureExtractor();
	extractor.extract();

	vector<Shot> shots = extractor.get_data();

	int rows = shots.size()*TRAIN_PCT;

	Mat trainingDataMat(rows, numBins, CV_32FC1);
	Mat labelsMat(rows, 1, CV_32SC1);

	// copy data
	for (int i = 0; i < rows; i++) 
	{
		for (int k = 0; k < numBins; k++) 
		{
			float value = shots[i].get_histogram().valueAt(k);
			trainingDataMat.at<float>(i, k) = value;
		}

		int label = shots[i].get_jumpOff();
		labelsMat.at<int>(i) = label;
	}

	// Train the SVM with the first part of data (i.e. 80%)
	Ptr<SVM> svm = SVM::create();
	svm->setType(SVM::C_SVC);
	svm->setKernel(SVM::RBF);
	// svm->setTermCriteria(TermCriteria(CV_TERMCRIT_ITER + CV_TERMCRIT_EPS, 1000, 1e-3));
	svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 1000, 1e-6));
	svm->train(trainingDataMat, ROW_SAMPLE, labelsMat);

	// Test the SVM with the second part of data (i.e. 20%)
	double correct = 0;

	for (int i = rows; i < shots.size(); i++)
	{
		Mat sampleHist(1, numBins, CV_32FC1);

		for (int k = 0; k < numBins; k++) 
		{
			float value = shots[i].get_histogram().valueAt(k);
			sampleHist.at<float>(0, k) = value;
		}

		float response = svm->predict(sampleHist);

		cout << "correct: " << shots[i].get_jumpOff()<< "\t-> response: " << response << endl;
		if (response == shots[i].get_jumpOff()) 
		{
			correct++;
		}
	}

	cout << "correct: " << correct << endl;

	return 0;
}