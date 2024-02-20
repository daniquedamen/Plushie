/*
Last modified 06-12-23
Danique Damen (d.damen-1@studen.utwente.nl)

Summary file:
Begin advertising BLE service. Write to BLE characteristics. 4 sensors are read and written to chars in bytes.

Library used for display: https://github.com/olikraus/u8g2

*/

#include "BLE.h"
#include <U8g2lib.h>


U8G2_SSD1306_64X32_1F_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

// Constructor for the BLE server Class including randomly generated version 4 UUIDs
BLE_Class::BLE_Class() :
  Plushie_service("4bd03949-19ce-466a-9abc-c53119e26f87"),
  mic_char("a25deb7b-ec5e-456d-b6e8-f0d0a0d49bee", BLERead, 2),
  imu_char("01410ba7-23f7-4516-8f17-25d4ebd8421c", BLERead, 2),
  air_char("659b10eb-350e-484b-b447-549ad5a258c4", BLERead, 2),
  cap_char("c3c8e822-f1cc-4edd-8e16-3b8624e5d377", BLERead)
  {

  }


  // functions for the BLE connection
void BLE_Class::BLE_initialization()
{
  Serial.begin(9600);
  while(!BLE.begin()){

  }

  // set names
  BLE.setLocalName("Plushie");
  BLE.setDeviceName("MC Xiao");

  // / set service UUID used when advertising
  BLE.setAdvertisedService(Plushie_service); 
  

  // connect the characteristics to the service
  Plushie_service.addCharacteristic(mic_char);
  Plushie_service.addCharacteristic(imu_char);
  Plushie_service.addCharacteristic(cap_char);
  Plushie_service.addCharacteristic(air_char);
  // Add Service with characteristic to BLE
  BLE.addService(Plushie_service);


  // Initialize sensors
  air.air_initialization();
  imu.IMU_initialization();
  cap.cap_initialization();
  mic.mic_initialization();

  u8g2.begin();
  u8g2_prepare();
  u8g2.clearBuffer();
  

}

void BLE_Class::BLE_loop() 
{
  BLE.advertise(); // start advertising
  u8g2.drawStr(0,24,"Advertising"); 
  u8g2.sendBuffer();
  BLEDevice central = BLE.central(); // connected device is the central (note that central and client are both used terms.)

  if (central)
  {
    Serial.print("Connected to client: ");
    Serial.println(central.address());
    BLE.advertise();
    u8g2.clearBuffer();
    u8g2.drawStr(0,24,"Connected"); 
    u8g2.sendBuffer();

    while(central.connected()) {
      WriteInteract();

      BLE.advertise(); // If laptop stops, disconnection is not seen. Therefore, keep advertising for reconnection.
    }

    // when client disconnects, this is not seen
    Serial.print(F("Disconnected from client: "));
    Serial.println(central.address());
  }

}

void BLE_Class::ByteFunc(int value, byte BArray[2]){
  BArray[0] = (byte)(value & 0xFF);
  BArray[1] = (byte)(value >> 8 & 0xFF);
}

// If interaction changes, write to characteristic.
void BLE_Class::WriteInteract() 
{ 
  int microphonedata = mic.mic_peak();
  ByteFunc(microphonedata, BArrayMic);
  mic_char.writeValue(BArrayMic, 2);

  int imudata = imu.IMU_loop();
  ByteFunc(imudata, BArrayIMU);
  imu_char.writeValue(BArrayIMU, 2);

  int capdata = cap.cap_loop();
  Serial.println(capdata);
  cap_char.writeValue((byte)capdata);

  int airdata = air.air_loop();
  ByteFunc(airdata, BArrayAir);
  air_char.writeValue(BArrayAir, 2);
  
}
