//include all necessary libraries
#include <SoftwareSerial.h>
#include <dht.h>
#define dht_apin A2  //defining the input pin for DHT11

dht DHT;    //creating a variable for using the library functions of DHT11
const int AOUTpin=1;  //variable for MQ-7 sensor
const int DOUTpin=8;  //variable for MQ-7 sensor
int value;    //variable for storing sensor reading

SoftwareSerial blue(0,1); //initializing the Bluetooth pins of rx and tx to 0 and 1 resp.
char inchar;    //variable for accepting string value
void setup() {
//declaring the necessary input and output pins
   pinMode(AOUTpin, INPUT);
   pinMode(DOUTpin, INPUT);
   pinMode(A0,INPUT);
   pinMode(6, OUTPUT);
   pinMode(10, INPUT);
   Serial.begin(9600);
   blue.begin(9600);
}
void loop() {
value= analogRead(AOUTpin); //input the value for gas sensor
float sensorValue = ((analogRead(A0)/1024.0)+0.095)/0.000009; //input value with mathematical calculation for pressure sensor
DHT.read11(dht_apin); //reading the dht11 pin by using dht library
int water = digitalRead(10);  //input value for water sensor
if(blue.available()==0);  //check if Bluetooth module is available or not

  if(blue.available()>0)  //loop for performing actions with the Bluetooth module and connection with smartphone
  {
    inchar=blue.read(); //read the value on the smartphone on the Bluetooth app
    delay(20);    //delay for smooth functioning
    if (inchar=='v')    //if the input on the Bluetooth app is ‘v’, then some function should occur
    {
      delay(10);    //delay for smooth functioning
      Serial.println("Pressure:");  //print the static value
      Serial.println(sensorValue, 2); //print the pressure sensor reading
      Serial.println("Humidity:");  //print the static value
      Serial.println(DHT.humidity);   //print the humidity sensor reading     
      Serial.println("Temperature:");   //print the static value
      Serial.println(DHT.temperature);  //print the temperature sensor reading
      Serial.println("CO Value:");    //print the static value
      Serial.println(value);      //print the gas sensor reading
      if(water==LOW)       //loop for checking if water is present on the water sensor or not
      {
        Serial.println("Water Sensor: LOW");  //if water is not present, print LOW
      }
      else
      {
        Serial.println("Water Sensor: HIGH"); //if water is present, print HIGH
      }
      delay(1000);        //delay for smooth functioning
    }
  }
      
  if(DHT.temperature>40 || value>375) //loop for checking if the value of temperature>40 or gas reading>375
  {
    digitalWrite(6, HIGH);      //buzzer should buzz
    digitalWrite(5, HIGH);      //red led should glow
  }
  else
  {
    digitalWrite(6, LOW);     //buzzer should not buzz
    digitalWrite(4, HIGH);      //green led should glow
  }
}
