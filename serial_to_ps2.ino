// Read serial TTY input and output as PS/2
// Currently only reads TTY input and echoes ps2dev codes back

#define SERIAL_CHECK_MS 100
#define PIN_DATA 5
#define PIN_CLOCK 6

#include "ps2dev.h"
#include "keyboard.h"

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0') 

#define PS2_ENABLED 1

#ifdef PS2_ENABLED
PS2dev keyboard(PIN_CLOCK, PIN_DATA);
#endif
unsigned char leds;

void setup() {
  Serial.begin(9600);
  Serial.println("setup()");
#ifdef PS2_ENABLED
  keyboard.keyboard_init();
#endif
}

char buffer[0xff];

void loop() {
  unsigned char new_leds;
  static unsigned long last_serial_check_ms;
  unsigned long time_ms = millis();

#ifdef PS2_ENABLED
  if(keyboard.keyboard_handle(&new_leds)) {
    if (new_leds != leds) {
      leds = new_leds;
      sprintf(buffer, "LEDs: " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(leds));
    }
    digitalWrite(LED_BUILTIN, leds);
  }
#endif

  if (time_ms - last_serial_check_ms > SERIAL_CHECK_MS) {
    last_serial_check_ms = time_ms;
    check_serial();
  }
}

#ifdef PS2_ENABLED
int shift, old_shift;
void check_shift() {
  if (shift != old_shift) {
    old_shift = shift;
    if (shift) {
      keyboard.keyboard_press(PS2dev::ScanCodes::LEFT_SHIFT);
    } else {
      keyboard.keyboard_release(PS2dev::ScanCodes::LEFT_SHIFT);
    }
  }
}
#endif

void check_serial() {
  *buffer = 0;
  if (Serial.available() > 0) {
    int kb_code = get_kb_from_serial();

    if (kb_code == KB_ERROR) {
      sprintf(buffer, "Error %i", kb_code);
      Serial.println(buffer);
      return;
    }

    sprintf(buffer, "%i %s;", kb_code, kb_to_string(kb_code));
    Serial.println(buffer);

    unsigned char scanCode = kb_to_ScanCode(&shift, kb_code);
    if (scanCode) {
      sprintf(buffer, "Non-special ScanCode %i %i", shift, scanCode);
      Serial.println(buffer);
#ifdef PS2_ENABLED
      check_shift();
      keyboard.keyboard_mkbrk(scanCode);
#endif
      return;
    }

    scanCode = kb_to_SpecialScanCode(&shift, kb_code);
    if (scanCode) {
      sprintf(buffer, "Special ScanCode %i %i", shift, scanCode);
      Serial.println(buffer);
#ifdef PS2_ENABLED
      check_shift();
      keyboard.keyboard_special_mkbrk(scanCode);
#endif
      return;
    }

    Serial.println("No ScanCode");
  }
}
