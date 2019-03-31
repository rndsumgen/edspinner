
#include <Adafruit_NeoPixel.h>          // Library for NeoPixels

#define pinPix 9                       // Pin driving NeoPixel Ring or String
#define numPix 12                       // Number of NeoPixels in the Ring or Strip

Adafruit_NeoPixel myNeoPixels = Adafruit_NeoPixel(numPix, pinPix, NEO_GRBW + NEO_KHZ800);


const byte extra = 6;  // how many ahead, and behind, to light up
const byte dimm = 4;   // additionally dim everything by this 1 is off


// Pause = delay between transitions
// Rf, Gf, Bf, Wf = RGB  "front" or preceding values
// Rt, Gt, Bt, Wt = rgbw "Target" or current value
// Rb, Gb, Bb, Wb = RGB  "Back" or trailing values
void ledTrail(int pause, byte Rf, byte Gf, byte Bf,byte Wf, byte Rt,byte  Gt,byte Bt, byte Wt, byte Rb, byte Gb, byte Bb, byte Wb) { 

  int tmpRf, tmpGf, tmpBf, tmpWf;         // Temp values
  int tmpRb, tmpGb, tmpBb, tmpWb;         // Temp values

  for (int i=0; i<numPix; i++) {
 
   myNeoPixels.setPixelColor(i,(Rt/dimm),(Gt/dimm),(Bt/dimm),(Wt/dimm));  // set the target/hilight pixle to it's own color 

   // now go "extra" pixels ahead and behind
    for (int s = 1; s < extra + 1; s++)
      {
      tmpRf = ((Rf * (extra - s)) / extra)/dimm;     // Multiply first to avoid truncation errors  
      tmpGf = ((Gf * (extra - s)) / extra)/dimm;     // Forground colors
      tmpBf = ((Bf * (extra - s)) / extra)/dimm;
      tmpWf = ((Wf * (extra - s)) / extra)/dimm;

      tmpRb = ((Rb * (extra - s)) / extra)/dimm;     // Multiply first to avoid truncation errors  
      tmpGb = ((Gb * (extra - s)) / extra)/dimm;     // Background colors
      tmpBb = ((Bb * (extra - s)) / extra)/dimm;
      tmpWb = ((Wb * (extra - s)) / extra)/dimm;
      
      
      myNeoPixels.setPixelColor((i + s) % numPix,tmpRf,tmpGf,tmpBf,tmpWf);
      myNeoPixels.setPixelColor((i + numPix - s) % numPix,tmpRb,tmpGb,tmpBb,tmpWb);
      }

    myNeoPixels.show();
    delay(pause);
  }
}


void setup() {
  myNeoPixels.begin();   // Initialize the NeoPixel array in the Arduino's memory,
  myNeoPixels.show();    // turn all pixels off, and upload to ring or string
}

void loop() {
  ledTrail(50, 75,21,0,25, 0,0,0,100, 255,113,0,10);       // Pause; R,G,B foreground; R,G,B background
}
