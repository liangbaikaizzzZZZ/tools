#include <iostream>
#include "change_to_vr.h"
#include "testjson.h"
#include"myconfig.h"
#include"oper_to_vr.h"

int main()
{
	//std::cout << "Hello World!\n";
	//MPT_test_fish_change_png("../image/test3840X1920.png");

	//std::string jsonStr = MPT_test_createJson();
	//MPT_test_saveJson("../json/json-none.json", jsonStr);
	//MPT_test_readJson("../json/json-none.json");
	//MPT_test_changeJson("../json/json-none.json");

	oper_to_vr oper;
	oper.conf.setconfig("../json/json-none.json");
	oper.oper();

	return 0;
}
