char eucDataArray[20];
char eucTempDataArray[20];

void driverRunOnStartup() {
    Serial.begin(115200);
}

int eucLightStripSpeed() {
    
}

void eucCollectData() {
    if (Serial.available()) {
        /*
        for (byte i = 0; i < 20; i++) { // цикл for который заполняет массив
            char incomingByte = Serial.read();
            eucDataArray[i] = incomingByte;
            if (
                i == 3 && 
                eucDataArray[1] == 0x5A && 
                eucDataArray[2] == 0x5A && 
                eucDataArray[3] == 0x5A
            ) {
                
            }
        }*/
        if (Serial.find(0x5A 0x5A, 2)) {

        }
        Serial.readBytes(eucDataArray, 20);
    }
}

int eucDeviceSpeed;

String eucDeviceState() {

}