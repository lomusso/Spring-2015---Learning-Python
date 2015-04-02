// These functions belong in the Genie library.

void Genie::SwitchScreen_rest() {
     id_entered = false; //reset the button to false
     genie.WriteObject(GENIE_OBJ_WINBUTTON, 0x00, 0); //reset button to false
     patient_ID = _digitstowrite; //store entered digits as the patient ID
     genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x00, 0); //reset patient ID digits to be 0
     genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x01, 0); //ensure that rest time digits are 0
     _digitstowrite = 0; //reset digitstowrite to zero
     genie.WriteObject(GENIE_OBJ_FORM, 0x01, 0); //go to RestTime form
}

void Genie::SwitchScreen_begintesting() {
     rest_entered = false; //Reset Done button to false
     genie.WriteObject(GENIE_OBJ_WINBUTTON, 0x01, 0);  //Reset Done Button
     rest_time = _digitstowrite; //use user input to set the rest time
     genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x00, 0); //reset TestID digits to 0
     genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x01, 0); //reset RestTime digits to 0
     _digitstowrite = 0; //reset digitstowrite to 0
     genie.WriteObject(GENIE_OBJ_FORM, 0x02, 0); //go to Begin Testing form
}

void Genie::SwitchScreen_testform() {
     begin_pressed = false; //Reset button to FALSE
     genie.WriteObject(GENIE_OBJ_WINBUTTON, 0x02, 0); //Reset button to 0
     genie.WriteObject(GENIE_OBJ_FORM, 0x03, 0); //go to Testing from
}

void Genie::SwitchScreen_resting() {
	genie.WriteObject(GENIE_OBJ_FORM, 0x04, 0); //Write Resting form
	_start_rest = (float)millis();
	while (_time_now < _start_rest + (rest_time*1000)) {
		_time_now = millis();
	}
}

void Genie::SwitchScreen_retest() {
	genie.WriteObject(GENIE_OBJ_FORM, 0x05, 0); //go to Retest Form
	genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x02, pressure); // Write maximum pressure to LED digits
	genie.DoEvents();
	if(test_again == true){ //If Test Again button pressed
    	//Reset Buttons
    	test_again = false;
    	genie.WriteObject(GENIE_OBJ_WINBUTTON, 0x03, 0); 
    	total_rest = total_rest + (millis() - _start_rest)/1000; //Calculate how long the patient rested
    	genie.WriteObject(GENIE_OBJ_FORM, 0x03, 0); // go to Testing form
    }
}

void myGenieEventHandler(void)
{
  genieFrame Event; //Grab the next event on the stack
  genie.DequeueEvent(&Event); //Store it and remove it

  if (Event.reportObject.cmd == GENIE_REPORT_EVENT) //If the cmd received is from a Reported Event
  {

    if (Event.reportObject.object == GENIE_OBJ_WINBUTTON) //If the Reported Message was from a winbutton
    { //Code for buttons
      ButtonPressed = TRUE;
      if (Event.reportObject.index == 0) // index 0
     {
        id_entered = TRUE; 
      }
     if (Event.reportObject.index == 1)
      {
       rest_entered = TRUE;
      } 
           if (Event.reportObject.index == 2)
      {
       begin_pressed = TRUE;
      } 
           if (Event.reportObject.index == 3)
      {
       test_again = TRUE;
      } 
           if (Event.reportObject.index == 4)
      {
       store_data = TRUE;
      } 
           if (Event.reportObject.index == 5)
      {
       test_from_start = TRUE;
      } 
    }
    else if (Event.reportObject.object == GENIE_OBJ_KEYBOARD) // code for keyboard
    {
     int key = genie.GetEventData(&Event);
        if(key != 10){
          digitstowrite = digitstowrite*10 + key;
        
        }
        else{
          int remainder = digitstowrite%10;
          digitstowrite = digitstowrite - remainder;
          digitstowrite = digitstowrite/10;
        }
        if(Event.reportObject.index == 0){
        if(digitstowrite <= 9999){
          genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x00, digitstowrite);
        }
        }
        else if(Event.reportObject.index == 1){
        if(digitstowrite<= 999){
          genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x01, digitstowrite);
        }  
        }
      }
  }
}

void Genie::StartOver() {
    test_from_start = false
    genie.WriteObject(GENIE_OBJ_WINBUTTON, 0x04, 0);
    genie.WriteObject(GENIE_OBJ_WINBUTTON, 0x05, 0);
    genie.WriteObject(GENIE_OBJ_FORM, 0x00, 0); //go to TestID screen
}
