#include "iostream"
#include "algorithm"
#include "cImageFilter.h"

namespace degawong {


	cImageFilter::cImageFilter() {
	}

	cImageFilter::cImageFilter(int filterMode) :nFilterMode(filterMode) {

	}

	cImageFilter::~cImageFilter() {
	}

	int cImageFilter::setFilterMode(int filterMode) {
		int res = 0;

		nFilterMode = filterMode;

		return res;
	}

	//////////////////////////////////////////////////////////////////////////
	// spherize
	int cImageFilter::spherize(cv::Mat &inputMat,cv::Mat &outputMat) {

		int res = 0;

		cv::Mat spherizeMat;
		inputMat.copyTo(spherizeMat);

		int width=inputMat.cols;  
    	int height=inputMat.rows;  
  
   	 	float R;  
    	float e;  
    	float a,b;  
    	float alpha=0.75;  
    	float K=dega_pi/2;

		a=height/2.0; b=width/2.0;  
		e=(float)width/(float)height;  
		R=std::min(a,b);  

		cv::Point Center(width/2, height/2);  
	
		float radius,Dis,new_x, new_y;  
		float p,q,x1,y1,x0,y0;  
		float theta;
		//////////////////////////////////////////////////////////////////////////
		// iterator
		cv::Mat_<cv::Vec3b>::iterator itend = inputMat.end<cv::Vec3b>();
		cv::Mat_<cv::Vec3b>::iterator itstart = inputMat.begin<cv::Vec3b>();

		cv::Mat_<cv::Vec3b>::iterator itOutput = spherizeMat.begin<cv::Vec3b>();

		for (int y=0; y<height; y++)  
    	{  
			for (int x=0; x<width; x++)  
			{  
				y0=Center.y-y;  
				x0=x-Center.x;  
				Dis=x0*x0+y0*y0;  
				if(Dis<R*R)  
				{  
					theta=atan(y0/(x0+0.00001));  
					if(x0<0) theta=theta+dega_pi;  
					radius=asin(sqrt(Dis)/R)*R/K;  
					radius=(sqrt(Dis)-radius)*(1-alpha)+radius;  
					new_x=radius*cos(theta);  
					new_y=radius*sin(theta);  
					new_x=Center.x+new_x;  
					new_y=Center.y-new_y;  
	
					if(new_x<0)         new_x=0;  
					if(new_x>=width-1)  new_x=width-2;  
					if(new_y<0)         new_y=0;  
					if(new_y>=height-1) new_y=height-2;  
	
					x1=(int)new_x;  
					y1=(int)new_y;  
	
					p=new_x-x1;  
					q=new_y-y1;  
	
					for (int k=0; k<3; k++)  
					{  
						spherizeMat.at<cv::Vec3b>(y, x)[k]=(1-p)*(1-q)*inputMat.at<cv::Vec3b>(y1, x1)[k]+  
												(p)*(1-q)*inputMat.at<cv::Vec3b>(y1,x1+1)[k]+  
												(1-p)*(q)*inputMat.at<cv::Vec3b>(y1+1,x1)[k]+  
												(p)*(q)*inputMat.at<cv::Vec3b>(y1+1,x1+1)[k];  
					}  
	
				}  
	
			}  
    	} 
		
		res = cv::imwrite("./output/Filter/spherizeImage.bmp", spherizeMat);

		return res;
	}

	//////////////////////////////////////////////////////////////////////////
	// edgeLight
	int cImageFilter::edgeLight(const cv::Mat &inputMat,cv::Mat &outputMat) {
		int res = 0;		
		int para_1 = 3;
		int para_2 = 0;
		float alpha = 0.5;

		cv::Mat edgeRes_x;
		cv::Mat edgeRes_y;
		inputMat.copyTo(outputMat);

		cv::Mat kernel_x = (cv::Mat_<int>(3,3) << -1, 0 ,1,
                                  	 		-para_1, para_2, para_1,
                                   			-1, 0 ,1);
		cv::Mat kernel_y = (cv::Mat_<int>(3,3) << -1, -para_1 ,-1,
                                  	 		0, para_2, 0,
                                   			1, para_1 ,1);
		filter2D(inputMat,edgeRes_x,inputMat.depth(),kernel_x);
		filter2D(inputMat,edgeRes_y,inputMat.depth(),kernel_y);

		//////////////////////////////////////////////////////////////////////////
		// iterator
		cv::Mat_<cv::Vec3b>::iterator itend_1 = edgeRes_x.end<cv::Vec3b>();
		cv::Mat_<cv::Vec3b>::iterator itstart_1 = edgeRes_x.begin<cv::Vec3b>();
		
		cv::Mat_<cv::Vec3b>::iterator itstart_2 = edgeRes_y.begin<cv::Vec3b>();
		
		cv::Mat_<cv::Vec3b>::iterator itstart = outputMat.begin<cv::Vec3b>();

		for (; itstart_1 != itend_1;  ++itstart, ++itstart_1, ++itstart_2) {
				for (size_t loop_i = 0; loop_i < inputMat.channels(); loop_i++) {
						(*itstart)[loop_i] = (alpha * ((*itstart_1)[loop_i]) + (1 - alpha) * ((*itstart_2)[loop_i]));
				}
		}
		return res;
	}
	//////////////////////////////////////////////////////////////////////////
	// imageSharp
	int cImageFilter::imageSharp(const cv::Mat &inputMat,cv::Mat &outputMat) {
		int res = 0;
		double sigma = 3;
		int threshold = 1;
		float amount = 50 / 100.0f;
		
		cv::Mat imgBlurred;
		GaussianBlur(inputMat, imgBlurred, cv::Size(7,7), sigma, sigma);

		inputMat.copyTo(outputMat);
		cv::Mat lowContrastMask = abs(inputMat - imgBlurred) < threshold;
		outputMat = inputMat * (1 + amount) + imgBlurred * (-amount);
		inputMat.copyTo(outputMat, lowContrastMask);

		return res;
	}

	
}
