#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"
#include "example_interfaces/srv/set_bool.hpp"

using namespace std::chrono_literals;
using namespace std::placeholders;

class NumberCounter : public rclcpp::Node 
{
public:
    NumberCounter() : Node("number_counter") 
    {

        subscriber_ = this->create_subscription<example_interfaces::msg::Int64>
                      ("number", 10, 
                        std::bind(&NumberCounter::callbackNumber, this, _1));
        
        publisher_ = this->create_publisher<example_interfaces::msg::Int64>("number_count", 10);

        server_ = this->create_service<example_interfaces::srv::SetBool>(
                    "reset_counter",
                    std::bind(&NumberCounter::callbackResetCounter, this, _1, _2));

        RCLCPP_INFO(this->get_logger(), "Number Counter C++ now active.");
    }

private:

    void callbackNumber(const example_interfaces::msg::Int64::SharedPtr msg)
    {
        counter_ += msg->data;
        auto new_msg = example_interfaces::msg::Int64();
        new_msg.data = counter_;
        publisher_->publish(new_msg);

    }

    void callbackResetCounter(const example_interfaces::srv::SetBool::Request::SharedPtr request,
                            const example_interfaces::srv::SetBool::Response::SharedPtr response)
    {        
        if (request->data) {
            counter_ = 0;
            response->success = true;
            response->message = "Counter has been reseted";
        } else {
            response->success = false;
            response->message = "Counter failed to reset";
        }                     
    }

    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscriber_;
    rclcpp::Service<example_interfaces::srv::SetBool>::SharedPtr server_;
    int counter_ = 0;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberCounter>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}