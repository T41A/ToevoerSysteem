#include <mcp_can.h>
#include "Valve.h"
#include "Pump.h"

long unsigned int rxID;
unsigned char len = 0;
unsigned char rxBuffer[8];
char msgString[128];

#define CAN0_INT 2
MCP_CAN CAN0(10);

const uint8_t amountOfDrinks = 2;
uint16_t mixWeight;
uint16_t airPressure = 2720;
uint8_t neededLiquidsPerBottle[amountOfDrinks] = {0, 0};

const uint8_t pumpPin = 7;
const uint8_t pressureSensorPin = A0;
Valve* valves[amountOfDrinks];
Pump* pump;


void setup()
{
  Serial.begin(9600);
  if (CAN0.begin(MCP_ANY, CAN_100KBPS, MCP_16MHZ) == CAN_OK)
  {
    Serial.println("MCP2515 Initialized Successfully!");
  }
  else
  {
    Serial.println("Error Initializing MCP2515...");
  }
  CAN0.setMode(MCP_NORMAL);
  pinMode(CAN0_INT, INPUT);
  pinMode(pumpPin, OUTPUT);
  pump = new Pump(airPressure, pumpPin, pressureSensorPin);
  valves[0] = new Valve(4);
  valves[1] = new Valve(5);
  valves[0]->Close();
  valves[1]->Close();
}

void loop()
{
  ReadCAN();
  if (neededLiquidsPerBottle[0] > 0 || neededLiquidsPerBottle[1] > 0)
  {
    uint8_t neededAmount = 0;
    for (uint8_t i = 0; i < amountOfDrinks; i++)
    {
      pump->SetOn();
      neededAmount += neededLiquidsPerBottle[i];
      valves[i]->Open();
      while (mixWeight < neededAmount)
      {
        ReadCAN(); //for mixing weight
      }
      valves[i]->Close();
      pump->SetOff();
    }
    for (uint8_t i = 0; i < amountOfDrinks; i++)
    {
      neededLiquidsPerBottle[i] = 0;
    }
    mixWeight = 0;
    neededAmount = 0;
    SendDone();
  }
}


void ReadCAN()
{
  if (!digitalRead(CAN0_INT))
  {
    CAN0.readMsgBuf(&rxID, &len, rxBuffer);
    if (rxID == 0x10)
    {
      neededLiquidsPerBottle[rxBuffer[0]] = rxBuffer[2];
      neededLiquidsPerBottle[rxBuffer[1]] = rxBuffer[3];
    }
    if (rxID == 0x20)
    {
      mixWeight = rxBuffer[1] | rxBuffer[2] << 8;
    }
  }
}


void SendDone()
{
  byte data[1] = {0x01};
  byte sndStat = CAN0.sendMsgBuf(0x30, 0, 1, data);
}

