char eucDataArray[]

void driverRunOnStartup() {
    uart.begin(115200);
}

int eucLightStripSpeed() {
    
}

void eucCollectData() {
    if (uart.parsePacket((int*)eucDataArray)) {

    }
}

int eucDeviceSpeed;

char eucDeviceState() {

}

