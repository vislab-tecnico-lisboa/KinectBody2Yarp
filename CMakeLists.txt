# Copyright: Any??
# Authors: Dario Figueira
# CopyPolicy: Any??

# cmake_minimum_required(VERSION 2.8.7) # Don't know what's the minimum required

set(PROJECTNAME KinectBody2Yarp)
project(${PROJECTNAME})
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/library/cmake) # DO WE NEED THIS?

find_package(YARP REQUIRED)
find_package(KinectSDK REQUIRED) # NuiKinectFusionApi.h IS WHAT? KinectSDK OR OpenNI? 
#find_package(OpenNI)
find_package(OpenCV REQUIRED)
list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH})


add_definitions(${YARP_DEFINES})   
include(YarpInstallationHelpers) 

#add_subdirectory(library)
#add_subdirectory(modules)

#icubcontrib_finalize_export(${PROJECTNAME})
#icubcontrib_add_uninstall_target()

add_executable(${PROJECTNAME} ... filenames?)
target_link_libraries(${PROJECTNAME} ${OpenCV_LIBS} ${YARP_LIBRARIES})
