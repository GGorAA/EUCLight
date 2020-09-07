#define DEBUG_ENABLED true // запуск режима отладки. 
#define LIGHTS_PIN 1 // пин, к которому подключена лента

void setup() {
  if (DEBUG_ENABLED == true) {
    setupSerial();
  }
}

void loop() {
  
}