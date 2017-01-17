boolean stepEventsEnabeled = true;   // whether you're polling or using events
long lastStepCount = 0;              // step count on previous polling check
//boolean blinkState = false;          // state of the LED

void krokiSetup(){
 // intialize the sensor:
  CurieIMU.begin();
  // turn on step detection mode:
  CurieIMU.setStepDetectionMode(CURIE_IMU_STEP_MODE_NORMAL);
  // enable step counting:
  CurieIMU.setStepCountEnabled(true);

  if (stepEventsEnabeled) {
    // attach the eventCallback function as the
    // step event handler:
    CurieIMU.attachInterrupt(eventCallback);
    CurieIMU.interrupts(CURIE_IMU_STEP);  // turn on step detection

    Serial.println("IMU initialisation complete, waiting for events...");
  }
}


void kroki(){
  /* Instead of using step detection event notifications,
     we can check the step count periodically */
  if (!stepEventsEnabeled) {
    updateStepCount();
  }
//  digitalWrite(13, blinkState);
//  blinkState = !blinkState;
//  delay(1000);
}


static void updateStepCount() {
  // get the step count:
  int stepCount = CurieIMU.getStepCount();

  // if the step count has changed, print it:
  if (stepCount != lastStepCount) {
    Serial.print("Step count: ");
    Serial.println(stepCount);
    // save the current count for comparison next check:
    lastStepCount = stepCount;
  }
}

static void eventCallback(void) {
  if (CurieIMU.stepsDetected())
    updateStepCount();
}
