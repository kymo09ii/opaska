volatile int BPM;                   // uderzenia na minutę aktualizowane co 2ms bazujace na 10 pomiarach
volatile int Signal;                // pomiar pulsu z A0
volatile int IBI = 600;             // odstep czasu miedzy uderzeniami


/////////////////////////////////////////
volatile int rate[10];                             // wektor 10 ostatnich odstepow miedzy bitami
volatile unsigned long sampleCounter = 0;          // czas bitu
volatile unsigned long lastBeatTime = 0;           // czas ostatniego uderzenia - IBI
volatile int P =712;                               // szczyt pulsu, seed
volatile int T = 712;                              // dolina pulsu, seed
volatile int thresh = 725;                         // used to find instant moment of heart beat, seed           !!!!!!!!!!!!!!!!!!!!!!!
volatile int amp = 100;                            // amplituda uderzen, seed
volatile boolean firstBeat = true;                 // seed dla wektora ostatnich uderzen BPM zeby byl plynny start
volatile boolean secondBeat = false;               // seed dla wektora ostatnich uderzen BPM zeby byl plynny start

// ==============================  przerwanie =======================================================================================
void przerwanie(){    
//------------------------------- przygotowanie -----------------------------------------------------------------------------------                            
  noInterrupts();                                 // wylacz interrupty
  Signal = analogRead(pulsePin);                  // odczyt analog czuj pulsu 
  sampleCounter += 2;                             // czas przerwania
  int N = sampleCounter - lastBeatTime;           // czas od ostatniego bitu

    
  if(Signal < thresh && N > (IBI/5)*3){           // unikniecie szumu dychrotycznego przez 3/5 czasu ostatniego uderzenia
    if (Signal < T)   
    {                                     
      T = Signal;                                 // min wart pulsu
    }
  }

  if(Signal > thresh && Signal > P)               // tresh od unikania szumow
  {                                               
    P = Signal;                                   // max wart pulsu
  }                                            
// --------------------------- szukanie pulsu -------------------------------------------------------------------------------------
  // signal surges up in value every time there is a pulse
  if (N > 250)                                    
  {                                   
    if ( (Signal > thresh) && (Pulse == false) && (N > (IBI/5)*3.5) )
    {        
      Pulse = true;                               // wykryto puls tak
      digitalWrite(blinkPin,HIGH);                // swiece dioda
      IBI = sampleCounter - lastBeatTime;         // czas miedzy odstepami w mS
      lastBeatTime = sampleCounter;               //ustawienie nowego czasu poprzedniego bitu
      if(secondBeat)
      {                                           // jesli wykryty drugi bit - wiarygodnie
        secondBeat = false;                       
        for(int i=0; i<=9; i++)
        {                                         // zeby bylo bardziej stabilnie na poczatku
          rate[i] = IBI;                      
        }
      }

      if(firstBeat)
      {                                           // jesli to pierwsze uderzenie to jest malo wiarygodne - return
        firstBeat = false;                        
        secondBeat = true;      
        interrupts();                             //wlacz obsluge przerwan
        return;                                   
      }   
    // ---SzP--------------- zapamietanie ostatnich 10 odstepow miedzy bitami -------------------------------------------------------
      word runningTotal = 0;                  // zmienna czasu ostatnich 9-10 uderzen    

      for(int i=0; i<=8; i++)                 
      {                
        rate[i] = rate[i+1];                  //usuwam najstarsza wartosc i dodaje 9 pozostalych do siebie
        runningTotal += rate[i];              
      }

      rate[9] = IBI;                          //aktualizacja o ostatnia odczytana wartosc
      runningTotal += rate[9];                //zsumowanie i wyciagniece sredniej
      runningTotal /= 10;                     
      BPM = 60000/runningTotal;               // przeliczenie uderzen na minute
      QS = true;                              //potwierdzenie wykrycia pulsu, BPM i IBI do loopa - tam reset
    }                       
  }
// ---------------------------koniec szukania pulsu------------------------------------------------------------------------------------------------------
  if (Signal < thresh && Pulse == true)     //koniec skorczu serca, spadek wartosci
  {   
    digitalWrite(blinkPin,LOW);             
    Pulse = false;                          
    amp = P - T;                            // amplituda pracy serca jako roznica min i max
    thresh = amp/2 + T;                     // nowy thresh dostosowany do starej amplitudy
    P = thresh;                             
    T = thresh;
  }

  if (N > 2500)                             // reset ustawien jesli 2,5 sec bez wykrycia pulsu
  {                           
    thresh = 712;                          
    P = 712;                               
    T = 712;                               
    lastBeatTime = sampleCounter;                 
    firstBeat = true;                      // unikamy szumow,odrzucajac pierwsze wartosci
    secondBeat = false;                    
  }
interrupts();
}








