#include "iostream"

#include "opencv2/opencv.hpp"
#include "cImageMerge.h"
#include "cImageFilter.h"

int main()
{
	int res;
	
	//////////////////////////////////////////////////////////////////////////
	// merge mode
	// degawong::cImageMerge degaMerge(1);
	// cv::Mat u_image_1 = cv::imread("./input/in_1.bmp");
	// cv::Mat u_image_2 = cv::imread("./input/in_2.bmp");
	// res = degaMerge.hardmix(u_image_1, u_image_2);
	// res = degaMerge.overlay(u_image_1, u_image_2);
	// res = degaMerge.pinlight(u_image_1, u_image_2);
	// res = degaMerge.hardlight(u_image_1, u_image_2);
	// res = degaMerge.softlight(u_image_1, u_image_2);
	// res = degaMerge.linerlight(u_image_1, u_image_2);
	// res = degaMerge.vividlight(u_image_1, u_image_2);


	//////////////////////////////////////////////////////////////////////////
	// filter mode
	//
	cv::Mat outputMat;
	degawong::cImageFilter degaFilter(1);
	cv::Mat inputImage = cv::imread("./input/in_1.bmp");
	// res = degaFilter.spherize(inputImage,outputMat);
	// res = degaFilter.edgeLight(inputImage,outputMat);
	res = degaFilter.imageSharp(inputImage,outputMat);
        imwrite("./output/imageSahrp.bmp",outputMat);
	cv::imshow("image result",outputMat);	
	       
	cv::waitKey(8888);

    return 0;
}

