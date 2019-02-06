#include "pitches.h" // header file containing the musical notes

void setup() {
  Serial.begin(115200);
}

float c;
int d;  // This variable is used to have some data in the serial port, it can be used for analyzing the signal with a virtual oscilloscope to check for the response of the system.

float ReadInput() {
  float x = analogRead(A2);
  c = (x * 5) / 1023; //Compensate for the gain of the hardware circuit.
  return c;
}

// The following function takes the average of the maximum values that are being read in. The number of maximums used for the average is dependent on the "counter" variable. 
// To determine each maximum value used for the average, a total of 10 samples are taken and compared to one another. The maximum is retained and after a total of "counter" number of passes, the accumulated value is
// averaged by the number of "counter". 
float FindAverageOfMax(float inputVals) {
  float val = 0, maxval = 0, counter = 3, avgval = 0;
  for (int j = 0; j < counter; j++) {
    for (int i = 0; i < 10; i++) {
      val = ReadInput();
      if (maxval < val) {
        maxval = val;
      }
    }
    avgval += maxval; /// addition of the determined max value of current pass, to the sum of past ones.
  }
  avgval = avgval / counter; // is the average maximum value, which will be passed.
  return avgval;
}

// The following function receives the computed value of the maximum of averages which has been determined in the FindAverageOfMax function. 
// This value is then being categorized into one of the different value brackets, causing a music tone based on the bracket it was categorized to.
// Whitin each bracket the tone function is called and a hard coded music note is then played for a set amount before being turned off again.
int Output(float avgval) {
  float noise = 2.29;
  if (avgval < noise) {
    d = 0;
    tone(8,NOTE_C4,250);
    delay(300);
  }
  else if (avgval >= noise && avgval <= 2.3) {
    d = 1;
    tone(8,NOTE_D4,250);
    delay(300);
  }
  else if (avgval <= 2.4 && avgval > 2.3) {
    d = 2;
    tone(8,NOTE_E4,250);
    delay(300);
  }
  else if (avgval <= 2.5 && avgval > 2.4) {
    tone(8,NOTE_F4,250);
    delay(300);
  }
  else {
    tone(8,NOTE_C4,250);
    delay(300);
  }
  return d;
}

void loop() {
  float noise,avgval;
  avgval = FindAverageOfMax(ReadInput());
  d = Output(avgval);
  for (int  k= 0; k < 500; k++) {  // This loop is mainly used for the analysis and debugging of the system through the serial port. 
    Serial.print(z);
    Serial.println();
    delay(1);}
}

