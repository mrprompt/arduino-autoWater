/**
 * Irrigação automática com sensor de umidade de solo + motor
 *
 * @author Thiago Paes <mrprompt@gmail.com>
 **/
#include <Servo.h>

Servo waterServo;  //creates the name of your servo

int sensPin = A0;  //assignes a pin for the soil sensor
int servoPin = 5; //sets the servo pin, this must be a PWM pin
int powerPin = 2; //assignes a pin to power the sensor. optional
int wetVal = 500; //the sensor value where the soil is sufficiently wet
int dryVal = 300; //the value where the soil is dry and needs watering
int dirtVal;    //variable to store one sensor reading
int waterPosition = 170;
int waterHold = 10;
double avgDirt; //variable to store average of 10 sensor readings

void setup()
{
  Serial.begin(9600);   //serial monitor for debugging purposes
  waterServo.attach(servoPin);  //sets the servo pin as output
  pinMode(sensPin, INPUT);  //sets the sensor pin as input
  pinMode(powerPin, OUTPUT);
  delay(10);
  digitalWrite(powerPin, HIGH); //provides power to the sensor

  Serial.println("Started");
}

void loop()
{
  // for loop to calculate average of ten soil readings
  for (int i = 0; i < 10; i++) { 
    dirtVal = analogRead(sensPin);
    delay(30 * 1000);
    avgDirt += dirtVal;
  }

  //gets average value of 10 sensor readings
  avgDirt = avgDirt / 10.0;     

  //for debugging
  Serial.print("Sensor value: "); 
  Serial.print(avgDirt);

  //if the average soil value is dry
  if (avgDirt <= dryVal) {
    //start watering the plants
    waterServo.write(waterPosition);  

    //while loop to keep watering until the soil is wet
    while (dirtVal <= wetVal) {
      dirtVal = analogRead(sensPin);
      
      Serial.println(avgDirt);
      delay(20);
    }

    //stops watering the plants
    waterServo.write(waterHold);  

    //resets average soil value
    avgDirt = dirtVal;
  }
  
  Serial.println(avgDirt);
  delay(5 * 60 * 1000);
}
