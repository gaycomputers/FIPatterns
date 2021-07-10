#include "common.h"
#include "md5.h"
int METHOD_1 = 47;
int METHOD_2 = 149;
int METHOD_3 = 257;
int METHOD_4 = 379;
int METHOD_5 = 491;
int METHOD_6 = 619;
int METHOD_7 = 757;
int METHOD_8 = 887;
int METHOD_9 = 1033;
int METHOD_10 = 1181;
int METHOD_11 = 1307;
int METHOD_12 = 1481;
int METHOD_13 = 1609;
int METHOD_14 = 1777;
int METHOD_15 = 1933;
int METHOD_16 = 2087;
volatile unsigned int METHOD_TOTAL = 0;

void __attribute__ ((noinline)) flash_load_img(void* base_addr, size_t* size_ptr) {
	*size_ptr = 16;
	METHOD_TOTAL += METHOD_1;
	// The engine will "magically" write some data to this location based on the hardware model
};

extern inline void __attribute__ ((always_inline)) boot_next_stage(void) {
	// Indicate we successfully bypassed the signature verification
	//if ( 0b1000000000000000 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0100000000000000 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0010000000000000 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0001000000000000 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0000100000000000 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0000010000000000 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0000001000000000 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0000000100000000 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0000000010000000 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0000000001000000 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0000000000100000 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0000000000010000 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0000000000001000 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0000000000000100 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0000000000000010 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0000000000000001 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}serial_putc('\n');

	if(METHOD_TOTAL ==  17037 ){
		if(~METHOD_TOTAL == ~17037 ){
			__SET_SIM_SUCCESS();
		}
	}
	
	serial_puts("Fault detected with flow control!\n");
	__SET_SIM_FAILED();
}

extern inline void __attribute__ ((always_inline)) bl1_entry() {
	MD5_CTX ctx;
	unsigned char img_hash[16];
	unsigned char otp_img_hash[16];
	bool is_sec_boot_en;
	
	void* img_base = IMG_LOAD_ADDR;
	size_t img_size;

	otp_init();
	
	otp_is_sec_boot_enabled(&is_sec_boot_en);
	
	if (!is_sec_boot_en) {
		goto do_boot;
	}
	
	serial_puts("Start Secure Boot...\n");
	
	otp_get_img_hash(otp_img_hash);
	
	flash_load_img(img_base, &img_size);
	
	MD5_Init(&ctx);
	MD5_Update(&ctx, img_base, img_size);
	MD5_Final(img_hash, &ctx);
	
	if(is_sec_boot_en && memcmp(img_hash, otp_img_hash, sizeof(otp_img_hash))) {
		serial_puts("Auth failed!\n");
		__SET_SIM_FAILED();
	}
	
do_boot:
	serial_puts("Boot next stage\n");

	boot_next_stage();
}