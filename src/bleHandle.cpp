#include "bleHandle.h"


void ClientCallback::onConnect(BLEClient *pclient){
  M5.Lcd.drawString("onConnect...", 30, 100);
  deviceConnected = true;
}

void ClientCallback::onDisconnect(BLEClient *pclient){
  M5.Lcd.drawString("onConnect...", 30, 100);
  deviceConnected = false;
}

void CharacteristicCallback::onWrite(BLECharacteristic *pCharacteristic) {
  M5.Lcd.drawString("onWrite...", 30, 100);
  String value = pCharacteristic->getValue().c_str();
  M5.Lcd.drawString(value, 50, 100);
}

void CharacteristicCallback::onRead(BLECharacteristic *pCharacteristic) {
  pCharacteristic->setValue("Hello World!");
}


// void AdvertisedDeviceCallbacks::onResult(BLEAdvertisedDevice advertisedDevice) {
//   if (advertisedDevice.haveName()){
//     pBLEAdvertiesdDeviceList.push_back(advertisedDevice);
//   }
// }

void BLEControl::BLEStart(){
  BLEDevice::init(CENTRAL_NAME);
  pServer = BLEDevice::createServer();
  pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_WRITE | 
        BLECharacteristic::PROPERTY_READ  |
        BLECharacteristic::PROPERTY_NOTIFY    
      );

  pCharacteristic->setCallbacks(new CharacteristicCallback());
  pCharacteristic->addDescriptor(new BLE2902());
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
}

void BLEControl::BLEEnd(){
  BLEDevice::deinit();
}
