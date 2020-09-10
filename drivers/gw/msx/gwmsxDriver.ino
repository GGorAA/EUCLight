char eucDataArray[20];
char eucTempDataArray[20];

void driverRunOnStartup() {
    Serial.begin(115200);
}

int eucLightStripSpeed() {
    
}

void eucCollectData() {
    while (!Serial.available());

    String incomingData = Serial.readStringUntil('5A5A5A5A')

    int speed = incomingData.substring()
    //Serial.readBytes(eucDataArray, 20);
}

int eucDeviceSpeed;

String eucDeviceState() {

}