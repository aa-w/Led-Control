#include <Pin_Control.h>

Pin_Control LED_BuiltIn;

void setup()
{
  LED_BuiltIn.Setup(LED_BUILTIN);
  LED_BuiltIn.Blink(5, 150, true); //Blink 5 times, 150ms duty, Block until complete
  
  LED_BuiltIn.Blink(-1, 1000, false); //Blink forever, 200ms duty, Non-Blocking (Updated by .Update)
}

void loop()
{
  LED_BuiltIn.Update(); //Required 
}
