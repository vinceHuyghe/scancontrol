#include "rclcpp/rclcpp.hpp"
#include "micro_epsilon_scancontrol_driver/driver.h"

static const rclcpp::Logger logger = rclcpp::get_logger("scancontrol_driver");

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    // rclcpp::Node::SharedPtr node = rclcpp::Node::make_shared("scancontrol_driver"); 
    // rclcpp::Node::SharedPtr private_node = rclcpp::Node::make_shared("scancontrol_driver"); 
    auto node = std::make_shared<rclcpp::Node>("scancontrol_driver");

    // Start the driver
    try
    {
        // scancontrol_driver::ScanControlDriver driver(node, private_node);
        scancontrol_driver::ScanControlDriver driver(node, node);
        RCLCPP_INFO(logger, "Driver started");

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
        RCLCPP_FATAL_STREAM(logger, error.what());
        rclcpp::shutdown();
        return 0;
    }


}
