#include "platform.h"
#include "fi-test.h"
#define METHOD1_STEP 13
#define METHOD2_STEP 17


int method1(int *counter){
	volatile int out = 3;
	*counter += METHOD1_STEP;
	return out;
	//return 1;
}
int method2(int *counter){
	volatile int out = 7;
	*counter += METHOD2_STEP;
	return out;
	//return 1;
}

volatile unsigned int __attribute__ ((noinline)) fi_test(volatile unsigned int input) {
	
	volatile int counter = 0;
	//volatile int junkspace = 0;
	if(input == FI_IN_OK){
		if(~input == ~FI_IN_OK){
			return FI_OUT_OK;
		}
	}
	if(method1(&counter) + method2(&counter) + method2(&counter) != 17){
		//junkspace += 4;
		//junkspace -= 5;
		//junkspace += 6;
		if (counter == (METHOD1_STEP + METHOD2_STEP*2)) return FI_OUT_OK;
	}
	return FI_OUT_FAIL;
}
