#include <U8glib.h>
#include <Sodaq_DS3231.h>
#include <Time.h>
#include <Wire.h>

// SPI hard
//U8GLIB_SSD1306_ADAFRUIT_128X64 u8g(8, 6, 7);

// I2C / TWI hard
U8GLIB_SSD1306_128X64 u8g(
  U8G_I2C_OPT_DEV_0|
  U8G_I2C_OPT_NO_ACK|
  U8G_I2C_OPT_FAST);

// icône tour
const uint8_t tour_bitmap[] U8G_PROGMEM = {
  B00000000, B01010101, B01010101, B01111111,
  B01111111, B00111110, B00111110, B00111110,
  B00111110, B00111110, B00111110, B00111110,
  B00111110, B00111110, B00111110, B01111111
};

// chaîne pour température
char temp_buffer[8];
// chaîne pour date/heure formatée
char date_buffer[20];

// fonction de dessin
void draw(void) {
  // hack ignoble : "°C\0"
  char degCascii[3] = {176, 67, 0};

  // affichage icônes zone jaune
  u8g.drawBitmapP(0, 0, 1, 16, tour_bitmap);
  u8g.drawBitmapP(119, 0, 1, 16, tour_bitmap);

  // date/heure sur zone jaune
  u8g.setFont(u8g_font_6x10);
  u8g.setFontPosTop(); // toujours après choix police
  u8g.drawStr(16, 4, date_buffer);

  // température en gros, zone bleue
  u8g.setFont(u8g_font_timR24);
  u8g.setFontPosTop();
  u8g.drawStr(10, 27, temp_buffer);
  u8g.drawStr(85, 27, degCascii);

  // joli cadre rond tout mimi
  u8g.drawRFrame(0, 17, 128, 46, 10);
}

void setup() {
  // init RTC DS3221
  rtc.begin();
  // activation mesure
  rtc.convertTemperature();

  // récuperation de la température
  dtostrf(rtc.getTemperature(), 4, 2, temp_buffer);

  // récupération de la date/heure
  DateTime now = rtc.now();
  // conversion en chaîne
  sprintf(date_buffer,"%02d/%02d/%d %02d:%02d",
    now.date(),    // jour
    now.month(),   // mois
    now.year(),    // année
    now.hour(),    // heures
    now.minute()); // minutes
}

void loop() {
  // picture loop
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );

  //rtc.begin();
  // idem que setup();
  rtc.convertTemperature();
  dtostrf(rtc.getTemperature(), 4, 2, temp_buffer);
  
  DateTime now = rtc.now();
  sprintf(date_buffer,"%02d/%02d/%d %02d:%02d",
    now.date(), now.month(), now.year(),
    now.hour(), now.minute());
  
  // pause 10s
  delay(10000);
}
