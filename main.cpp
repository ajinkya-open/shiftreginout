
#include <Arduino.h>
#include <MultiShiftRegister.h>
#include <ShiftIn.h>
ShiftIn<2> shift;

int latchPin = 4;
int clockPin = 5;
int dataPin = 2;

// How many 8 bit shift registers we're talking to.
// Two 8 bit registers can host 16 individually
// addressable binary outputs.
int numberOfRegisters = 2;

// Setup group of shift registers and name it `msr`.
// All outputs are initialized to low/off.
MultiShiftRegister msr(numberOfRegisters, latchPin, clockPin, dataPin);

void displayValues()
{
  for (uint8_t i = 0; i < shift.getDataWidth(); i++)
  {
    if(shift.state(i))
      msr.set_shift(i);
    if(!shift.state(i))
      msr.clear_shift(i);
  Serial.print(shift.state(i)); // get state of button i
  }
  msr.shift();
  Serial.println();
}

void setup()
{

  // declare pins: pLoadPin, clockEnablePin, dataPin, clockPin
  shift.begin(A5, A4, A2, A3);

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(13, OUTPUT);

  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);

  Serial.begin(9600);
}

void loop()
{
  // Prepare to turn on pin 5.
  // Pin 5 is still low/off.


  // This set and shift business is getting repetitive.
  // Let's do it in one line instead.



  // But wait, this is inefficient. It doesn't actually turn
  // outputs 5 and 12 on simultaneously. There is a very tiny delay
  // as it shifts output 5 before setting output 12. This may or
  // may not be a problem, depending on your application.
  // msr.set_shift(5);
  // msr.set_shift(12);
  // delay(1000);
  // msr.clear_shift(5);
  // msr.clear_shift(12);

  // delay(1000);

  // // So, consider doing this to prepare both outputs before shifting them.
  // msr.set(5);
  // msr.set(12);
  // msr.shift();
  // delay(1000);
  // msr.clear(5);
  // msr.clear(12);
  // msr.shift();

  if (shift.update()) // read in all values. returns true if any button has changed
    displayValues();
}