#!/usr/bin/env python3
import rclpy
from rclpy.node import Node

# OOP VERSION
class MyNode(Node):
    
    # node initializer in class
    def __init__(self):
        super().__init__("py_test")
        self.counter_ = 0
        self.get_logger().info("Hello World")
        self.create_timer(1.0, self.timer_callback)

    def timer_callback(self):
        self.get_logger().info("Zuko here... it's rough here buddy " + str(self.counter_))
        self.counter_ += 1

def main(args=None):
    rclpy.init(args=args) # initialize ROS2 communication
    # node = Node("py_test") # node initializer
    node = MyNode()
    # node.get_logger().info("Hello World") # prints this in terminal
    rclpy.spin(node) # spin method keeps node alive (ctrl+c to terminate)


    rclpy.shutdown() # last step

if __name__ == "__main__": # makes it easier to run program directly from terminal
    main()