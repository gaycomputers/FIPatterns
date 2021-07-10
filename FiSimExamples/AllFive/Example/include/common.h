#ifndef H_COMMON
#define H_COMMON

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define IMG_LOAD_ADDR ((void*)0x32000000)
#define UART_OUT_BUF_ADDR ((void*)0x11000000)
#define SUCCESS 0x1BADB002
#define FAILURE 0xD00D2BAD
#define ENABLED 0xB0021BAD
#define DISABLED 0x2BADD00D
#define ZERO 0xBAAAAAAD
#define NEGATIVE 0xBEEFBABE
#define POSITIVE 0xFEEDC0DE
/** otp.c **/
int otp_init();
volatile int otp_get_img_hash(unsigned char* img_hash);
int otp_burn_img_hash(unsigned char* img_hash);
void otp_is_sec_boot_enabled(int* is_enabled);
bool otp_sec_boot_enable();
extern int METHOD_1;
extern int METHOD_2;
extern int METHOD_3;
extern int METHOD_4;
extern int METHOD_5;
extern int METHOD_6;
extern int METHOD_7;
extern int METHOD_8;
extern int METHOD_9;
extern int METHOD_10;
extern int METHOD_11;
extern int METHOD_12;
extern int METHOD_13;
extern int METHOD_14;
extern int METHOD_15;
extern int METHOD_16;
extern volatile unsigned int METHOD_TOTAL;

#define __SET_SIM_SUCCESS() \
	do { *((volatile unsigned int *)(0xAA01000)) = 0x1; } while (1);

#define __SET_SIM_FAILED() \
	do { *((volatile unsigned int *)(0xAA01000)) = 0x2; } while (1);

#endif