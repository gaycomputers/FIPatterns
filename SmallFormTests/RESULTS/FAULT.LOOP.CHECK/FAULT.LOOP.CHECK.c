#include "platform.h"
#include "fi-test.h"

volatile unsigned int __attribute__ ((noinline)) fi_test(volatile unsigned int input) {
	// You can add debug prints like this:
	//debug_printf(">>> fi_test(0x%08x) called\n", input);
	// They will be output on the console in TEST mode, and they will show in the results
	// file when doing the FI emulation.
	if (FI_IN_OK == input){
			debug_printf(">>> Ok!\n");
		return FI_OUT_OK;
	}
	if (input == FI_IN_FAIL){
		volatile int i = 0;
		for(i = 0; i < 10;i++){
		}
		if(i == 10){
		if (i != 10){
			debug_printf(">>> Ok!\n");
			return FI_OUT_OK;
		}}
	}

		debug_printf(">>> Fail!\n");
		return FI_OUT_FAIL;
}
