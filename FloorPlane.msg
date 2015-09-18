# This represents the floor plane.
#
#Floor Determination
#Each skeleton frame also contains a floor-clipping-plane vector, which contains the coefficients of an estimated floor-plane equation. The skeleton tracking system updates this estimate for each frame and uses it as a clipping plane for removing the background and segmenting players. The general plane equation is:
#        Ax + By + Cz + D = 0
#      
#where:
#        A = vFloorClipPlane.x
#        B = vFloorClipPlane.y
#        C = vFloorClipPlane.z
#        D = vFloorClipPlane.w
#      
#The equation is normalized so that the physical interpretation of D is the height of the camera from the floor, in meters. Note that the floor might not always be visible or detectable. In this case, the floor clipping plane is a zero vector.
#The floor clipping plane is used in the vFloorClipPlane member of the NUI_SKELETON_FRAME structure (for C++) and in the FloorClipPlane property in managed code.

float64 x
float64 y
float64 z
float64 w
