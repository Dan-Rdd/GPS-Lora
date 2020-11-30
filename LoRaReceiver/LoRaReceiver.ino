#include <SPI.h>
#include <LoRa.h>
#include "TFT_eSPI.h"

TFT_eSPI tft = TFT_eSPI();
#define ss 5
#define rst 34
#define dio0 35
float prevLatitude, prevLongitude;
bool isReadyToShow;
void setup() {
  Serial.begin(115200);

  tft.begin();
  tft.setRotation(3);

  isReadyToShow = false;
  //initScreen();
 
  Serial.println("LoRa Receiver Callback");
 
  LoRa.setPins(ss, rst, dio0);
 
  if (!LoRa.begin(473E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
 
  // register the receive callback
  LoRa.onReceive(onReceive);
 
  // put the radio into receive mode
  LoRa.receive();
}
 
void loop() {

}
 
void onReceive(int packetSize) {
   
    String LoRaData; 
    //int packetSize = LoRa.parsePacket();
    if (packetSize) 
    {
      // received a packet
      Serial.print("Received packet '");
      // read packet
      while (LoRa.available())
      {
        LoRaData = LoRa.readString();
        //Serial.print(LoRaData);
        Serial.println();
        String latitude = (LoRaData.substring(0,12));
        String longtitude = (LoRaData.substring(13,25));
        Serial.println(latitude);
        Serial.println(longtitude);
       
      }
      // print RSSI of packet
      Serial.print("' with RSSI ");
      Serial.println(LoRa.packetRssi());
      
    // }
     //if (LoRaData != NULL){
      //float latitude1 = latitude.toFloat();
      //if(latitude1 != prevLatitude){
       // Serial.print(String(latitude1));
        //tft.drawString(String(latitude1, 6), 360, 120, 4);
      }
      //prevLatitude = latitude1;

      //float longitude1 = longtitude.toFloat();
      //if(longitude1 != prevLongitude){
      //  Serial.print(String(longitude1));
        //tft.drawString(String(longitude1, 6), 360, 120, 4);
      //}
     // prevLongitude = longitude1;
    } 


void initScreen(){
  tft.fillScreen(TFT_WHITE);
  tft.setTextSize(1);
  tft.setTextColor(TFT_RED, TFT_WHITE);
  tft.setTextDatum(TC_DATUM);
  tft.drawString("Waiting for GPS...", 240, 140, 4);
}

//void errorScreen(){
  //tft.fillScreen(TFT_RED);
  //tft.setTextSize(1);
  //tft.setTextColor(TFT_WHITE, TFT_RED);
  //tft.setTextDatum(TC_DATUM);
  //tft.drawString("No GPS detected: Check Wiring!", 240, 140, 4);
//}
