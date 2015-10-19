Sources et fichiers pour le magazine Hackable #9
================================================

Ce dépôt contient les croquis présents dans le neuvième numéro de [Hackable](http://www.hackable.fr/) :

* `WSmatrix44ok/` : le croquis Arduino complet du simulateur de TV avec le `.h` contenant les images extraites de la vidéo avec FFMPEG,
* `script_images/go.sh` : le script shell (Bash) permettant de créer le `.h` à partir du répertoire contenant les images (en `txt`) extraites avec FFMPEG,
* `chauf_ctrl/` : le croquis Arduino du contrôle de chauffe "tout-ou-rien",
* `chauf_ctrl_pid/` : le croquis Arduino avec régulation PID,
* `chauf_ctrl_pid_pc/` : le croquis Processing 3 communiquant avec l'Arduino et traçant le graphique,
* `pointeur/` : croquis Arduino de démonstration des pointeurs sur fonctions,
* `ssd1306_spi_mag/` : le croquis Arduino du pilotage d'écran Oled avec les bibliothèques Adafruit,
* `u8_mag/` : le croquis Arduino pour la même chose mais avec le bibliothèque U8Glib,
* `u8_mag_clock_temp/` : le croquis Arduino final de l'afficheur horloge/température avec RTC/capteur DS3231,
* `DTS/lcdgeneric22b.dts` : le fichier source Device Tree pour la configuration de deux écran LCD SPI sur la Raspberry Pi.

Le script Python permettant de générer une image à partir des données collectées par `rtl_power`, modifié pour utiliser une image comme palette, est disponible [dans ce dépôt GitHub](https://github.com/Lefinnois/SDR-heatmap).

