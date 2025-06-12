#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <LoRa.h>
#include "EmonLib.h"

// I²C LCD: address 0x27, 20 cols × 4 rows
LiquidCrystal_I2C lcd(0x27, 20, 4);

// EnergyMonitor for voltage
EnergyMonitor emon1;

// Current sensor on A1
const int Sensor_Pin    = A1;
int sensitivity   = 185;   // 5 A module = 185 mV/A
int offsetVoltage = 2542;  // mV at zero current

// LoRa status LEDs
const int LED_RED    = 5;
const int LED_GREEN   = 6;

// keep track of accumulated energy
//float Energy = 0;
unsigned long lastMillis = 0;

void setup() {
  // ---- LCD init ----
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(" Smart Meter ");
  //delay(1000);
  //lcd.clear();

  // ---- Voltage sensor ----
  // A0, calibration 187, phase shift 1.7
  emon1.voltage(A0, 187.0, 1.7);
 
  // ---- LoRa init ----
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);

  Serial.begin(9600);
  while (!Serial);

    if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed!");
    digitalWrite(LED_GREEN, HIGH);
    while (1);
  }
  Serial.println("LoRa OK");
}

void loop() {
  //************************* Measure Voltage ******************************************
  emon1.calcVI(20,2000); // Calculate all. No.of half wavelengths (crossings), time-out
  int Voltage   = emon1.Vrms;  //extract Vrms into Variable
  
  lcd.setCursor(0,1);
  lcd.print("V =");
  lcd.print(Voltage);
  lcd.print("V ");
    //************************* Measure Current ******************************************
  unsigned int temp=0;
  float maxpoint = 0;
  for(int i=0;i<500;i++)
  {
    if(temp = analogRead(Sensor_Pin), temp>maxpoint)
    {
      maxpoint = temp;
    }
  }
  float ADCvalue = maxpoint; 
  double eVoltage = (ADCvalue / 1024.0) * 5000; // Gets you mV
  double Current = ((eVoltage - offsetVoltage) / sensitivity);
  double AC_Current = ( Current ) / ( sqrt(2) );

  lcd.print("I =");
  lcd.print(AC_Current,2);
  lcd.print("A "); //unit for the current to be measured

  //************************* Measure Power ******************************************
  int Power = (Voltage * AC_Current);
  
  lcd.setCursor(0,2);
  lcd.print("P =");
  lcd.print(Power);
  lcd.print("W "); //unit for the current to be measured
  
  //************************* Measure Energy ******************************************
  long milisec = millis(); // calculate time in milliseconds 
  long time=milisec/1000; // convert milliseconds to seconds 
  
  float Energy = (Power*time)/3600; //Watt-sec is again convert to Watt-Hr by dividing 1hr(3600sec) 
  lcd.setCursor(0,3);
  lcd.print("E = ");
  lcd.print(Energy);
  lcd.print("Wh   "); //unit for the current to be measured

  // ---- 5) Transmit over LoRa ----
  String payload = String(Voltage) + "," +
                   String(AC_Current,2) + "," +
                   String(Power,0) + "," +
                   String(Energy,2);

  digitalWrite(LED_RED, LOW);
  LoRa.beginPacket();
    LoRa.print(payload);
  LoRa.endPacket();
  digitalWrite(LED_RED, HIGH);

  Serial.print("Sent: ");
  Serial.println(payload);

  delay(2000);
}
