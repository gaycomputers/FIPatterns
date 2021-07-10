#include "platform.h"
#include "fi-test.h"
#define const_input (0x87654321)
volatile unsigned int __attribute__ ((noinline)) fi_test(volatile unsigned int input) {
	// You can add debug prints like this:
	//debug_printf(">>> fi_test(0x%08x) called\n", input);
	// They will be output on the console in TEST mode, and they will show in the results
	// file when doing the FI emulation.
	switch(input){
		case const_input:
				debug_printf(">>> Ok!\n");
				return FI_OUT_OK;
				break;
		default:
			debug_printf(">>> Fail!\n");
			return FI_OUT_FAIL;
	}
}
