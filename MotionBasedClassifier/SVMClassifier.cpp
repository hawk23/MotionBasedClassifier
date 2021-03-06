#include "stdafx.h"
#include "SVMClassifier.h"


SVMClassifier::SVMClassifier()
{
	// initialize SVM
	this->svm = SVM::create();

	this->svm->setType			(SVM::C_SVC);
	this->svm->setKernel		(SVM::RBF);

	// TermCriteria tc = TermCriteria(CV_TERMCRIT_ITER + CV_TERMCRIT_EPS, 1000, 1e-3);
	TermCriteria tc = TermCriteria(TermCriteria::MAX_ITER, 1000, 1e-6);

	this->svm->setTermCriteria	(tc);
}

SVMClassifier::~SVMClassifier()
{
}

void SVMClassifier::train(Mat trainingData, Mat trainingLabels)
{
	this->svm->train(trainingData, ROW_SAMPLE, trainingLabels);
}

void SVMClassifier::test(Mat testData, Mat testLabels)
{
	testResult = TestResult();

	for (int i = 0; i < testData.rows; i++)
	{
		Mat sampleHist(0, testData.cols, CV_32FC1);
		sampleHist.push_back(testData.row(i));

		int response				= (int) svm->predict(sampleHist);
		int correctResponse			= testLabels.at<int>(i, 0);

		// cout << "correct: " << correctResponse << "\t-> response: " << response << endl;

		// evalute performance
		if (correctResponse == 1 && response == 1)
		{
			// true positives
			testResult.truePositive++;
		}
		else if (correctResponse == 0 && response == 1)
		{
			// false positives
			testResult.falsePositive++;
		}
		else if (correctResponse == 1 && response == 0)
		{
			// false negatives
			testResult.falseNegative++;
		}
		else if (correctResponse == 0 && response == 0)
		{
			// true negatives
			testResult.trueNegative++;
		}
	}
}

void SVMClassifier::printPerformance(int foldNumber)
{
	float precision		= PerformanceMeasure::computePrecision(testResult.truePositive, testResult.falsePositive);
	float recall		= PerformanceMeasure::computeRecall(testResult.truePositive, testResult.falseNegative);
	float f1			= PerformanceMeasure::computeF1(testResult.truePositive, testResult.falsePositive, testResult.falseNegative);
	float accuracy		= PerformanceMeasure::computeAccuracy(testResult.truePositive, testResult.falsePositive, testResult.trueNegative, testResult.falseNegative);

	cout << "Test Result for fold " << foldNumber << endl;
	cout << "Precision:\t"			<< setprecision(3) << precision <<endl;
	cout << "Recall:\t\t"			<< setprecision(3) << recall << endl;
	cout << "F1:\t\t"				<< setprecision(3) << f1 << endl;
	cout << "accuracy:\t"			<< setprecision(3) << accuracy << endl;
	cout << "------------------------------------" << endl;
}