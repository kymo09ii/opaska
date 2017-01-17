//changelog
/*
 * 
 * 
 */
#include <CurieTimerOne.h>
#include <BMI160.h>
#include <CurieIMU.h>
#include <CurieBLE.h>

#define SERIAL_PORT_LOG_ENABLE 1
                        
//=======================  Zmienne ==================================================================
int pulsePin = 0;              // Sygnal‚ czujnika pulsu
int blinkPin = 13;             // led pulsu
const int MiliSec = 1000;      // milisekunda
int time = MiliSec*2;          // przerwanie co 2 ms     
static boolean serialVisual = true;   //false dane w serialu | true rysowanie pulsu

//--- do przerwania ---
volatile boolean Pulse = false;     // flaga wykrycia pulsu - przerwanie
volatile boolean QS = false;        // flaga wykrycia pulsu - wyswietlanie
// ----- BLUETOOTH --------

//============================= setup ==========================================================================
void setup(){
//--- podstawa ---
pinMode(blinkPin,OUTPUT);         // deklaracja diody na puls
#ifdef SERIAL_PORT_LOG_ENABLE
  Serial.begin(115200);
  while (!Serial);                //start na otwarcie seriala
#endif

//BLEserceSetup();                   //setup bluetootha
krokiSetup();




//   analogReference(EXTERNAL);   // !!! w przypadku napiÄ™cia czujnika niĹĽszego niĹĽ napiÄ™cie pĹ‚ytki
//------------------ bluetooth ----------(poprostu zrob funkcje void SetupBLE i odeslij do 2 pliku--------------------------------------------------------------------------------------------------
///  Serial.begin(9600);    // initialize serial communication
//  pinMode(13, OUTPUT);   // initialize the LED on pin 13 to indicate when a central is connected

  /* Set a local name for the BLE device
     This name will appear in advertising packets
     and can be used by remote devices to identify this BLE device
     The name can be changed but maybe be truncated based on space left in advertisement packet */
//  blePeripheral.setLocalName("HeartRateSketch");
// blePeripheral.setAdvertisedServiceUuid(heartRateService.uuid());  // add the service UUID
//  blePeripheral.addAttribute(heartRateService);   // Add the BLE Heart Rate service
//  blePeripheral.addAttribute(heartRateChar); // add the Heart Rate Measurement characteristic

  /* Now activate the BLE device.  It will start continuously transmitting BLE
     advertising packets and will be visible to remote BLE central devices
     until it receives a new connection */
 // blePeripheral.begin();
 // Serial.println("Bluetooth device active, waiting for connections...");
}


//============================== LOOP ====================================================================================================
void loop(){
  #ifdef SERIAL_PORT_LOG_ENABLE
   serialOutput() ;       
  #endif
  CurieTimerOne.start(time, &przerwanie);      // ustawienie timeta i wywolanie przerwania
  
  if (QS == true)                             // jesli wykryto puls, policzone BPM i IPI
  {                       
  #ifdef SERIAL_PORT_LOG_ENABLE
   serialOutputWhenBeatHappens();             // wyswietl jak wykryje uderzenie
  #endif  
  QS = false;                                 // reset flagi wykrycia    
  }

//BLEserceLoop();                          //obsluga bluetootha
kroki(); 
 delay(20);// zwieksz zeby zmniejszyc spam


//------------------ bluetooth -------------------------------------------------------------------------------------------------------------
 /*
  BLECentral central = blePeripheral.central(); // listen for BLE peripherals to connect:
  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());    // print the central's MAC address:
    digitalWrite(13, HIGH);           // turn on the LED to indicate the connection:
    // check the heart rate measurement every 200ms as long as the central is still connected:
    while (central.connected()) {
      long currentMillis = millis();
      // if 200ms have passed, check the heart rate measurement:
      if (currentMillis - previousMillis >= 200) {
        previousMillis = currentMillis;
           updateHeartRate();     //!!!!!!! pomiar!!!!!!!!!
      }
    }
    // when the central disconnects, turn off the LED:
    digitalWrite(13, LOW);
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }
  */
}

//========================== END ===================================================================================================
//=========================== test z loopa ===================================================================================================
//delay(10000); 
 /*        Serial.print("Total number of ticks in 10 seconds: ");
    Serial.println(CurieTimerOne.rdRstTickCount());  // Reads and Resets tick count
    Serial.println(xx);
    Serial.println("----");
*/
  //  CurieTimerOne.restart(time);   // Restarts Timer
    
 // ledFadeToBeat();                      // Makes the LED Fade Effect Happen 
//  delay(20);                             //  take a break
 // xx=0;

//==========================================  smieci ==============================================================================================
/*
void ledFadeToBeat(){
    fadeRate -= 15;                         //  set LED fade value
    fadeRate = constrain(fadeRate,0,255);   //  keep LED fade value from going into negative numbers!
    analogWrite(fadePin,fadeRate);          //  fade LED
  }
*/





