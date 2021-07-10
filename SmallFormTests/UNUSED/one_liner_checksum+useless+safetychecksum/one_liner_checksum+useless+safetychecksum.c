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
	int safetyInt = 179820;
	if (input == FI_IN_OK && output == checksum){
		int safetyInt = 15216;
		debug_printf(">>> Ok!\n");
		if(safetyInt == 15216)
		return FI_OUT_OK;
		else 
		return FI_OUT_FAIL;
	} else {
		debug_printf(">>> Fail!\n");
		return FI_OUT_FAIL;
	}
}
