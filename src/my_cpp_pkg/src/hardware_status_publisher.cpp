#include "rclcpp/rclcpp.hpp"
#include "my_robot_interfaces/msg/hardware_status.hpp"

using namespace std::chrono_literals;

class HardwareStatusPublisherNode : public rclcpp::Node 
{
public:
    HardwareStatusPublisherNode() : Node("hardware_status") 
    {
        hw_status_pub_ =  this->create_publisher<my_robot_interfaces::msg::HardwareStatus>(
            "hardware_status", 10
        );
        timer_ = this->create_wall_timer(
            1s,
            std::bind(&HardwareStatusPublisherNode::publishHardwareStatus, this)
        );
        RCLCPP_INFO(this->get_logger(), "Hardware Status Publisher now ready to view.");
    }
private:

    void publishHardwareStatus() {
        auto msg = my_robot_interfaces::msg::HardwareStatus();
        msg.temperature = 47.3;
        msg.are_systems_ready = false;
        msg.debug_message = "Life's intent to be a rock.";
        hw_status_pub_->publish(msg);
    }

    rclcpp::Publisher<my_robot_interfaces::msg::HardwareStatus>::SharedPtr hw_status_pub_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<HardwareStatusPublisherNode >(); // MODIFY NAME
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}