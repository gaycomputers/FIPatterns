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

void __attribute__ ((noinline)) boot_next_stage(void) {
	// Indicate we successfully bypassed the signature verification
	//this next line is proof im actually insane, it prints the binary value of an integer i didnt have printf for
	//if ( 0b1000000000000000 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0100000000000000 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0010000000000000 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0001000000000000 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0000100000000000 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0000010000000000 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0000001000000000 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0000000100000000 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0000000010000000 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0000000001000000 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0000000000100000 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0000000000010000 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0000000000001000 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0000000000000100 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0000000000000010 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}if ( 0b0000000000000001 & METHOD_TOTAL){serial_putc('1');}else{serial_putc('0');}serial_putc('\n');
	if(METHOD_TOTAL ==  34588 ){
		if(~METHOD_TOTAL == ~34588 ){
			__SET_SIM_SUCCESS();
		}
	}
	serial_puts("Fault detected with flow control!\n");
	__SET_SIM_FAILED();
}

void bl1_entry() {
	MD5_CTX ctx;
	MD5_CTX ctx_sec;//for future FAULT.CRYPTO.CHECK
	unsigned char img_hash[16];
	unsigned char img_hash_sec[16];//for future FAULT.CRYPTO.CHECK
	unsigned char otp_img_hash[16];
	volatile int is_sec_boot_en = DISABLED;
	if(~is_sec_boot_en != ~DISABLED){//An experimental value check XXXJOSH
		serial_puts("Fault detected!\n");
		__SET_SIM_FAILED();
	}
	
	void* img_base = IMG_LOAD_ADDR;
	void* img_base_sec = IMG_LOAD_ADDR;//for future FAULT.CRYPTO.CHECK
	size_t img_size;
	size_t img_size_sec;//for future FAULT.CRYPTO.CHECK
	
	otp_init();
	
	otp_is_sec_boot_enabled(&is_sec_boot_en);
	int is_sec_boot_en_checksum = ~is_sec_boot_en;
	if (is_sec_boot_en_checksum == ~DISABLED) {//favor anti positives
		if(is_sec_boot_en == DISABLED){//FAULT.DECISION.CHECK
			serial_puts("Wimpy nonsecure boot\n");
			goto do_boot;
		}
		else{
			serial_puts("Fault detected!\n");
			__SET_SIM_FAILED();
		}
	}
	
	serial_puts("Start Secure Boot...\n");
	volatile int otp_get_has = otp_get_img_hash(otp_img_hash);
	volatile int otp_get_has_checksum = ~otp_get_img_hash(otp_img_hash);
	if ((otp_get_has_checksum == ~FAILURE) || (otp_get_has == FAILURE) || (otp_get_has_checksum != ~otp_get_has)){ //FAULT.VALUE.CHECK
		serial_puts("Fault detected!\n");
		__SET_SIM_FAILED();
	}
	
	flash_load_img(img_base, &img_size);
	flash_load_img(img_base_sec, &img_size_sec); //for future FAULT.CRYPTO.CHECK
	
	MD5_Init(&ctx);
	MD5_Update(&ctx, img_base, img_size);
	MD5_Final(img_hash, &ctx);
	
	//basic FAULT.CRYPTO.CHECK
	MD5_Init(&ctx_sec);
	MD5_Update(&ctx_sec, img_base_sec, img_size_sec);
	MD5_Final(img_hash_sec, &ctx_sec);
	if((memcmp(img_hash, img_hash_sec, sizeof(img_hash)) != ZERO)){
		serial_puts("Auth failed!\n");
		__SET_SIM_FAILED();
	}
	//back to scheduled programming
	if((is_sec_boot_en != DISABLED) && (memcmp(img_hash, otp_img_hash, sizeof(otp_img_hash)) != ZERO )) {
		serial_puts("Auth failed!\n");
		__SET_SIM_FAILED();
	}
	if((~is_sec_boot_en != ~DISABLED) && (memcmp(img_hash, otp_img_hash, sizeof(otp_img_hash)) != ZERO )) {//FAULT.VALUE.CHECK
		serial_puts("Auth failed!\n");
		__SET_SIM_FAILED();
	}
	
do_boot:
	if(METHOD_TOTAL ==  34588 ){
		if(~METHOD_TOTAL == ~34588 ){
			serial_puts("Boot next stage\n");
			boot_next_stage();
		}
	}
	serial_puts("Auth failed!\n");
	__SET_SIM_FAILED();
}