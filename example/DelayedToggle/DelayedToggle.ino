#include <Led_Control.h>

Led_Control LED_BuiltIn;

void setup()
{
  LED_BuiltIn.Setup(LED_BUILTIN);
  LED_BuiltIn.Toggle();
  delay(100);
  LED_BuiltIn.Toggle();
  LED_BuiltIn.DelayedToggle(5000);
  LED_BuiltIn.BlockingUpdate();
  LED_BuiltIn.DelayedToggle(10000); //New calls to the delay function will override older calls unless they are completed
}

void loop()
{
  LED_BuiltIn.Update(); //Required to change state
}
