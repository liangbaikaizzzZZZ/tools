cmake_minimum_required(VERSION 3.2)
message("srt_master_tool")

#add_compile_options(-std=c++11 -Wall -fpic )

#add_definitions(-DWANGSHI_BASE_MODEL_NAME=wangshi_srt_master_tool)

project(srt_master_tool)

#set(CMAKE_BUILD_TYPE Release)
set(TARGET srt_master_tool)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

#link_directories(
#    /usr/local/lib
#)

find_library(log-lib log)

set(SRC_LIST 
    ${PROJECT_SOURCE_DIR}/src/srt_main.cpp
    ${PROJECT_SOURCE_DIR}/src/tinyxml2.cpp
)


add_executable(${TARGET}  ${SRC_LIST})


#链接库文件
#target_link_libraries(${TARGET} 
#	rt
#)



