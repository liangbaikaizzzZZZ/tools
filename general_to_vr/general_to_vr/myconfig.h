#pragma once
#include <iostream>
#include <iostream>
#include "json/json.h"
#include <fstream>
class myconfig
{
public:
	myconfig();
	virtual ~myconfig();
	void setconfig(std::string jsonfile);
	std::string srcpath;
	std::string dstpath;
	int srcwidth;
	int srcheight;
	int dstwidth;
	int dstheight;
	int displayx;
	int displayy;
};
