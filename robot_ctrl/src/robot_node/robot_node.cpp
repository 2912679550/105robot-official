#include "robot_node.hpp"

// ! ========================== single side ctrl ===========================
// ! ========================== single side ctrl ===========================

SINGLE_SIDE_CTRL::SINGLE_SIDE_CTRL(std::string cmd_topic , std::string val_topic , ros::NodeHandle* nh){
    if(nh == nullptr){
        nh_ = new ros::NodeHandle();
    }
    cmd_pub_ = nh_->advertise<ROBOT_STM_CMD_TYPE>(cmd_topic, 1);
    val_sub_ = nh_->subscribe(val_topic, 1, &SINGLE_SIDE_CTRL::val_callback, this);
}

SINGLE_SIDE_CTRL::~SINGLE_SIDE_CTRL(){
    if(nh_ != nullptr){
        delete nh_;
        nh_ = nullptr;
    }
}

void SINGLE_SIDE_CTRL::pub_cmd(const ROBOT_STM_CMD_TYPE &cmdIn){
    cmd_pub_.publish(cmdIn);
}

void SINGLE_SIDE_CTRL::val_callback(const STM_ROBOT_VAL_CPTR &msg){
    val_data_ = *msg;
}

// ! ========================== main robot ===========================
// ! ========================== main robot ===========================

MAIN_ROBOT::MAIN_ROBOT(ros::NodeHandle* nh_ ){
    std::cout<< GREEN_STRING << BLOD_STRING << "main robot node start" << RESET_STRING << std::endl;
    if(nh_ == nullptr){
        nh_ = new ros::NodeHandle();
    }
    front_side_ = new SINGLE_SIDE_CTRL(ROBOT_STM_CMD_F, STM_ROBOT_VAL_F, nh_);
    back_side_ = new SINGLE_SIDE_CTRL(ROBOT_STM_CMD_B, STM_ROBOT_VAL_B, nh_);
}

MAIN_ROBOT::~MAIN_ROBOT(){
    if(front_side_ != nullptr){
        delete front_side_;
        front_side_ = nullptr;
    }
    if(back_side_ != nullptr){
        delete back_side_;
        back_side_ = nullptr;
    }
}

