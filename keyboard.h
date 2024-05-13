#define KB_ERROR         -1
  
#define KB_ESC            0
  
#define KB_F1             1
#define KB_F2             2
#define KB_F3             3
#define KB_F4             4
#define KB_F5             5
#define KB_F6             6
#define KB_F7             7
#define KB_F8             8
#define KB_F9             9
#define KB_F10           10
#define KB_F11           11
#define KB_F12           12
  
#define KB_INS           13
#define KB_HOME          14
#define KB_PGUP          15
#define KB_DEL           16
#define KB_END           17
#define KB_PGDN          18

#define KB_UP            19
#define KB_DOWN          20
#define KB_LEFT          21
#define KB_RIGHT         22
  
#define KB_BACKSPACE     23
#define KB_SPACE         24
#define KB_ENTER         25
#define KB_TAB           26
  
#define KB_BACKTICK      27
#define KB_1             28
#define KB_2             29
#define KB_3             30
#define KB_4             31
#define KB_5             32
#define KB_6             33
#define KB_7             34
#define KB_8             35
#define KB_9             36
#define KB_0             37
#define KB_MINUS         38
#define KB_EQUALS        39
  
#define KB_Q             40
#define KB_W             41
#define KB_E             42
#define KB_R             43
#define KB_T             44
#define KB_Y             45
#define KB_U             46
#define KB_I             47
#define KB_O             48
#define KB_P             49
#define KB_OPEN_BRACKET  50
#define KB_CLOSE_BRACKET 51
#define KB_BACKSLASH     52

#define KB_A             53
#define KB_S             54
#define KB_D             55
#define KB_F             56
#define KB_G             57
#define KB_H             58
#define KB_J             59
#define KB_K             60
#define KB_L             61
#define KB_SEMICOLON     62
#define KB_SINGLE_QUOTE  63

#define KB_Z             64
#define KB_X             65
#define KB_C             66
#define KB_V             67
#define KB_B             68
#define KB_N             69
#define KB_M             70
#define KB_COMMA         71
#define KB_PERIOD        72
#define KB_SLASH         73

#define KB_TILDE         74
#define KB_EXCLAMATION   75
#define KB_AT            76
#define KB_HASH          77
#define KB_DOLLAR        78
#define KB_PERCENT       79
#define KB_CARET         80
#define KB_AMPERSAND     81
#define KB_ASTERISK      82
#define KB_OPEN_PAREN    83
#define KB_CLOSE_PAREN   84
#define KB_UNDERSCORE    85
#define KB_PLUS          86

#define KB_q             87
#define KB_w             88
#define KB_e             89
#define KB_r             90
#define KB_t             91
#define KB_y             92
#define KB_u             93
#define KB_i             94
#define KB_o             95
#define KB_p             96
#define KB_OPEN_BRACE    97
#define KB_CLOSE_BRACE   98
#define KB_PIPE          99

#define KB_a            100
#define KB_s            101
#define KB_d            102
#define KB_f            103
#define KB_g            104
#define KB_h            105
#define KB_j            106
#define KB_k            107
#define KB_l            108
#define KB_COLON        109
#define KB_DOUBLE_QUOTE 110

#define KB_z            111
#define KB_x            112
#define KB_c            113
#define KB_v            114
#define KB_b            115
#define KB_n            116
#define KB_m            117
#define KB_LESS         118
#define KB_GREATER      119
#define KB_QUESTION     120

PROGMEM extern const char KB_TO_STRING[121][8];

extern char* kb_to_string(int kb);

extern int get_kb_from_serial();

extern unsigned char kb_to_ScanCode(int* shift, int kb);

extern unsigned char kb_to_SpecialScanCode(int* shift, int kb);

