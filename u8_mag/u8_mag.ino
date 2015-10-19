#include "U8glib.h"

// Déclaration pour SPI matériel
// SCK sur 13 et MOSI sur 11
// arguments : CS, D/C, RST
//U8GLIB_SSD1306_ADAFRUIT_128X64 u8g(8, 6, 7);

// Déclaration pour I2C / TWI matériel
U8GLIB_SSD1306_128X64 u8g(
  U8G_I2C_OPT_DEV_0|
  U8G_I2C_OPT_NO_ACK|
  U8G_I2C_OPT_FAST);

// Déclaration d'une image bitmap en flash
// notez le U8G_PROGMEM, un PROGMEM propre à u8glib
// La macro B pour spécifier des valeurs en binaire
// est ici très utile
const uint8_t tour_bitmap[] U8G_PROGMEM = {
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

// notre fonction de dessin
// contenant les instructions de tracé
void draw(void) {
  // on place l'icone bitmap
  // arg : x, y, nombre d'octet pour une ligne, nombre de lignes
  u8g.drawBitmapP(0, 0, 1, 16, tour_bitmap);
  u8g.drawBitmapP(119, 0, 1, 16, tour_bitmap);
  
  // un cadre à coins arrondis
  // arg : x, y, largeur, hauteur, rayon coins
  u8g.drawRFrame(0, 16, 128, 40, 10);
  
  // un rectangle plein
  // arg : x, y, largeur, hauteur
  u8g.drawBox(34, 26, 40, 22);
  
  // disque (cercle plein)
  // arg : centre x, cente y, rayon, segment à afficher
  // Les modificateurs de segment possibles sont :
  // U8G_DRAW_UPPER_RIGHT : haut/droite
  // U8G_DRAW_UPPER_LEFT : haut/gauche
  // U8G_DRAW_LOWER_LEFT : bas/gauche
  // U8G_DRAW_LOWER_RIGHT : bas/droite
  // U8G_DRAW_ALL : tout, par défaut en l'absence de modificateur
  // ici haut/droite :
  u8g.drawDisc(90, 43, 10, U8G_DRAW_UPPER_RIGHT);
  // idem mais bas/droite :
  u8g.drawDisc(90, 48, 10, U8G_DRAW_LOWER_RIGHT);
  
  // une ligne
  // arg : départ x, départ y, fin x, fin y
  u8g.drawLine(0, 63, 127, 26);
  
  // un triangle plein
  // arg : x et y de chaque sommet
  u8g.drawTriangle(3,20, 10,52, 20,40);
  
  // un cercle (vide)
  // arg : centre x, centre y, rayon
  // les modificateurs de segment sont identiques à drawDisc
  u8g.drawCircle(127, 32, 27);

  // affichage de texte
  // on commence par choisir la police
  // (voir libraries/U8glib/src/clib/u8g.h)
  u8g.setFont(u8g_font_6x10);
  // le point de placement est relatif au plus haut pixel du texte +1
  u8g.setFontPosTop();
  // on écrit le texte
  // arg : x, y, chaîne de caractères (pointeur)
  u8g.drawStr(14, 5, "Coucou Hackable");

  // Nous pouvons aussi dessiner en noir
  // Il faut spécifier la couleur dans l'index
  // Sur écran monochrome 0=fond, 1=avant plan
  u8g.setColorIndex(0);
  // dessin d'un disque
  u8g.drawDisc(45, 36, 8);
  // on revient sur la couleur d'avant plan
  u8g.setColorIndex(1);
}

void setup() {
  // il n'a a rien à faire ici
}

void loop() {
  // début de la boucle d'affichage  
  u8g.firstPage();
  
  // boucle d'affichage d'U8glib
  do {
    // appel répété à notre fonction de dessin
    draw();
  // fin de boucle
  } while( u8g.nextPage() );
  // nextPage() retourne 0 si le travail est fini
  // et 1 si un rafraîchissement est encore nécessaire
  
  // petite pause
  delay(1000);
}
