char eucDataArray[20];
char eucTempDataArray[20];

void driverRunOnStartup() {
    Serial.begin(115200);
    arduinoLED.displayString("cw");
}

int eucLightStripSpeed() {
    
}



void eucCollectData() {
    //String incomingData = Serial.readStringUntil('5A5A5A5A');
    
    //int speed = incomingData.substring();
}

int eucDeviceSpeed;

String eucDeviceState() {

}