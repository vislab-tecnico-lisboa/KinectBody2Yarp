# Message header for Kinect tracked people's message
#
#

# The floor plane
FloorPlane floorPlane

# The tracked people
Body[] bodies

#Two-integer timestamp that is expressed as:
# * header.stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * header.stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# The other fields of header are always zero
std_msgs/Header header

