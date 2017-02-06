#include <math.h>
#include <main.h>

#define SIGNUM(num) ((num > 0) - (num < 0))
#define MIN(num1, num2) (num1 < num2 ? num1 : num2)

/**
 * Use input from joystick to find what the motor outputs should be
 */
void calculateArcadeDrive(const int movement, const int rotation, int *leftSpeed, int *rightSpeed){
	*leftSpeed = movement + rotation;
	*rightSpeed = movement - rotation;
	
	// restrict motor output values to -127 to 127
	*leftSpeed = SIGNUM(*leftSpeed) * MIN(abs(*leftSpeed), 127);
	*rightSpeed = SIGNUM(*rightSpeed) * MIN(abs(*rightSpeed), 127);
}