#include "iostream"
#include "algorithm"
#include "cImageMerge.h"

namespace degawong {


	cImageMerge::cImageMerge() {
	}

	cImageMerge::cImageMerge(int mergeMode) :nMergeMode(mergeMode) {

	}

	cImageMerge::~cImageMerge() {
	}

	int cImageMerge::setMergeMode(int mergeMode) {
		int res = 0;

		nMergeMode = mergeMode;

		return res;
	}

	//////////////////////////////////////////////////////////////////////////
	// hardmix
	int cImageMerge::hardmix(cv::Mat &inputImage_1, cv::Mat &inputImage_2) {

		int res = 0;

		cv::Mat hardmixMat;
		cv::Mat f_image_1, f_image_2;

		inputImage_1.convertTo(f_image_1, CV_32FC3);
		inputImage_2.convertTo(f_image_2, CV_32FC3);

		//////////////////////////////////////////////////////////////////////////
		// iterator
		cv::Mat_<cv::Vec3b>::iterator itend = inputImage_2.end<cv::Vec3b>();
		cv::Mat_<cv::Vec3b>::iterator itstart = inputImage_2.begin<cv::Vec3b>();

		cv::Mat_<cv::Vec3f>::iterator itinput = f_image_1.begin<cv::Vec3f>();
		cv::Mat_<cv::Vec3f>::iterator itaddit = f_image_2.begin<cv::Vec3f>();

		for (; itstart != itend; ++itstart, ++itaddit, ++itinput) {
			for (size_t loop_i = 0; loop_i < inputImage_1.channels(); loop_i++) {
				if (255 > ((*itinput)[loop_i] + (*itaddit)[loop_i])) {
					(*itinput)[loop_i] = 0.0f;
				} else {
					(*itinput)[loop_i] = 255.0f;
				}
			}
		}

		f_image_1.convertTo(hardmixMat, CV_8UC3);
		if (0 != nMergeMode) {
			res = imwrite("./output/Merge/hardmixImage.bmp", hardmixMat);
		}

		return res;
	}

	//////////////////////////////////////////////////////////////////////////
	// overlay
	int cImageMerge::overlay(cv::Mat &inputImage_1, cv::Mat &inputImage_2) {
		
		int res = 0;

		cv::Mat overlayMat;
		cv::Mat f_image_1, f_image_2;

		inputImage_1.convertTo(f_image_1, CV_32FC3);
		inputImage_2.convertTo(f_image_2, CV_32FC3);

		//////////////////////////////////////////////////////////////////////////
		// ptr<>() ptr ��������ֻ���� uchar*
		//for (size_t loop_i = 0; loop_i < inputImage_1.rows; loop_i++) {
		//	uchar *judgeData = inputImage_1.ptr(loop_i);
		//	uchar *addiData = f_image_2.ptr(loop_i);
		//	uchar *inputData = f_image_1.ptr(loop_i);
		//	
		//	for (size_t loop_j = 0; loop_j < inputImage_1.channels(); loop_j++) {
		//		if (128 < judgeData[loop_j]) {
		//			inputData[loop_j] = 2 * addiData[loop_j] * inputData[loop_j] / 255;
		//		} else {
		//			inputData[loop_j] = 255 - 2 * (255 - addiData[loop_j]) * (255 - inputData[loop_j]) / 255;
		//		}
		//	}
		//}

		//////////////////////////////////////////////////////////////////////////
		// iterator
		cv::Mat_<cv::Vec3b>::iterator itstart = inputImage_2.begin<cv::Vec3b>();
		cv::Mat_<cv::Vec3b>::iterator itend = inputImage_2.end<cv::Vec3b>();

		cv::Mat_<cv::Vec3f>::iterator itinput = f_image_1.begin<cv::Vec3f>();
		cv::Mat_<cv::Vec3f>::iterator itaddit = f_image_2.begin<cv::Vec3f>();

		for (; itstart != itend; ++itstart, ++itaddit, ++itinput) {
			for (size_t loop_i = 0; loop_i < inputImage_2.channels(); loop_i++) {
				if (128 < (*itstart)[loop_i]) {
					(*itinput)[loop_i] = 2 * (*itinput)[loop_i] * (*itaddit)[loop_i] / 255;
				} else {
					(*itinput)[loop_i] = 255 - 2 * (255 - (*itinput)[loop_i]) * (255 - (*itaddit)[loop_i]) / 255;
				}
			}
		}

		//////////////////////////////////////////////////////////////////////////
		// at<>()[]
		//for (size_t loop_i = 0; loop_i < inputImage_1.rows; loop_i++) {
		//	for (size_t loop_j = 0; loop_j < inputImage_1.cols; loop_j++) {
		//		for (size_t loop_k = 0; loop_k < inputImage_1.channels(); loop_k++) {
		//			if (128.0 < inputImage_2.at<cv::Vec3b>(loop_i, loop_j)[loop_k]) {
		//				f_image_1.at<cv::Vec3f>(loop_i, loop_j)[loop_k] = 2.0f * f_image_1.at<cv::Vec3f>(loop_i, loop_j)[loop_k] * f_image_2.at<cv::Vec3f>(loop_i, loop_j)[loop_k] / 255.0f;
		//			} else {
		//				f_image_1.at<cv::Vec3f>(loop_i, loop_j)[loop_k] = 255.0f - (2.0f * (255.0f - f_image_1.at<cv::Vec3f>(loop_i, loop_j)[loop_k]) * (255.0f - f_image_2.at<cv::Vec3f>(loop_i, loop_j)[loop_k]) / 255.0f);
		//			}
		//		}
		//	}
		//}
		
		f_image_1.convertTo(overlayMat, CV_8UC3);
		if (0 != nMergeMode) {
			res = imwrite("./output/Merge/overlayImage.bmp", overlayMat);
		}

		return res;
	}

