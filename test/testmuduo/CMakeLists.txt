#最低版本
#cmake_minimum_required(VERSION 3.0)
#project(chat)

#配置编译选项
#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

#配置头文件搜索路径
#include_directories()
#配置库文件搜索路径
#link_directories()

#设置需要编译的源文件列表
set(SRC_LIST ./muduo_server.cpp)

#设置可执行文件最终存储的路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#把.指定路径下的所有源文件的名字放入到SRC_LIST里面
#aux_source_directory(.SRC_LIST)

#表示生成可执行文件server,由SRC_LIST变量所定义的源文件编译而来
add_executable(muduoserver ${SRC_LIST})
#表示server这个目标程序，需要连接muduo.net muduo.base pthread这三个库文件
target_link_libraries(muduoserver muduo_net muduo_base pthread)
