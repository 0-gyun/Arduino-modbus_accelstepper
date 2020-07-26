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
Arduion AVR devices can communicate with default UART.
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







## References
> [1] https://en.wikipedia.org/wiki/Modbus \
> [2] https://www.arduino.cc/en/ArduinoModbus/ArduinoModbus
