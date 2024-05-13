#define KB_DBG 0
#if KB_DBG
char kb_buffer[255];
#endif

#include <Arduino.h>
#include "keyboard.h"

PROGMEM const char KB_TO_STRING[121][8] = {
  /*   0 */ "KB_ESC",
  /*   1 */ "KB_F1",
  /*   2 */ "KB_F2",
  /*   3 */ "KB_F3",
  /*   4 */ "KB_F4",
  /*   5 */ "KB_F5",
  /*   6 */ "KB_F6",
  /*   7 */ "KB_F7",
  /*   8 */ "KB_F8",
  /*   9 */ "KB_F9",
  /*  10 */ "KB_F10",
  /*  11 */ "KB_F11",
  /*  12 */ "KB_F12",

  /*  13 */ "KB_INS",
  /*  14 */ "KB_HOM",
  /*  15 */ "KB_PGU",
  /*  16 */ "KB_DEL",
  /*  17 */ "KB_END",
  /*  18 */ "KB_PGD",

  /*  19 */ "KB_UP",
  /*  20 */ "KB_DN",
  /*  21 */ "KB_LE",
  /*  22 */ "KB_RI",

  /*  23 */ "KB_BKS",
  /*  24 */ "KB_SP",
  /*  25 */ "KB_ENT",
  /*  26 */ "KB_TAB",

  /*  27 */ "KB_BT",
  /*  28 */ "KB_1",
  /*  29 */ "KB_2",
  /*  30 */ "KB_3",
  /*  31 */ "KB_4",
  /*  32 */ "KB_5",
  /*  33 */ "KB_6",
  /*  34 */ "KB_7",
  /*  35 */ "KB_8",
  /*  36 */ "KB_9",
  /*  37 */ "KB_0",
  /*  38 */ "KB_MN",
  /*  39 */ "KB_EQ",

  /*  40 */ "KB_Q",
  /*  41 */ "KB_W",
  /*  42 */ "KB_E",
  /*  43 */ "KB_R",
  /*  44 */ "KB_T",
  /*  45 */ "KB_Y",
  /*  46 */ "KB_U",
  /*  47 */ "KB_I",
  /*  48 */ "KB_O",
  /*  49 */ "KB_P",
  /*  50 */ "KB_OBK",
  /*  51 */ "KB_CBK",
  /*  52 */ "KB_BS",

  /*  53 */ "KB_A",
  /*  54 */ "KB_S",
  /*  55 */ "KB_D",
  /*  56 */ "KB_F",
  /*  57 */ "KB_G",
  /*  58 */ "KB_H",
  /*  59 */ "KB_J",
  /*  60 */ "KB_K",
  /*  61 */ "KB_L",
  /*  62 */ "KB_SC",
  /*  63 */ "KB_SQ",

  /*  64 */ "KB_Z",
  /*  65 */ "KB_X",
  /*  66 */ "KB_C",
  /*  67 */ "KB_V",
  /*  68 */ "KB_B",
  /*  69 */ "KB_N",
  /*  70 */ "KB_M",
  /*  71 */ "KB_COM",
  /*  72 */ "KB_PER",
  /*  73 */ "KB_SLA",

  /*  74 */ "KB_TIL",
  /*  75 */ "KB_EXC",
  /*  76 */ "KB_AT",
  /*  77 */ "KB_HSH",
  /*  78 */ "KB_DLR",
  /*  79 */ "KB_PCT",
  /*  80 */ "KB_CRT",
  /*  81 */ "KB_ASD",
  /*  82 */ "KB_AK",
  /*  83 */ "KB_OP",
  /*  84 */ "KB_CP",
  /*  85 */ "KB_US",
  /*  86 */ "KB_PL",

  /*  87 */ "KB_q",
  /*  88 */ "KB_w",
  /*  89 */ "KB_e",
  /*  90 */ "KB_r",
  /*  91 */ "KB_t",
  /*  92 */ "KB_y",
  /*  93 */ "KB_u",
  /*  94 */ "KB_i",
  /*  95 */ "KB_o",
  /*  96 */ "KB_p",
  /*  97 */ "KB_OBC",
  /*  98 */ "KB_CBC",
  /*  99 */ "KB_PI",

  /* 100 */ "KB_a",
  /* 101 */ "KB_s",
  /* 102 */ "KB_d",
  /* 103 */ "KB_f",
  /* 104 */ "KB_g",
  /* 105 */ "KB_h",
  /* 106 */ "KB_j",
  /* 107 */ "KB_k",
  /* 108 */ "KB_l",
  /* 109 */ "KB_CLN",
  /* 110 */ "KB_DQ",
  
  /* 111 */ "KB_z",
  /* 112 */ "KB_x",
  /* 113 */ "KB_c",
  /* 114 */ "KB_v",
  /* 115 */ "KB_b",
  /* 116 */ "KB_n",
  /* 117 */ "KB_m",
  /* 118 */ "KB_LT",
  /* 119 */ "KB_GT",
  /* 120 */ "KB_Q"
};

