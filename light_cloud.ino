#include <EasyButton.h>
#define MODE_BTN 2
/* This sketch is made by zimmermannard */

const int red = 11; /* connected to PWM pin 11 */

const int green = 10; /* connected to PWM pin 10 */

const int blue = 9; /* connected to PWM pin 9 */

const int red2 = 6;
const int green2 = 5;
const int blue2 = 3;

const int mic = 0;
unsigned int sample;


int r = 0; /* red led value is temporally 255 and it will be the first led to light up */
int b = 0; /* blue led value is temporally 0 */
int g = 0; /* green led value is temporally 0 */

int r2 = 0; /* red led value is temporally 255 and it will be the first led to light up */
int b2 = 0; /* blue led value is temporally 0 */
int g2 = 0; /* green led value is temporally 0 */

uint8_t mode = 0;

int ptr = 0;

int startMillis = 50; /* "t" (time) 1000 milliseconds, feel free to change it */

EasyButton button(MODE_BTN);

unsigned int getSoundLevel() {
   unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level
 
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
   int sampleWindow = 50;
   
   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(mic);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude

   if (peakToPeak > 255) {
      peakToPeak = 255;
   }
   return peakToPeak;

}

void cycleMode() {
  mode++;
  if(mode > 3) {
    mode = 0;
  }
}
void setup() {/* no setup */
  r = 0;
  g = 0;
  b = 0;
  r2 = 0;
  g2 = 0;
  b2 = 0;
  button.begin();
  button.onPressed(cycleMode);
}

void tempSetRGB(int led, int rx, int gx, int bx) {
  if( led == 0 ) {
    analogWrite(red, rx);
    analogWrite(green, gx);
    analogWrite(blue, bx);
  } else if ( led == 1 ) {
    analogWrite(red2, rx);
    analogWrite(green2, gx);
    analogWrite(blue2, bx);
  }  
}

void setRGB() {
  analogWrite(red, r);
  analogWrite(green, g);
  analogWrite(blue, b);
  analogWrite(red2, r2);
  analogWrite(green2, g2);
  analogWrite(blue2, b2);
}

void setRGB(int led, int rx, int gx, int bx) {
  if( led == 0 ) {
    r = rx;
    g = gx;
    b = bx;
    analogWrite(red, r);
    analogWrite(green, g);
    analogWrite(blue, b);
  } else if ( led == 1 ) {
    r2 = rx;
    g2 = gx;
    b2 = bx;
    analogWrite(red2, r2);
    analogWrite(green2, g2);
    analogWrite(blue2, b2);
  }
}

void lightning() {
    int whichled;
    int typeofstrike = random(1,5);

    if(typeofstrike == 1) {
      if(random(0,2) == 0) {
        tempSetRGB(0, 150,150,150);
        delay(random(100,300));
        tempSetRGB(1, 255,255,255);
        delay(random(100,400));
      } else {
        tempSetRGB(1, 150,150,150);
        delay(random(100,300));
        tempSetRGB(0, 255,255,255);
        delay(random(100,400));
      }
    } else {
      int strikes = random(1,5);
      for(int i=0; i<strikes; i++) {
        whichled = random(0,2);
        tempSetRGB(whichled, 255,255,255);
        delay(20);
        tempSetRGB(whichled,r,g,b);
        delay(random(50,300));
      }
    }
  

}

void fadeColor(int red, int green, int blue, int red2, int green2, int blue2, int del) {
  while ( r != red || g != green || b != blue || r2 != red2 || g2 != green2 || b2 != blue2) {
    // because i'm too lazy to redo this in non-delay stuff
    button.read();
    if ( r < red ) r += 1;
    if ( r > red ) r -= 1;

    if ( g < green ) g += 1;
    if ( g > green ) g -= 1;

    if ( b < blue ) b += 1;
    if ( b > blue ) b -= 1;

    if ( r2 < red2 ) r2 += 1;
    if ( r2 > red2 ) r2 -= 1;

    if ( g2 < green2 ) g2 += 1;
    if ( g2 > green2 ) g2 -= 1;

    if ( b2 < blue2 ) b2 += 1;
    if ( b2 > blue2 ) b2 -= 1;


    setRGB();
    delay(del);
  }
}


void loop() {
  button.read();

  if (mode == 0 ) {
    //night light
    setRGB(0, 100, 35, 0);
    setRGB(1, 100, 35, 0);
  } else if(mode == 1) {
    // sunset
    fadeColor(
      255, 255, 255, 
      255, 223, 96, 
      50
    );

    if(mode !=1) {
      return;
    }
    fadeColor(
      255, 223, 96, 
      249, 137, 67, 
      50
    );
    if(mode !=1) {
      return;
    }
    fadeColor(
      249, 137, 67, 
      250, 69, 66, 
      50
    );
    if(mode !=1) {
      return;
    }
    fadeColor(
      250, 69, 66, 
      58, 45, 77, 
      50
    );
    if(mode !=1) {
      return;
    }
    fadeColor(
      58, 45, 77, 
      17, 29, 64,
      50
    );
    if(mode !=1) {
      return;
    }
    fadeColor(
      17, 29, 64, 
      9, 18, 44, 
      50
    );
    if(mode !=1) {
      return;
    }
    fadeColor(
      9, 18, 44, 
      0,0,0,
      50
    );
    if(mode !=1) {
      return;
    }
    fadeColor(
      0,0,0,
      0,0,0,
      200
    );
    if(mode !=1) {
      return;
    }
    mode++;
  } else if (mode == 2) {
    // storm
    setRGB(0, 20, 0, 200);
    setRGB(1, 20, 0, 200);
    if(getSoundLevel() > 100) {
      lightning();
    }
  } else if (mode == 3) { 
    // interactive rainbow
    if(getSoundLevel() > 100) {
      ptr++;
    }  
  
    ptr = ptr % 6;
  
    switch(ptr) {
      case 0: 
        fadeColor(
          127,0,127,
          255,0,0,
          1
        );
        break;
      case 1: 
        fadeColor(
          255,0,0,
          127,127,0,
          1
        );
        break;
      case 2: 
        fadeColor(
          127,127,0,
          0,200,0,
          1
        );
        break;
      case 3: 
        fadeColor(
          0,200,0,
          0,127,127,
          1
        );
        break;
      case 4: 
        fadeColor(
          0,127,127,
          0,0,255,
          1
        );
        break;
      case 5: 
        fadeColor(
          0,0,255,
          127,0,127,
          1
        );
        break;
    }
  }
}
