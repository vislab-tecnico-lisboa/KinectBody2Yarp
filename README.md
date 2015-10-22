Kinect Tracked People's Joints to Yarp and ROS
===

Connects to Kinect v2, opens Yarp Bottle port, ROS message topic, and sends the tracked people's joints positions and orientation alongside the floor estimation and a Header with a time stamp.

~~~~~~~~~~~~~~~~
~ Prerequisites: This code requires OpenCV, Yarp, and Kinect SDK v2, and Kinect SDK v2 requires Windows 8.

~ Requires: OPENCV_DIR environment variable to be set to 
~~~~~~~~~~~~~~~~

To compile:

Run CMake gui setting the source folder to the folder of this code, and the build folder to anything of your choice (suggested same folder/build)



(this assumes you set the environment variable OPENCV_VER, in my case to 2411)
