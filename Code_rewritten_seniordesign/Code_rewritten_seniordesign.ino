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
}

void loop(){
  // display TestID form on touchscreen
  genie.WriteObject(GENIE_OBJ_FORM, 0x00, 0);
  
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
    *        Patient is tested for 7.5 seconds
    *        Device goes into an untestable mode until the rest time has expired
    *        Need to perform at least 3 tests and at most 6
    */
    
    pressureTrans.test();
    genie.WriteObject(GENIE_OBJ_FORM, 0x04, 0);
    pressureTrans.rest();
    

    
   

   
   
