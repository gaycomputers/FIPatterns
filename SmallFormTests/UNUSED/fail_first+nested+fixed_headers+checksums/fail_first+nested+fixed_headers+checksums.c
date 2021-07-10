#include "platform.h"
#include "fi-test.h"

volatile unsigned int __attribute__((noinline)) fi_test(volatile unsigned int input)
{
   // You can add debug prints like this:
   //debug_printf(">>> fi_test(0x%08x) called\n", input);
   // They will be output on the console in TEST mode, and they will show in the results
   // file when doing the FI emulation.
   // Simple check, sensitive to faults
   // If you want to fix this, do the if statement twice
   volatile unsigned int output = ~input;
   unsigned int checksum = ~FI_IN_OK;
   if (input != FI_IN_OK)
   {
      if (output != checksum)
      {
         return FI_OUT_FAIL;
      }
      else
         return FI_OUT_FAIL;
   }
   else
   {
      if (input == FI_IN_OK)
      {
         if (output == checksum)
         {
            return FI_OUT_OK;
         }
         else
            return FI_OUT_FAIL;
      }
      else
      {
         return FI_OUT_FAIL;
      }
      
   }
}
