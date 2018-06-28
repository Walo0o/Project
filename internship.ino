#include <TimerOne.h>

#define interruptPin  2
#define led_Pin 13
#define Temperature_Sensor_Pin A0

// set led on or off 
volatile boolean onOrOff = LOW; 
       
//variable to maintain analog value of temperature sensor 
unsigned int temperature_sensorValue = 0; 

void setup() {
  
 //initiate intrupt for switch
 pinMode(interruptPin, INPUT_PULLUP);
 attachInterrupt(digitalPinToInterrupt(interruptPin), lighting , RISING);
 
 //initiate led as OUTPUT
 pinMode(led_Pin , OUTPUT);
 
 //initiate timer intrupt 
 Timer1.initialize(3000000); // 3 million microseconds is 3 seconds
  Timer1.attachInterrupt(function);
  
  //initiate serial boudrate for serial monitor
  Serial.begin(9600);

}

void loop() {
//loop to keep process working  

}

// set led on or off inside the ISR
void lighting(){
  //turn led on or off 
  digitalWrite(led_Pin , onOrOff);
  
  //send to serial monitor
  if(onOrOff == LOW)
  {
    Serial.println("Pressed OFF" );
  }
  else
  {
    Serial.println("Pressed ON" );
  }
  //toggle state to following pressed button
 onOrOff =! onOrOff;

}


//interrupt service routine function
void function(){
  
  //maintain analog value of temperature sensor 
  temperature_sensorValue = analogRead(Temperature_Sensor_Pin);

  //scale analog value to temperature value For example LM35 
  temperature_sensorValue = temperature_sensorValue *0.48828;

  //print temperatue value 
  Serial.print("temperature value is:" );
  Serial.println(temperature_sensorValue);
}



