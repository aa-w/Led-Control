#include "Led_Control.h"

// Constructor
Led_Control::Led_Control() : pin(0),
             State(false),
             BlinkDuty(500),
             BlinkCount(0),
             Animation(false),
             LastAnimation(0),
             LastUpdate(0),
             AnimationDelay(0)
{
}

void Led_Control::Setup(byte AssignedPin)
{
    pin = AssignedPin;

    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    State = false;

    Animation = false;
    AnimationDelay = 0;
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
    Animation = false;
    BlinkCount = 0;
    AnimationDelay = 0;
    LastUpdate = millis();
}

void Led_Control::TurnOff()
{
    digitalWrite(pin, LOW);
    State = false;
    Animation = false;
    BlinkCount = 0;
    AnimationDelay = 0;
    LastUpdate = millis();
}

void Led_Control::DelayedToggle(uint16_t DurationMs)
{
    Animation = true;
    BlinkCount = 2;
    AnimationDelay = DurationMs;
    LastAnimation = millis();
}

void Led_Control::Blink(int16_t Count, bool Blocking)
{
    Blink(Count, BlinkDuty, Blocking);
}

void Led_Control::Blink(int16_t Count, uint16_t Duty, bool Blocking)
{
    BlinkDuty = Duty;
    AnimationDelay = 0;

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

void Led_Control::DelayedBlink(uint16_t DurationMs, int16_t Count, uint16_t Duty, bool Blocking)
{
    BlinkDuty = Duty;
    AnimationDelay = DurationMs;
    if (Count < 0)
    {
        // Blink forever
        BlinkCount = -1;
    }
    else
    {
        // ON + OFF transitions
        BlinkCount = (Count * 2) + 2;
    }

    Animation = true;

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

void Led_Control::BlockingUpdate(uint16_t DurationMs)
{
    unsigned long Timer = millis() + DurationMs;
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
    
    if ((uint32_t)(millis() - LastAnimation) < (BlinkDuty + AnimationDelay))
    {
        return;
    }

    AnimationDelay = 0;
    LastAnimation = millis();

    Toggle();

    // Finite blink sequence
    if (BlinkCount > 0)
    {
        BlinkCount--;

        if (BlinkCount == 0)
        {
            Toggle();
            Animation = false;
        }
    }
}