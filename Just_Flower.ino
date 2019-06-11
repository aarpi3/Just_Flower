// Just Flower
// By Tomas Heydal & Harald Martin Aarbogh
// 2019

//Libraries
#include <dht.h>

// mousture sensor
int threshold = 500;      // an arbitrary threshold level that's in the range of the analog input (for reference, 660 is wet, newly watered).
int soilMoisture = A1;    // pin that the soilMoisture analog sensor is attached to
int x = 10000;            // Duration of which pump will be runned, devided by 1000, giving sec [10sec]

// water pump
int pump = 1;             // BLUE pin that the reley (and pump is attached to)
int count = 0;            // Our water counter

//int ledcount10 = 6;     // NOT USED YET initialize the led indicator as an digital output pin5
//int maxNum = 2000;      // NOT USED YET Assigned max number of counts of watering
//int tempHumidity = 5;   // NOT USED YET pin that the tempHumidity digital sensor is attached to.


//Temperature sensor DHT21
dht DHT;
#define DHT21_PIN 6     // DHT 22  (AM2302) - what pin we're connected to
float hum;  //Stores humidity value
float temp; //Stores temperature value

// Water level 
int levelFull = 2;      // NOT USED YET assigning the levelFull indicator as an digital input pin2
int levelMid = 3;         // GREEN, initialize the levelMid indicator as an digital input pin3
int levelEmpty = 4;       // YELLOW, initialize the levelEmpty indicator as an digital input pin4
int waterLevelValue = 100; // Assign value 100 as water tank level

void setup() {
  pinMode(pump, OUTPUT);          // initialize the pump pin as an output:
  pinMode(LED_BUILTIN, OUTPUT);   // initialize the built in LED pin as an output

  pinMode (levelFull, INPUT);     // initialize the levelFull indicator as an digital input
  pinMode (levelMid, INPUT);      // initialize the levelMid indicator as an digital input
  pinMode (levelEmpty, INPUT);    // initialize the levelEmpty indicator as an digital input
  pinMode (soilMoisture, INPUT);  // initialize the soilMoisture indicator as an analog input

  digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW
  Serial.begin(9600);  // initialize serial communications:
}

void loop() {
  delay(1000);        // delay in between reads for stability
  int soilMoistureValue = analogRead(soilMoisture); // read the value of the analog soilMoisture sensor and store it in soilMoistureValue
  delay(15);        // delay in between reads for stability
  int waterLevelFullValue = digitalRead(levelFull); // checks if the waterlevel is full and assigns the value to waterLevelFullValue
  delay(15);        // delay in between reads for stability
  int waterLevelMidValue = digitalRead(levelMid); // checks if the waterlevel is Mid and assigns the value to waterLevelMidValue
  delay(15);        // delay in between reads for stability
  int waterLevelEmptyValue = digitalRead(levelEmpty); // checks if the waterlevel is Mid and assigns the value to waterLevelEmptyValue
  delay(15);        // delay in between reads for stability
  Serial.println("Soil Moisture Level (0-1000) "); Serial.println(soilMoistureValue); //Print soilMoisture value to internal Serial Monitor
  delay(15);        // delay in between reads for stability
  Serial.println("Water Tank Level "); Serial.println(waterLevelValue); //Print water levelFull
  delay(1000);        // delay in between reads for stability

  if (digitalRead(levelMid) == HIGH) {
    waterLevelValue = 50;
  }
  if (digitalRead(levelEmpty) == HIGH) {
    waterLevelValue = 0;
  }
  if (soilMoistureValue < threshold && waterLevelValue == 100) { // if the soilMoisture analog value is low enough (value assigned on top of program), and the water level is Full start Pump:
    delay(15);        // delay in between reads for stability
    digitalWrite(pump, HIGH); //Turns on the waterpump
    delay(x);                 //x is duration in seconds of watering (devided by 1000)
    digitalWrite(pump, LOW);  //Turns off the waterpump
    delay(15);              // delay in between reads for stability
    count++;                  // add one (1) to our count
    delay(15);              // delay in between reads for stability
    Serial.println("Watering done, when waterlevel full"); //Print text
    Serial.println("Water count since start of Software ");Serial.println(count); //Print text and water count
    delay(15);              // delay in between reads for stability
  }
  else if (soilMoistureValue < threshold && waterLevelValue == 50) { // if the soilMoisture analog value is low enough (value assigned on top of program), and the water level is Mid start Pump:
    delay(15);        // delay in between reads for stability
    digitalWrite(pump, HIGH); //Turns on the waterpump
    delay(x);                 //x is duration  in seconds of watering (devided by 1000)
    digitalWrite(pump, LOW);  //Turns off the waterpump
    delay(15);              // delay in between reads for stability
    count++;                  // add one (1) to our count
    delay(15);              // delay in between reads for stability
    Serial.println("Watering done, when waterlevel mid"); //Print text
    Serial.println("Water count since start of Software ");Serial.println(count); //Print text and water count
    delay(15);              // delay in between reads for stability
  }
  else if (soilMoistureValue < threshold && waterLevelValue == 0) { // if the soilMoisture analog value is low enough (value assigned on top of program), and the water level is Mid start Pump:
    delay(15);              // delay in between reads for stability
    digitalWrite(pump, LOW);  //Turns off the waterpump
    delay(15);              // delay in between reads for stability
    Serial.println("Warning! Watering not executed, because waterlevel Empty"); //Print text
    Serial.println("Water count unchanged ");Serial.println(count); //Print text and water count
    delay(15);              // delay in between reads for stability
    
  }
}

void readTemp(){
    int chk = DHT.read21(DHT21_PIN);
    //Read data and store it to variables hum and temp
    hum = DHT.humidity;
    temp= DHT.temperature;
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    delay(2000); //Delay 2 sec.
}
