/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include "RobotMap.h"
#include "OI.h"
#include <subsystems/DriveBase.h>
#include <frc/Commands/Scheduler.h>
#include <frc/SmartDashboard/SmartDashboard.h>
#include <frc/drive/DifferentialDrive.h>
#include "OI.h"
#include <frc/Joystick.h>
#include <frc/RobotDrive.h>
#include <iostream>
#include "Robot.h"
#include <ctre/Phoenix.h>
#include <commands/TankDrive.h>
WPI_TalonSRX * FrontL;
WPI_TalonSRX * FrontR;
WPI_TalonSRX * BackL; 
WPI_TalonSRX * BackR;
frc::DifferentialDrive * _diffDrive;
DriveBase::DriveBase() : Subsystem("DriveBase") {}

void DriveBase::DriveBaseInit() {
initialized = true;
	FrontL = new WPI_TalonSRX (frontLeftDrive);
		FrontR = new WPI_TalonSRX (frontRightDrive);
		BackL = new WPI_TalonSRX (backLeftDrive);
		BackR = new WPI_TalonSRX (backRightDrive);
		_diffDrive = new frc::DifferentialDrive (*FrontL, *FrontR);

		FrontR->ConfigFactoryDefault();
		FrontL->ConfigFactoryDefault();
		BackR->ConfigFactoryDefault();
		BackL->ConfigFactoryDefault();

		FrontR->SetInverted(true);
		FrontL->SetInverted(false);
		BackR->SetInverted(true);
		BackL->SetInverted(false);

		FrontR->ConfigPeakCurrentLimit(50,0);
		FrontL->ConfigPeakCurrentLimit(50,0);
		BackR->ConfigPeakCurrentLimit(50,0);
		BackL->ConfigPeakCurrentLimit(50,0);

		FrontR->ConfigPeakCurrentDuration(1000,0);
		FrontL->ConfigPeakCurrentDuration(1000,0);
		BackR->ConfigPeakCurrentDuration(1000,0);
		BackL->ConfigPeakCurrentDuration(1000,0);

		FrontL->ConfigOpenloopRamp(RampTime, 0);
    	FrontR->ConfigOpenloopRamp(RampTime, 0);
   		BackL->ConfigOpenloopRamp(RampTime, 0);
    	BackR->ConfigOpenloopRamp(RampTime, 0);

		FrontR->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
		FrontL->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);

		FrontR->EnableCurrentLimit(true);
		FrontL->EnableCurrentLimit(true);
		BackR->EnableCurrentLimit(true);
		BackL->EnableCurrentLimit(true);


		//PID BTW
		FrontR->Config_kP(0, RightP, 0);
		FrontR->Config_kI(0, RightI, 0);
		FrontR->Config_kD(0, RightD, 0);
		FrontL->Config_kP(0, LeftP, 0);
		FrontL->Config_kI(0, LeftI, 0);
		FrontL->Config_kD(0, LeftD, 0);

		FrontR->ConfigNominalOutputForward(NominalOutput, 0);
		FrontR->ConfigNominalOutputReverse(-NominalOutput, 0);
		FrontL->ConfigNominalOutputForward(NominalOutput, 0);
		FrontL->ConfigNominalOutputReverse(-NominalOutput, 0);

		FrontR->SetSensorPhase(false);
		FrontL->SetSensorPhase(false);


		FrontR->ConfigPeakOutputForward(MaxOutput, 0);
		FrontR->ConfigPeakOutputReverse(-MaxOutput, 0);
		FrontL->ConfigPeakOutputForward(MaxOutput, 0);
		FrontL->ConfigPeakOutputReverse(-MaxOutput, 0);

		FrontR->ConfigNeutralDeadband(PIDDeadband, 0);
		FrontL->ConfigNeutralDeadband(PIDDeadband, 0);

		FrontR->SetSelectedSensorPosition(0,0,0);
		FrontL->SetSelectedSensorPosition(0,0,0);

		_diffDrive->SetSafetyEnabled(false);

		BackL->SetSafetyEnabled(false);
		BackR->SetSafetyEnabled(false);
		_diffDrive->SetExpiration(.5);

		BackL->Set(ctre::phoenix::motorcontrol::ControlMode::Follower, frontLeftDrive);
		BackR->Set(ctre::phoenix::motorcontrol::ControlMode::Follower, frontRightDrive);
		printf("Done setting up motor \n");
}
void DriveBase::ArcadeDrive(double xAxis, double yAxis) {
  	double parsedLeft;
	double parsedRight;
	double parsedX;
	double parsedY;
	double power = 2.3;
	//Setting inputs to a power
	parsedX = pow((xAxis>0)?xAxis:-xAxis, power) * (xAxis / (xAxis>0)?xAxis:-xAxis);

	parsedY = pow((yAxis>0)?yAxis:-yAxis, power) * (yAxis / (yAxis>0)?yAxis:-yAxis);

	if (yAxis < 0) // forward
	{
		//TO BE
		//FILLED IN
		//Turning Left?
		
			parsedLeft = parsedY + parsedX;
			parsedRight = parsedY - parsedX;
		
	}
	else //backwards
	{
			parsedLeft = parsedY - parsedX;
			parsedRight = parsedY + parsedX;
	}
	_diffDrive->TankDrive(-parsedLeft, parsedRight);

}
void DriveBase::RampSwitch(bool rampOn) {
	double ramp = (rampOn)?RampTime:0;
	FrontL->ConfigOpenloopRamp(ramp, 0);
    FrontR->ConfigOpenloopRamp(ramp, 0);
   	BackL->ConfigOpenloopRamp(ramp, 0);
    BackR->ConfigOpenloopRamp(ramp, 0);

}
void DriveBase::InitDefaultCommand() {
  if (!initialized) {
		DriveBase::DriveBaseInit();
	}
	Robot::m_drivebase.SetDefaultCommand(new TankDrive());
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
