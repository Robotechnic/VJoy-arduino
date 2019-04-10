# VJoy-arduino
Application Qt c++ qui transforme une télécommande en joystick virtuel grâce à [VJoy](http://vjoystick.sourceforge.net/site/index.php) et une arduino connecté à une radiocommande spektrum (il est cependant possible d'adapter pour d'autres radiocommandes en changeant la connectique dans le montage).

🚩 cette application n'est encore disponible que pour Windows

## Chema
[chema de montage](https://github.com/Robotechnic/VJoy-arduino/blob/master/image/arduinoShema.png)

## Mise en place
1 - dans le fichier Arduino présiser le nombre de voies et le nombre de données pour le filtre. Plus le nombre de données est grand plus la précision est grande mais plus les données sont envoiyées lentement et plus le nombre est petit moins la présision est grande mais plus la fréquence denvoi est rapide.
[démo des éxplications](https://github.com/Robotechnic/VJoy-arduino/blob/master/image/demo1.png)
2 - Televerser le programme

## compilation depuis les sources
1 - Telechargez le projet https://github.com/Robotechnic/VJoy-arduino.git
2 - une fois Qt ouvert build le projet
3 - avant d'executer le programme ne pas oubliet de rajouter le fichier [vJoyInterface.dll](https://github.com/Robotechnic/VJoy-arduino/tree/master/vJoyLib) dans le dossier de l'executable


Les joypads viennent de (ce projet)[https://github.com/officinerobotiche/simple_unav_console/tree/develop/qt_simple_unav_console/joypad]