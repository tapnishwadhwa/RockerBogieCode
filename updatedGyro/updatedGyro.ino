

#include <Wire.h>
#include "MPU3050lib.h"
#include <math.h>
#include <Servo.h>

#define SAMPLES 300

Gyroscope gyro;
Servo myservo;  
const int calibrate = 4;
bool fail;
int pos = 0;

int8_t gatherAverage(double * avgX, double * avgY, double * avgZ)
{
    Serial.println("Gathering Average...");

    int16_t x, y, z;

    *avgX = 0;
    *avgY = 0;
    *avgZ = 0;

    for (uint16_t i = 0; i < SAMPLES; ++i)
    {
        if (gyro.readRaw(&x, &y, &z) != 0)
        {
            Serial.println("Failed to read gyroscope");
            return -1;
        }

        *avgX += (x - *avgX) / (double)(i + 1);
        *avgY += (y - *avgY) / (double)(i + 1);
        *avgZ += (z - *avgZ) / (double)(i + 1);

        delay(10);
    }

    Serial.println("Averages Gathered:");
    Serial.print("X: ");
    Serial.print(*avgX);
    Serial.print(" Y: ");
    Serial.print(*avgY);
    Serial.print(" Z: ");
    Serial.println(*avgZ);

    return 0;
}

void setup()
{
    Serial.begin(57600);



      myservo.attach(5);
      
   
    
    
    if (gyro.begin(OSEPP_GYRO_SW_ON) != 0)
    {
        Serial.println("Error connecting to gyroscope");
        return;
    }

    gyro.setRange(MPU3050_RANGE_PM250);

    gyro.setOffsets(0, 0, 0);

   
    gyro.setLowPassFilterBw(MPU3050_LOWPASS_5HZ);


    Serial.println("This example will calculate offset values");
    Serial.println("to calibrate the gyroscope. Record");
    Serial.println("these values and enter them in your own");
    Serial.println("projects using this library.");
    Serial.println();

    Serial.println("You need to prevent the gyroscope from moving or");
    Serial.println("vibrating during this test.");
\

    while (true)
    {
      
           if (Serial.available())
        {
            char inByte = Serial.read();
            
            if (inByte == 'k' || inByte == 'K')
                break;
        }
        }
    


    double avgX = 0;
    double avgY = 0;
    double avgZ = 0;

    if (gatherAverage(&avgX, &avgY, &avgZ) != 0)
        return;

    Serial.println();
    Serial.println("Cacluating Offsets...");

    int16_t offset_x, offset_y, offset_z;

    avgX /= 4;
    avgY /= 4;
    avgZ /= 4;

    offset_x = round(avgX) * -1;
    offset_y = round(avgY) * -1;
    offset_z = round(avgZ) * -1;

    Serial.println("Save these values for use in your program:");
    Serial.print("X: ");
    Serial.print(offset_x);
    Serial.print(" Y: ");
    Serial.print(offset_y);
    Serial.print(" Z: ");
    Serial.println(offset_z);


    Serial.println();
    Serial.print("Setting Offsets with \"gyro.setOffsets(");
    Serial.print(offset_x);
    Serial.print(", ");
    Serial.print(offset_y);
    Serial.print(", ");
    Serial.print(offset_z);
    Serial.print(");\"");
    Serial.println();
    Serial.println();

    gyro.setOffsets(offset_x, offset_y, offset_z);

    if (gatherAverage(&avgX, &avgY, &avgZ) != 0)
        return;

    Serial.println();
    Serial.println("If your new averages are close to 0 you've");
    Serial.println("gathered good offset values.");
    double x, y, z;
gyro.readDegPerSecond(&x, &y, &z) == 1;
}

const int Kp = 0.5;
const int Kd = 0.05;
volatile int error;
volatile int lasterror;




void loop() {
  
  
  
  if (fail)
        return;

    // 3 doubles to store the data
    double x, y, z;

    // Read degrees per second
    // Note: You can also read the raw data by calling
//    readRaw() 
    if (gyro.readDegPerSecond(&x, &y, &z) != 0)
    {
        Serial.println("Failed to read gyroscope");
        return;
    }
    
    // print them out
    Serial.print("X: ");
    Serial.print(x);
    Serial.print(" Y: ");
    Serial.print(y);
    Serial.print(" Z: ");
    Serial.println(z);
/*
if (x > 25){
  myservo.writeMicroseconds(1400);
  delay(500);
}
    
    

else if(x < -25){
  myservo.writeMicroseconds(1600);
  delay(500);
}

else if (x > -25 && x < 25){
  myservo.writeMicroseconds(1500);
  
}*/

 for (pos = 0; pos <= x; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(1);                       // waits 15ms for the servo to reach the position
  }
  for (pos = -x; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

  
  
  
  
