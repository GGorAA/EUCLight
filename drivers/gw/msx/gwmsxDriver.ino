char eucDataArray[20]
char eucTempDataArray[20]

void driverRunOnStartup() {
    uart.begin(115200);
}

int eucLightStripSpeed() {
    
}

void eucCollectData() {
    if (uart.available()) {
        if (uart.parsePacket((int*)eucDataArray)) {
            for (byte i = 0; i < 20; i++) {
                
            }
            
        }
    }
}

int eucDeviceSpeed;

char eucDeviceState() {

}

