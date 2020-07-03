#ifndef CRANE_X7_MPC_STATE_FEEDBACK_CONTROLLER_HPP_
#define CRANE_X7_MPC_STATE_FEEDBACK_CONTROLLER_HPP_

#include <string>
#include <vector>

#include "ros/ros.h"
#include "controller_interface/controller.h"
#include "hardware_interface/joint_command_interface.h"
#include "std_msgs/Float64MultiArray.h"
#include "sensor_msgs/JointState.h"

#include "Eigen/Core"

#include "crane_x7_mpc/ControlInputPolicy.h"


namespace cranex7mpc {

class StateFeedbackController : public controller_interface::Controller<hardware_interface::EffortJointInterface> {
public:
  StateFeedbackController(const unsigned int dimq, const unsigned int dimv);
  bool init(hardware_interface::EffortJointInterface* hardware, 
            ros::NodeHandle &node_handler) override;
  void starting(const ros::Time& time) override;
  void stopping(const ros::Time& time) override;

private:
  void update(const ros::Time& time, const ros::Duration& period) override;
  void subscribeControlInputPolicy(
      const crane_x7_mpc::ControlInputPolicy& policy);

  std::vector<hardware_interface::JointHandle> joint_handlers_;
  ros::NodeHandle node_handle_;
  ros::Subscriber control_input_policy_subscriber_;

  unsigned int dimq_, dimv_;
  Eigen::VectorXd q_stn_, v_stn_, u_stn_, q_, v_, u_;
  Eigen::MatrixXd Kq_, kv_;
};

} // namespace cranex7mpc


#endif // CRANE_X7_MPC_STATE_FEEDBACK_CONTROLLER_HPP_