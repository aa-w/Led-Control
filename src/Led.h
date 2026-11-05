/*!
 *  @file       Led.h
 *  Project     Led-Control Libraru
 *  @brief      Led Control Library for Arduino
 *  @author     aa-w
 *  @date       05/11/2026
 *  @license    MIT - Copyright (c) 2026 aa-w
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef LED_H  // Prevent multiple inclusions
#define LED_H

#ifndef ARDUINO_H_
#define ARDUINO_H_
#include <Arduino.h>
#endif

class Led
{
private:
    byte pin;
    uint16_t BlinkDuty;
    int16_t BlinkCount;      // -1 = forever
    bool Animation;
    uint32_t LastAnimation;
    uint32_t LastUpdate;
    bool State;
    void ProcessAnimation();
public:
    Led(); //Constructor
    void Setup(byte AssignedPin);
    void Blink(int16_t Count, bool Blocking);
    void Blink(int16_t Count, uint16_t Duty, bool Blocking);
    void Toggle();
    void Update();
    void BlockingUpdate();
    void TurnOn();
    void TurnOff();
};

#endif // LED