// KinectBody2Yarp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <cstdio>
#include <stdio.h>

#include <Windows.h>
#include <NuiKinectFusionApi.h>
#include <opencv2/opencv.hpp>
/* Get all OS and signal processing YARP classes */
#include <opencv2/legacy/compat.hpp> // for cvCopyImage
#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <yarp/os/Wire.h>
#include <yarp/os/idl/WireTypes.h>
#include "KinectTrackedPeopleMessage.h"

#include <chrono>
#include <ctime> // to fill the timestamp field of ROS Message

using namespace yarp::os;
using namespace yarp::sig;

using namespace std;

template<class Interface>
inline void SafeRelease(Interface *& pInterfaceToRelease)
{
	if (pInterfaceToRelease != NULL){
		pInterfaceToRelease->Release();
		pInterfaceToRelease = NULL;
	}
}

int main()
{
	Network yarp;
	if (!yarp.checkNetwork())
	{
		fprintf(stdout, "YARP server not available!\n");
		return 1;
	}

	BufferedPort<Bottle> bodiesOutputPort;
	bodiesOutputPort.open("/kinect/bodyBottle/out");
	if (bodiesOutputPort.isClosed()){
		throw(runtime_error("bodiesOutputPort did not open."));
	}

	BufferedPort<KinectTrackedPeopleMessage> bodiesOutputPortROS;
	bodiesOutputPortROS.open("/kinect/bodyBottleROS/out");
	if (bodiesOutputPortROS.isClosed()){
		throw(runtime_error("bodiesOutputPortROS did not open."));
	}

	Network::connect("/kinect/bodyBottleROS/out", "/read");

	// Sensor
	IKinectSensor* pSensor;
	HRESULT hResult = S_OK;
	hResult = GetDefaultKinectSensor(&pSensor);
	if (FAILED(hResult)){
		std::cerr << "Error : GetDefaultKinectSensor" << std::endl;
		return -1;
	}

	hResult = pSensor->Open();
	if (FAILED(hResult)){
		std::cerr << "Error : IKinectSensor::Open()" << std::endl;
		return -1;
	}

	// Source
	IColorFrameSource* pColorSource;
	hResult = pSensor->get_ColorFrameSource(&pColorSource);
	if (FAILED(hResult)){
		std::cerr << "Error : IKinectSensor::get_ColorFrameSource()" << std::endl;
		return -1;
	}

	IBodyFrameSource* pBodySource;
	hResult = pSensor->get_BodyFrameSource(&pBodySource);
	if (FAILED(hResult)){
		std::cerr << "Error : IKinectSensor::get_BodyFrameSource()" << std::endl;
		return -1;
	}

	// Reader
	IColorFrameReader* pColorReader;
	hResult = pColorSource->OpenReader(&pColorReader);
	if (FAILED(hResult)){
		std::cerr << "Error : IColorFrameSource::OpenReader()" << std::endl;
		return -1;
	}

	IBodyFrameReader* pBodyReader;
	hResult = pBodySource->OpenReader(&pBodyReader);
	if (FAILED(hResult)){
		std::cerr << "Error : IBodyFrameSource::OpenReader()" << std::endl;
		return -1;
	}

	// Description
	IFrameDescription* pDescription;
	hResult = pColorSource->get_FrameDescription(&pDescription);
	if (FAILED(hResult)){
		std::cerr << "Error : IColorFrameSource::get_FrameDescription()" << std::endl;
		return -1;
	}

	int width = 0;
	int height = 0;
	pDescription->get_Width(&width); // 1920
	pDescription->get_Height(&height); // 1080
	unsigned int bufferSize = width * height * 4 * sizeof(unsigned char);

	cv::Mat bufferMat(height, width, CV_8UC4);
	cv::Mat bodyMat(height / 2, width / 2, CV_8UC4);
	cv::namedWindow("Body");

	// Color Table
	cv::Vec3b color[BODY_COUNT];
	color[0] = cv::Vec3b(255, 0, 0);
	color[1] = cv::Vec3b(0, 255, 0);
	color[2] = cv::Vec3b(0, 0, 255);
	color[3] = cv::Vec3b(255, 255, 0);
	color[4] = cv::Vec3b(255, 0, 255);
	color[5] = cv::Vec3b(0, 255, 255);

	// Coordinate Mapper
	ICoordinateMapper* pCoordinateMapper;
	hResult = pSensor->get_CoordinateMapper(&pCoordinateMapper);
	if (FAILED(hResult)){
		std::cerr << "Error : IKinectSensor::get_CoordinateMapper()" << std::endl;
		return -1;
	}

	while (1){
		// Frame
		IColorFrame* pColorFrame = nullptr;
		hResult = pColorReader->AcquireLatestFrame(&pColorFrame);
		if (SUCCEEDED(hResult)){
			hResult = pColorFrame->CopyConvertedFrameDataToArray(bufferSize, reinterpret_cast<BYTE*>(bufferMat.data), ColorImageFormat::ColorImageFormat_Bgra);
			if (SUCCEEDED(hResult)){
				cv::resize(bufferMat, bodyMat, cv::Size(), 0.5, 0.5);
			}
		}

		IBodyFrame* pBodyFrame = nullptr;
		hResult = pBodyReader->AcquireLatestFrame(&pBodyFrame);
		if (SUCCEEDED(hResult)){
			IBody* pBody[BODY_COUNT] = { 0 };
			hResult = pBodyFrame->GetAndRefreshBodyData(BODY_COUNT, pBody);
			if (SUCCEEDED(hResult)){
				Bottle& sendBottle = bodiesOutputPort.prepare();   // Yarp Bottle
				KinectTrackedPeopleMessage& sendBottleROS = bodiesOutputPortROS.prepare();   // ROS Message
				sendBottleROS.bodies.clear();

				Bottle bodiesBottle;

				int numTrackedPpl = 0;
				for (int count = 0; count < BODY_COUNT; count++){
					BOOLEAN bTracked = false;
					hResult = pBody[count]->get_IsTracked(&bTracked);
					if (SUCCEEDED(hResult) && bTracked){
						numTrackedPpl++;
						Joint joint[JointType::JointType_Count];
						HRESULT hResultJoints = S_OK;
						hResultJoints = pBody[count]->GetJoints(JointType::JointType_Count, joint);
						JointOrientation jointsOrientations[JointType::JointType_Count];
						HRESULT hResultJointsOrientations = S_OK;
						hResultJointsOrientations = pBody[count]->GetJointOrientations(JointType::JointType_Count, jointsOrientations);
						if (SUCCEEDED(hResultJoints) && SUCCEEDED(hResultJointsOrientations)){

							// Add the tracking ID
							UINT64 trackingID = 0;
							pBody[count]->get_TrackingId(&trackingID);
							char str[100];
							sprintf_s(str, "%I64u", trackingID); // WINDOWS ONLY code
							Bottle bodyBottle; // Yarp Bottle
							bodyBottle.addString(str); 
							Body body; // ROS Message
							body.trackID = str;

							// Joints
							for (int type = 0; type < JointType::JointType_Count; type++){
								ColorSpacePoint colorSpacePoint = { 0 };
								pCoordinateMapper->MapCameraPointToColorSpace(joint[type].Position, &colorSpacePoint);
								int x = static_cast<int>(colorSpacePoint.X);
								int y = static_cast<int>(colorSpacePoint.Y);
								if ((x >= 0) && (x < width) && (y >= 0) && (y < height)){
									cv::circle(bufferMat, cv::Point(x, y), 5, static_cast<cv::Scalar>(color[count]), -1); // , CV_AA );
								}

								Bottle jointBottle;

								Bottle typeBottle;
								typeBottle.addInt(type);
								const char * JointTypesStr[] = { "SpineBase", "SpineMid", "Neck", "Head", "ShoulderLeft", 
									"ElbowLeft", "WristLeft", "HandLeft", "ShoulderRight", "ElbowRight", "WristRight", 
									"HandRight", "HipLeft", "KneeLeft", "AnkleLeft", "FootLeft", "HipRight", "KneeRight",
									"AnkleRight", "FootRight", "SpineShoulder", "HandTipLeft", "ThumbLeft", "HandTipRight", "ThumbRight" };
								typeBottle.addString(JointTypesStr[type]);
								jointBottle.addList() = typeBottle;

								Bottle trackingBottle;
								trackingBottle.addInt(joint[type].TrackingState);
								jointBottle.addList() = trackingBottle;

								Bottle positionBottle;
								positionBottle.addDouble(joint[type].Position.X);
								positionBottle.addDouble(joint[type].Position.Y);
								positionBottle.addDouble(joint[type].Position.Z);
								jointBottle.addList() = positionBottle;

								Bottle orientationBottle;
								orientationBottle.addDouble(jointsOrientations[type].Orientation.x);
								orientationBottle.addDouble(jointsOrientations[type].Orientation.y);
								orientationBottle.addDouble(jointsOrientations[type].Orientation.z);
								orientationBottle.addDouble(jointsOrientations[type].Orientation.w);
								jointBottle.addList() = orientationBottle;

								bodyBottle.addList() = jointBottle;

								// ROS Message
								body.joints[type].typeNum = type;
								body.joints[type].typeStr = JointTypesStr[type];
								body.joints[type].pose.position.x = joint[type].Position.X;
								body.joints[type].pose.position.y = joint[type].Position.Y;
								body.joints[type].pose.position.z = joint[type].Position.Z;
								body.joints[type].pose.orientation.x = jointsOrientations[type].Orientation.x;
								body.joints[type].pose.orientation.y = jointsOrientations[type].Orientation.y;
								body.joints[type].pose.orientation.z = jointsOrientations[type].Orientation.z;
								body.joints[type].pose.orientation.w = jointsOrientations[type].Orientation.w;

							}
							//cout << sendBottle.toString().c_str() << endl; 
							bodiesBottle.addList() = bodyBottle; // Yarp Bottle
							sendBottleROS.bodies.push_back(body); // ROS Message
						}
					}
				}
				cv::resize(bufferMat, bodyMat, cv::Size(), 0.5, 0.5);

				// Only send bottle when people tracked (could send bottle with just floor estimation)
				if (numTrackedPpl){

					// Yarp Bottle (only need to compute time stamp and floor if we are going to send the message)
					Bottle floorBottle;
					Vector4 floorPlane;
					pBodyFrame->get_FloorClipPlane(&floorPlane);
					floorBottle.addDouble(floorPlane.x);
					floorBottle.addDouble(floorPlane.y);
					floorBottle.addDouble(floorPlane.z);
					floorBottle.addDouble(floorPlane.w);
					sendBottle.addString("floor");
					sendBottle.addList() = floorBottle;
					sendBottle.addString("bodies");
					sendBottle.addList() = bodiesBottle;
					bodiesOutputPort.write(); 

					// ROS Message (only need to compute time stamp and floor if we are going to send the message)
					sendBottleROS.floorPlane.x = floorPlane.x; // Fill in floor
					sendBottleROS.floorPlane.y = floorPlane.y;
					sendBottleROS.floorPlane.z = floorPlane.z;
					sendBottleROS.floorPlane.w = floorPlane.w;
					auto nanoseconds_since_epoch =
						std::chrono::duration_cast<std::chrono::nanoseconds>
						(std::chrono::system_clock::now().time_since_epoch()).count();
					auto seconds_since_epoch =
						std::chrono::duration_cast<std::chrono::seconds>
						(std::chrono::system_clock::now().time_since_epoch()).count();
					auto nanoseconds = nanoseconds_since_epoch - seconds_since_epoch * 1000000000;

					sendBottleROS.header.stamp.sec = seconds_since_epoch; // Fill in time
					sendBottleROS.header.stamp.nsec = nanoseconds;

					sendBottleROS.header.frame_id = "0"; // Unused field
					sendBottleROS.header.seq = 0;		 // Unused field

					bodiesOutputPortROS.write();
				}
			}

			for (int count = 0; count < BODY_COUNT; count++){
				SafeRelease(pBody[count]);
			}
		}

		SafeRelease(pColorFrame);
		SafeRelease(pBodyFrame);

		cv::imshow("Body", bodyMat);

		if (cv::waitKey(10) == VK_ESCAPE){
			break;
		}
	}

	SafeRelease(pColorSource);
	SafeRelease(pBodySource);
	SafeRelease(pColorReader);
	SafeRelease(pBodyReader);
	SafeRelease(pDescription);
	SafeRelease(pCoordinateMapper);
	if (pSensor){
		pSensor->Close();
	}
	SafeRelease(pSensor);
	cv::destroyAllWindows();


	return 0;
}

