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
	// Test the SVM with the second part of data (i.e. 20%)
	double correct = 0;

	for (int i = 0; i < testData.rows; i++)
	{
		Mat sampleHist(0, testData.cols, CV_32FC1);
		sampleHist.push_back(testData.row(i));

		int response				= (int) svm->predict(sampleHist);
		int correctResponse			= testLabels.at<int>(i, 0);

		cout << "correct: " << correctResponse << "\t-> response: " << response << endl;

		if (response == correctResponse)
		{
			correct++;
		}
	}

	cout << "correct: " << correct << endl;

	// TODO: Precision, Recall, F1
}
