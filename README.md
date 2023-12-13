# IK Service

This package performs the inverse kinematics calculations for the UR10 robot,
via a ROS service. 

This service is part of an ARIAC competition entry. The documentation for ARIAC 2019
can be found [here](https://bitbucket.org/osrf/ariac/wiki/2019/Home).

## Usage
The following code launches the ik_service from the command line.
```shell
    # alternatively setup.zsh if you use zsh
    source /opt/ros/<ros_version>/setup.sh
    source devel/setup.sh
    # launch the service
    roslaunch ik_service ik_service 
```
In order to call the service, you can instantiate an instance of it in `rcpp`
as so:
```c++
    ros::ServiceClient client = n.serviceClient<ik_service::PoseIK>("pose_ik");
```
or alternatively, use it from the command line:
```shell
rosservice call /pose_ik "part_pose:
  position:
    x: 0.0
    y: 0.0
    z: 0.0
  orientation:
    x: 0.0
    y: 0.0
    z: 0.0
    w: 0.0
    " 
```
Which is made easier with tab-complete.