char* kb_to_string(int kb) {
  static char buffer[16];
  memcpy_P(buffer, KB_TO_STRING[kb], 16);
  return buffer;
}

int get_kb_from_serial() {
    int r = Serial.read();
    int r2;
    #if KB_DBG
      *kb_buffer = 0;
      sprintf(kb_buffer, "1=%i ", r);
      Serial.println(kb_buffer);
    #endif
// 27
    if (r == 27) {
      if (Serial.available()) {
        r2 = Serial.read();
        #if KB_DBG
          sprintf(kb_buffer, "%s 2=%i ", kb_buffer, r2);
          Serial.println(kb_buffer);
        #endif
        if (r2 != 91) {
          #if KB_DBG
            sprintf(kb_buffer, "%s error 27->not 91", kb_buffer);
            Serial.println(kb_buffer);
          #endif
          return KB_ERROR;
        }
// 27 -> 91
        if (!Serial.available()) {
          #if KB_DBG
            sprintf(kb_buffer, "%s error 27->91->not available", kb_buffer);
            Serial.println(kb_buffer);
          #endif
          return KB_ERROR;
        }
        r = Serial.read();
// 27->91->r
        #if KB_DBG
          sprintf(kb_buffer, "%s 3=r=%i", kb_buffer, r);
          Serial.println(kb_buffer);
        #endif
        switch (r) {
          case 65: return KB_UP;
          case 66: return KB_DOWN;
          case 68: return KB_LEFT;
          case 67: return KB_RIGHT;
        }
        if (!Serial.available()) {
          #if KB_DBG
            sprintf(kb_buffer, "%s error 27->91->%i->not available", kb_buffer, r);
            Serial.println(kb_buffer);
          #endif
          return KB_ERROR;
        }
        r2 = Serial.read();
// 27->91->r->r2
        #if KB_DBG
          sprintf(kb_buffer, "%s 4=r2=%i", kb_buffer, r2);
          Serial.println(kb_buffer);
        #endif
        if (r2 == 126) {
// 27->91->r->126
          #if KB_DBG
            sprintf(kb_buffer, "%s 27->91->r->126 ", kb_buffer);
            Serial.println(kb_buffer);
          #endif
          switch (r) {
            case 50: return KB_INS;
            case 49: return KB_HOME;
            case 53: return KB_PGUP;
            case 51: return KB_DEL;
            case 52: return KB_END;
            case 54: return KB_PGDN;
          }
          #if KB_DBG
            sprintf(kb_buffer, "%s error 27->91->%i->%i", kb_buffer, r, r2);
            Serial.println(kb_buffer);
          #endif
          return KB_ERROR;
        }
// 27->91->r->r2
        switch (r) {
          case 49:
// 27->91->49->r2
            if (!Serial.available()) {
              #if KB_DBG
                sprintf(kb_buffer, "%s error 27->91->49->not available", kb_buffer);
                Serial.println(kb_buffer);
              #endif
              return KB_ERROR;
            }
            r = Serial.read();
// 27->91->49->r2->r
            #if KB_DBG
              sprintf(kb_buffer, "%s 5=%i", kb_buffer, r);
              Serial.println(kb_buffer);
            #endif
            if (r != 126) {
              #if KB_DBG
                sprintf(kb_buffer, "%s error not 126", kb_buffer);
                Serial.println(kb_buffer);
              #endif
              return KB_ERROR;
            }
            switch (r2) {
              case 49: return KB_F1;       // 27 91 49 49 126
              case 50: return KB_F2;       // 27 91 49 50 126
              case 51: return KB_F3;       // 27 91 49 51 126
              case 52: return KB_F4;       // 27 91 49 52 126
              case 53: return KB_F5;       // 27 91 49 53 126
              case 55: return KB_F6;       // 27 91 49 55 126
              case 56: return KB_F7;       // 27 91 49 56 126
              case 57: return KB_F8;       // 27 91 49 57 126
            }
            #if KB_DBG
              sprintf(kb_buffer, "%s 4=unrecognized", kb_buffer);
              Serial.println(kb_buffer);
            #endif
            return KB_ERROR;
          case 50:
// 27->91->50->r2
            if (!Serial.available()) {
              #if KB_DBG
                sprintf(kb_buffer, "%s error 27->50->not available", kb_buffer);
                Serial.println(kb_buffer);
              #endif
              return KB_ERROR;
            }
            r = Serial.read();
// 27->91->50->r2->r
            if (r != 126) {
              #if KB_DBG
                sprintf(kb_buffer, "%s error 27->50->%i->not 126", kb_buffer, r);
                Serial.println(kb_buffer);
              #endif
              return KB_ERROR;
            }
            #if KB_DBG
              sprintf(kb_buffer, "%s 5=%i", kb_buffer, r);
              Serial.println(kb_buffer);
            #endif
            switch (r2) {
              case 48: return KB_F9;       // 27 91 50 48 126
              case 49: return KB_F10;      // 27 91 50 49 126
              case 51: return KB_F11;      // 27 91 50 51 126
              case 52: return KB_F12;      // 27 91 50 52 126
            }
            #if KB_DBG
              sprintf(kb_buffer, "%s error 27->91->50->%i->126", kb_buffer, r2);
              Serial.println(kb_buffer);
            #endif
            return KB_ERROR;
        }
        #if KB_DBG
          sprintf(kb_buffer, "%s error 27->%i", kb_buffer, r);
          Serial.println(kb_buffer);
        #endif
        return KB_ERROR;
      }
    }

    #if KB_DBG
      sprintf(kb_buffer, "%s end case %i", kb_buffer, r);
      Serial.println(kb_buffer);
    #endif

    switch (r) {
      case 27:   return KB_ESC;            // 27

      case 127:  return KB_BACKSPACE;      // 127
      case 32:   return KB_SPACE;          // 32
      case 13:   return KB_ENTER;          // 13
      case 9:    return KB_TAB;            // 9

      case 96:   return KB_BACKTICK;       // 96
      case 49:   return KB_1;              // 49
      case 50:   return KB_2;              // 50
      case 51:   return KB_3;              // 51
      case 52:   return KB_4;              // 52
      case 53:   return KB_5;              // 53
      case 54:   return KB_6;              // 54
      case 55:   return KB_7;              // 55
      case 56:   return KB_8;              // 56
      case 57:   return KB_9;              // 57
      case 48:   return KB_0;              // 48
      case 45:   return KB_MINUS;          // 45
      case 61:   return KB_EQUALS;         // 61

      case 81:   return KB_Q;              // 81
      case 87:   return KB_W;              // 87
      case 69:   return KB_E;              // 69
      case 82:   return KB_R;              // 82
      case 84:   return KB_T;              // 84
      case 89:   return KB_Y;              // 89
      case 85:   return KB_U;              // 85
      case 73:   return KB_I;              // 73
      case 79:   return KB_O;              // 79
      case 80:   return KB_P;              // 80
      case 91:   return KB_OPEN_BRACKET;   // 91
      case 93:   return KB_CLOSE_BRACKET;  // 93
      case 92:   return KB_BACKSLASH;      // 92

      case 65:   return KB_A;              // 65
      case 83:   return KB_S;              // 83
      case 68:   return KB_D;              // 68
      case 70:   return KB_F;              // 70
      case 71:   return KB_G;              // 71
      case 72:   return KB_H;              // 72
      case 74:   return KB_J;              // 74
      case 75:   return KB_K;              // 75
      case 76:   return KB_L;              // 76
      case 59:   return KB_SEMICOLON;      // 59
      case 39:   return KB_SINGLE_QUOTE;   // 39

      case 90:   return KB_Z;              // 90
      case 88:   return KB_X;              // 88
      case 67:   return KB_C;              // 67
      case 86:   return KB_V;              // 86
      case 66:   return KB_B;              // 66
      case 78:   return KB_N;              // 78
      case 77:   return KB_M;              // 77
      case 44:   return KB_COMMA;          // 44
      case 46:   return KB_PERIOD;         // 46
      case 47:   return KB_SLASH;          // 47

      case 126:  return KB_TILDE;          // 126
      case 33:   return KB_EXCLAMATION;    // 33
      case 64:   return KB_AT;             // 64
      case 35:   return KB_HASH;           // 35
      case 36:   return KB_DOLLAR;         // 36
      case 37:   return KB_PERCENT;        // 37
      case 94:   return KB_CARET;          // 94
      case 38:   return KB_AMPERSAND;      // 38
      case 42:   return KB_ASTERISK;       // 42
      case 40:   return KB_OPEN_PAREN;     // 40
      case 41:   return KB_CLOSE_PAREN;    // 41
      case 95:   return KB_UNDERSCORE;     // 95
      case 43:   return KB_PLUS;           // 43

      case 113:  return KB_q;              // 113
      case 119:  return KB_w;              // 119
      case 101:  return KB_e;              // 101
      case 114:  return KB_r;              // 114
      case 116:  return KB_t;              // 116
      case 121:  return KB_y;              // 121
      case 117:  return KB_u;              // 117
      case 105:  return KB_i;              // 105
      case 111:  return KB_o;              // 111
      case 112:  return KB_p;              // 112
      case 123:  return KB_OPEN_BRACE;     // 123
      case 125:  return KB_CLOSE_BRACE;    // 125
      case 124:  return KB_PIPE;           // 124

      case 97:   return KB_a;              // 97
      case 115:  return KB_s;              // 115
      case 100:  return KB_d;              // 100
      case 102:  return KB_f;              // 102
      case 103:  return KB_g;              // 103
      case 104:  return KB_h;              // 104
      case 106:  return KB_j;              // 106
      case 107:  return KB_k;              // 107
      case 108:  return KB_l;              // 108
      case 58:   return KB_COLON;          // 58
      case 34:   return KB_DOUBLE_QUOTE;   // 34

      case 122:  return KB_z;              // 122
      case 120:  return KB_x;              // 120
      case 99:   return KB_c;              // 99
      case 118:  return KB_v;              // 118
      case 98:   return KB_b;              // 98
      case 110:  return KB_n;              // 110
      case 109:  return KB_m;              // 109
      case 60:   return KB_LESS;           // 60
      case 62:   return KB_GREATER;        // 62
      case 63:   return KB_QUESTION;       // 63

      #if KB_DBG
        sprintf(kb_buffer, "%s error %i", kb_buffer, r);
        Serial.println(kb_buffer);
      #endif
      return KB_ERROR;
    }
}

