#include "ros/ros.h"
#include "ik_service/PoseIK.h"



int main(int argc, char **argv) {
    ros::init(argc, argv, "ik_client");
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<ik_service::PoseIK>("pose_ik");
    ik_service::PoseIK ik_pose;
    geometry_msgs::Pose part_pose;
    part_pose.position.x = 0.5;
    ik_pose.request.part_pose = part_pose;
    if(client.call(ik_pose)) {
      for (int i = 0; i < ik_pose.response.num_sols; ++i) {
          ROS_INFO("solution %i:\n", i);
          for (int j = 0; j < 6; ++j) {
              ROS_INFO("    %f\n", ik_pose.response.joint_solutions[i].joint_angles[j]);
          }
      }
    } else {
      ROS_ERROR("failed to call ik_service!");
      return 1;
    }
    return 0;
}