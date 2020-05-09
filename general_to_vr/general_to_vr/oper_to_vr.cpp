#include "oper_to_vr.h"

int oper_to_vr::oper()
{
	srcpic = cv::imread(conf.srcpath, cv::IMREAD_UNCHANGED);
	if (srcpic.empty()) {
		std::cout << "no srcpic!" << std::endl;
		return -1;
	}

	if ((srcpic.rows != conf.srcheight) || (srcpic.cols != conf.srcwidth)) {
		if (conf.srcwidth <= 0 || conf.srcheight <= 0) {
			std::cout << "srcpic size error!" << std::endl;
			return -1;
		}
		cv::resize(srcpic, srcpic, cv::Size(conf.srcwidth, conf.srcheight));
	}

	dstpic.create(conf.dstheight, conf.dstwidth, CV_8UC4);
	dstpic.setTo(cv::Scalar::all(0));
	if ((conf.displayx < 0) || (conf.displayx + conf.srcwidth > conf.dstwidth) || (conf.displayy < 0) || (conf.displayy + conf.srcheight > conf.dstheight)) {
		std::cout << "config error" << std::endl;
		return -1;
	}
	srcpic.copyTo(dstpic(cv::Rect(conf.displayx, conf.displayy, conf.srcwidth, conf.srcheight)));


	cv::Mat src = dstpic.clone();


	double PI = 3.1415926;
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


	cv::namedWindow("dstpic", 0);
	cv::imshow("dstpic", dstpic);
	cv::namedWindow("dst", 0);
	cv::imshow("dst", dst);

	std::vector<int> compression_params;
	compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(0);
	cv::imwrite(conf.dstpath, dst, compression_params);
	cv::waitKey(0);


	return 0;
}
