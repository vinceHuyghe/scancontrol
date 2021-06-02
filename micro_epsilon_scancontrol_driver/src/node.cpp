#include "rclcpp/rclcpp.hpp"
#include "micro_epsilon_scancontrol_driver/driver.h"

int main(int argc, char** argv)
{
    // ros::init(argc, argv, "");
    // ros::NodeHandle node;
    // ros::NodeHandle private_nh("~");
    rclcpp::init(argc, argv);
    rclcpp::Node::SharedPtr node;
    auto private_node = rclcpp::Node::make_shared("~") 

    // Start the driver
    try
    {
        scancontrol_driver::ScanControlDriver driver(node, private_node);
        RCLCPP_INFO(LOGGER, "Driver started");

        // Loop driver until shutdown
        driver.StartProfileTransfer();
        while(rclcpp::ok())
        {
            rclcpp::spin_some(node);
        }
        driver.StopProfileTransfer();
        return 0;
    }
    catch(const std::runtime_error& error)
    {
        RCLCPP_FATAL_STREAM(LOGGER, error.what());
        rclcpp::shutdown();
        return 0;
    }


}
