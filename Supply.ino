#include "Valve.h"


int amountOfDrinks = 2;
//array of valves
Valve valves[amountOfDrinks];

int neededLiquidsPerBottle[amountOfDrinks] = {0, 0}; //array for all bottles? 
int mixWeight = 0;
pump* pump;

void setup() 
{
  pump = new Pump(/*airpressure*/, );
  
  for (int i = 0; i < 4; i++)
  {
    valves[i] = new Valve(/*pin*/)
  }
}

void loop() 
{
  pump->KeepPressure(bool enabled);
  if (/*received message of amount of liquids needed per bottle + mix weight)*/ == true)
  {
    neededLiquidsPerBottle[0] = //amount of liquids needed for first drink;
    neededLiquidsPerBottle[1] = //amount of liquids needed for second drink;
    mixWeight = //mix weight;
    int neededAmount = 0;
    for(int i = 0; i < drinks; i++)
    {
      neededAmount += neededLiquidsPerBottle[i];
      AddLiquid(i, neededAmount, mixWeight);
    }
    //send done
    for(int i = 0; i < neededLiquidsPerBottle; i++)
    {
      neededLiquidsPerBottle[i] = 0;
    }
  }
}

AddLiquid(int valve, int neededWeight, int mixingWeight)
{
  valve[valve].Open();
  while (neededWeight >= mixingWeight)
  {
    //check communication for mixing weight
  }
  valve[valve].Close();
}