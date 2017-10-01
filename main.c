/*----------------------------------------------------------------------------
LAB EXERCISE 5.2 - SQUARE ROOT APPROXIMATION
 ----------------------------------------
Write an assembly code subroutine to approximate the square root of an 
argument using the bisection method. All math is done with integers, so the 
resulting square root will also be an integer

GOOD LUCK!
 *----------------------------------------------------------------------------*/

__asm int my_sqrt(int x){
	PUSH {r4,r5,r6,r7,r8,r9} ; Push r4-r9 registers onto the stack to save their states
	; This block will initialize all variables needed for the main functionality
	MOVS r1, #0 ; Use r1 for "done." Initializing it to 0
	MOVS r2, #0 ; Use r2 for "a." Initializing it to 0
	MOVS r3, #256 ; Use r3 for "b." Initializing it to 256 (Largest possible value)
	MOVS r4, #-1 ; Use r4 for "c." Initializing it to -1
	MOVS r7, #2 ; Set r7 to 2 for use in division later
	
do_while
	ADDS r5, r4, #0 ; Use r5 for "c_old" and set it to "c" (r4) at the start of every loop
	ADDS r6, r2, r3 ; Use r6 for the sum of "a" (r2) and "b" (r3)
	UDIV r4, r6, r7 ; Divide r6 (a+b) by 2 (r7) and store in "c" (r4)
	MUL r6, r4, r4 ; Compute c*c and store the result in r6
	CMP r6, r0 ; if (c*c == x)
	BEQ done ; Exit the loop if true
	BLT set_a; else if (c*c < x) set a = c
	ADDS r3, r4, #0 ; b = c or r3 = r4
	B loop_conditions ; Test the loop conditions
	
set_a
	ADDS r2, r4, #0 ; set a = c
	B loop_conditions ; Test loop conditions
	
loop_conditions
	CMP r1, #0 ; if (done != 0)
	BNE done ; Exit the loop
	CMP r4, r5 ; if (c == c_old)
	BEQ done ; Exit the loop
	B do_while ; Else, continue with the loop
	
done
	ADDS r0, r4, #0 ; set x = c to return the result
	POP {r4,r5,r6,r7,r8,r9} ; Pop registers to return them to their previous values before exiting the subroutine
	BX lr ; Return to main

}

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/
int main(void){
	volatile int r, j=0;
	int i;
  r = my_sqrt(0);     // should be 0
  r = my_sqrt(25);    // should be 5
	r = my_sqrt(133); 	// should be 11
  for (i=0; i<10000; i++){
		r = my_sqrt(i);
    j+=r;
  }
	while(1)
		;
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2014*************************************
