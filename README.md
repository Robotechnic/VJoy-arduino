# VJoy-arduino
Application Qt c++ qui transforme une télécommande en joystick virtuel grâce à [VJoy](http://vjoystick.sourceforge.net/site/index.php) et une arduino connecté à une radiocommande spektrum (il est cependant possible d'adapter pour d'autres radiocommandes en changeant la connectique dans le montage).

🚩 cette application est disponible pour linux et pour windows mais pas pour mac (et elle ne le seras jamais)
Pour linux allez sur la branche linux

## Chema
![chema de montage](https://github.com/Robotechnic/VJoy-arduino/blob/master/images/arduinoShema.png)

## Mise en place
1 - dans le fichier Arduino présiser le nombre de voies et le nombre de données pour le filtre. Plus le nombre de données est grand plus la précision est grande mais plus les données sont envoiyées lentement et plus le nombre est petit moins la présision est grande mais plus la fréquence denvoi est rapide.
![démo des éxplications](https://github.com/Robotechnic/VJoy-arduino/blob/master/images/demo1.png)

2 - Televerser le programme


## compilation depuis les sources
1 - Telechargez le projet https://github.com/Robotechnic/VJoy-arduino.git

2 - une fois Qt ouvert build le projet

3 - avant d'executer le programme ne pas oubliet de rajouter le fichier [vJoyInterface.dll](https://github.com/Robotechnic/VJoy-arduino/tree/master/vJoyLib) dans le dossier de l'executable

## instalation
Lancez l'instalateur présent dans le dossier instalateur
puis:
1 - Choisisez la langue

![choix de langue](https://github.com/Robotechnic/VJoy-arduino/blob/master/images/langue.png)

2 - Aprés l'instalation vous pouvez lire les instruction pour configurer l'arduino
![instructions](https://github.com/Robotechnic/VJoy-arduino/blob/master/images/step4.png)

3 - Atention ici vous pouvez choisir si vous instalez vjoy ou pas si vous ne l'avez pas instalé précédament instalez le c'est important pour le bon fonctionnement du logiciel.


Les joypads viennent de (ce projet)[https://github.com/officinerobotiche/simple_unav_console/tree/develop/qt_simple_unav_console/joypad]
