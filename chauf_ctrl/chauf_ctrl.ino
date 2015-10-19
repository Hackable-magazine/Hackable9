#include <OneWire.h>
#include <DallasTemperature.h>

// le bus est sur la broche 2
#define ONE_WIRE_BUS 2

// On contrôle avec la broche 11
// On choisi une sortie PWM au cas où
#define OUTP 11

// déclaration du bus 1-wire
OneWire oneWire(ONE_WIRE_BUS);
// déclaration du capteur
// (il pourrait y en avoir plusieurs)
DallasTemperature sensors(&oneWire);

// fonction chauffage
void chauffage_on() {
  // on peut jouer avec la PWM si nécessaire
  analogWrite(OUTP, 255);
}

// arrêt chauffage
void chauffage_off() {
  analogWrite(OUTP, 0);
}

void setup(void) {
  Serial.begin(115200);
  // démarrage capteurs
  sensors.begin();
  // broche 11 en sortie
  pinMode(OUTP, OUTPUT);
  // par défaut on coupe le chauffage
  chauffage_off();
}

void loop(void) { 
  // demande de lecture des températures
  sensors.requestTemperatures();

  // on affiche la température du premier
  // capteur (le seul dans notre cas)
  Serial.print(sensors.getTempCByIndex(0));
  // si on est au dessus de la consigne
  if(sensors.getTempCByIndex(0) > 39) {
    // affiche valeur bidon pour le graph
    Serial.println(":34");
    // on  ne chauffe pas
    chauffage_off();
  // si on est en dessous
  } else if(sensors.getTempCByIndex(0) < 39) {
    // affiche valeur bidon pour le graph
    Serial.println(":45");
    // on chauffe
    chauffage_on();
  }
  // si on est à la consigne on ne change rien,
  // dans un cas comme dans l'autre la température
  // changera en plus ou en moins.
}

