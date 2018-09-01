

#include "RAK811.h"
#include <String.h>
#define WORK_MODE LoRaP2P  //  LoRaWAN or LoRaP2P
#define CODE  PING  // PING or PONG
char buffer[100] = "111111111111111111111";
String FREQ = "434000000";  // frequency 433-470Mhz --> RAK812
String ret;
RAK811 RAKLoRa(Serial, Serial1);

void setup() {
  // set up serial 0
  Serial.begin(9600);
  while(Serial.read()>= 0) {}
  while(!Serial);
  Serial.println("StartUP");  

  Serial1.begin(115200); // Note: Please manually set the baud rate of the WisNode RAK812 device to 115200
  delay(100);
  Serial.println(RAKLoRa.rk_getVersion());
  delay(200);
  Serial.println(RAKLoRa.rk_getBand());
  delay(200);
}

void loop() {
  // Set up mode P2P for Wisnode 
    if (RAKLoRa.rk_setWorkingMode(WORK_MODE))
  {
    Serial.println("You set Working mode is OK!");
    //Set up configuration for Wisnode
    if (RAKLoRa.rk_initP2P(FREQ,7,0,1,8,14))
    {
      Serial.println("You init P2P parameter is OK!");
      while (1)
      {
        //Mode Sending
          #if  CODE == PING
         if (RAKLoRa.rk_sendP2PData(100,"1000",buffer)) //Send 1 packet, inteval time = 10 with data = buffer
         {
          Serial.println("test");
          String ver = RAKLoRa.rk_recvData();
//          Serial.println(ver);
          
          if (ver == STATUS_P2PTX_COMPLETE)
          {
            Serial.println("send success");
            if (RAKLoRa.rk_recvP2PData(1))
            {
              Serial.println("open recv");
              Serial.println(RAKLoRa.rk_recvData());
            }
          }
          else
          {
            Serial.println(ver);
            delay(200000);
          }
         }
         delay(200000);
   //-----------------------------------------------------
         //Mode Receiving
        #else if CODE == PONG
        if (RAKLoRa.rk_recvP2PData(1))
         {
          Serial.println("open recv");
          Serial.println(RAKLoRa.rk_recvData());
          if (RAKLoRa.rk_sendP2PData(1,"10",buffer))
          {
            String ver = RAKLoRa.rk_recvData();
            if (ver == STATUS_P2PTX_COMPLETE)
            {
              Serial.println("send success");
            }
            else
            {
              Serial.println(ver);
              delay(2000);
            }
          }
         }
        #endif
      }
    }
  }

}
