cmake_minimum_required(VERSION 3.10)

project(RorationModel)
set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/package")
#set(PACKVERSION 2.0.0.1)
######################################################################
#全局编译标志
######################################################################

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

set(CUDA_cublas_device_LIBRARY /usr/local/cuda/lib64)
######################################################################
#全局链接和包含
######################################################################

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/3rdParty)
include_directories(${CMAKE_SOURCE_DIR}/3rdParty/opencv/include)
include_directories(${CMAKE_SOURCE_DIR}/alg/include)
link_directories(${CMAKE_SOURCE_DIR}/3rdParty/json/lib)
link_directories(${CMAKE_SOURCE_DIR}/3rdParty/opencv/lib)
link_directories(${CMAKE_SOURCE_DIR}/ai_model/libs/linux/gpu)
link_directories(${CMAKE_SOURCE_DIR}/3rdParty/ubuntu-cuda10)
link_directories(${CMAKE_SOURCE_DIR}/alg/lib)

find_package(Boost REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

#################################################################L#####
#全局编译输出指定
######################################################################

#IF(CMAKE_BUILD_TYPE MATCHES Debug)
set(CMAKE_VERBOSE_MAKEFILE ON)
#ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${BUILD_TYPE})


######################################################################
#子工程目录
######################################################################
add_subdirectory(third_party)

######################################################################
#common目录 获取所有源文件
######################################################################
# aux_source_directory(${CMAKE_SOURCE_DIR}/common DIR_COMMON_SRCS)
######################################################################
#编译对象
######################################################################
add_executable(RorationModel
    rotation_model.cpp

    ${DIR_COMMON_SRCS}
)

if(Boost_FOUND)
    target_link_libraries(RorationModel ${Boost_LIBRARIES})
endif()

target_link_libraries(RorationModel
        jsoncpp
        curl
        ssl
        crypto
        boost_system
        cudnn
        z
        opencv_core
        opencv_imgcodecs
        opencv_imgproc
        opencv_highgui
        rotate_cls
        det_timu_yolov5
        cls_image_rotate_tal
    )
