char eucDataArray[20];
char eucTempDataArray[20];

void driverRunOnStartup() {
    Serial.begin(115200);
    arduinoLED.displayString("cw");
}

int eucLightStripSpeed() {
    
}



void eucCollectData() {
    //String incomingData = Serial.readStringUntil(0x5A5A5A5A);
    
    //int speed = incomingData.substring();
}

int eucDeviceSpeed;

int eucDeviceState() {
     /* 1 означает ускоряеться
      * 2 означает останавливаеться
      * 3 означает движеться назад
      * 4 означает торможит при движении назад
      * 5 означает остановился
      */
}