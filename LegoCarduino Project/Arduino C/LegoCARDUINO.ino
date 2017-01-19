
//*************LegoCarduino***********************
  
int var[] = {3,4,5,6,7,8,9,10};              //bestemmer hvilken plass i arrayet portene skal stå på

//navngir variabler og setter variablene til sine ulike plasser og porter i arrayet  
int hovedRod = var[0], hovedGul = var[1], hovedGronn = var[2], sideRod = var[3], sideGul = var[4]; 
int sideGronn = var[5], goendeRod = var[7], goendeGronn = var[6];
int hovedKnappVerdi = 2;
int sensTrig = 12; 
int sensEcho = 11;
int i = 0;                                       //setter telleren "i" lik 0  
bool skiftLys = false;


//setter de ulike fargene til fargenavn som ikke kan endre verdi gjennom programmet

#define gronn 0                                 
#define gul 1
#define rod 2
#define gulrod 3
#define gronnBlink 4
#define hvit 5



void setup() 
{
  Serial.begin(9600);
  for(i=0;i<8;i++)
  {
    pinMode(var[i], OUTPUT);                    //setter pinne 3,4,6,7,8,9,10,11 til å være utganger
  }

  pinMode(hovedKnappVerdi, INPUT_PULLUP);       //setter pinne 2 til å være en inngang med pullup slik at knappen ikke blir følsom for små forstyrrelser
  pinMode(sensEcho, INPUT);                     //setter den ene pinnen til sensoren som inngang(leser signaler som sendes ut av sensTrig)
  pinMode(sensTrig, OUTPUT);                    //setter den andre pinnen til sensoren som utganger(sender ut signaler som leses av sensEcho)
}

void loop() 
{  
  long avstand;
  long varighet;
  int avstandsVerdi = 0;

  /*while-løkka gjør at programmet settes i standardtilstand med hovedlys grønt, side-og gåendelys rødt
  sjekker hele tiden avstand til sensoren eller om knappen trykkes på
  */
  while(avstandsVerdi == 0)
  {  
    settHovedLys(gronn);                                                       
    settGoendeLys(rod);
    settSideLys(rod);
    int hovedKnappVerdi = digitalRead(2);
    
    //måler og regner ut avstand til eventuelle objekter med avstandssensoren 
    
    digitalWrite(sensTrig, LOW);
    delay(2);
    digitalWrite(sensTrig, HIGH);
    delay(10);
    digitalWrite(sensTrig, LOW);
    varighet = pulseIn(sensEcho, HIGH);           
    avstand = (varighet/2)/29.1;                  //avstand måles i cm

    //når knappen trykkes eller et objekt har en avstand mindre enn ca.5cm fra sensoren, så starter programmet
 
    if (avstand < 5)                            
    {
      avstandsVerdi = 1;
    }
    if(hovedKnappVerdi == LOW)
    {
      avstandsVerdi = 1;
      delay(200);
    }
  }
       
    /*kaller de ulike funksjonene som endrer farge på lyskryssene og sender bluetooth-signaler. 
    Denne sekvensen bytter hovedlyset til rødt, og sidelys samt gående lys til grønt.
    Når hovedlyset endrer seg fra grønt til gult og fra gult til rødt, sendes bluetooth signalene, 1,2 og 3 til NXT-roboten. 
    Tallene 1-3 tilsvarer: Grønt lys(1), gult lys(2) og rødt lys(3).  
    På slutten av sekvensen går lyskrysset tilbake til standardtilstand: Hovedlys grønt, sidelys samt gående lys rødt.
    */
     
  while(avstandsVerdi == 1)           
  {
    delay(500);            
    settHovedLys(gul);                       
    settSideLys(gulrod);   
    settHovedLys(rod); 
    settSideLys(gronn);           
    settGoendeLys(gronn); 
    delay(10000); 
    settSideLys(gul); 
    settGoendeLys(gronnBlink); 
    settHovedLys(gulrod);  
    settSideLys(rod);  
    settGoendeLys(rod); 
    settHovedLys(gronn); 
    avstandsVerdi = 0;
   }                                                         
}


