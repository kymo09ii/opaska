//changelog
/*
 * 
 * 
 */

void serialOutput(){                            // rodzaj wyswietlania true- wizualne // false- dane 
 if (serialVisual == true)
 {  
     arduinoSerialMonitorVisual('-', Signal);   // wizualizacja
 } else{
      sendDataToSerial('S', Signal);            // dane
 }        
}


void serialOutputWhenBeatHappens()               
{    
 if (serialVisual == true)                        // wizualizacja
 {                                                 
    Serial.print("*** Heart-Beat Happened *** "); 
    Serial.print("BPM: ");
    Serial.print(BPM);
    Serial.print("  ");
 } else                                           // dane
 {
    sendDataToSerial('B',BPM);                    // uderzenia na minutę poprzedzone 'B'
    sendDataToSerial('Q',IBI);                    // czas miedzy uderzeniami poprzedzony 'Q'
 }   
}
void sendDataToSerial(char symbol, int data )     //przeslanie do seriala
  {
    Serial.print(symbol);
    Serial.println(data);                
  }

void arduinoSerialMonitorVisual(char symbol, int data )         // wizualizacja
{    
  const int sensorMin = 0;                                      
  const int sensorMax = 1024;                                   // max wartosc czujnika
  int sensorReading = data;
  int range = map(sensorReading, sensorMin, sensorMax, 0, 11);  // mapowanie zakresu do 12 wartosci
                                                    
  switch (range) {                                              // rysunek do wartosci
  case 0:     
    Serial.println("");     
    break;
  case 1:   
    Serial.println("---");
    break;
  case 2:    
    Serial.println("------");
    break;
  case 3:    
    Serial.println("---------");
    break;
  case 4:   
    Serial.println("------------");
    break;
  case 5:   
    Serial.println("--------------|-");
    break;
  case 6:   
    Serial.println("--------------|---");
    break;
  case 7:   
    Serial.println("--------------|-------");
    break;
  case 8:  
    Serial.println("--------------|----------");
    break;
  case 9:    
    Serial.println("--------------|----------------");
    break;
  case 10:   
    Serial.println("--------------|-------------------");
    break;
  case 11:   
    Serial.println("--------------|-----------------------");
    break;
  
  } 
}





