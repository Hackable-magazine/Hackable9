#include <OneWire.h>
#include <DallasTemperature.h>
#include <PID_v1.h>

// le bus est sur la broche 2
#define ONE_WIRE_BUS 2
// On contrôle avec la broche 11
#define OUTP 11

// Variables pour PID
// La température souhaitée :
double Consigne;
// La température mesurée :
double Temp;
// La valeur PWM 0-255 :
double Mosfet;

// déclaration du bus 1-wire
OneWire oneWire(ONE_WIRE_BUS);
// déclaration des capteurs
DallasTemperature sensors(&oneWire);


// Déclaration de l'objet PID
// Les argument sont les variables de gestion
// puis les gains pour P, I et D
// et enfin,le mode.
PID myPID(&Temp, &Mosfet, &Consigne, 6, 1, 0.25, DIRECT);

// Valeurs de l'exemple fourni
//PID myPID(&Temp, &Mosfet, &Consigne, 2, 5, 1, DIRECT);
// Agressif
//PID myPID(&Temp, &Mosfet, &Consigne, 6, 3, 1, DIRECT);
// Moins agressif
// PID myPID(&Temp, &Mosfet, &Consigne, 1, 0.05, 0.25, DIRECT);

void setup(void) {
  // broche 11 en sortie
  pinMode(OUTP, OUTPUT);
  // activation port série
  Serial.begin(115200);
  // démarrage capteurs
  sensors.begin();
  // consigne à 39°C
  Consigne = 39;
  // contrôle entre 0-255
  myPID.SetOutputLimits(0, 255);
  // on active la régulation PID
  myPID.SetMode(AUTOMATIC);
}

void loop(void) { 
  // demande de mesure
  sensors.requestTemperatures();
  // obtention de la température du premier
  // et seul capteur DS18B20
  Temp = sensors.getTempCByIndex(0);
  // calcul PID, la variable Mosfet contient 
  // ensuite la valeur calculée
  myPID.Compute();
  // écriture PWM
  analogWrite(OUTP, Mosfet);

  // envoi des informations temp:PWM à Processing
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print(":");
  Serial.println(Mosfet);
}




