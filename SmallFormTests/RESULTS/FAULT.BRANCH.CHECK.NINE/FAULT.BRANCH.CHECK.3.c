#include "platform.h"
#include "fi-test.h"
volatile unsigned int __attribute__ ((noinline)) fi_test(volatile unsigned int input) {
	// You can add debug prints like this:
	//debug_printf(">>> fi_test(0x%08x) called\n", input);
	// They will be output on the console in TEST mode, and they will show in the results
	// file when doing the FI emulation.
	switch(input){
		case 2271560481:
			if (~input == 2023406814){
				debug_printf(">>> Ok!\n");
				return FI_OUT_OK;
			}
			else{
				return FI_OUT_FAIL;
			} break;
		case 305419896:
			return FI_OUT_FAIL;
		default:
			debug_printf(">>> Fail!\n");
			return FI_OUT_FAIL;
	}
}
