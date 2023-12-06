#include "ros/ros.h"
#include "ik_service/PoseIK.h"


int main(int argc, char **argv)
{
  ros::init(argc, argv, "ik_client");
  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<ik_service::PoseIK>("pose_ik");
  ik_service::PoseIK ik_pose;
  geometry_msgs::Pose part_pose;
  part_pose.position.x = 0.5;
  ik_pose.request.part_pose = part_pose;

  if(client.call(ik_pose)) {
      ROS_INFO("Call to ik_service returned [%i] solutions", ik_pose.response.num_sols);
  } else {
      ROS_ERROR("failed to call service ik_service");
      return 1;
  }
  return 0;
}