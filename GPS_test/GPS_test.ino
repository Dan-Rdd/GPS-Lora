
#include <TinyGPS++.h>
#include <LoRa.h>
#include <Wire.h>

#define ss 15
#define rst 16
#define dio0 2
int counter = 0;

TinyGPSPlus gps;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  while (!Serial);
  Serial.println("LoRa Sender");
  LoRa.setPins(ss, rst, dio0);
    if (!LoRa.begin(473E6)) {
    Serial.println("Starting LoRa failed!");
    delay(100);
    while (1);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0)
  {
    if (gps.encode(Serial.read()))
    {
      //displayInfo();

      Serial.print(F("Pkt No:"));
      Serial.print(counter);
      // send packet
      LoRa.setSyncWord(0xE3);
      LoRa.beginPacket();
      LoRa.print(gps.location.lat(), 8);
      LoRa.print(F(":"));
      LoRa.print(gps.location.lng(), 8);
      LoRa.print(F("Pkt No:"));
      LoRa.println(counter);
      LoRa.endPacket(); 
      counter++;
      delay(3000);
    }
  }
}
void displayInfo()
{
  Serial.print(F("Location: "));
  if (gps.location.isValid())
  {
    Serial.print (gps.location.lat(), 8);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 8);
  }
  else
  {
    Serial.print(F("Invalid"));
  }
  Serial.println();
}
