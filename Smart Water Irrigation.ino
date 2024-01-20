
#include "DHT.h"
#define DHTTYPE DHT11   // DHT 11
#define DHTPIN 2     // what pin we're connected to（DHT10 and DHT20 don't need define it）
DHT dht(DHTPIN, DHTTYPE);   //   DHT11 DHT21 DHT22

#if defined(ARDUINO_ARCH_AVR)
    #define debug  Serial

#elif defined(ARDUINO_ARCH_SAMD) ||  defined(ARDUINO_ARCH_SAM)
    #define debug  SerialUSB
#else
    #define debug  Serial
#endif

int soil=A0;
int relay=8;

void setup() {

//temp
    debug.begin(9600);
    debug.println("DHTxx test!");
    Wire.begin();

   

    dht.begin();
    //soil

pinMode(soil,INPUT);
pinMode(relay,OUTPUT);
Serial.begin(9600);


//rain
Serial.begin(9600);//enable serial monitor
  pinMode(4, OUTPUT);//define LED pin
  pinMode(3, OUTPUT);//define LED pin

}

void loop() 
{
    float temp_hum_val[2] = {0};
    


    if (!dht.readTempAndHumidity(temp_hum_val)) {
        debug.print("Humidity: ");
        debug.print(temp_hum_val[0]);
        debug.print(" %\t");
        debug.print("Temperature: ");
        debug.print(temp_hum_val[1]);
        debug.println(" *C");
    } else {
        debug.println("Failed to get temprature and humidity value.");
    }

int soilData=analogRead(soil);
Serial.print("Soil DATA:");
Serial.println(soilData);


int value = analogRead(A1);//read value
  Serial.print("Value : ");
  Serial.println(value);
  if (value < 300 and soilData>900) {//check condition
    Serial.print("Heavy rain ");
    digitalWrite(3, HIGH);
    Serial.print("Dry Soil ");
    }

  else if(value > 300 and soilData<900){
    Serial.print("No Rain ");
    Serial.print("Wet Soil ");
    digitalWrite(3, HIGH);
  }
  else if(value < 300 and soilData<900){
    Serial.print("Heavy rain ");
    Serial.print("Wet Soil ");
    digitalWrite(3, HIGH);
  } 
  else {
    digitalWrite(3, LOW);
    Serial.print("No Rain ");
    Serial.print("Dry Soil ");
  }
  delay(1000);

}
