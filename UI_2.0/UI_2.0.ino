#include <mcp_can.h>
#include "serLCD.h"

const int buttonLeft = 9;
const int buttonRight = 3;
const int buttonUp = 4;
const int lcdPin = 6;
const int buttonDown = 5;

serLCD lcd(lcdPin);
uint8_t state = 0;
bool toClear = true;
uint8_t alcoholValue = 0;
uint8_t temperatureValue = 15;
double fluidBottleOne = 0;
double fluidBottleTwo = 0;
uint8_t totalFluid = 100;
uint8_t MixerStatus = 0;
String PreviousText = "";

long unsigned int rxID;
unsigned char len = 0;
unsigned char rxBuffer[8];
char msgString[128];

#define CAN0_INT 2
MCP_CAN CAN0(10);


void setup()
{
  Serial.begin(9600);
  pinMode(buttonLeft, INPUT_PULLUP);
  pinMode(buttonRight, INPUT_PULLUP);
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);

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

  lcd.setType(3);
}

void loop()
{
  if (!digitalRead(buttonDown))
  {
    state = 0;
  }
  switch (state)
  {
    //waiting
    case 0:
      WriteDisplay("Waiting for user    input, please press upper button", 1);
      if (!digitalRead(buttonRight))
      {
        temperatureValue++;
        SendCAN(2);
      }
      if (!digitalRead(buttonRight))
      {
        temperatureValue--;
        SendCAN(2);
      }
      if (!digitalRead(buttonUp))
      {
        state = 1;
        toClear = true;
      }
      break;

    //let user choose drink
    case 1:
      if (toClear == true)
      {
        lcd.clear();
        toClear = false;
      }
      lcd.selectLine(1);
      lcd.print("Please choose drink \r");
      lcd.print("Large: Btn left    \r");
      lcd.print("Small: Btn right");

      //choose drinks
      if (!digitalRead(buttonLeft))
      {
        totalFluid = 100;
        state = 2;
        toClear = true;
      }
      if (!digitalRead(buttonRight))
      {
        totalFluid = 50;
        state = 2;
      }
      break;

    //get alcohol measurements
    case 2:
      WriteDisplay("Please blow on the  sensor", 1);
      alcoholValue = 0;
      while (alcoholValue == 0)
      {
        ReadCAN();
      }
      CalculateRatioBottles();
      SendCAN(1);
      state = 3;
      alcoholValue = 0;
      break;

    case 3:
      ReadCAN();
      switch (MixerStatus)
      {
        
        case 0: //Filling cup
        WriteDisplay("Preparing to make   your drink", 1);
          break;

        case 1: //Emptying cup
          WriteDisplay("filling cup", 1);
          break;
          
        case 2: //Done
          state = 4;
          toClear = true;
          break;
          
        case 3: //No Cup
          WriteDisplay("Please place your   cup", 1);
          break;
      }
      break;
      

    case 4:
    MixerStatus = 0;
      WriteDisplay("Grap your cup and   enjoy your drink! :)", 1);
      delay(5000);
      state = 0;
      break;
  }
}


void CalculateRatioBottles()
{
  if (alcoholValue < 6)
  {
    fluidBottleOne = 0.90 * totalFluid;
    fluidBottleTwo = 0.10 * totalFluid;
  }
  else if (alcoholValue > 10)
  {
    fluidBottleOne = 0.10 * totalFluid;
    fluidBottleTwo = 0.90 * totalFluid;
  }
  else
  {
    fluidBottleOne = 0.50 * totalFluid;
    fluidBottleTwo = 0.50 * totalFluid;
  }
}

void ReadCAN()
{
  if (!digitalRead(CAN0_INT))
  {
    CAN0.readMsgBuf(&rxID, &len, rxBuffer);
    if (rxID == 0x60)
    {
      if (rxBuffer[1] == 2)
      {
        alcoholValue = rxBuffer[0];
      }
    }
    if (rxID == 0x20)
    {
        MixerStatus = rxBuffer[0];
    }
  }
}

void SendCAN(int device)
{
  byte sndStat = 0;
  if (device == 1)
  {
    byte data[4] = {0x00, 0x01, fluidBottleOne, fluidBottleTwo};
    sndStat = CAN0.sendMsgBuf(0x10, 0, 4, data);
  }
  if (device == 2)
  {
    byte data[1] = {temperatureValue};
    sndStat = CAN0.sendMsgBuf(0x11, 0, 1, data);
  }
}

void WriteDisplay(String text, int lineNumber)
{
  if(PreviousText != text)
  {
    lcd.clear();
    lcd.selectLine(lineNumber);
    lcd.print(text);
    PreviousText = text;
  }
}

