#include "Led_Control.h"

// Constructor
Led_Control::Led_Control() : pin(0),
             State(false),
             BlinkDuty(500),
             BlinkCount(0),
             Animation(false),
             LastAnimation(0),
             LastUpdate(0)
{
}

void Led_Control::Setup(byte AssignedPin)
{
    pin = AssignedPin;

    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    State = false;

    Animation = false;
    BlinkCount = 0;
}

void Led_Control::Toggle()
{
    State = !State;

    digitalWrite(pin, State);

    LastUpdate = millis();
}

void Led_Control::TurnOn()
{
    digitalWrite(pin, HIGH);
    State = true;
    LastUpdate = millis();
    Animation = false;
    BlinkCount = 0;
}

void Led_Control::TurnOff()
{
    digitalWrite(pin, LOW);
    State = false;
    LastUpdate = millis();
    Animation = false;
    BlinkCount = 0;
}

void Led_Control::Blink(int16_t Count, bool Blocking)
{
    Blink(Count, BlinkDuty, Blocking);
}

void Led_Control::Blink(int16_t Count, uint16_t Duty, bool Blocking)
{
    BlinkDuty = Duty;

    if (Count < 0)
    {
        // Blink forever
        BlinkCount = -1;
    }
    else
    {
        // ON + OFF transitions
        BlinkCount = Count * 2;
    }

    Animation = true;

    Toggle();

    if (BlinkCount > 0)
    {
        BlinkCount--;
    }

    LastAnimation = millis();

    if (Blocking)
    {
        BlockingUpdate();
    }
}

void Led_Control::Update()
{
    ProcessAnimation();
}

void Led_Control::BlockingUpdate()
{
    while (Animation)
    {
        ProcessAnimation();
        delay(1);
    }
}

void Led_Control::BlockingUpdate(unsigned long Durationms)
{
    unsigned long Timer = millis() + Durationms;
    while ((Animation) && (millis() < Timer))
    {
        ProcessAnimation();
        delay(1);
    }
}

void Led_Control::ProcessAnimation()
{
    if (!Animation)
    {
        return;
    }
    
    if ((uint32_t)(millis() - LastAnimation) < BlinkDuty)
    {
        return;
    }

    LastAnimation = millis();

    Toggle();

    // Finite blink sequence
    if (BlinkCount > 0)
    {
        BlinkCount--;

        if (BlinkCount == 0)
        {
            TurnOff();
        }
    }
}