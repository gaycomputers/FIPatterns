#include "platform.h"
#include "fi-test.h"

volatile unsigned int __attribute__ ((noinline)) fi_test(volatile unsigned int input) {
	// You can add debug prints like this:
	//debug_printf(">>> fi_test(0x%08x) called\n", input);
	// They will be output on the console in TEST mode, and they will show in the results
	// file when doing the FI emulation.

	// Simple check, sensitive to faults
	// If you want to fix this, do the if statement twice
	volatile unsigned int output = ~input;
	int checksum = ~FI_IN_OK;
	if (input == FI_IN_OK && output == checksum){
		//if (output == checksum) {
			debug_printf(">>> Ok!\n");
			return FI_OUT_OK;
		//}
		
	} else {
		debug_printf(">>> Fail!\n");
		return FI_OUT_FAIL;
	}
}
