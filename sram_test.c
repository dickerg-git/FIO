
unsigned int 
sram_test( UINT32 * start, UINT32 length )
{

#define PATTERN_1 0xAA55AACC

register UINT32   *  src_ptr;
register UINT32      loop_length;
register UINT32      xx, expd, recd, fail;

   expd = recd = 0;
   fail = 0;
   
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
         fail = (UINT32)src_ptr;
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
         fail = (UINT32)src_ptr;
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
         fail = (UINT32)src_ptr;
         goto error_end;
      }      
   }


   return( fail );


   }
         

/*-------------------------------------------------------------------
*-------------------------------------------------------------------*
*   A fault was detected.
*-------------------------------------------------------------------*
*------------------------------------------------------------------*/
         
   error_end:
      
   return( fail );         /*diags return fail status*/

           
} /* End of function sram_test */
