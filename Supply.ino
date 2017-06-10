#include "Valve.h"
#include "Pump.h"
#include "iCommunicatie.hpp"


const int pumpPin = 0; //te veranderen naar digitale pin 
const int pressureSensorPin = 0 // te veranderen naar analoge pin

int amountOfDrinks = 2;
int mixWeight = 0;

Valve valves[amountOfDrinks];
int neededLiquidsPerBottle[amountOfDrinks] = {0, 0}; //array for all bottles?
int airPressure = 0 // nog te veranderen, moet in Pa 

Pump* pump;
CANMSG msg;
iCommunicatie communication;


void setup()
{
  Serial.begin(9600);
  while(!Serial);
  pump = new Pump(airPressure, PumpPin);
  if(!communication.Init())
  {
    Serial.println("Setting up CAN failed");
  }
  communication.SetCallback(GetMessage);
  for (int i = 0; i < amountOfDrinks; i++)
  {
    valves[i] = new Valve(i) 
  }
  Serial.println("Setup completed");
}

void loop()
{
  communication.Read(); //for needed amount of liquids
  int neededAmount = 0;
  for (int i = 0; i < amountOfDrinks; i++)
  {
    pump->KeepPressure(true);
    communication.Read(); //for needed amount of liquids
    neededAmount += neededLiquidsPerBottle[i];
    valve[i].Open();
    while(mixWeight < neededAmount)
    {
      pump->KeepPressure(true);
      communication.Read(); //for mixing weight
    }
    valve[i].Close();
  }
  for(int i = 0; i < amountOfDrinks; i++) 
  {
      neededLiquidsPerBottle[i] = 0;
  }
  mixWeight = 0;
  SendDoneMessage();
} 

void GetMessage(CANMSG msg)
{
  for (uint8_t i = 0; i < msg.dataLength; i++)
  {
    /*Serial.print("Msg: ");
    Serial.print(i);
    Serial.print(" Data: ");
    Serial.println(msg.data[i]);*/
    if(msg.adrsValue == 0x10)
    {
        neededLiquidsPerBottle[msg.data[1]] = msg.data[2];
    //neededLiquidsPerBottle[1] = //amount of liquids needed for second drink;
    }
    else if(msg.adrsValue = 0x20)
    {
      mixWeight = //mix weight;
    }
   }
}

void SendDoneMessage()
{
  msg.adrsValue = 0x30;
  msg.isExtendedAdrs = false;
  msg.rtr = false;
  msg.dataLength = 8;
  msg.data[0] = 0x01;
  msg.data[1] = 0;
  msg.data[2] = 0;
  msg.data[3] = 0;
  msg.data[4] = 0;
  msg.data[5] = 0;
  msg.data[6] = 0;
  msg.data[7] = 0;

  if (_com.Write(msg)) 
  {
    Serial.println("Message Done is written");
  }
  else 
  {
    Serial.println("Writing went wrong");
  }
}
