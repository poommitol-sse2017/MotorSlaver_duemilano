#include <Arduino.h>
#include <Motor.h>
#include <Configuration.h>


long count[4] = {0, 0, 0, 0};
bool last_dir[4] = {0, 0, 0, 0};
bool turning = false;
bool last_turning = false;
String inputString = "";     // a String to hold incoming data
bool stringComplete = false; // whether the string is complete

float speedRPM[4] = {0, 0, 0, 0};
long time = 0;
int speed = 0;
int wdt = 0;

void setup()
{
    // put your setup code here, to run once:
    initialization();
    Serial.begin(115200);
    Serial.println("GGG");
}

void resp(){
    Serial.write('#');
    Serial.write('s');
    Serial.print(wheelRR.getSpeedRPM());
    Serial.print(wheelRL.getSpeedRPM());
    Serial.print(wheelFR.getSpeedRPM());
    Serial.print(wheelFL.getSpeedRPM());
    Serial.write('E');
    Serial.println();
}
void debug(){
    Serial.print(wheelRR.getSpeedRPM());
    Serial.print(", ");
    Serial.print(wheelRL.getSpeedRPM());
    Serial.print(", ");
    Serial.print(wheelFR.getSpeedRPM());
    Serial.print(", ");
    Serial.print(wheelFL.getSpeedRPM());
    Serial.println();
}
void loop()
{
    // put your main code here, to run repeatedly:
    time = micros();
    while((micros() - time) < 40000);
    wheelRR.computeSpeed(micros() - time);
    wheelRL.computeSpeed(micros() - time);
    wheelFR.computeSpeed(micros() - time);
    wheelFL.computeSpeed(micros() - time);
    wheelRR.runPWM(speed);
    wheelRL.runPWM(speed);
    wheelFR.runPWM(speed);
    wheelFL.runPWM(speed);
    //debug();
    resp();
    if (wdt == 100)
        speed = 0;
    wdt++;   
}

void serialEvent()
{
    while (Serial.available())
    {
        // get the new byte:
        char inChar = (char)Serial.read();
        // add it to the inputString:
        if (isDigit(inChar) || inChar == '-')
            inputString += inChar;
        // if the incoming character is a newline, set a flag so the main loop can
        // do something about it:
        if (inChar == '\n')
        {
            stringComplete = true;
            speed = inputString.toFloat();
            wdt = 0;
            inputString = "";
        }
    }
}