	//////////////////////////////////////////////////////////////////////////
	// pinlight
	int cImageMerge::pinlight(cv::Mat &inputImage_1, cv::Mat &inputImage_2) {

		int res = 0;

		cv::Mat pinlightMat;
		cv::Mat f_image_1, f_image_2;

		inputImage_1.convertTo(f_image_1, CV_32FC3);
		inputImage_2.convertTo(f_image_2, CV_32FC3);

		//////////////////////////////////////////////////////////////////////////
		// iterator
		cv::Mat_<cv::Vec3b>::iterator itend = inputImage_1.end<cv::Vec3b>();
		cv::Mat_<cv::Vec3b>::iterator itstart = inputImage_1.begin<cv::Vec3b>();

		cv::Mat_<cv::Vec3f>::iterator itinput = f_image_1.begin<cv::Vec3f>();
		cv::Mat_<cv::Vec3f>::iterator itaddit = f_image_2.begin<cv::Vec3f>();

		for (; itstart != itend; ++itstart, ++itaddit, ++itinput) {
			for (size_t loop_i = 0; loop_i < inputImage_2.channels(); loop_i++) {
				//if (128 >= (*itstart)[loop_i]) {
				//	(*itinput)[loop_i] = std::min((*itaddit)[loop_i], 2.0f * (*itinput)[loop_i]);
				//} else {
				//	(*itinput)[loop_i] = std::min((*itaddit)[loop_i], 2.0f * (*itinput)[loop_i] - 255.0f);
				//}
				if (128 >= (*itstart)[loop_i]) {
					(*itinput)[loop_i] = std::min((*itinput)[loop_i], 2.0f * (*itaddit)[loop_i]);
				} else {
					(*itinput)[loop_i] = std::min((*itinput)[loop_i], 2.0f * (*itaddit)[loop_i] - 255.0f);
				}
			}
		}

		f_image_1.convertTo(pinlightMat, CV_8UC3);
		if (0 != nMergeMode) {
			res = imwrite("./output/Merge/pinlightImage.bmp", pinlightMat);
		}

		return res;
	}

	//////////////////////////////////////////////////////////////////////////
	// hardlight
	int cImageMerge::hardlight(cv::Mat &inputImage_1, cv::Mat &inputImage_2) {

		int res = 0;

		cv::Mat hardlightMat;
		cv::Mat f_image_1, f_image_2;

		inputImage_1.convertTo(f_image_1, CV_32FC3);
		inputImage_2.convertTo(f_image_2, CV_32FC3);

		//////////////////////////////////////////////////////////////////////////
		// iterator
		cv::Mat_<cv::Vec3b>::iterator itstart = inputImage_1.begin<cv::Vec3b>();
		cv::Mat_<cv::Vec3b>::iterator itend = inputImage_1.end<cv::Vec3b>();

		cv::Mat_<cv::Vec3f>::iterator itinput = f_image_1.begin<cv::Vec3f>();
		cv::Mat_<cv::Vec3f>::iterator itaddit = f_image_2.begin<cv::Vec3f>();

		for (; itstart != itend; ++itstart, ++itaddit, ++itinput) {
			for (size_t loop_i = 0; loop_i < inputImage_1.channels(); loop_i++) {
				if (128 < (*itstart)[loop_i]) {
					(*itinput)[loop_i] = 2 * (*itinput)[loop_i] * (*itaddit)[loop_i] / 255;
				} else {
					(*itinput)[loop_i] = 255 - 2 * (255 - (*itinput)[loop_i]) * (255 - (*itaddit)[loop_i]) / 255;
				}
			}
		}

		f_image_1.convertTo(hardlightMat, CV_8UC3);
		if (0 != nMergeMode) {
			res = imwrite("./output/Merge/hardlightImage.bmp", hardlightMat);
		}

		return res;
	}

