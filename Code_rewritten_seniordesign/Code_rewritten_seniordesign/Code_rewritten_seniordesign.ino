// library that contains Genie class for the touchscreen
#include <genieArduino.h> 
// instantiate genie object
Genie genie;
// run the reset of the touchscreen and Arduino through digital pin #4
#define RESETLINE 4

// library that contains Testing class
#include "Testing.h"
// instantiate pressure signal object on analog pin A3
Testing pressureTrans(A3)

void setup(){
  Serial.begin(115200);
  genie.Begin(Serial);
  genie.AttachEventHandler(myGenieEventHandler);
  pinMode(4, OUTPUT); // reset line
  // touchscreen and Arduino are reset when turned on
  digitalWrite(RESETLINE, 1)
  delay(100);
  digitalWrite(RESETLINE, 0);
  delay(3500);
  genie.WriteContrast(1);
  // Display TestID form on touchscreen
  genie.WriteObject(GENIE_OBJ_FORM, 0x00, 0);
}

void loop(){
  
  /* ==== Entering Test ID and Rest Time ====
   * Before testing can begin:
   *        ID needs to be entered
   *        Rest time needs to be entered
   *        "Begin Testing" button needs to be pressed
   */
   
   genie.DoEvents();
   if (genie.id_entered == true){
     genie.SwitchScreen_rest()
   }
   genie.DoEvents();
   if (genie.rest_entered == true){
     genie.SwitchScreen_begintesting() 
   }
   genie.DoEvents();
   if (genie.begin_pressed == true){
     genie.SwitchScreen_testform() 
   }
   
   /* ==== Testing Procedure ====
    *        Patient is tested for 7.5 seconds, saving the maximum pressure value measured
    *        Device goes into an untestable mode until the rest time has expired
    *        Need to perform at least 3 tests
    */
    
    pressureTrans.test();
    genie.SwitchScreen_resting();
    
    if (pressureTrans.number_trials < 3) {
      Retest();
    }
    
    /* ==== Is more testing needed? ====
     *        If the recorded pressure is still increasing after successive trials,
     *        more tests will be done until the recorded pressure has begun
     *        to decrease, allowing up to a maximum of 6 trials.  After which the
     *        average, standard deviation, and coefficient are calculated and displayed
     *        on the touchscreen.
     */
     
     else if (pressureTrans.pressure_values[pressureTrans.number_trials-1] > pressureTrans.pressure_values[pressureTrans.number_trials-2] && pressureTrans.number_trials < 6) {
       Retest();
     }
     
     else {
       pressureTrans.calculate_stats();
       DisplayResults();
     }
     
     /* ==== Further Testing ====
      *        From the results screen, the user can select to go through
      *        the testing process again, starting with the patient ID.
      */
      
      genie.DoEvents();
      if (test_from_start == true) {
        genie.StartOver();
      }
      
}

void Retest() {
  genie.SwitchScreen_retest;
  pressureTrans.test();
  genie.SwitchScreen_resting();
}

void DisplayResults() {
  genie.WriteObject(GENIE_OBJ_FORM, 0x06, 0); // go to Calculate Results form
  //Write mean, standard deviation, coefficient of variation, and average rest time to the Screen
  genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x03, pressureTrans.average_pressure*100.0);
  genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x04, pressureTrans.standard_deviation*100.0);
  genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x05, pressureTrans.coef_var*100.0);
  genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x06, (genie.total_rest/(pressureTrans.number_trials-1))*100.0);
}
