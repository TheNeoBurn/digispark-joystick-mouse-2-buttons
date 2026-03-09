# Digispark Joystick Mouse (2 buttons)

I used a potentiometer joystick plus an additional pushbutton and connected it to a Digispark ATTiny85. This tool mapps the hardware input to a USB mouse functionality.

Connections:
- VCC           -> 10kΩ -> PB5
- Joystick VRX  -> 34kΩ -> PB5 (I used 2x68kΩ in parallel)
- Joystick VRY  ->         PB2
- Joystick SW   ->         PB1
- Button 1 Pin1 ->         PB0
- VCC           -> 10kΩ -> PB0
- Button 1 Pin2 ->         GND
- PB3 and PB4 are used for USB

I used the 10kΩ / 34kΩ voltage divider to use PB5 despite not being able to deactivate its reset functionality for my chip. This way, it won't trigger the reset because of values below 1/2 VCC but will instead drastically shorten the possible value range.

