// KeypointMatching.cpp : Defines the entry point for the console application.
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

using namespace std;
using namespace cv;

int main()
{
	VideoCapture capture(0);

	if (!capture.isOpened()) 
	{
		cout << "error at opening camera" << endl;
		return 1;
	}

	Mat frametoFind;

	//Use ORB Keypoint Detector & Descriptor
	Ptr<Feature2D> orb = ORB::create(100, 1.2f, 4, 63);

	vector<KeyPoint> kpFrameToFind;
	Mat descFrameToFind;

	//Create Brute-Force Matcher
	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming(2)");

	Mat frame;
	bool setFrameToFind = true;

	while (capture.read(frame)) 
	{
		//resize for sake of better demonstration
		resize(frame, frame, Size(frame.cols / 2, frame.rows / 2));

		imshow("Matches", frame);

		//set current frame as target
		if (setFrameToFind) 
		{
			frametoFind = frame.clone();
			orb->detectAndCompute(frametoFind, noArray(), kpFrameToFind, descFrameToFind);
			setFrameToFind = false;
		}

		//detect keypoints and compute descriptors
		vector<KeyPoint> kpFrame;
		Mat descFrame;
		orb->detectAndCompute(frame, noArray(), kpFrame, descFrame);
		
		//match descriptors
		vector<DMatch> matches;

		if (descFrameToFind.rows == descFrame.rows && descFrameToFind.cols == descFrame.cols) 
		{
			matcher->match(descFrameToFind, descFrame, matches);
			//compute average distance
			double dist = 0;
			for (int i = 0; i < matches.size(); i++) {
				dist += matches[i].distance;
			}
			dist /= matches.size();
			cout << "Distance: " << dist << endl;
			//leave only 25 matches with lowest distance
			nth_element(matches.begin(), matches.begin() + 24, matches.end());
			matches.erase(matches.begin() + 25, matches.end());
			//draw matches
			Mat result;
			drawMatches(frametoFind, kpFrameToFind, frame, kpFrame, matches,
				result);
			imshow("Matches", result);
		}

		int key = waitKey(5);

		if (key == 32) {
			setFrameToFind = true;
		}
		else if (key == 'q') {
			break;
		}
	}

	capture.release();

	return 0;
}

