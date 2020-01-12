#include "main.h"

// OPCONTORL CHASSIS
auto drive =
ChassisControllerBuilder()
  .withMotors({15, 13},{-12, -14})
  .withDimensions(AbstractMotor::gearset::green, {{4.125_in, 10.5_in}, imev5GreenTPR})
  .build();


// ODOM CHASSIS
auto odomChassis =
ChassisControllerBuilder()
  .withMotors(1, -2) // left motor is 1, right motor is 2 (reversed)
  .withGains(
      {0.001, 0, 0.0001}, // Distance controller gains
      {0.001, 0, 0.0001}, // Turn controller gains
      {0.001, 0, 0.0001}  // Angle controller gains (helps drive straight)
  )
  // green gearset, 4 inch wheel diameter, 11.5 inch wheelbase
  .withDimensions(AbstractMotor::gearset::green, {{4.125_in, 10.5_in}, imev5GreenTPR})
  .withOdometry() // use the same scales as the chassis (above)
  .buildOdometry(); // build an odometry chassis

// MOTION PROFILE CHASSIS AUTON
auto profileChassis =
ChassisControllerBuilder()
  .withMotors({15, 13}, {-12, -14})
  // Green gearset, 4 in wheel diam, 11.5 in wheel track
  .withDimensions(AbstractMotor::gearset::green, {{4.125_in, 10.5_in}, imev5GreenTPR})
  .withMaxVelocity(100)
  .build();

// PROFILE CONTROLLER
auto profileController =
AsyncMotionProfileControllerBuilder()
  .withLimits({1.0, 2.0, 10.0})
  .withOutput(profileChassis)
  .buildMotionProfileController();


// Button Configuration
ControllerButton leftArrow(ControllerDigital::left);
ControllerButton rightArrow(ControllerDigital::right);
ControllerButton upArrow(ControllerDigital::up);
ControllerButton downArrow(ControllerDigital::down);
ControllerButton armUp(ControllerDigital::L1);
ControllerButton armDown(ControllerDigital::L2);
ControllerButton Intake(ControllerDigital::R1);
ControllerButton Outake(ControllerDigital::R2);
ControllerButton Angler(ControllerDigital::A);
Controller master;

// Motor Configuration
okapi::MotorGroup intakeMotors({5, -6});
okapi::Motor armMotor(2);
okapi::Motor angleMotor(8);
