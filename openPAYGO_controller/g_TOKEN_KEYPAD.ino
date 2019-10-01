#ifdef MEMBRANE_KEYPAD_MODE

void initializeInterface()
{
  // nothing to initialize
}



bool isDataAvailable()
{
  key = 0; // make sure no char was stored in the variable before
  key = keypad.getKey();
  keyWaitingToBeRead = true;
  return(key);
 }


char getKeyPressed()
/*
 * returns the key pressed on the IR remote as a char (this function forces to put the key in a char, good practice)
 */
{
  char incomingByte;
  if (keyWaitingToBeRead == true){ // to deal with a case where a key was already read when the data availability was checked: bool isDataAvailable()
    incomingByte = key;
    key = '/';
    keyWaitingToBeRead = false;
  }
  else{
    incomingByte = keypad.getKey();
  }
  Serial.print("incoming byte = ");
  Serial.println(incomingByte);
  if (isAccepted(incomingByte)){
    return(incomingByte);
  }
  Serial.println("Char not accepted");
  return(NON_ACCEPTED_CHAR);
}




uint32_t getCode(){
  /*
   * get the coming 9 keys pressed and return the corresponding 9 digits number, as a uint32_t
   * if '*' is pressed during the process, the operation is cancelled and the function returns -1
   */
  uint32_t t0 = millis();
  int codeArray[9] = {0};
  int i;
  for (i = 0; i < 9; i++){
    while (isDataAvailable() == 0){
      if ((millis()-t0) > MAX_TIME_TOKEN_ENTRY*1000){
        return(EXCEEDED_TIME_TOKEN);
      }
    }
    char a = getKeyPressed();
    if (a == '*'){
      return(STAR_KEY_PRESSED);
    }
    else if (a == NON_ACCEPTED_CHAR){
      i--; // if the char was not valid, the user should press the key again
    }
    else if (a != '\n'){
      codeArray[i] = (int)(a-'0'); // convert ascii into int
    }
  }
  return(convertArrayToUint32(codeArray));
}

#endif
