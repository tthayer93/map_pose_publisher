#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/transform_listener.h>

int main(int argc, char** argv){
    // init
    ros::init(argc, argv, "map_pose_publisher");
    ros::NodeHandle nh;
    ros::NodeHandle nh_private("~");
    tf::TransformListener* tf_listener = new tf::TransformListener();
    ros::Publisher pub_pose = nh.advertise<geometry_msgs::PoseStamped>("/map_pose", 1000);
    // parameters
    float publish_rate;
    nh_private.param<float>("publish_rate", publish_rate, 1.0);
    std::string base_frame;
    nh_private.param<std::string>("base_frame", base_frame, "base_link");
    std::string map_frame;
    nh_private.param<std::string>("map_frame", map_frame, "map");
    // looping
    ros::Rate rate(publish_rate);
    tf::StampedTransform transform;
    geometry_msgs::PoseStamped out_pose;
    unsigned int seq = 0;
    while(nh.ok()){
        rate.sleep();
        // get transform
        try{
            tf_listener->lookupTransform(map_frame, base_frame, ros::Time(0), transform);
        }catch(tf::TransformException exception){
            ROS_INFO("%s", exception.what());
            continue;
        }
        // set pose message
        out_pose.header.seq = ++seq;
        out_pose.header.stamp = transform.stamp_;
        out_pose.header.frame_id = transform.frame_id_;
        out_pose.pose.position.x = transform.getOrigin().getX();
        out_pose.pose.position.y = transform.getOrigin().getY();
        out_pose.pose.position.z = transform.getOrigin().getZ();
        out_pose.pose.orientation.x = transform.getRotation().getX();
        out_pose.pose.orientation.y = transform.getRotation().getY();
        out_pose.pose.orientation.z = transform.getRotation().getZ();
        out_pose.pose.orientation.w = transform.getRotation().getW();
        // publish
        pub_pose.publish(out_pose);
    }
}
