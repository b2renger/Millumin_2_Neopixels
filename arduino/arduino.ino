

#include <Adafruit_NeoPixel.h>



Adafruit_NeoPixel pixels0(36, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels1(10, 9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(10, 10, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3(10, 11, NEO_GRB + NEO_KHZ800);

int r0 = 255;
int g0 = 0;
int b0 = 0;

int r1 = 0;
int g1 = 0;
int b1 = 0;


int r2 = 0;
int g2 = 0;
int b2 = 0;


int r3 = 0;
int g3 = 0;
int b3 = 0;


// from http://www.esologic.com/parsing-serial-data-sent-to-arduino/

// code needed for receiving and retrieving data from processing
const char EOPmarker = ';'; //This is the end of packet marker
char serialbuf[64]; //This gives the incoming serial some room. Change it if you want a longer incoming.
#include <string.h> // we'll need this for subString
#define MAX_STRING_LEN 48 // like 3 lines above, change as needed.

void setup() {
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  pixels0.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels1.begin();
  pixels2.begin();
  pixels3.begin();
}

void loop() {

  if (Serial.available() > 0) { //makes sure something is ready to be read
    // this part of code allows you to recompose the message from processing
    static int bufpos = 0; //starts the buffer back at the first position in the incoming serial.read
    char inchar = Serial.read(); //assigns one byte (as serial.read()'s only input one byte at a time
    if (inchar != EOPmarker) { //if the incoming character is not the byte that is the incoming package ender
      serialbuf[bufpos] = inchar; //the buffer position in the array get assigned to the current read
      bufpos++; //once that has happend the buffer advances, doing this over and over again until the end of package marker is read.
    }

    // inside this else we can recover our values ​​and use them
    else { //once the end of package marker has been read
      serialbuf[bufpos] = 0; //restart the buff
      bufpos = 0; //restart the position of the buff


      r0 = atoi(subStr(serialbuf, ",", 1)); // get the first value and store it in a variable
      g0 = atoi(subStr(serialbuf, ",", 2)); // get back the second ...
      b0 = atoi(subStr(serialbuf, ",", 3)); // get back the third ...
      r1 = atoi(subStr(serialbuf, ",", 4)); // get the first value and store it in a variable
      g1 = atoi(subStr(serialbuf, ",", 5)); // get back the second ...
      b1 = atoi(subStr(serialbuf, ",", 6)); // get back the third ...
      r2 = atoi(subStr(serialbuf, ",", 7)); // get the first value and store it in a variable
      g2 = atoi(subStr(serialbuf, ",", 8)); // get back the second ...
      b2 = atoi(subStr(serialbuf, ",", 9)); // get back the third ...
      r3 = atoi(subStr(serialbuf, ",", 10)); // get the first value and store it in a variable
      g3 = atoi(subStr(serialbuf, ",", 11)); // get back the second ...
      b3 = atoi(subStr(serialbuf, ",", 12)); // get back the third ...

      // if (n > 1) {



      //  }
      for (int i = 0; i < 36; i++) { // For each pixel...
        pixels0.setPixelColor(i, pixels0.Color(r0, g0, b0));
      }
      pixels0.show();   // Send the updated pixel colors to the hardware.

      for (int i = 0; i < 10; i++) { // For each pixel...
        pixels1.setPixelColor(i, pixels1.Color(r1, g1, b1));
      }
      pixels1.show();   // Send the updated pixel colors to the hardware.

      for (int i = 0; i < 10; i++) { // For each pixel...
        pixels2.setPixelColor(i, pixels2.Color(r2, g2, b2));
      }
      pixels2.show();   // Send the updated pixel colors to the hardware.

      for (int i = 0; i < 10; i++) { // For each pixel...
        pixels3.setPixelColor(i, pixels3.Color(r3, g3, b3));
      }
      pixels3.show();   // Send the updated pixel colors to the hardware.



    }
  }


}


// this function is necessary to allow to cut the string from processing
char* subStr (char* input_string, char *separator, int segment_number) {
  char *act, *sub, *ptr;
  static char copy[MAX_STRING_LEN];
  int i;
  strcpy(copy, input_string);
  for (i = 1, act = copy; i <= segment_number; i++, act = NULL) {
    sub = strtok_r(act, separator, &ptr);
    if (sub == NULL) break;
  }
  return sub;
}
