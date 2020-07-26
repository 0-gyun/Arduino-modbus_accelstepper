# modbus_accelstepper

## modbus [1]
### What is modbus
Modbus is a data communications protocol for use with programmable logic controllers (PLCs).
Modbus is a commonly available means of connecting industrial electronic devices.
#### Adventage
> 1. Openly published
> 2. Royalty-free
> 3. Developed for industrial applications
> 4. Relatively easy to deploy and maintain
> 5. Places few restrictions on the format of the data to be transmitted

#### Wiring
Modbus uses the RS485 or Ethernet as its wiring type.
Modbus supports communication to and from multiple devices connected to the **same cable or Ethernet network**.


## Arduino modbus [2]

    #include <ArduinoRS485.h>
    #include <ArduinoModbus.h> 

ArudinoModbus library is based ArduinoRS485 library for serial communication.
Arduion AVR devices can communicate with default UART (USB port).
But boards using other cores like ARM (DUE or STM32..) have to modify.

### Setting
    ModbusRTUServer.begin(1, 115200);
    ModbusRTUServer.configureCoils(0x00, 1);               //(Read & Write)
    //0. motor Stop
    ModbusRTUServer.configureInputRegisters(0x00, 1);      // (Read Only)
    // 0. Current Position
    ModbusRTUServer.configureHoldingRegisters(0x00, 4);    //(Read & Write)
    // 0. Target Position 
    // 1. Max Speed
    // 2. Acceleration
The begin() function sets the device ID and baudrate and configuration. In this code, I set the ID as 1 and baudrate as 115200bps. \
The configure...function allocate the number of addresses.\
Coil is the 1 bit information so it can use like switch.
Register is the 2byte (16bit) information so it can allocate date from 0 to 65535.
By using multiple registers, you can handle more than 2 byte data.
Holding Register and Coil can read and write. Input register desctret input can read only.

### Application
    target_pos = ModbusRTUServer.holdingRegisterRead(0x00);
THe ...Read function read the data allocated data at each adresses.
 
    ModbusRTUServer.inputRegisterWrite(0x00, stepper1.currentPosition());
The ...Write function write the data at the adress.
 
    ModbusRTUServer.poll();
The poll() function update the data. poll() must update often. So the device can response faster.


## Arduino Accelstepper [3]
    #include <AccelStepper.h>
AccelStepper library helps using stepper motor.

    // Accelstepper difining pin and declaration
    const int stepper1_step = 2;
    const int stepper1_dir = 3;
    AccelStepper stepper1(AccelStepper:: DRIVER , stepper1_step, stepper1_dir);
Typicaly, by defining pulse and dirction pin and wiring with stepper driver, you can contoll stepper motor.

    stepper1.moveTo(target_pos);
    if(stepper1.distanceToGo() == 0 || ModbusRTUServer.coilRead(0x00)){      // If motor do not need to move or motor stop flag(Coil (0x00)) is on,
        stepper1.setMaxSpeed(ModbusRTUServer.holdingRegisterRead(0x01));       // Set the Maxspeed to setMaxSpeed() function
        stepper1.setAcceleration(ModbusRTUServer.holdingRegisterRead(0x02));   // Set the Acceleration to setAcceleration() function
     }
The moveTo() function cammand the motor postion as step number.
The setMaxSpeed() function set the motor speed.
The setAcceleration() function set the motor acceleration.

    stepper1.run(); 
And run(); function run the motor. This command 


## References
> [1] https://en.wikipedia.org/wiki/Modbus \
> [2] https://www.arduino.cc/en/ArduinoModbus/ArduinoModbus \
> [3] https://www.airspayce.com/mikem/arduino/AccelStepper/index.html
