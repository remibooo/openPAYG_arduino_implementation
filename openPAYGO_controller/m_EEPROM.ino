// --- EEPROM

void storeDataToEeprom() {
  EEPROM.put(SERIAL_COUNT_ADDRESS,serialCount);
  EEPROM.put(SERIAL_NUMBER_ADDRESS, serialNumber);
  EEPROM.put(STARTING_CODE_ADDRESS, startingCode);
  EEPROM.put(SECRET_KEY_ADDRESS, secretKey);
  EEPROM.put(LAST_COUNT_ADDRESS,lastCount); 
  Serial.println("Data saved in EEPROM");
}

void storeTimeStampEEPROM(uint32_t timeStampInSeconds){
  EEPROM.put(LAST_TIME_STAMP_ADDRESS, timeStampInSeconds);
}

void storeNbDisconnectionsEEPROM(){
  EEPROM.put(NB_DISCONNECTIONS_ADDRESS, nbDisconnections);
}


void getDataEeprom()
/*
 * get all the data from the EEPROM and put it in the associated RAM variables
 */
{
  EEPROM.get(SERIAL_NUMBER_ADDRESS, serialNumber);
  EEPROM.get(STARTING_CODE_ADDRESS, startingCode);
  EEPROM.get(SECRET_KEY_ADDRESS, secretKey);
  EEPROM.get(LAST_COUNT_ADDRESS,lastCount);
  EEPROM.get(LAST_TIME_STAMP_ADDRESS,lastTimeStampInSeconds);
  EEPROM.get(PAYG_DISABLED_ADDRESS,paygDisabled);
  EEPROM.get(NB_DISCONNECTIONS_ADDRESS,nbDisconnections);
}


void enablePaygInEeprom()
/*
 * if paygDisabled is at 1, it puts it back to 0 in the RAM and in the EEPROM
 */
{
  if (paygDisabled == 1){
    paygDisabled = 0;
    EEPROM.put(PAYG_DISABLED_ADDRESS, paygDisabled);
  }
}


void incrementNbDisconnectionsEeprom(){
  Serial.println("Disconnection spotted!!"); // will be displayed if DEBUG_MODE is uncommented
  getDataEeprom(); // just to be sure we have the proper nb of disconnections
  nbDisconnections++;
  storeNbDisconnectionsEEPROM();
}
