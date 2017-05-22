#include "Valve.h"

//list of valves
Valve valves[?];
//list of drinks 
Drink drinks[2];

void setup() 
{
  for(int i = 0; i < 4; i++)
  {
    valves[i] = new Valve(/*pin*/)
  }
  for(int i = 0; i < 2; i++)
  {
    drinks[i] = new Drink();
  }
}

void loop() 
{
  if(/*received message of amount of liquids needed + mix weight)*/ == true)
  for(int i = 0; drinks.size(); i++)
  {
    valve[].Open();
    while(/*mixing weight != amount of liquid needed*/)
    {
      //check amount?  
    }
    valve[].Close();
  }
}
