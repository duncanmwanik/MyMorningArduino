
extern BLEServer *pServer;
extern BLECharacteristic *pCharacteristic;
extern bool deviceConnected;
extern bool oldDeviceConnected;

extern String previous;
extern String current;

void setupBLE();
void checkForNewData();

void sendBatteryPercentage();
void sendAlarmList();