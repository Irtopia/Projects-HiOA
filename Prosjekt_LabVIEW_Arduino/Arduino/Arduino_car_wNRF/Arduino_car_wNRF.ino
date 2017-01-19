#include <SPI.h>
#include "RF24.h"

RF24 myRadio(7, 8);
byte adresses[][6] = {"0"}; // PIPE adress til 0

int motors[] = {3, 5, 6, 9}; // PMW pinenen som motorene er koblet til
int f1 = 3, f2 = 9, b1 = 5, b2 = 6; // f1 = side 1 forover, f2 = side 2 forover, b1 = siden 1 bakover, b2 = side 2 bakover
int motorSpeed; // Variabelen som bestemmer farten til motorene
int i; // teller

struct variabels // Structen som lagrer verdier fra den serielle kommunikasjonen mellom arduino og LabVIEW serveren
{
  int forward, backward, gir, dir;
  String forwardString, backwardString, dirString, girString;
};
typedef struct variabels Variabels;
Variabels movment;


void setup()
{
  Serial.setTimeout(5); // Setter dalayen for seriell lesing til 5ms
  Serial.begin(115200); // Setter baudrate til 115200

  myRadio.begin();
  myRadio.setChannel(115); // setter Channel 115
  myRadio.setPALevel(RF24_PA_MAX); // max transmitting power
  myRadio.setDataRate(RF24_250KBPS); //datarate, laveste, for å få best mulig avstand
  myRadio.openReadingPipe(1, adresses[0]); // Åpner pipen for å kommunisere
  myRadio.startListening();

  for (i = 0; i < 5; i++)
    pinMode(motors[i], OUTPUT); // setter alle motorpinnene som output


  for (i = 0; i < 5; i++)
    digitalWrite(motors[i], LOW); // setter alle motorene av
}


void loop()
{
  if (myRadio.available())
  {
    myRadio.read( &movment, sizeof(movment));
    motorSpeed = motor_speed(movment.gir); // setter hastigheten til motorene ved å hente gir variabelen i movment structen og utføre den i motor_speed funksjonen
    if (movment.forward == 1 && movment.backward == 0) // hvis R2 på PS4 kontrollen er trykket
    {
      if (movment.dir > 50) // skjekker om det er noe retningsverdi
      {
        analogWrite(f1, motorSpeed);
        analogWrite(f2, LOW); // svinger mot høyre ved å redusere farten til venstre motorene
        digitalWrite(b1, LOW);
        digitalWrite(b2, LOW);
      }

      else if (movment.dir < -50)
      {
        analogWrite(f1, LOW); // svinger mot venstre ved å redusere farten til høyre motorene
        analogWrite(f2, motorSpeed );
        digitalWrite(b1, LOW);
        digitalWrite(b2, LOW);
      }

      else
      {
        analogWrite(f1, motorSpeed);
        analogWrite(f2, motorSpeed); //default kjører ratt fram
        digitalWrite(b1, LOW);
        digitalWrite(b2, LOW);
      }
    }


    if (movment.backward == 1 && movment.forward == 0) // skjekker om L2 er presset på kontroller
    {
      if (movment.dir > 50)
      {
        analogWrite(b1, motorSpeed);
        analogWrite(b2, LOW);
        digitalWrite(f1, LOW);
        digitalWrite(f2, LOW);
      }

      else if (movment.dir < -50)
      {
        analogWrite(b1, LOW);
        analogWrite(b2, motorSpeed);
        digitalWrite(f1, LOW);
        digitalWrite(f2, LOW);
      }

      else
      {
        analogWrite(b1, motorSpeed);
        analogWrite(b2, motorSpeed);
        digitalWrite(f1, LOW);
        digitalWrite(f2, LOW);
      }
    }


    if(movment.backward == 0 && movment.forward == 0) // når begge L2 og R2 verdiene er lave stopper alle motrene
    {
      for(i = 0; i < 5; i++)
      {
        digitalWrite(motors[i], LOW);
      }
    }

    if (movment.backward == 1 && movment.forward == 1) // når begge L2 og R2 verdiene er høye så vil motorene også stoppe
    {
      for (i = 0; i < 5; i++)
      {
        digitalWrite(motors[i], LOW);
      }
    }
  }
}

int motor_speed(int  var)  // Funksjon som returenerer PMW verdien til motor utifra hvilket gir
{
  switch (var)
  {
    case 1:
      return 200;
      break;
    case 2:
      return 220;
      break;
    case 3:
      return 240;
      break;
    case 4:
      return 254;
      break;
    default:
      return 0;
      break;
  }
}

