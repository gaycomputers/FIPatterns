#include "platform.h"
#include "fi-test.h"
	bool check_Func(volatile unsigned int passed_input, volatile unsigned int passed_input2){
		if (passed_input == FI_IN_OK){
		if (passed_input2 == ~FI_IN_OK){
			return true;
		}
		}
		return false;
	}
volatile unsigned int __attribute__ ((noinline)) fi_test(volatile unsigned int input) {
	// You can add debug prints like this:
	//debug_printf(">>> fi_test(0x%08x) called\n", input);
	// They will be output on the console in TEST mode, and they will show in the results
	// file when doing the FI emulation.


	if (check_Func(input, ~input)){
			debug_printf(">>> Ok!\n");
			return FI_OUT_OK;
	} else {
		debug_printf(">>> Fail!\n");
		return FI_OUT_FAIL;
	}
}
