#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <Adafruit_NeoPixel.h>
#include "images.h"

#define PIX 16
#define MAXB 255
#define MINB 35

Adafruit_NeoPixel pixels =
  Adafruit_NeoPixel(PIX, 9, NEO_GRB + NEO_KHZ800);

typedef void (*fonction) (int t);

void HSVtoRGB(int  *r, int *g,int *b, int h, int s, int v) {
  int c;
  long l, m, n;

  // saturation zéro, pas de couleur
  if(s == 0) {
    *r = *g = *b = v;
    return;
  }

  // chroma
  c = ((h%60)*255)/60;
  h /= 60;

  // intermédiaire
  l = (v*(256-s))/256;
  m = (v*(256-(s*c)/256))/256;
  n = (v*(256-(s*(256-c))/256))/256;

  // choix dominante
  switch(h) {
    case 0:
      *r = v;
      *g = n;
      *b = l;
      break;
    case 1:
      *r = m;
      *g = v;
      *b = l;
      break;
    case 2:
      *r = l;
      *g = v;
      *b = n;
      break;
    case 3:
      *r = l;
      *g = m;
      *b = v;
      break;
    case 4:
      *r = n;
      *g = l;
      *b = v;
      break;
    default:
      *r = v;
      *g = l;
      *b = m;
      break;
  }
}

const unsigned char simple[48] PROGMEM  = {
  255,255,255,  255,255,255,  255,255,255,  255,255,255,
    0,  0,255,    0,  0,255,    0,  0,255,    0,  0,255,
    0,255,  0,    0,255,  0,    0,255,  0,    0,255,  0,
    0,255,  0,    0,255,  0,    0,255,  0,    0,255,  0
};

void arcenciel(int tempo) {
  int r,g,b;
  for(int i=0; i<360; i++) {
    HSVtoRGB( &r, &g, &b, i, 255, 255);
    for(int j=0; j<PIX; j++) {
      pixels.setPixelColor(j, pixels.Color(r,g,b));
    }
    pixels.show();
    delay(tempo);
  }  
}

void marcenciel(int tempo) {
  int r,g,b;
  int debut = random(0,360);
  int fin = random(debut,360);
  for(int i=debut; i<fin; i++) {
    HSVtoRGB( &r, &g, &b, i, 255, 255);
    for(int j=0; j<PIX; j++) {
      pixels.setPixelColor(j, pixels.Color(r,g,b));
    }
    pixels.show();
    delay(tempo);
  }  
}

void gmotif(int tempo) {
  int r,g,b;
  int idx=random(0,NBRIMG)*48;
    
  for(int j=0; j<PIX; j++) {
    r =  pgm_read_byte_near(images + (j*3)+idx+0);
    g =  pgm_read_byte_near(images + (j*3)+idx+1);
    b =  pgm_read_byte_near(images + (j*3)+idx+2);
    pixels.setPixelColor(j, r, g, b);
  }
  pixels.show();
  delay(tempo*100);  
}

void fondu_out(int tempo) {
  for(int i=MAXB; i>MINB; i--) {
    pixels.setBrightness(i);
    pixels.show();
    delay(tempo*2);
  }
  pixels.setBrightness(MAXB);
  pixels.show();
}

void fondu_in(int tempo) {
  for(int i=MINB; i<MAXB; i++) {
    pixels.setBrightness(i);
    pixels.show();
    delay(tempo*2);
  }
  pixels.setBrightness(MAXB);
  pixels.show();
}

void pmotif(int tempo) {
  int r,g,b;
  for(int j=0; j<PIX; j++) {
    r =  pgm_read_byte_near(simple + (j*3)+0);
    g =  pgm_read_byte_near(simple + (j*3)+1);
    b =  pgm_read_byte_near(simple + (j*3)+2);
    pixels.setPixelColor(j, r, g, b);
  }
  pixels.show();
  delay(tempo*100);  
}

void couleur(int tempo) {
  int r,g,b;
  HSVtoRGB( &r, &g, &b, random(0,360), 255, 255);
  for(int j=0; j<PIX; j++) {
    pixels.setPixelColor(j, pixels.Color(r,g,b));
  }
  pixels.show();
  delay(tempo*100);
}

void RTCerror(int err) {
  int r = 255;
  int g = 0;
  if(err!=0) g=100;
  while(1) {
    for(int j=0; j<PIX; j++) {
      pixels.setPixelColor(j, pixels.Color(r,g,0));
    }
    pixels.show();
    delay(75);
    pixels.clear();
    pixels.show();
    delay(75);
  }
}

void setup() {
  pixels.begin();
  pixels.clear();
  pixels.setBrightness(MAXB);
  pixels.show();
  randomSeed(analogRead(0));
  delay(2000);
}

void loop() {
  fonction ftable[] = {gmotif, gmotif, gmotif, couleur, fondu_out, fondu_in, marcenciel};
  tmElements_t tm;
  if (RTC.read(tm)) {
    // RTC ok, on test la plage horaire
    if(tm.Hour < 17 && tm.Hour > 8) {
      ftable[random(0,sizeof(ftable)/sizeof(ftable[0]))](random(1,30));
    } else {
      pixels.clear();
      pixels.show();
      delay(5000);
    }
  } else {
    if (RTC.chipPresent()) {
      // mauvaise date
      RTCerror(1);
    } else {
      // RTC introuvable
      RTCerror(0);
    }
  }
}

