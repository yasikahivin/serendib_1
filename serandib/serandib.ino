
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Servo.h>
/*
 * Serendib 1.0
-------------
Units
-------------
Temprature C
Pressure hPa
Approx. Altitude m
Humidity %
Time millis

-------------
Data Array
-------------
[{time},{temp},{pressure},{altitude},{humi}]

-------------
Sea level Pressure
-------------
colombo (7m)
*/

#define SEALEVELPRESSURE_HPA (1011.25)

Adafruit_BME280 bme;
int motor=9;
int angle=0;
Servo rocketMotor;

void setup() {
  Serial.begin(9600);
  pinMode (motor,OUTPUT);
  rocketMotor.attach(10);

  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}

void loop() {
  
  int altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);

  unsigned long runMillis= millis();
  unsigned long allSeconds=millis()/1000;
  int runHours= allSeconds/3600;
  int secsRemaining=allSeconds%3600;
  int runMinutes=secsRemaining/60;
  int runSeconds=secsRemaining%60;
  
  char myTime[21];
  sprintf(myTime,"%02d:%02d:%02d",runHours,runMinutes,runSeconds);
  

  Serial.print("[");
  Serial.print(myTime); //prints time since program started
  
  Serial.print(", ");
  Serial.print(bme.readTemperature());

  Serial.print(", ");
  Serial.print(bme.readPressure() / 100.0F);

  Serial.print(", ");
  Serial.print(altitude);

  Serial.print(", ");
  Serial.print(bme.readHumidity());
  Serial.print("],");

  Serial.println("");
 
  //rocket release
if(altitude>5000 && altitude<=5050){
for (angle=0;angle<=180;angle++)
{
rocketMotor.write(angle);
delay(10);
    
     
    }
     delay (5000);
    
 }
//  
  
  //air pump
  if(altitude>25000 && altitude<=25300 ){
        int buf=millis();
        int buf2;
        int buf3;
    
          if(runSeconds>5  ){
        digitalWrite(motor, 0); 
        }
        
        if(runSeconds<=35){
          digitalWrite(motor, 255);
        }
    }

  

       
  
  delay(1000);
}
