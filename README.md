# ArduinoTTYToPS2
Arduino TTY serial input to PS/2 output.

## Use
1. Connect:
    1. Arduino pin 5 to PS/2 pin 1 (data)
    2. Arduino pin 6 to PS/2 pin 5 (clock)
    3. Arduino pin 14 to PS/2 pin 3 (data ground)
2. Upload to Arduino
3. Connect to Arduino over serial (I use a USB connection and PuTTy with default terminal settings)
4. Turn on the device that needs PS/2

### Debugging
- serial_to_ps2.ino: set PS2_ENABLED to 0 to only echo key codes back, do not send PS/2
- keyboard.cpp: set KB_DBG to 1 for debugging output
