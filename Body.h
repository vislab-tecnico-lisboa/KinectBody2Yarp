// This is an automatically generated file.
// Generated from this Body.msg definition:
//   # A tracked person
//   
//   # The person's track ID, usually very large numbers, converted to string just because historical reasons
//   string trackID
//   
//   # The 25 joints to be tracked that compose a person
//   JointROSmsg[25] joints// Instances of this class can be read and written with YARP ports,
// using a ROS-compatible format.

#ifndef YARPMSG_TYPE_Body
#define YARPMSG_TYPE_Body

#include <string>
#include <vector>
#include <yarp/os/Wire.h>
#include <yarp/os/idl/WireTypes.h>
#include "FloorPlane.h"
#include "geometry_msgs_Point.h"
#include "geometry_msgs_Quaternion.h"
#include "JointROSmsg.h"

class Body : public yarp::os::idl::WirePortable {
public:
  std::string trackID;
  std::vector<JointROSmsg> joints;

  Body() {
    joints.resize(25);
  }

  bool readBare(yarp::os::ConnectionReader& connection) {
    // *** trackID ***
    int len = connection.expectInt();
    trackID.resize(len);
    if (!connection.expectBlock((char*)trackID.c_str(),len)) return false;

    // *** joints ***
    len = connection.expectInt();
    joints.resize(len);
    for (int i=0; i<len; i++) {
      if (!joints[i].read(connection)) return false;
    }
    return !connection.isError();
  }

  bool readBottle(yarp::os::ConnectionReader& connection) {
    connection.convertTextMode();
    yarp::os::idl::WireReader reader(connection);
    if (!reader.readListHeader(2)) return false;

    // *** trackID ***
    if (!reader.readString(trackID)) return false;

    // *** joints ***
    if (connection.expectInt()!=BOTTLE_TAG_LIST) return false;
    int len = connection.expectInt();
    joints.resize(len);
    for (int i=0; i<len; i++) {
      if (!joints[i].read(connection)) return false;
    }
    return !connection.isError();
  }

  bool read(yarp::os::ConnectionReader& connection) {
    if (connection.isBareMode()) return readBare(connection);
    return readBottle(connection);
  }

  bool writeBare(yarp::os::ConnectionWriter& connection) {
    // *** trackID ***
    connection.appendInt(trackID.length());
    connection.appendExternalBlock((char*)trackID.c_str(),trackID.length());

    // *** joints ***
    for (size_t i=0; i<joints.size(); i++) {
      if (!joints[i].write(connection)) return false;
    }
    return !connection.isError();
  }

  bool writeBottle(yarp::os::ConnectionWriter& connection) {
    connection.appendInt(BOTTLE_TAG_LIST);
    connection.appendInt(2);

    // *** trackID ***
    connection.appendInt(BOTTLE_TAG_STRING);
    connection.appendInt(trackID.length());
    connection.appendExternalBlock((char*)trackID.c_str(),trackID.length());

    // *** joints ***
    connection.appendInt(BOTTLE_TAG_LIST);
    connection.appendInt(joints.size());
    for (size_t i=0; i<joints.size(); i++) {
      if (!joints[i].write(connection)) return false;
    }
    connection.convertTextMode();
    return !connection.isError();
  }

  bool write(yarp::os::ConnectionWriter& connection) {
    if (connection.isBareMode()) return writeBare(connection);
    return writeBottle(connection);
  }

  // This class will serialize ROS style or YARP style depending on protocol.
  // If you need to force a serialization style, use one of these classes:
  typedef yarp::os::idl::BareStyle<Body> rosStyle;
  typedef yarp::os::idl::BottleStyle<Body> bottleStyle;

  // Give source text for class, ROS will need this
  yarp::os::ConstString getTypeText() {
    return "# A tracked person\n\
\n\
# The person's track ID, usually very large numbers, converted to string just because historical reasons\n\
string trackID\n\
\n\
# The 25 joints to be tracked that compose a person\n\
JointROSmsg[25] joints\n================================================================================\n\
MSG: JointROSmsg\n\
# A body joint that is tracked by kinect\n\
\n\
# The joint number and description\n\
int64 typeNum\n\
string typeStr\n\
\n\
# Position in space and orientation\n\
geometry_msgs/Point position\n\
geometry_msgs/Quaternion orientation\n\
\n================================================================================\n\
MSG: geometry_msgs/Point\n\
float64 x\n\
float64 y\n\
float64 z\n================================================================================\n\
MSG: geometry_msgs/Quaternion\n\
float64 x\n\
float64 y\n\
float64 z\n\
float64 w";
  }

  // Name the class, ROS will need this
  yarp::os::Type getType() {
    yarp::os::Type typ = yarp::os::Type::byName("Body","Body");
    typ.addProperty("md5sum",yarp::os::Value("06eeb572632c0459442d402176bc5b63"));
    typ.addProperty("message_definition",yarp::os::Value(getTypeText()));
    return typ;
  }
};

#endif
