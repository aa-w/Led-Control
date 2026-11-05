#include <Led.h>

Led LED_BuiltIn;

void setup()
{
  LED_BuiltIn.Setup(LED_BUILTIN);
  LED_BuiltIn.Blink(5, 150, true); //Blink 5 times, 150ms duty, Block until complete

  LED_BuiltIn.TurnOn();
  delay(500);
  LED_BuiltIn.TurnOff();
  delay(500);

  LED_BuiltIn.Toggle();
  delay(500);
  LED_BuiltIn.Toggle();
  delay(500);

  LED_BuiltIn.Blink(-1, 500, false); //Blink forever, 200ms duty, Non-Blocking (Updated by .Update)

}

void loop()
{
  LED_BuiltIn.Update(); //Required 
}
