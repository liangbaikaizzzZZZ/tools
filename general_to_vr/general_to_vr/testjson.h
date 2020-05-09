#pragma once
#include <iostream>
#include "json/json.h"
#include <fstream>


std::string MPT_test_createJson(void);
void MPT_test_saveJson(std::string file, std::string& jsonStr);
void MPT_test_readJson(std::string file);
//void MPT_test_changeJson(std::string file);
