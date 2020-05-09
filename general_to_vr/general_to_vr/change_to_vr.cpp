#include"change_to_vr.h"


int MPT_resize_mat(cv::Mat& src, int width, int height) {
	if (width <= 0 || height <= 0) {
		return -1;
	}
	cv::resize(src, src, cv::Size(width, height));
	return 0;
}


int MPT_test_fish_change_png(std::string file) {
	double PI = 3.1415926;
	cv::Mat src = cv::imread(file, cv::IMREAD_UNCHANGED);
	int w = src.size().width;
	int h = src.size().height;
	int bigsize = w > h ? w : h;
	cv::resize(src, src, cv::Size(bigsize, bigsize));
	cv::Mat dst(src.rows, src.cols, CV_8UC4);

	for (int id = 0; id < dst.rows; id++) {
		for (int jd = 0; jd < dst.cols; jd++) {
			double xd = jd * 2.0 / dst.cols - 1.0;
			double yd = id * 2.0 / dst.cols - 1.0;
			double rd = sqrt(xd * xd + yd * yd);
			double phid = atan2(yd, xd);
			double xs = asin(rd) * 2 / PI * cos(phid);
			double ys = asin(rd) * 2 / PI * sin(phid);
			int is = round((ys + 1.000000) * dst.rows / 2.000000);
			int js = round((xs + 1.000000) * dst.cols / 2.000000);
			if (is > dst.rows || is < 0 || js>dst.cols || js < 0)
				continue;
			dst.at<cv::Vec4b>(id, jd)[0] = src.at<cv::Vec4b>(is, js)[0];
			dst.at<cv::Vec4b>(id, jd)[1] = src.at<cv::Vec4b>(is, js)[1];
			dst.at<cv::Vec4b>(id, jd)[2] = src.at<cv::Vec4b>(is, js)[2];
			dst.at<cv::Vec4b>(id, jd)[3] = src.at<cv::Vec4b>(is, js)[3];
		}
	}

	cv::resize(dst, dst, cv::Size(w, h));
	std::vector<int> compression_params;
	compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(0);
	imwrite("../image/test3840X1920_3.png", dst, compression_params);
	cv::waitKey(0);
	return 0;
}
