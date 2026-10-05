#include <rclcpp/rclcpp.hpp>
#include <tf2_ros/transform_broadcaster.h>
#include <turtlesim/msg/pose.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <tf2/LinearMath/Quaternion.h>
using namespace std;

class TurtleTfBroadcaster : public rclcpp::Node
{
public:
    TurtleTfBroadcaster(const std::string & turtle_name)
    : Node("my_tf_broadcaster"), turtle_name_(turtle_name)
    {
        // 创建 TF 广播器
        tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*this);

        // 订阅乌龟的 pose 信息
        subscription_ = this->create_subscription<turtlesim::msg::Pose>(
            turtle_name_ + "/pose", 10,
            std::bind(&TurtleTfBroadcaster::poseCallback, this, std::placeholders::_1));
    }

private:
    using turtlesim::msg::Pose;
    void poseCallback(const Pose::SharedPtr msg)
    {
        // 根据乌龟当前的位姿，设置相对于世界坐标系的坐标变换
        geometry_msgs::msg::TransformStamped transform;

        transform.header.stamp = this->get_clock()->now();
        transform.header.frame_id = "world";
        transform.child_frame_id = turtle_name_;

        // 平移
        transform.transform.translation.x = msg->x;
        transform.transform.translation.y = msg->y;
        transform.transform.translation.z = 0.0;

        // 旋转（由 theta 转换为四元数）
        tf2::Quaternion q;
        q.setRPY(0, 0, msg->theta);
        transform.transform.rotation.x = q.x();
        transform.transform.rotation.y = q.y();
        transform.transform.rotation.z = q.z();
        transform.transform.rotation.w = q.w();

        // 发布坐标变换
        tf_broadcaster_->sendTransform(transform);
    }

    std::string turtle_name_;
    std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscription_;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);

    // 检查命令行参数
    if (argc != 2)
    {
        RCLCPP_ERROR(rclcpp::get_logger("my_tf_broadcaster"), "need turtle name as argument");
        return -1;
    }

    auto node = std::make_shared<TurtleTfBroadcaster>(argv[1]);

    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}