
#include "RobotMap.h"
#include "OI.h"
#include "OpenOneMotor.h"
#include <frc/IterativeRobot.h>
#include "OI.h"
#include <iostream>
#include <ctre/Phoenix.h>

OpenOneMotor::OpenOneMotor () {

}
WPI_TalonSRX * OpenOneMotor::Open (int DeviceNumber) {
	WPI_TalonSRX * ReturnTalonObj;
	ReturnTalonObj = new WPI_TalonSRX (DeviceNumber);
	ReturnTalonObj->SetInverted(Invert);
	ReturnTalonObj->ConfigPeakCurrentLimit(CurrentLimitAmp, 0);
	ReturnTalonObj->ConfigPeakCurrentDuration(1000,0);
	ReturnTalonObj->ConfigOpenloopRamp(RampTime, 0);
	ReturnTalonObj->EnableCurrentLimit(CurrentLimit);
	ReturnTalonObj->SetSafetyEnabled(true);
	return ReturnTalonObj;
}
