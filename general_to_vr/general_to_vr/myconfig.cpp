#include "myconfig.h"

myconfig::myconfig()
{
	srcpath = "./image/src.png";
	dstpath = "./image/dst.png";
	srcwidth = 406;
	srcheight = 41;
	dstwidth = 3840;
	dstheight = 1920;
	displayx = 100;
	displayy = 100;
}

myconfig::~myconfig()
{
}

void myconfig::setconfig(std::string jsonfile)
{
	std::ifstream ifs;
	ifs.open(jsonfile, std::ios::in);
	if (!ifs.is_open())
	{
		std::cout << "open json file failed." << std::endl;
		return;
	}

	Json::CharReaderBuilder reader;
	Json::Value root;

	int iage = 0;
	std::string sname;
	JSONCPP_STRING errs;

	bool res = Json::parseFromStream(reader, ifs, &root, &errs);
	if (!res || !errs.empty())
	{
		std::cout << "parseJson error! " << errs << std::endl;
		return;
	}
	srcpath = root["srcpic"]["path"].asString();
	srcwidth = root["srcpic"]["width"].asInt();
	srcheight = root["srcpic"]["height"].asInt();
	dstpath = root["dstpic"]["path"].asString();
	dstwidth = root["dstpic"]["width"].asInt();
	dstheight = root["dstpic"]["height"].asInt();
	displayx = root["display"]["x"].asInt();
	displayy = root["display"]["y"].asInt();

	std::cout << "srcpic path: " << srcpath << std::endl;
	std::cout << "srcpic width: " << srcwidth << std::endl;
	std::cout << "srcpic height: " << srcheight << std::endl;
	std::cout << "dstpic path: " << dstpath << std::endl;
	std::cout << "dstpic width: " << dstwidth << std::endl;
	std::cout << "dstpic height: " << dstheight << std::endl;
	std::cout << "display x: " << displayx << std::endl;
	std::cout << "display y: " << displayy << std::endl;
	ifs.close();
	return;
}
