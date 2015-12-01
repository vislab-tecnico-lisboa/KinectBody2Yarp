# Copyright: Any??
# Authors: Dario Figueira
# CopyPolicy: Any??

cmake_minimum_required(VERSION 2.8.7) # Don't know what's the minimum required

set(PROJECTNAME KinectBody2Yarp)
project(${PROJECTNAME})
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}) # For reading the FindKinectSDK20.cmake, and NOW FOR READING FindOpenCV.cmake
#list(APPEND CMAKE_MODULE_PATH ${OPENCV_DIR}/lib) # For checking if this way FindOpenCV.cmake finds a OpenCVConfig.cmake that is in OPENCV_DIR/lib, HE DIDN'T


find_package(YARP REQUIRED) # Requires YARP_DIR to be set to the root directory, and to have the /bin folder in the PATH, but when installing from binaries it sets everything automatically :)
find_package(KinectSDK20 REQUIRED) # Requires KINECTSDK20_DIR environment variable, but when installing the SDK it already adds it ^_^. Provides KinectSDK20_LIB_DIR, KinectSDK20_INCLUDE_DIRS, KinectSDK20_LIBRARIES


list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH}) # To be able to load files YarpInstallationHelpers, and find the FindOpenCV.cmake file

find_package(OpenCV REQUIRED)  # Requires having the OpenCV_DIR (CASE-SENSITIVE) environment variable set to folder with an OpenCVConfig.cmake file.
# OpenCV installation is just a zip file unpacking, and they suggest you set by hand the OPENCV_DIR to (i.e., ...opencv\Build\x64\vc11) and add that same folder/bin to PATH
# but this is irrelevant to Cmake needs, Cmake needs OpenCV_DIR (case-sensitive, and windows does not allow to have also a OPENCV_DIR variable) to be set to opencv\Build where a OpenCVConfig.cmake is, and it adds the include dirs hard-coded to the OpenCVConfig directory/include
# BUT DON'T FORGET TO SET the \bin to PATH env variable 

add_definitions(${YARP_DEFINES})   
include(YarpInstallationHelpers) 

include_directories(${YARP_INCLUDE_DIRS} ${KinectSDK20_INCLUDE_DIRS}) #OpenCVConfig.cmake in %OPENCV_DIR%\lib already calls include_directories, so we don't need to include the opencv ones here

add_executable(${PROJECTNAME} KinectBody2Yarp.cpp stdafx.cpp)
target_link_libraries(${PROJECTNAME} ${OpenCV_LIBS} ${YARP_LIBRARIES} ${KinectSDK20_LIBRARIES})

message("OpenCV_LIBS " ${OpenCV_LIBS}) # Hmm, in this variable there isn't the specific version of OpenCV dll's (i.e. opencv_highgui2411d.dll) so how is it correctly linking? Is there a link from "opencv_highgui" to the specific version dll ? 
