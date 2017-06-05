#include "Valve.h"
#include "Pump"
#include "iCommunicatie.hpp"


int amountOfDrinks = 2;
int mixWeight = 0;

Valve valves[amountOfDrinks];
int neededLiquidsPerBottle[amountOfDrinks] = {0, 0}; //array for all bottles? 

pump pump;
CANMSG msg;
iCommunicatie communication;


void setup() 
{
  Serial.begin(9600);
  while(!Serial);
  pump = new Pump(/*airpressure*/, );
  if(!communication.Init())
  {
    Serial.println("Setting up CAN failed);
  }
  communication.SetCallback(GetMessage);
  for (int i = 0; i < 4; i++)
  {
    valves[i] = new Valve(/*pin*/)
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
  for(int i = 0; i < neededLiquidsPerBottle; i++)
  {
      neededLiquidsPerBottle[i] = 0;
  }
  mixWeight = 0;
  //send done 
}

void GetMessage(CANMSG msg) 
{
  for (uint8_t i = 0; i < msg.dataLength; i++) 
  {
    /*Serial.print("Msg: ");
    Serial.print(i);
    Serial.print(" Data: ");
    Serial.println(msg.data[i]);*/
    if(msg.data[0] == 0x10)
    {
        neededLiquidsPerBottle[msg.data[1]] = msg.data[2];
    //neededLiquidsPerBottle[1] = //amount of liquids needed for second drink;
    }
    else if(msg.data[0] = 0x20)
    {
      mixWeight = //mix weight;
    }
   }
}
