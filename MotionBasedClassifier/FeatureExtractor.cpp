#include "stdafx.h"
#include "FeatureExtractor.h"


FeatureExtractor::FeatureExtractor()
{
}


FeatureExtractor::~FeatureExtractor()
{
}

void FeatureExtractor::extract()
{
	// reads the ground truth and creates Shot objects
	readGroundTruth();

	// extract features

	vector<MotionHistogram> result;

	//open VideoCapture etc...
	VideoCapture capture = VideoCapture(videoPath);
	int frameNumber = 1;

	vector<Point2f> currFeatures;
	vector<Point2f> prevFeatures;

	int count = 0;
	Mat fullframe, frame, gray, prevFrame;
	int resizeFactor = 1;

	int currentShot = 0;
	MotionHistogram currentHistogram;

	while (capture.read(fullframe))
	{
		//resize for sake of better demonstration
		resize(fullframe, frame, Size(fullframe.cols / resizeFactor, fullframe.rows / resizeFactor));

		//convert to grayscale (for optical flow estimation)
		cvtColor(frame, gray, CV_RGB2GRAY);

		// perform dense sampling of points)

		// maximum number of points returned
		int maxCorners = 400;
		double qualityLevel = 0.01;
		double minDistance = 10.; // minDistance – The minimum possible Euclidean distance between the returned corners

		Mat cloned = gray.clone();
		cv::goodFeaturesToTrack(cloned, currFeatures, maxCorners, qualityLevel, minDistance);

		//optical flow estimation
		vector<uchar> status;
		vector<float> err;

		if (prevFeatures.size() == currFeatures.size())
		{
			calcOpticalFlowPyrLK(prevFrame, gray, prevFeatures, currFeatures, status, err);
		}

		for (int i = 0; i < status.size(); i++)
		{
			if (status[i] != 0)
			{
				currentHistogram.addMotionVector(prevFeatures[i], currFeatures[i]);
			}
		}

		//next time continue with current features
		prevFeatures = currFeatures;
		prevFrame = gray.clone();

		// check if next shot is finished
		if (frameNumber == shots[currentShot].get_end())
		{
			// save hist to shot
			shots[currentShot].set_histogram(currentHistogram);

			// reset hist
			currentHistogram = MotionHistogram();

			// goto next shot;
			currentShot++;

			// check if last shot was reached
			if (shots.size() == currentShot)
			{
				break;
			}
		}

		frameNumber++;
	}

	//close VideoCapture etc.
	capture.release();
}

void FeatureExtractor::readGroundTruth()
{
	string line;
	ifstream infile(groundTruthPath);

	while (getline(infile, line))
	{
		stringstream		lineStream(line);
		string				cell;
		vector<string>		result;

		while (std::getline(lineStream, cell, ';'))
		{
			result.push_back(cell);
		}

		if (!isInteger(result[0]))
		{
			continue;
		}

		// create Shot object
		Shot shot(stoi(result[0]), stoi(result[1]), stoi(result[2]));
		shots.push_back(shot);
	}
}

bool FeatureExtractor::isInteger(const std::string & s)
{
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

	char * p;
	strtol(s.c_str(), &p, 10);

	return (*p == 0);
}

vector<Shot>& FeatureExtractor::get_data()
{
	return shots;
}