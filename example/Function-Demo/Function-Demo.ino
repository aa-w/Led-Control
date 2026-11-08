#include <Led_Control.h>

Led_Control LED_BuiltIn;

void setup()
{
  LED_BuiltIn.Setup(LED_BUILTIN);
  LED_BuiltIn.Blink(5, 150, true); //Blink 5 times, 150ms duty, Block until complete

  LED_BuiltIn.TurnOn(); //Turn LED On - trigger this before calling blink to invert its logic
  delay(500);
  LED_BuiltIn.TurnOff(); //Turn LED Off
  delay(500);

  LED_BuiltIn.Toggle(); //Flip LED state
  delay(500);
  LED_BuiltIn.Toggle();
  delay(500);

  LED_BuiltIn.DelayedToggle(5000);
  LED_BuiltIn.BlockingUpdate(6000);

  LED_BuiltIn.Blink(-1, 500, false); //Blink forever, 200ms duty, Non-Blocking (Updated by .Update)

}

void loop()
{
  LED_BuiltIn.Update(); //Required 
}
