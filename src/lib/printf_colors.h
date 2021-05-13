#ifndef PRINTF_COLORS
#define PRINTF_COLORS

#include <stdio.h>

#define P_NRM  "\x1B[0m"
#define P_RED  "\x1B[31m"
#define P_GRN  "\x1B[32m"
#define P_YEL  "\x1B[33m"
#define P_BLU  "\x1B[34m"
#define P_MAG  "\x1B[35m"
#define P_CYN  "\x1B[36m"
#define P_WHT  "\x1B[37m"

#define printf_color1(COLOR, FORMAT, P1) printf("%s"FORMAT"%s", COLOR, P1, P_NRM)
#define printf_color2(COLOR, FORMAT, P1, P2) printf("%s"FORMAT"%s", COLOR, P1, P2, P_NRM)
#define printf_color3(COLOR, FORMAT, P1, P2, P3) printf("%s"FORMAT"%s", COLOR, P1, P2, P3, P_NRM)
#define printf_color4(COLOR, FORMAT, P1, P2, P3, P4) printf("%s"FORMAT"%s", COLOR, P1, P2, P3, P4, P_NRM)

#endif