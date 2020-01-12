#include "main.h"
#include "devices.h"
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize()
{

}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void autonomous()
{
	profileController->generatePath(
	{{0_in, 0_in, 0_deg},
	 {8_ft, 0_ft, 0_deg}},
	"A");

	profileController->generatePath(
	{{24_in, 0_in, 0_deg},
	 {52_in, 0_in, 0_deg}},
	"B");

	profileController->generatePath(
	{{0_in, 24_in, 0_deg},
	 {24_in, 0_in, 0_deg}},
	"C");

	profileController->generatePath(
	{{0_in, 24_in, 0_deg},
	 {52_in, -24_in, 0_deg}},
	"D");

	profileController->generatePath(
	{{24_in, -24_in, 0_deg},
	 {52_in, -24_in, 0_deg}},
	"E");

	profileController->generatePath(
	{{24_in, -24_in, 0_deg},
	 {24_in, -24_in, 135_deg}},
	"F");

	intakeMotors.moveVoltage(12000);

	profileController->setTarget("A");
	profileController->waitUntilSettled();
	//profileController->removePath("A");
	intakeMotors.moveVoltage(0);

	profileController->setTarget("B", true);
	profileController->waitUntilSettled();
	profileController->removePath("B");

	intakeMotors.moveVoltage(12000);

	profileController->setTarget("C", true);
	profileController->waitUntilSettled();
	profileController->removePath("C");

	intakeMotors.moveVoltage(0);

	profileController->setTarget("D", true);
	profileController->waitUntilSettled();
	profileController->removePath("D");

	profileController->setTarget("E", true);
	profileController->waitUntilSettled();
	profileController->removePath("E");

	profileController->setTarget("F");
	profileController->waitUntilSettled();
	profileController->removePath("F");
}


const int angle1 = 3;
const int angle2 = 5;
const int angle3 = 7;

//void anglerToggle(void* inp);

void opcontrol()
{
//	pros::Task (anglerToggle, (void*)"inp", "angleToggle");

	while (1)
	{
		// DRIVETRAIN
		drive->getModel()->arcade(master.getAnalog(ControllerAnalog::leftY),
														  master.getAnalog(ControllerAnalog::rightX));

		// INTAKE AND OUTAKE MECHANISM
		if (Intake.isPressed())
			intakeMotors.moveVoltage(12000);

		else if (Outake.isPressed())
			intakeMotors.moveVoltage(-12000);

		else
			intakeMotors.moveVoltage(0);

		// // ANGLER MECH
		// if (Angler.isPressed())
		// {
		// 	angleMotor.moveVelocity(100);
		// 	if ((angleMotor.getPosition() > angle1) && (angleMotor.getPosition() < angle2))
		// 		angleMotor.moveVelocity(50);
		//
		// 	else
		// 		angleMotor.moveVelocity(0);
		// }
		//
		// else
		// 	angleMotor.moveVelocity(0);

		// DELAY
		pros::delay(10);
	}
}

// void anglerToggle(void* inp)
// {
// 	while (1)
// 	{
// 		bool angler;
// 		if(Angler.changedToPressed())
// 			angler = !angler;
//
// 		if (angler == true)
// 		{
// 			angleMotor.moveVelocity(100);
// 			if ((angleMotor.getPosition() > angle1) && (angleMotor.getPosition() < angle2))
// 				angleMotor.moveVelocity(50);
//
// 			else
// 				angleMotor.moveVelocity(0);
// 		}
//
// 		else if ((angleMotor.getPosition() > angle3) && (angler == false))
// 			angleMotor.moveVelocity(-100);
//
// 		else
// 			angleMotor.moveVelocity(0);
// 	}
// }
