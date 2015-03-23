// These functions belong in the Genie library.

void Genie::SwitchScreen_rest() {
	 id_entered = false; //reset the button to false
     genie.WriteObject(GENIE_OBJ_WINBUTTON, 0x00, 0); //reset button to false
     testID = digitstowrite; //store entered digits as the patient ID
     genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x00, 0); //reset patient ID digits to be 0
     genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x01, 0); //ensure that rest time digits are 0
     digitstowrite = 0; //reset digitstowrite to zero
     genie.WriteObject(GENIE_OBJ_FORM, 0x01, 0); //go to RestTime form
}

void Genie::SwitchScreen_begintesting() {
	 rest_entered = false; //Reset Done button to false
     genie.WriteObject(GENIE_OBJ_WINBUTTON, 0x01, 0);  //Reset Done Button
     setresttime = digitstowrite; //use user input to set the rest time
     genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x00, 0); //reset TestID digits to 0
     genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0x01, 0); //reset RestTime digits to 0
     digitstowrite = 0; //reset digitstowrite to 0
     genie.WriteObject(GENIE_OBJ_FORM, 0x02, 0); //go to Begin Testing form
}

void Genie::SwitchScreen_testform() {
	 begin_pressed = false; //Reset button to FALSE
     genie.WriteObject(GENIE_OBJ_WINBUTTON, 0x02, 0); //Reset button to 0
     genie.WriteObject(GENIE_OBJ_FORM, 0x03, 0); //go to Testing from
}