#include "ros/ros.h"
#include "ik_service/PoseIK.h"
#include "ur_kinematics/ur_kin.h"

bool pose_ik(ik_service::PoseIK::Request  &req, ik_service::PoseIK::Response &res) {
    ROS_INFO("ik_service request received");
    double T[4][4] = {
        {  0.0, -1.0,  0.0,  req.part_pose.position.x},
        {  0.0,  0.0,  1.0,  req.part_pose.position.y},
        { -1.0,  0.0,  0.0,  req.part_pose.position.z},
        {  0.0,  0.0,  0.0,  -1.0}
    };
    int num_sol;
    double q_sols[8][6];
    num_sol = ur_kinematics::inverse(&T[0][0], &q_sols[0][0], 0.0);
    for (int i = 0; i < num_sol; ++i) {
        for (int j = 0; j < 6; ++j) {
            res.joint_solutions[i].joint_angles[j] = q_sols[i][j];
        }
    }
    ROS_INFO("ik_service found %i solutions", num_sol);
    res.num_sols = num_sol;
    return true;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "ik_service");
    ros::NodeHandle n;
    ros::ServiceServer service = n.advertiseService("pose_ik", pose_ik);
    ROS_INFO("started IK service!");
    ros::spin();

    return 0;
}