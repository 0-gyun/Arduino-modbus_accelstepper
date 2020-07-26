#include <ArduinoRS485.h> 
#include <ArduinoModbus.h>
#include <AccelStepper.h>

// Accelstepper difine pin and declaration
const int stepper1_step = 2;
const int stepper1_dir = 3;
AccelStepper stepper1(AccelStepper:: DRIVER , stepper1_step, stepper1_dir);

// stepper motor's position information
long target_pos;        // Using when command
long current_pos;       // Using when get current position

void setup() {
  ModbusRTUServer.begin(1, 115200);
  ModbusRTUServer.configureCoils(0x00, 1);               //(Read & Write)
  //0. motor Stop
  ModbusRTUServer.configureInputRegisters(0x00, 1);      // (Read Only)
  // 0. Current Position
  ModbusRTUServer.configureHoldingRegisters(0x00, 4);    //(Read & Write)
  // 0. Target Position 
  // 1. Max Speed
  // 2. Acceleration

  //Initial Setting)
  ModbusRTUServer.holdingRegisterWrite(0x00, 0);       // Initial target pos = 0
  ModbusRTUServer.holdingRegisterWrite(0x01, 500);     // Initial max speed = 500
  ModbusRTUServer.holdingRegisterWrite(0x02, 500);     // Initial accleration = 500
}

void loop() {
target_pos = ModbusRTUServer.holdingRegisterRead(0x00);                    // Read the Target pos from Holding Resigister (0x00)
stepper1.moveTo(target_pos);                                               // Set the Target pos to moveTo() function
  if(stepper1.distanceToGo() == 0 || ModbusRTUServer.coilRead(0x00)){      // If motor do not need to move or motor stop flag(Coil (0x00)) is on,
    stepper1.setMaxSpeed(ModbusRTUServer.holdingRegisterRead(0x01));       // Set the Maxspeed to setMaxSpeed() function
    stepper1.setAcceleration(ModbusRTUServer.holdingRegisterRead(0x02));   // Set the Acceleration to setAcceleration() function
  }
  else{
    stepper1.run();                                                        // If the distance to go of motor is not zero, motor run
  }
  
ModbusRTUServer.inputRegisterWrite(0x00, stepper1.currentPosition());      // Motor current position is allocated at Input Resister (0x00)
ModbusRTUServer.poll();
}
