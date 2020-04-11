

/* CONEXIONES

Esquemas
Arduino: https://store.arduino.cc/arduino-nano
L293DNE (convención. 16 el superior a la izquierda, 1 el inferior a la izquierda)  http://electronica-fix.blogspot.com/2015/03/brazo-robot.html


Arduino Vin a 12v
Arduino GND a GND
L293DNE 15 a 12v
L293DNE 2 y 7 respectivamente van a D10 y D11 de Arduino.
L293DNE 1 y 16 a 5v Arduino
L293DNE 4 y 5 a GND
L293DNE 3 y 6 a motor (ojo solo gira en un sentido)

Sensores de temperatura a Arduino D2 (los dos)
*/


#include <OneWire.h> 
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2 

OneWire oneWire(ONE_WIRE_BUS); 

DallasTemperature sensors(&oneWire);

float t_out;
float t_in;
float d;

const int pin2 = 10;
const int pin3 = 11;

int k_out = 1;
int delta_out = 3;
int x_out;

void setup(void) 
{ 
 Serial.begin(9600);
 sensors.begin(); 
 
 pinMode(pin2,OUTPUT);
 pinMode(pin3,OUTPUT);

} 
void loop(void) 
{ 

 sensors.requestTemperatures(); 
 


t_out = sensors.getTempCByIndex(0);
t_in = sensors.getTempCByIndex(1);

d = t_out-t_in;
 Serial.println(d); 
if(d < 3){

d=0;
delta_out=0;
  
}


x_out = k_out*d + delta_out;

//d desde 2 hasta 50
//x_out desde 5 hasta 53

if(d>4){
//fan_speed(x_out);
fan_yes_no();
}
   //delay(300); 
} 


void fan_speed(int x)
{
  analogWrite(pin3,255);
  analogWrite(pin2,0);
     
  delay(x);
  analogWrite(pin3,0);
  analogWrite(pin2,255);
  
  delay(20-x);
  
    
  
}


void fan_yes_no()
{
  analogWrite(pin3,255);
  analogWrite(pin2,0);
     
  delay(1000);
  analogWrite(pin3,0);
  analogWrite(pin2,255);
  
  //delay(0);
  
    
  
}
