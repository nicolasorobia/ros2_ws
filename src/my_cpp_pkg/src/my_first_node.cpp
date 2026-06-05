#include "rclcpp/rclcpp.hpp"

class MyNode : public rclcpp::Node
{
public:
    MyNode() : Node("cpp_test"), counter_(0)
    {
        RCLCPP_INFO(this->get_logger(), "Hello from cpp node");
        timer_ = this->create_wall_timer(std::chrono::seconds(1),
                                         std::bind(&MyNode::timerCallback, this));
    }
    
private:
    void timerCallback()
    {
        RCLCPP_INFO(this->get_logger(), "... Zuko here %d", counter_);
        counter_++;
    }
    rclcpp::TimerBase::SharedPtr timer_;
    int counter_;
};

int main(int argc, char **argv)
{
    // initialize ROS2 communication
    rclcpp::init(argc, argv);
    
    // auto node = std::make_shared<rclcpp::Node>("cpp_test");
    // RCLCPP_INFO(node->get_logger(), "Hello from cpp node");

    // OOP Version
    auto node = std::make_shared<MyNode>();
    
    rclcpp::spin(node);

    // shutdown ROS2 communication
    rclcpp::shutdown();
    return 0;
}