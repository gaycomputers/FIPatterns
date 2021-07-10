#include "platform.h"
#include "fi-test.h"
volatile unsigned int __attribute__ ((noinline)) fi_test(volatile unsigned int input) {
	// You can add debug prints like this:
	//debug_printf(">>> fi_test(0x%08x) called\n", input);
	// They will be output on the console in TEST mode, and they will show in the results
	// file when doing the FI emulation.
	int volatile inputxor = 2023406814;
	switch(input){
		case 2271560481:
			if (~input == inputxor){
				debug_printf(">>> Ok!\n");
				return FI_OUT_OK;
			}
			else{
				return FI_OUT_FAIL;
			} break;
		default:
			debug_printf(">>> Fail!\n");
			return FI_OUT_FAIL;
	}
}
