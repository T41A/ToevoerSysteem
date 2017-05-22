Pump* pump;

void setup() 
{
  pump = new Pump();
}

void loop() 
{
  pump->KeepPressure();
}

