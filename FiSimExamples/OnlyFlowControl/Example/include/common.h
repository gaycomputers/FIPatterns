#ifndef H_COMMON
#define H_COMMON

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define IMG_LOAD_ADDR ((void*)0x32000000)
#define UART_OUT_BUF_ADDR ((void*)0x11000000)

/** otp.c **/
extern bool otp_init();
extern void otp_get_img_hash(unsigned char* img_hash);
extern void otp_burn_img_hash(unsigned char* img_hash);
extern void otp_is_sec_boot_enabled(bool* is_enabled);
extern bool otp_sec_boot_enable();
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