#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// déclaration pour SPI matériel
// SCK sur 13 et MOSI sur 11
// argument ; D/C, RST, CS
Adafruit_SSD1306 display(6, 7, 8);

// déclaration pour i2c / TWI matériel
// argument : RST
//Adafruit_SSD1306 display(7);

const uint8_t PROGMEM tour_bitmap[]= {
  B00000000, 
  B01010101,
  B01010101,
  B01111111,
  B01111111,
  B00111110,
  B00111110,
  B00111110,
  B00111110,
  B00111110,
  B00111110,
  B00111110,
  B00111110,
  B00111110,
  B00111110,
  B01111111
};

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC);

  // la mémoire de l'afficheur est initialisé avec le
  // logo de Adafruit par la bibliothèque.
  // Donc on efface d'abord l'écran
  display.clearDisplay();
  // puis on rafraîchit l'affichage
  display.display();

  // Les primitives d'affichage utilisent des arguments
  // similaires à ceux d'U8glib mais avec, en plus, à la fin
  // l'index de la couleur utilisée (1 = avant plan, 0 = fond)

  // affichage icônes
  display.drawBitmap(0, 0, tour_bitmap, 8, 16, 1);
  display.drawBitmap(119, 0, tour_bitmap, 8, 16, 1);
  // cadre à coins ronds
  display.drawRoundRect(0, 16, 128, 40, 10,1);
  // rectangle plein
  display.fillRect(34, 26, 40, 22, 1);
  // disque (plein)
  display.fillCircle(90, 43, 10, 1);
  // pas de segment. fillCircleHelper() ne semble 
  // servir que pour les boites à coins ronds
  // Une ligne
  display.drawLine(0, 63, 127, 26, 1);
  // un triangle
  display.fillTriangle(3,20, 10,52, 20,40, 1);
  // un cercle
  display.drawCircle(127, 32, 27, 1);

  // Il n'y a pas de gestion de polices
  // une seul est disponible en une seule taille
  // Avec une taille >1 le texte est simplement grossi
  display.setTextSize(1);
  // La couleur. WHITE est défini à 1 dans Adafruit_SSD1306.h
  // et BLACK à 0
  display.setTextColor(WHITE);
  // position du texte
  display.setCursor(16,5);
  // Notez l'utilisation de la classe Print
  // pour l'affichage sur l'écran. On obtient un comportement
  // identique à print, incluant l'affichage de valeurs. U8glib
  // le fait aussi mais GFX ajoute le saut de lignes automatique
  // (mais pas le défilement du texte).
  display.println("Coucou Hackable");
  // un disque en noir sur le blanc du rectangle plein
  display.fillCircle(45, 36, 8, 0); // <- 0 = BLACK = fond

  // pas de boucle ici
  // on ordonne simplement le rafraîchissement 
  display.display();
}

void loop() {
  // rien ici
}

