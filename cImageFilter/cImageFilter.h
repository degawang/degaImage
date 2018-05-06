#pragma once
#include "opencv2/opencv.hpp"

namespace degawong {

#define dega_pi 3.1415926

	class cImageFilter {
	public:
		cImageFilter();
		cImageFilter(int mergeMode);
		virtual ~cImageFilter();

	public:
		int setFilterMode(int mergeMode);

	
	public:
		int spherize(cv::Mat &inputMat,cv::Mat &outputMat);
		int edgeLight(const cv::Mat &inputMat,cv::Mat &outputMat);
		int imageSharp(const cv::Mat &inputMat,cv::Mat &outputMat);
	private:
		int nFilterMode;

	};
}


