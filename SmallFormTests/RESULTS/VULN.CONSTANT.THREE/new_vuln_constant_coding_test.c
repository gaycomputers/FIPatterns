#include "platform.h"
#include "fi-test.h"
#define good 0x51236784
#define bad 0x48763215
volatile unsigned int __attribute__ ((noinline)) fi_test(volatile unsigned int input) {
	// You can add debug prints like this:
	//debug_printf(">>> fi_test(0x%08x) called\n", input);
	// They will be output on the console in TEST mode, and they will show in the results
	// file when doing the FI emulation.
	//volatile int good = 305419896; //(0x12345678);
	//volatile int bad = 2271560481; //(0x87654321);
	volatile int value = bad; //false
	if (input == FI_IN_OK){
		value = good;
	}
	if (value == good){
			debug_printf(">>> Ok!\n");
			return FI_OUT_OK;
	} else {
		debug_printf(">>> Fail!\n");
		return FI_OUT_FAIL;
	}
}
