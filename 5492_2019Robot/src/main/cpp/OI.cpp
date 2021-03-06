/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include <frc/WPILib.h>
#include <frc/Joystick.h>
#include <frc/GenericHID.h>
#include <frc/XboxController.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableEntry.h>
#include <networktables/NetworkTableInstance.h>
#include <frc/WPILib.h>

OI::OI() {
  _driverStick = 0;
	_manualStick = 0;
	table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
  // Process operator interface input here.
}
void OI::OIInit(){
  	if (_driverStick == 0)
	{
		_driverStick = new frc::XboxController(0);
	}
	if (_manualStick == 0)
	{
		_manualStick = new frc::XboxController(1);
	}
	LightSensorZero = new frc::DigitalInput(0);
	LightSensorOne = new frc::DigitalInput(1);
}
double OI::ReturnDriverXAxis(){
	return DeadBand(_driverStick->GetX(frc::GenericHID::kRightHand));

}
double OI::ReturnDriverYAxis(){
	return DeadBand(_driverStick->GetY(frc::GenericHID::kLeftHand));
}

double OI::DeadBand(double joystick) {
	if (-0.2 < joystick && joystick < 0.2) {
		joystick = 0;
	}
		return joystick;
}

double OI::ReturnManualLeftYAxis(){
	return DeadBand(_manualStick->GetY(frc::GenericHID::kLeftHand));
}
bool OI::ReturnDriverXButton() {
	return _driverStick->GetXButton();
}
double* OI::ReturnVisionX(){
	targetOffsetAngle_Horizontal = table->GetNumber("tx",0.0); 
	targetArea = table->GetNumber("ta",0.0);
	visionData[0] = targetOffsetAngle_Horizontal;
	visionData[1] = targetArea;
	return visionData;
  
}
bool* OI::ReturnLightSensors() {
	lightData[0] = LightSensorZero->Get();
	lightData[1] = LightSensorOne->Get();
	return lightData;
}


