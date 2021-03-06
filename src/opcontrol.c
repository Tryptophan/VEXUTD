/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
void operatorControl()
{


	setAutoDriveMode(NONE);
	//initHeadingThread();
	/*delay(5000);
	moveY(400);
	delay(3000);
	moveY(-400);
	delay(3000);
	moveX(400);
	delay(3000);
	moveX(-400);
	delay(2000);
	moveY(400);
	delay(2000);
	moveX(400);
	delay(2000);
	moveY(-400);
	delay(2000);
	moveX(-400);
	//setPIDTarget(y_pid, 0.0);
	delay(100000);*/
	/*
	initHeadingThread();

	setAutoDriveMode(ROTATION_ONLY);

	delay(2000);
	setHeading(90);
	delay(2000);
	setHeading(180);
	delay(2000);
	setHeading(0);
	delay(2000);
	setAutoDriveMode(X_ROTATION);
	delay(2000);
	setAutoDriveMode(ROTATION_ONLY);
	delay(100);
	setHeading(180);
	delay(1500);
	setAutoDriveMode(X_ROTATION);
	delay(2000);
	setAutoDriveMode(NONE);
	*/


	/*
	delay(1000);
	setArmTarget(-145);
	delay(3000);
	clawPower(-127);
	delay(500);
	clawPower(-100);
	delay(250);
	setArmTarget(250);
	delay(1500);
	setArmTarget(00);
	delay(375);
	clawPower(127);
	delay(350);
	clawPower(0);
	delay(10000000);
	*/


	bool pick_up = false;
	bool pick_up_cube = false;
	bool toss = false;
	bool claw_overide = false;
	bool arm_override = false;
	bool pick_up_continue = false;
	bool pick_up_cube_continue = false;
	while (1)
	{
		moveBase(joystickGetAnalog(1,4),joystickGetAnalog(1,3),joystickGetAnalog(1,1));

		if(joystickGetDigital(1,8,JOY_DOWN) && pick_up == false)
		{
			if(pick_up_continue == false)
			{
				pickUpDownMacro();	
			}
			else
			{
				pickUpUpMacro();
			}
			pick_up_continue = !pick_up_continue;
		}
		pick_up = joystickGetDigital(1,8,JOY_DOWN);
		
		if(joystickGetDigital(1,8,JOY_UP) && pick_up_cube == false)
		{
			if(pick_up_cube_continue == false)
			{
				pickUpDownCubeMacro();	
			}
			else
			{
				pickUpUpCubeMacro();
			}
			pick_up_cube_continue = !pick_up_cube_continue;
		}
		pick_up_cube = joystickGetDigital(1,8,JOY_UP);

		if(joystickGetDigital(1,8,JOY_RIGHT) && toss == false)
		{
			tossMacro();
		}
		toss = joystickGetDigital(1,8,JOY_RIGHT);
		
		
		
		// manual control of arm target
		if (!arm_override) {
			if (joystickGetDigital(1, 7, JOY_UP))
			{
				arm_macro_mutex = true;
				arm_pid->target += 30;
			} else if (joystickGetDigital(1, 7, JOY_DOWN)) {
				arm_macro_mutex = true;
				arm_pid->target -= 30;
			} else {
				arm_macro_mutex = false;
			}
		}
		arm_override = joystickGetDigital(1, 7, JOY_UP) | joystickGetDigital(1, 7, JOY_DOWN);
		
		//claw_overide
		if(joystickGetDigital(1, 6, JOY_UP))
		{
			claw_overide = true;
			clawPower(75);
		}
		else if(joystickGetDigital(1, 6, JOY_DOWN))
		{
			claw_overide = true;
			clawPower(-75);
		}
		else if(claw_overide)
		{
			claw_overide = false;
			clawPower(0);
		}
		
		
		// move lift with up and down buttons in button group 5
		if (joystickGetDigital(1, 5, JOY_UP)) {
			liftPower(64);
		} else {
			liftPower(-64 * joystickGetDigital(1, 5, JOY_DOWN));
		}
		
		delay(20);
	}
}