	//////////////////////////////////////////////////////////////////////////
	// softlight
	int cImageMerge::softlight(cv::Mat &inputImage_1, cv::Mat &inputImage_2) {

		int res = 0;

		cv::Mat softlightMat;
		cv::Mat f_image_1, f_image_2;

		inputImage_1.convertTo(f_image_1, CV_32FC3);
		inputImage_2.convertTo(f_image_2, CV_32FC3);

		//////////////////////////////////////////////////////////////////////////
		// iterator
		cv::Mat_<cv::Vec3b>::iterator itend = inputImage_2.end<cv::Vec3b>();
		cv::Mat_<cv::Vec3b>::iterator itstart = inputImage_2.begin<cv::Vec3b>();

		cv::Mat_<cv::Vec3f>::iterator itinput = f_image_1.begin<cv::Vec3f>();
		cv::Mat_<cv::Vec3f>::iterator itaddit = f_image_2.begin<cv::Vec3f>();

		for (; itstart != itend; ++itstart, ++itaddit, ++itinput) {
			for (size_t loop_i = 0; loop_i < inputImage_1.channels(); loop_i++) {
				if (128 <= (*itstart)[loop_i]) {
					(*itinput)[loop_i] = (*itinput)[loop_i] + ((2 * (*itaddit)[loop_i] - 255.0f) * (*itinput)[loop_i] - ((*itinput)[loop_i] * (*itinput)[loop_i]) / 255.0f) / 255.0f;
				} else {
					(*itinput)[loop_i] = (*itinput)[loop_i] + (2 * (*itaddit)[loop_i] - 255.0f) * (sqrt((*itinput)[loop_i] / 255.0f) * 255.0f - (*itinput)[loop_i]) / 255.0f;
				}
			}
		}

		f_image_1.convertTo(softlightMat, CV_8UC3);
		if (0 != nMergeMode) {
			res = imwrite("./output/Merge/softlightImage.bmp", softlightMat);
		}
		
		return res;
	}

	//////////////////////////////////////////////////////////////////////////
	// linerlight
	int cImageMerge::linerlight(cv::Mat &inputImage_1, cv::Mat &inputImage_2) {

		int res = 0;

		cv::Mat linerlightMat;
		cv::Mat f_image_1, f_image_2;

		inputImage_1.convertTo(f_image_1, CV_32FC3);
		inputImage_2.convertTo(f_image_2, CV_32FC3);

		//////////////////////////////////////////////////////////////////////////
		// iterator
		cv::Mat_<cv::Vec3b>::iterator itend = inputImage_2.end<cv::Vec3b>();
		cv::Mat_<cv::Vec3b>::iterator itstart = inputImage_2.begin<cv::Vec3b>();

		cv::Mat_<cv::Vec3f>::iterator itinput = f_image_1.begin<cv::Vec3f>();
		cv::Mat_<cv::Vec3f>::iterator itaddit = f_image_2.begin<cv::Vec3f>();

		for (; itstart != itend; ++itstart, ++itaddit, ++itinput) {
			for (size_t loop_i = 0; loop_i < inputImage_1.channels(); loop_i++) {
				(*itinput)[loop_i] = std::min(255.0f, std::max(0.0f, ((*itinput)[loop_i] + 2.0f * (*itaddit)[loop_i]) - 255.0f));
				
			}
		}

		f_image_1.convertTo(linerlightMat, CV_8UC3);
		if (0 != nMergeMode) {
			res = imwrite("./output/Merge/linerlightImage.bmp", linerlightMat);
		}

		return res;
	}

	//////////////////////////////////////////////////////////////////////////
	// vividlight
	int cImageMerge::vividlight(cv::Mat &inputImage_1, cv::Mat &inputImage_2) {

		int res = 0;

		cv::Mat vividlightMat;
		cv::Mat f_image_1, f_image_2;

		inputImage_1.convertTo(f_image_1, CV_32FC3);
		inputImage_2.convertTo(f_image_2, CV_32FC3);

		//////////////////////////////////////////////////////////////////////////
		// iterator
		cv::Mat_<cv::Vec3b>::iterator itend = inputImage_2.end<cv::Vec3b>();
		cv::Mat_<cv::Vec3b>::iterator itstart = inputImage_2.begin<cv::Vec3b>();

		cv::Mat_<cv::Vec3f>::iterator itinput = f_image_1.begin<cv::Vec3f>();
		cv::Mat_<cv::Vec3f>::iterator itaddit = f_image_2.begin<cv::Vec3f>();

		for (; itstart != itend; ++itstart, ++itaddit, ++itinput) {
			for (size_t loop_i = 0; loop_i < inputImage_1.channels(); loop_i++) {
				if (128 >= (*itstart)[loop_i]) {
					(*itinput)[loop_i] = std::max(0.0f, ((*itinput)[loop_i] - (255.0f - (*itinput)[loop_i]) * ((255.0f - 2 * (*itaddit)[loop_i])) / (2.0f * (*itaddit)[loop_i])));
				} else {
					(*itinput)[loop_i] = std::min(255.0f, (*itinput)[loop_i] + ((*itinput)[loop_i] * (2.0f * (*itaddit)[loop_i] - 255.0f) / (2.0f * (255.0f - (*itaddit)[loop_i]))));
				}
			}
		}

		f_image_1.convertTo(vividlightMat, CV_8UC3);
		if (0 != nMergeMode) {
			res = imwrite("./output/Merge/vividlightImage.bmp", vividlightMat);
		}

		return res;
	}

}
