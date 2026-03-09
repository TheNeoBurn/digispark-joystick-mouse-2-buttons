/* Using a potentiometer joystick and an additional pushbutton to implement
 * a USB mouse with that
 * 
 * Connections:
 * - VCC           -> 10kΩ -> PB5
 * - Joystick VRX  -> 34kΩ -> PB5 (I used 2x68kΩ in parallel)
 * - Joystick VRY  ->         PB2
 * - Joystick SW   ->         PB1
 * - Button 1 Pin1 ->         PB0
 * - VCC           -> 10kΩ -> PB0
 * - Button 1 Pin2 ->         GND
 * - PB3 and PB4 are used for USB
 * 
 * I used the 10kΩ / 34kΩ voltage divider to use PB5 despite not being able
 * to deactivate its reset functionality for my chip. This way, it won't
 * trigger the reset because of values below 1/2 VCC but will instead
 * drastically shorten the possible value range.
 * 
 */


#include "DigiMouse.h"

// Global variables to store the currently precessed hardware states
unsigned char lastBtn = 0;   // Buttons
uint32_t last0 = 0;
uint32_t last1 = 0;

void setup() {
  // Define pin usage (PB3 and PB4 are handled by DigiMouse)
  pinMode(PB0, INPUT_PULLUP); // Btn1 (below)
  pinMode(PB1, INPUT_PULLUP); // Btn2 (JoyStick)
  pinMode(PB2, INPUT);        // VRY
  pinMode(PB5, INPUT);        // VRX

  DigiMouse.begin();
}

void loop() {
  // Read current hardware values
  bool btn1 = digitalRead(PB0) == LOW;
  bool btn2 = digitalRead(PB1) == LOW;
  int x = analogRead(0); // PB5 is Analog 0
  int y = analogRead(1); // PB2 is Analog 1

  // Calculate current button state
  unsigned char btn = 0;
  if (btn1) btn |= 1;
  if (btn2) btn |= 2;

  // Apply joystick x state in steps
  // I had to drastically shrikt the range here because I wasn't able 
  // to deactivate the reset functionality on PB5
  int dx;
  if (x < 880)      dx = 6;
  else if (x < 900) dx = 4;
  else if (x < 920) dx = 2;
  else if (x < 990) dx = 0;
  else if (x < 1000) dx = -2;
  else if (x < 1010) dx = -4;
  else              dx = -6;

  // Apply joystick y state in steps
  int dy;
  if (y < 150)      dy = -6;
  else if (y < 300) dy = -4;
  else if (y < 450) dy = -3;
  else if (y < 573) dy = 0;
  else if (y < 723) dy = 2;
  else if (y < 873) dy = 4;
  else              dy = 6;

  // Update changed button state
  if (lastBtn != btn) {
    lastBtn = btn;
    DigiMouse.setButtons(btn);
  }

  // Move cursor if not centered
  if (dx != 0 || dy != 0) {
    DigiMouse.move(dx, dy, 0);
  }

  // This delay will determin the mouse speed
  DigiMouse.delay(15);
}
