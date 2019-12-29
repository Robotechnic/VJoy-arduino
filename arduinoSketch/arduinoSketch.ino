int const nombreCanaux = 6; //ici régler le nombre de canaux de la radio
int const filtre =  10; //filtre pour éviter les glish
int channel[nombreCanaux];
int dernierChannelLut[nombreCanaux];
int conte=0;
String texte = "";

void setup()
{
 Serial.begin(9600);
 pinMode(3, INPUT); // branchement du +
}

void loop()
{
 if(pulseIn(3, HIGH) > 3000)//si on ressois quelque chose
 { 
   for(int i = 0; i <= nombreCanaux-1; i++)
   {
     channel[i]=pulseIn(3, HIGH);
   }
   for(int i = 0; i <= nombreCanaux-1; i++)
   {
     if((channel[i] > 2000) || (channel[i] <100))
     {
      channel[i]= dernierChannelLut[i]; 
     }
     else
     {
      channel[i]=(dernierChannelLut[i]+channel[i])/2;
      conte++;
     }
   }

 }
 if(conte > filtre)
 {
     texte = ""; //initialisation du texte
     for(int i = 0; i <= nombreCanaux-1; i++)
     {
       texte += String(channel[i])+":"; // fabrication du texte a envoyer
       dernierChannelLut[i]=channel[i];
     }
     Serial.println(texte); // envoi du texte
     conte=0;
 }
}