/**
 * 
		enum ScanCodes
		{
			ESCAPE = 0x76,
			F1 = 0x05,
			F2 = 0x06,
			F3 = 0x04,
			F4 = 0x0c,
			F5 = 0x03,
			F6 = 0x0b,
			F7 = 0x83,
			F8 = 0x0a,
			F9 = 0x01,
			F10 = 0x09,
			F11 = 0x78,
			F12 = 0x07,
			
			ACCENT = 0x0e,
			ONE = 0x16,
			TWO = 0x1e,
			THREE = 0x26,
			FOUR = 0x25,
			FIVE = 0x2e,
			SIX = 0x36,
			SEVEN = 0x3d,
			EIGHT = 0x3e,
			NINE = 0x46,
			ZERO = 0x45,
			MINUS = 0x4e,
			EQUAL = 0x55,
			BACKSPACE = 0x66,

			TAB = 0x0d,
			Q = 0x15,
			W = 0x1d,
			E = 0x24,
			R = 0x2d,
			T = 0x2c,
			Y = 0x35,
			U = 0x3c,
			I = 0x43,
			O = 0x44,
			P = 0x4d,
			OPEN_BRACKET = 0x54,
			CLOSE_BRACKET = 0x5b,
			BACKSLASH = 0x5d,

			A = 0x1c,
			S = 0x1b,
			D = 0x23,
			F = 0x2b,
			G = 0x34,
			H = 0x33,
			J = 0x3b,
			K = 0x42,
			L = 0x4b,
			SEMI_COLON = 0x4c,
			TICK_MARK = 0x52,
			ENTER = 0x5a,

			Z = 0x1a,
			X = 0x22,
			C = 0x21,
			V = 0x2a,
			B = 0x32,
			N = 0x31,
			M = 0x3a,
			COMMA = 0x41,
			PERIOD = 0x49,
			SLASH = 0x4a,

			SPACE = 0x29,
			ASTERISK = 0x7c,
			PLUS = 0x79,
			DECIMAL = 0x71
		};
*/

