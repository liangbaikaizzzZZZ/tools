#include"testjson.h"

std::string MPT_test_createJson(void)
{
	std::string jsonStr;
	Json::Value root, srcpic, dstpic, display;
	Json::StreamWriterBuilder writerBuilder;
	std::ostringstream os;

	writerBuilder.settings_["indentation"] = "\t";

	srcpic["path"] = "./image/test.png";
	srcpic["width"] = 100;
	srcpic["height"] = 70;
	root["srcpic"] = srcpic;

	dstpic["path"] = "./image/test.png";
	dstpic["width"] = 1920;
	dstpic["height"] = 1080;
	root["dstpic"] = dstpic;

	display["x"] = 100;
	display["y"] = 100;
	root["display"] = display;

	std::unique_ptr<Json::StreamWriter> jsonWriter(writerBuilder.newStreamWriter());
	jsonWriter->write(root, &os);
	jsonStr = os.str();

	std::cout << "Json:" << jsonStr << std::endl;
	return jsonStr;
}

void MPT_test_saveJson(std::string file, std::string& jsonStr)
{
	std::ofstream ofs;
	ofs.open(file);
	if (!ofs.is_open())
	{
		std::cout << "open json file failed." << std::endl;
		return;
	}
	ofs << jsonStr;
	ofs.close();
	return;
}

void MPT_test_readJson(std::string file) {
	std::ifstream ifs;
	ifs.open(file, std::ios::in);
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

	std::cout << "srcpic path: " << root["srcpic"]["path"] << std::endl;
	std::cout << "srcpic width: " << root["srcpic"]["width"] << std::endl;
	std::cout << "srcpic height: " << root["srcpic"]["height"] << std::endl;
	std::cout << "dstpic path: " << root["dstpic"]["path"] << std::endl;
	std::cout << "dstpic width: " << root["dstpic"]["width"] << std::endl;
	std::cout << "dstpic height: " << root["dstpic"]["height"] << std::endl;
	std::cout << "display x: " << root["display"]["x"] << std::endl;
	std::cout << "display y: " << root["display"]["y"] << std::endl;
	ifs.close();
	return;
}

//void MPT_test_changeJson(std::string file) {
//	std::ifstream ifs;
//	ifs.open(file, std::ios::in);
//	if (!ifs.is_open())
//	{
//		std::cout << "open json file failed." << std::endl;
//		return;
//	}
//
//	Json::CharReaderBuilder reader;
//	Json::Value root;
//
//	JSONCPP_STRING errs;
//
//	bool res = Json::parseFromStream(reader, ifs, &root, &errs);
//	if (!res || !errs.empty())
//	{
//		std::cout << "parseJson error! " << errs << std::endl;
//		return;
//	}
//
//	root["Age"] = 30;
//	root["Name"] = "Liangbaikai's liangbaikai";
//	root["fruit"][0] = "strawberry";
//	ifs.close();
//
//	std::ofstream os;
//	os.open(file, std::ios::out);
//	if (!os.is_open())
//	{
//		std::cout << "open json file failed." << std::endl;
//		return;
//	}
//	Json::StreamWriterBuilder builder;
//	std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
//	writer->write(root, &os);
//	return;
//}
