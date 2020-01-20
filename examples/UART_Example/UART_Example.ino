

/*
UART Passthrough.
Type a message in the Serial monitor. It will send it between Serial ports and echo to the monitor. 
Required Library: ESPSoftwareSerial v5.4.0 
Very impotant to use the correct version!


*/


void setup()
{
    Serial.begin(115200);
    Serial1.begin(115200);
}

void loop()
{

    if (Serial.available())
    {                                 // If anything comes in Serial (USB),
        char in_S0 = Serial.read();
        Serial.print(in_S0);
        Serial1.write(in_S0); // read it and send it out Serial2 (pins 0 & 1)
    }
//
    if (Serial1.available())
    {                       
        char in_S1 = Serial1.read();
        Serial.write(in_S1); // read it and send it out Serial2 (pins 0 & 1)// If anything comes in Serial2 (pins 0 & 1)
    }
}