unsigned char kb_to_ScanCode(int* shift, int kb) {
  *shift = 0;
  switch (kb) {
    case KB_ESC:             return 0x76;
    case KB_F1:              return 0x05;
    case KB_F2:              return 0x06;
    case KB_F3:              return 0x04;
    case KB_F4:              return 0x0c;
    case KB_F5:              return 0x03;
    case KB_F6:              return 0x0b;
    case KB_F7:              return 0x83;
    case KB_F8:              return 0x0a;
    case KB_F9:              return 0x01;
    case KB_F10:             return 0x09;
    case KB_F11:             return 0x78;
    case KB_F12:             return 0x07;
    
    case KB_TILDE:         *shift = 1;
    case KB_BACKTICK:        return 0x0e;
    case KB_EXCLAMATION:   *shift = 1;
    case KB_1:               return 0x16;
    case KB_AT:            *shift = 1;
    case KB_2:               return 0x1e;
    case KB_HASH:          *shift = 1;
    case KB_3:               return 0x26;
    case KB_DOLLAR:        *shift = 1;
    case KB_4:               return 0x25;
    case KB_PERCENT:       *shift = 1;
    case KB_5:               return 0x2e;
    case KB_CARET:         *shift = 1;
    case KB_6:               return 0x36;
    case KB_AMPERSAND:     *shift = 1;
    case KB_7:               return 0x3d;
    case KB_ASTERISK:      *shift = 1;
    case KB_8:               return 0x3e;
    case KB_OPEN_PAREN:    *shift = 1;
    case KB_9:               return 0x46;
    case KB_CLOSE_PAREN:   *shift = 1;
    case KB_0:               return 0x45;
    case KB_UNDERSCORE:    *shift = 1;
    case KB_MINUS:           return 0x4e;
    case KB_PLUS:          *shift = 1;
    case KB_EQUALS:          return 0x55;
    case KB_BACKSPACE:       return 0x66;

    case KB_TAB:             return 0x0d;
    case KB_Q:             *shift = 1;
    case KB_q:               return 0x15;
    case KB_W:             *shift = 1;
    case KB_w:               return 0x1d;
    case KB_E:             *shift = 1;
    case KB_e:               return 0x24;
    case KB_R:             *shift = 1;
    case KB_r:               return 0x2d;
    case KB_T:             *shift = 1;
    case KB_t:               return 0x2c;
    case KB_Y:             *shift = 1;
    case KB_y:               return 0x35;
    case KB_U:             *shift = 1;
    case KB_u:               return 0x3c;
    case KB_I:             *shift = 1;
    case KB_i:               return 0x43;
    case KB_O:             *shift = 1;
    case KB_o:               return 0x44;
    case KB_P:             *shift = 1;
    case KB_p:               return 0x4d;
    case KB_OPEN_BRACE:    *shift = 1;
    case KB_OPEN_BRACKET:    return 0x54;
    case KB_CLOSE_BRACE:   *shift = 1;
    case KB_CLOSE_BRACKET:   return 0x5b;
    case KB_PIPE:          *shift = 1;
    case KB_BACKSLASH:       return 0x5d;

    case KB_A:             *shift = 1;
    case KB_a:               return 0x1c;
    case KB_S:             *shift = 1;
    case KB_s:               return 0x1b;
    case KB_D:             *shift = 1;
    case KB_d:               return 0x23;
    case KB_F:             *shift = 1;
    case KB_f:               return 0x2b;
    case KB_G:             *shift = 1;
    case KB_g:               return 0x34;
    case KB_H:             *shift = 1;
    case KB_h:               return 0x33;
    case KB_J:             *shift = 1;
    case KB_j:               return 0x3b;
    case KB_K:             *shift = 1;
    case KB_k:               return 0x42;
    case KB_L:             *shift = 1;
    case KB_l:               return 0x4b;
    case KB_COLON:         *shift = 1;
    case KB_SEMICOLON:       return 0x4c;
    case KB_DOUBLE_QUOTE:  *shift = 1;
    case KB_SINGLE_QUOTE:    return 0x52;
    case KB_ENTER:           return 0x5a;

    case KB_Z:             *shift = 1;
    case KB_z:               return 0x1a;
    case KB_X:             *shift = 1;
    case KB_x:               return 0x22;
    case KB_C:             *shift = 1;
    case KB_c:               return 0x21;
    case KB_V:             *shift = 1;
    case KB_v:               return 0x2a;
    case KB_B:             *shift = 1;
    case KB_b:               return 0x32;
    case KB_N:             *shift = 1;
    case KB_n:               return 0x31;
    case KB_M:             *shift = 1;
    case KB_m:               return 0x3a;
    case KB_LESS:          *shift = 1;
    case KB_COMMA:           return 0x41;
    case KB_GREATER:       *shift = 1;
    case KB_PERIOD:          return 0x49;
    case KB_QUESTION:      *shift = 1;
    case KB_SLASH:           return 0x4a;
  }
  return 0;
}

/**
		enum SpecialScanCodes
		{
			INSERT = 0x70,
			HOME = 0x6c,
			PAGE_UP = 0x7d,
			DELETE = 0x71,
			END = 0x69,
			PAGE_DOWN = 0x7a,

			UP_ARROW = 0x75,
			LEFT_ARROW = 0x6b,
			DOWN_ARROW = 0x72,
			RIGHT_ARROW = 0x74,
		};
*/

unsigned char kb_to_SpecialScanCode(int* shift, int kb) {
  switch (kb) {
    case KB_INS:   return 0x70;
    case KB_HOME:  return 0x6c;
    case KB_PGUP:  return 0x7d;
    case KB_DEL:   return 0x71;
    case KB_END:   return 0x69;
    case KB_PGDN:  return 0x7a;

    case KB_UP:    return 0x75;
    case KB_LEFT:  return 0x6b;
    case KB_DOWN:  return 0x72;
    case KB_RIGHT: return 0x74;
  }
  return 0;
}
