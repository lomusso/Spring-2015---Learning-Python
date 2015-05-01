// library that contains Shield class
#include "Shield.h"
// instantiate shield object
Shield shield;

// library that contains Testing class
#include "Testing.h"
// instantiate pressure signal object on analog pin A3
Testing pressureTrans(A3)

void setup(){
  shield.reset();
  pressureTrans.reset();
}

void loop(){
  
  shield.StartScreen();
   
   /* ==== Testing Procedure ====
    *        Patient is tested for 7.5 seconds, saving the maximum pressure value measured
    *        Device goes into an untestable mode until the rest time has expired
    *        Need to perform at least 3 tests
    */
   
   pressureTrans.test();
   shield.RestScreen();
        
   if (pressureTrans.number_trials < 3) {
     Retest();
   }
       
    /* ==== Is more testing needed? ====
     *        If the recorded pressure is still increasing after successive trials,
     *        more tests will be done until the recorded pressure has begun
     *        to decrease, allowing up to a maximum of 6 trials.
     */
     
     else if (pressureTrans.pressure_values[pressureTrans.number_trials-1] > pressureTrans.pressure_values[pressureTrans.number_trials-2] && pressureTrans.number_trials < 6) {
       Retest();
     }

     else {
       pressureTrans.calculate_stats();
       shield.DisplayResults();
     }
     
     /* ==== Further Testing ====
      *        From the start screen, the user can select to go
      *        through the testing process again.
      */
      
      shield.reset();
      pressureTrans.reset();
      
}

void Retest() {
  shield.StartScreen();
  pressureTrans.test();  
  shield.RestScreen();
}


