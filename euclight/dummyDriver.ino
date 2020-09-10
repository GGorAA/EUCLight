char eucDataArray[20];
char eucTempDataArray[20];

void driverRunOnStartup() {
    Serial.begin(115200);
    Serial.println("poweron");
}

int eucLightStripSpeed() {
    
}



void eucCollectData() {
    char Comp(char* This) {
        while (Serial.available() > 0) { // Don't read unless there you know there is data
            if(index < 19) // One less than the size of the array
                {
                    inChar = Serial.read(); // Read a character
                    inData[index] = inChar; // Store it
                    index++; // Increment where to write next
                    inData[index] = '\0'; // Null terminate the string
                }
        }

        if (strcmp(inData,This)  == 0) {
            for (int i=0;i<19;i++) {
                inData[i]=0;
            }
            index=0;
            return(0);
        } else {
            return(1);
        }
    }
    //String incomingData = Serial.readStringUntil('5A5A5A5A');
    
    //int speed = incomingData.substring();
}

int eucDeviceSpeed;

String eucDeviceState() {

}