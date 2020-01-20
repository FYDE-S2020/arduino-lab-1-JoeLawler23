

/* Demonstrates outputting a message recieved with Serial with SPI on ESP32 
 * Type a short (<100 char) message in the serial monitor and observe the output on the logic analyzer.
 * Many MCUs, including the ESP32 and TM4C, have SPI implemented in hardware as a peripheral.
 * At the lowest level, you are writing bytes to special SPI registers. Arduino abstracts this away.
 * SPI is a synchronous communcation protocol, meaning it requires a clock signal. 
 * Clock speeds are determined by your parts - check their data sheets. 
 * There are four pins used for SPI: 
 * MOSI: Master out Slave in. We will be outputting the message on this line.
 * MISO: Master in Slave Out. Since we don't have peripherals, this is unconnected. You may ignore it.
 * SCLK: Clock signal. We will use 1MHz. You can try experimenting with other speeds and profiling them.
 * CS or SS: Chip Select, aka Slave Select. This tells the ESP32 or the Slave that they should be listening. It is active LOW. 
 * Arduino doesn't handle CS for you, it must be set before and after sending the message.
 * 
 * Created 1/15/2019 by Rita Kambil
 */

#include <SPI.h>

static const int spiClk = 1000000; // 1 MHz

//uninitalised pointers to SPI objects
SPIClass *vspi = NULL;

void setup()
{
    Serial.begin(115200);

    //initialise two instances of the SPIClass attached to VSPI and HSPI respectively
    vspi = new SPIClass(VSPI);

    //clock miso mosi ss

    //initialise vspi with default pins
    //SCLK = 18, MISO = 19, MOSI = 23, SS = 5
    vspi->begin();

    //set up slave select pins as outputs as the Arduino API
    //doesn't handle automatically pulling SS low
    pinMode(5, OUTPUT); //VSPI SS
    digitalWrite(5, HIGH); //Initialize
}

// the loop function runs over and over again until power down or reset
void loop()
{
    //use the SPI buses
    if (Serial.available())
    { // If anything comes in Serial (USB),
        byte in_S0 = Serial.read();
        Serial.print(in_S0);
        vspiCommand(in_S0);
    }
    // delay(10);
}

void vspiCommand(byte data)
{
    vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
    digitalWrite(5, LOW); //pull SS slow to prep other end for transfer
    vspi->transfer(data);
    digitalWrite(5, HIGH); //pull ss high to signify end of data transfer
    vspi->endTransaction();
}
