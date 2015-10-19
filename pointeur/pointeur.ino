typedef void (*fonction) (int t);

void coucou(int num) {
  for(int i=0; i<num; i++) {
    Serial.println("Coucou monde!");
  }
}

void bonjour(int num) {
  for(int i=0; i<num; i++) {
    Serial.println("Bonjour monde!");
  }
}

void hello(int num) {
  for(int i=0; i<num; i++) {
    Serial.println("Hello monde!");
  }
}

void setup() {
  randomSeed(analogRead(0));
  Serial.begin(115200);
  delay(2000);

  fonction ftable[] = {coucou, bonjour, hello};
  Serial.println(sizeof(ftable)/sizeof(ftable[0]));

  for(int i=0; i<12; i++) {
    ftable[random(0,sizeof(ftable)/sizeof(ftable[0]))](1);
    delay(100);
  }
}

void loop() {}
