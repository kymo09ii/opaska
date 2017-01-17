#include <CurieBLE.h>

BLEPeripheral blePeripheral;         // BLE Peripheral Device (the board you're programming)
BLEService heartRateService("180D"); // BLE Heart Rate Service

// BLE Heart Rate Measurement Characteristic"
BLECharacteristic heartRateChar("2A37",  // standard 16-bit characteristic UUID
    BLERead | BLENotify, 2);  // remote clients will be able to get notifications if this characteristic changes
                              // the characteristic is 2 bytes long as the first field needs to be "Flags" as per BLE specifications
                              // https://developer.bluetooth.org/gatt/characteristics/Pages/CharacteristicViewer.aspx?u=org.bluetooth.characteristic.heart_rate_measurement.xml


void BLEserceSetup() {
  /* Set a local name for the BLE device
     This name will appear in advertising packets
     and can be used by remote devices to identify this BLE device
     The name can be changed but maybe be truncated based on space left in advertisement packet */
blePeripheral.setLocalName("HeartRateSketch");
blePeripheral.setAdvertisedServiceUuid(heartRateService.uuid());  // add the service UUID
blePeripheral.addAttribute(heartRateService);   // Add the BLE Heart Rate service
blePeripheral.addAttribute(heartRateChar); // add the Heart Rate Measurement characteristic
  /* Now activate the BLE device.  It will start continuously transmitting BLE
     advertising packets and will be visible to remote BLE central devices
     until it receives a new connection */
blePeripheral.begin();
Serial.println("Bluetooth device active, waiting for connections...");
}

void BLEserceLoop(){
  BLECentral central = blePeripheral.central(); // listen for BLE peripherals to connect:
  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central (BLEserce): ");
    Serial.println(central.address());    // print the central's MAC address:
    digitalWrite(12, HIGH);           // wyjscie na pin 2 ze jest BLE
    // check the heart rate measurement every 200ms as long as the central is still connected:
    while (central.connected()) {
     serialOutputWhenBeatHappens();
     Serial.println("lubie placki");
    }
    // when the central disconnects, turn off the LED:
    digitalWrite(13, LOW);
    Serial.print("Disconnected from central (BLEserce): ");
    Serial.println(central.address());
  }
  
}


//////////////////////////////////////////////////////////////////////////
/*
//////////////////////
void updateHeartRate() {
  // Read the current voltage level on the A0 analog input pin.
   //  This is used here to simulate the heart rate's measurement.
 
  int heartRateMeasurement = analogRead(A0);
  Serial.println(heartRateMeasurement);
  int heartRate = map(heartRateMeasurement, 0, 1023, 0, 100);
  if (heartRate != oldHeartRate) {      // if the heart rate has changed
    Serial.print("Heart Rate is now: "); // print it
    Serial.println(heartRate);
    const unsigned char heartRateCharArray[2] = { 0, (char)heartRate };
    heartRateChar.setValue(heartRateCharArray, 2);  // and update the heart rate measurement characteristic
    oldHeartRate = heartRate;           // save the level for next comparison
  }
}

*/
