Kinect Tracked People's Joints to Yarp and ROS
===

Connects to Kinect v2, opens Yarp Bottle port, ROS message topic, and sends the tracked people's joints positions and orientation alongside the floor estimation and a Header with a time stamp.

~~~~~~~~~~~~~~~~
~ Prerequisites: This code requires OpenCV, Yarp, and Kinect SDK v2, and Kinect SDK v2 requires Windows 8.

~ Requires: OpenCV_DIR environment variable (case sensitive!) to be set to opencv_root\Build where a OpenCVConfig.cmake is located (this superseeds what is suggested in OpenCV website, that they suggest you set it to OpenCV/Build/x64/vc11 )
            opencv correct bin folder added to PATH environement variable

~~~~~~~~~~~~~~~~

To compile:

Run CMake gui setting the source folder to the folder of this code, and the build folder to anything of your choice (suggested same folder/build)
**BEWARE** The default MSCV compiler chosen by Cmake in the GUI is actually 32bit one, you have to choose in the dropdown menu the explicit 64bit one.




