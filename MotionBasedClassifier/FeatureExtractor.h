#include "stdafx.h"
#include <iostream>
#include <opencv2\opencv.hpp>
#include <opencv2\video.hpp>
#include <opencv2\imgproc.hpp>
#include <set>
#include <iterator>
#include <iomanip>
#include <fstream>
#include "MotionHistogram.h"
#include "Shot.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

#pragma once
class FeatureExtractor
{
public:
	FeatureExtractor();
	~FeatureExtractor();

	// methods

	void extract();
	vector<Shot>& get_data();

private:
	void readGroundTruth();
	bool isInteger(const std::string & s);

	vector<Shot> shots;

	const string videoPath = "D:\\Uni\\WS2015\\VC Current Topics in Distributed Multimedia Systems Video Retrieval\\Final Project\\oberstdorf08small.mp4";
	const string groundTruthPath = "D:\\Uni\\WS2015\\VC Current Topics in Distributed Multimedia Systems Video Retrieval\\Final Project\\GroundTruth.csv";
};

