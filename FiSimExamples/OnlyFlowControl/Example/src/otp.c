#include <stdbool.h>
#include <stdint.h>
#include <common.h>

#define OTP_BASE (0x12000000)

enum OTP_CMD {
	OTP_CMD_INIT = 1,
	OTP_CMD_READ,
	OTP_CMD_WRITE
};

struct otp_ctrl_reg {
	uint32_t status;
	uint32_t cmd;
	uint32_t address;
	uint32_t data;
};
 bool otp_init() {
	volatile struct otp_ctrl_reg* volatile otp_ctrl = (volatile struct otp_ctrl_reg* volatile)OTP_BASE;
	
	otp_ctrl->cmd = OTP_CMD_INIT;
	
	while ((otp_ctrl->status & 0x4)) {}
	METHOD_TOTAL += METHOD_3;
	return (otp_ctrl->status & 0x2) != 0;
}

inline bool __attribute__ ((always_inline)) otp_read32(uint32_t otp_address, uint32_t* val) {
	volatile struct otp_ctrl_reg* volatile otp_ctrl = (volatile struct otp_ctrl_reg* volatile)OTP_BASE;
	METHOD_TOTAL += METHOD_4;
	if (!(otp_ctrl->status & 0x2)) {
		return false;
	}
	
	otp_ctrl->address = otp_address;
	otp_ctrl->cmd = OTP_CMD_READ;
	
	while ((otp_ctrl->status & 0x4)) {}
	
	if ((otp_ctrl->status & 0x1)) { // ERROR
		return false;
	}
	
	*val = otp_ctrl->data;
	
	return true;
}

inline bool __attribute__ ((always_inline)) otp_write32(uint32_t otp_address, volatile uint32_t data) {
	volatile struct otp_ctrl_reg* volatile otp_ctrl = (volatile struct otp_ctrl_reg* volatile)OTP_BASE;
	
	otp_ctrl->address = otp_address;
	otp_ctrl->data = data;
	otp_ctrl->cmd = OTP_CMD_WRITE;
	
	while ((otp_ctrl->status & 0x4)) {}
	METHOD_TOTAL += METHOD_5;
	if ((otp_ctrl->status & 0x1)) { // ERROR
		return false;
	}
	
	return otp_ctrl->data == data;
}

 void otp_get_img_hash(unsigned char* img_hash) {
	for (unsigned i = 0; i < 16; i+= 4) {
		otp_read32(0x20 + i, (void*)&img_hash[i]);
	}
	METHOD_TOTAL += METHOD_6;
}

inline void __attribute__ ((always_inline)) otp_burn_img_hash(unsigned char* img_hash) {
	for (unsigned i = 0; i < 16; i+= 4) {
		otp_write32(0x20 + i, *(uint32_t*)&img_hash[i]);
	}
}

void otp_is_sec_boot_enabled(bool* is_enabled) {
	uint32_t val;
	METHOD_TOTAL += METHOD_7;
	if (!otp_read32(0x10, &val)) {
		return;
	}
	
	*is_enabled = val & (0x1 << 17);
}

inline bool __attribute__ ((always_inline)) otp_sec_boot_enable() {
	uint32_t val;
	METHOD_TOTAL += METHOD_9;
	if (!otp_read32(0x10, &val)) {
		return false;
	}
	
	val |= (0x1 << 17);
	
	return otp_write32(0x10, val);
}