cmake_minimum_required(VERSION 3.0)
# 指定项目的名称, 版本
project(zxlibproj VERSION 0.1)

# 如果想生成静态库，使用下面的语句
# add_library(mymath mymath.cc)
# target_include_directories(mymath PUBLIC ${CMAKE_SOURCE_DIR}/include)

#####开始######################################
# 如果想生成动态库，使用下面的语句
set(CMAKE_CXX_STANDARD 11)
add_library(zxlib SHARED dummy.cpp)

# target_include_directories和include_directoriesd的区别我已经搞清楚了, 一个是指针对特定目标, 一个是针对所有子目录都生效, 具体的介绍可以看 https://www.codenong.com/31969547/ 
# include_directories(x/y)影响目录范围。此CMakeList中的所有目标，以及在其调用点之后添加的所有子目录中的目标，均会将路径x/y添加到其包含路径中。

# target_include_directories(t x/y)具有目标作用域它将x/y添加到目标t的包含路径。

# 如果所有目标都使用所涉及的包含目录，则需要前一个。如果路径特定于目标，或者想要更好地控制路径的可见性，则需要后一种。后者来自target_include_directories()支持PRIVATE，PUBLIC和INTERFACE限定词的事实。

# private 表示是自己的路径, public则是
target_include_directories(zxlib PRIVATE  ${CMAKE_SOURCE_DIR}/include)
# https://cmake.org/cmake/help/latest/command/set_target_properties.html
# 上面那个链接是 set_target_properties 的解释

set_target_properties(zxlib PROPERTIES PUBLIC_HEADER ${CMAKE_SOURCE_DIR}/include/print.h)
#####结束######################################


# 生成可执行文件
# add_executable(mymathapp mymathApp.cc)
# target_link_libraries(mymathapp mymath)
# target_include_directories(mymathapp PRIVATE ${CMAKE_SOURCE_DIR}/include)

# 改变安装路径可以使用下面的语句，Unix: "/usr/local", Windows: "c:/Program Files/${PROJECT_NAME}" 为默认值，所有的DESTINATION均以此目录为根目录
# set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/mymath)

# 将库文件，可执行文件，头文件安装到指定目录
install(TARGETS zxlib # mymathapp
        EXPORT zxlibTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include/zxlib
        )

