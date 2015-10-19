import processing.serial.*;
// objet représentant le port série
Serial lePort;

// position courante sur l'axe x
float xPos = 0;
float num;
float numcmd;

void setup () {
  // taille de la fenêtre
  size(1600, 1000, JAVA2D);
 
  // Afficher la liste des ports séries détectés
  printArray(Serial.list());
  //String portName = Serial.list()[5];
  //lePort = new Serial(this, portName, 115200);
  
  // Ouverture du port série
  lePort = new Serial(this, "/dev/ttyUSB1", 115200);
 
  // fond noir + effacement
  background(#000000);
  // vert
  stroke(#00FF00);
  // lignes horizontales 
  line(0, height-410, width, height-410);
  line(0, height-400, width, height-400);
  // jaune
  stroke(#FFFF00);
  // Cette ligne est la consigne 39degC x 10
  line(0, height-390, width, height-390);
  // re-vert
  stroke(#00FF00);  
  line(0, height-380, width, height-380);
}

// equivalent au loop() d'Arduino
void draw () {
  PFont f;
  f = createFont("Arial",12,true); // Arial, 16 point, anti-aliasing on
  textFont(f);
  
  
  // on retrace les lignes horizontales
  stroke(#00FF00);
  line(0, height-410, width, height-410);
  line(0, height-400, width, height-400);
  stroke(#FFFF00);
  line(0, height-390, width, height-390);
  stroke(#00FF00);  
  line(0, height-380, width, height-380);
  
  // rouge pour les températures
  stroke(#FF0000);
  point(xPos, height - num*10);
  // cyan pour la valeur PWM (commande)
  stroke(#00FFFF);
  point(xPos, height - numcmd*10/4);
    
  // noir
  stroke(#000000);
  // remplissage des formes en noir
  fill(#000000);
  // rectangle noir plein pour effacer le tracé
  // avant la position courante
  rect(xPos+1, 0, 42, height);
  // pas de remplissage
  noFill();
  
  // ajout texte
  fill(#FF0000);
  text(str(num),xPos+8, height - num*10);
  fill(#00FFFF);
  text(str(int(numcmd)),xPos+8, height - numcmd*10/4);
  noFill();
}

// quelque chose se passe sur le port série
void serialEvent (Serial lePort) {
  String maChaine = null;

  // on récupère toute la ligne
  maChaine = lePort.readStringUntil(10);
  // si ce n'est pas une ligne vide
  if (maChaine != null) {
    // récupération position du ":"
    int p = maChaine.indexOf(":");
    // récupération chaîne température
    String temp = maChaine.substring(0, p);
    // récupération chaîne pwm/commande
    String cmd = maChaine.substring(p+1);

    // chaîne température en valeur à virgule flottante    
    num=float(temp);
    // chaîne pwm/commande en valeur à virgule flottante
    numcmd=float(cmd);
    // affichage
    print(num);
    print("    --    ");
    println(numcmd);
    
    // On arrive au bord de la fenêtre (à droite)
    if (xPos >= width) {
      // On revient au début (gauche)
      xPos = 0;
    } else {
      // sinon, on avance la position courante d'un pixel
      // à chaque nouvelle ligne reçue sur le port série
      // Le tracé se fait dans draw()
      xPos++;
    }
  }
  //redraw();
}