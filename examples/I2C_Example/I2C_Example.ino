

/* Demonstrates outputting a message recieved with Serial with I2C on ESP32 
 * YOU DO NOT NEED TO RUN THIS CODE. IT WILL NOT WORK WITHOUT A SLAVE DEVICE CONNECTED. 
 * 
 * Many MCUs, including the ESP32 and TM4C, have I2C implemented in hardware as a peripheral.
 * At the lowest level, you are writing bytes to special I2C registers. Arduino abstracts this away.
 * I2C has a few different names. Sometimes it's called "TWI" for Two Wire Interface. Arduino just calles it Wire. 
 * I2C is a synchronous communcation protocol, meaning it requires a clock signal. 
 * Clock speeds are determined by your parts - check their data sheets. Standard default is 100kHz. Fast mode is 400kHz
 * 
 * There are two pins used for I2C: 
 * SDA aka SDI: Single data line shared between master and all slaves. Default pin 21. 
 * SCL aka SCK: Single clock line. Default pin 22. 
 * 
 * I2C is very useful when you have multiple slave devices. All devices will share the SDA and SCL lines in a daisy chain.
 * Each slave has a unique identifier, which is 7 or 8 bits. If it's 7 bits, the LSB is often a Read or Write bit. 
 * The Arduino library supports sending up to 32 bytes in one transaction. Other libraries/devices may support more or less.
 * Each packet from the master starts with the Slave's identifier and then the message. The master requires an acknowledgment from the Slave to continue transmission.
 * A Slave cannot respond unless requested by the master. This is important, since there is only one data line we can't have multiple things talking at once.
 * I2C is very useful because it only requires two pins and can support multiple slaves. However, it has its downsides.
 * The lines are open drain, so they require pull up or pull down resistors. There are weak ones built into the ESP32, but weak ones need a longer setup 
 * time when toggling, and therefore need a lower clock speed. Sometimes external I2C modules come with resistors built in.  
 * I2C lines are notoriously sensitive to interference. Keep them as short and shielded as possible. 
 * 
 * Created 1/15/2019 by Rita Kambil
 */

#include <Wire.h>

void setup()
{
    Wire.begin(); // join i2c bus (address optional for master)
}

byte x = 0;

void loop()
{
    Wire.beginTransmission(4); // transmit to device #4
    Wire.write("x is ");       // sends five bytes
    Wire.write(x);             // sends one byte
    Wire.endTransmission();    // stop transmitting

    x++;
    delay(500);
}
