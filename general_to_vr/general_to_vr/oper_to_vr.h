#pragma once
#include"myconfig.h"
#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>                  
#include <opencv2/highgui/highgui.hpp>      
#include <opencv2/imgproc/imgproc.hpp>
class oper_to_vr
{
public:
	myconfig conf;
	int oper();
private:
	cv::Mat srcpic;
	cv::Mat dstpic;

};
