from geometry_msgs.msg import Twist
import rclpy
from rclpy.node import Node


class TurtleControlNode(Node):
    """发布恒定线速度与角速度，控制小乌龟做圆周运动."""

    def __init__(self):
        super().__init__('turtle_control_node')
        self.declare_parameter('linear_speed', 2.0)
        self.declare_parameter('angular_speed', 1.0)

        self.publisher_ = self.create_publisher(Twist, '/turtle1/cmd_vel', 10)
        self.timer = self.create_timer(0.1, self.timer_callback)
        self.get_logger().info('turtle_control_node 已启动，小乌龟开始画圆')

    def timer_callback(self):
        msg = Twist()
        msg.linear.x = self.get_parameter('linear_speed').value
        msg.angular.z = self.get_parameter('angular_speed').value
        self.publisher_.publish(msg)


def main(args=None):
    rclpy.init(args=args)
    node = TurtleControlNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
