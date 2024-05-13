// Read serial TTY input and output as PS/2
// Currently only reads TTY input and echoes ps2dev codes back

//#include "ps2dev.h"
#include "keyboard.h"

//PS2dev keyboard(8,7);

void setup() {
  Serial.begin(9600);
  Serial.println("setup()");
  //keyboard.keyboard_init();
}

char buffer[0xff];
int shift;

void loop() {
  delay(200);
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
      return;
    }

    scanCode = kb_to_SpecialScanCode(&shift, kb_code);
    if (scanCode) {
      sprintf(buffer, "Special ScanCode %i %i", shift, scanCode);
      Serial.println(buffer);
      return;
    }

    Serial.println("No ScanCode");
  }
}
