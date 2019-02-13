
unsigned int 
diag_asia_fibre_sram_test( UINT32 * start, UINT32 length )
{

#define PATTERN_1 0xAA55AACC

register UINT32   *  src_ptr;
register UINT32      loop_length;
register UINT32      xx, expd, recd;

   expd = recd = 0;
   
/*-------------------------------------------------------------------
*   Setup the RAM test.
*------------------------------------------------------------------*/

   src_ptr = (UINT32*)start;
   /* Length specifies 4 byte words, length is modulo 4. */
   loop_length = (length & 0xFFFFFFFC) / 4;

/*-------------------------------------------------------------------
*   Run the RAM test.
*------------------------------------------------------------------*/

   /* PASS1, fill the array, address ascending. */
   for ( xx = 0; xx < loop_length; xx++ )
   {
      *src_ptr++ = PATTERN_1;
   }

   /* PASS2, read/invert/write, address descending. */
   src_ptr = (UINT32*)((UINT32)start + length);
   for ( xx = 0; xx < loop_length; xx++ )
   {
      src_ptr--;
      if( *src_ptr != PATTERN_1)
      {
         recd = *src_ptr;
         expd = PATTERN_1;
         *Asia_sim_verilog_ctl_1_rw = diag_output.failed_register = (UINT32)src_ptr;
         goto error_end;
      }
      
      *src_ptr = ~PATTERN_1;
   }

   /* PASS3, read/invert/write, address ascending. */
   src_ptr = (UINT32*)start;
   for ( xx = 0; xx < loop_length; xx++ )
   {
      if( *src_ptr != ~PATTERN_1)
      {
         recd = *src_ptr;
         expd = ~PATTERN_1;
         *Asia_sim_verilog_ctl_1_rw = diag_output.failed_register = (UINT32)src_ptr;
         goto error_end;
      }
      
      *src_ptr++ = PATTERN_1;
   }

   /* PASS4, read, address descending. */
   src_ptr = (UINT32*)((UINT32)start + length);
   for ( xx = 0; xx < loop_length; xx++ )
   {
      src_ptr--;
      if( *src_ptr != PATTERN_1)
      {
         recd = *src_ptr;
         expd = PATTERN_1;
         *Asia_sim_verilog_ctl_1_rw = diag_output.failed_register = (UINT32)src_ptr;
         goto error_end;
      }      
   }


   return( DIAG_PASS );


   }
         

/*-------------------------------------------------------------------
*-------------------------------------------------------------------*
*   A fault was detected.
*-------------------------------------------------------------------*
*------------------------------------------------------------------*/
         
   error_end:
      
   return( DIAG_FAIL );         /*diags return fail status*/

           
} /* End of function diag_asia_fibre_sram_test */
