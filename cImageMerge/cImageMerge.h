#pragma once
#include "opencv2/opencv.hpp"

namespace degawong {

	class cImageMerge {
	public:
		cImageMerge();
		cImageMerge(int mergeMode);
		virtual ~cImageMerge();

	public:
		int setMergeMode(int mergeMode);


	public:
		int hardmix(cv::Mat &inputImage_1, cv::Mat &inputImage_2);
		int overlay(cv::Mat &inputImage_1, cv::Mat &inputImage_2);
		int pinlight(cv::Mat &inputImage_1, cv::Mat &inputImage_2);
		int hardlight(cv::Mat &inputImage_1, cv::Mat &inputImage_2);
		int softlight(cv::Mat &inputImage_1, cv::Mat &inputImage_2);
		int linerlight(cv::Mat &inputImage_1, cv::Mat &inputImage_2);
		int vividlight(cv::Mat &inputImage_1, cv::Mat &inputImage_2);

	private:
		int nMergeMode;

	};
}


