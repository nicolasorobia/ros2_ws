#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

using namespace std::chrono_literals;

class NumberPublisher : public rclcpp::Node 
{
public:
    NumberPublisher() : Node("number_publisher") 
    {
        publisher_ = this->create_publisher<example_interfaces::msg::Int64>("number", 10);
        timer_ = this->create_wall_timer(0.5s, std::bind(&NumberPublisher::publishNumber, this));
        RCLCPP_INFO(this->get_logger(), "Number Publisher C++ now active.");
    }

private:
    void publishNumber()
    {
        auto msg = example_interfaces::msg::Int64();
        msg.data = 365;
        publisher_->publish(msg);
    }

    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberPublisher>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
