#include <SPI.h>
#include "RF24.h"

RF24 myRadio(7, 8);
byte adresses[][6] = {"0"}; // PIPE adress til 0

String stringToSend = ""; //Lagrer feedbacken som skal sendes fra brettet til LabVIEW serveren
const String frwrd = "Forward - ", frwrdLft = "Forward left - ", frwrdRght = "Forward right - "; //Variablene som skal skriver til feedback
const String bckwrd = "Backward - ", bckwrdLft = "Backward left - ", bckwrdRght = "Backward right - ";
const String spd = "Speed: ", stp = "Stop", error = "To many inputs", notacmd = "Not a command";

int i, motorSpeed;
const int Direction[] = {2, 3, 4, 5, 6};
const int Back = Direction[0], Left = Direction[1], Stop = Direction[2], Right = Direction[3], Go = Direction[4];

struct variabels // Structen som lagrer verdier fra den serielle kommunikasjonen mellom arduino og LabVIEW serveren
{
  int forward, backward, gir, dir;
  String forwardString, backwardString, dirString, girString;
};
typedef struct variabels Variabels;
Variabels movment;

void setup()
{
  for (i = 0; i < 5; i++)
    pinMode(Direction[i], OUTPUT);

  Serial.setTimeout(5);
  Serial.begin(115200);

  myRadio.begin();
  myRadio.setChannel(115); // setter Channel 115
  myRadio.setPALevel(RF24_PA_MAX); // max transmitting power
  myRadio.setDataRate(RF24_250KBPS); //datarate, laveste, for å få best mulig avstand
  myRadio.openWritingPipe( adresses[0]); // Åpner pipen for å kommunisere
}

void loop()
{
  movment.forwardString = Serial.readStringUntil(' '); // Skjekker om første ord i seriellen er R2
  if (movment.forwardString == "R2:")
  {
    serial_read();
    myRadio.write(&movment, sizeof(movment));
    motorSpeed = motor_speed(movment.gir);
    if (movment.forward == 1 && movment.backward == 0) // hvis R2 på PS4 kontrollen er trykket
    {
      if (movment.dir > 50)
      {
        lights_out();
        digitalWrite(Go, HIGH);
        digitalWrite(Right, HIGH);
        stringToSend = frwrdRght + spd + String(motorSpeed) + "\t"; // lagrer stringen som skal sendes i feedback
      }

      else if (movment.dir < -50)
      {
        lights_out();
        digitalWrite(Go, HIGH);
        digitalWrite(Left, HIGH);
        stringToSend = frwrdLft + spd + String(motorSpeed) + "\t";
      }

      else
      {
        lights_out();
        digitalWrite(Go, HIGH);
        stringToSend = frwrd + spd + String(motorSpeed) + "\t";
      }
    }

    if (movment.backward == 1 && movment.forward == 0) // skjekker om L2 er presset på kontroller
    {
      if (movment.dir > 50)
      {
        lights_out();
        digitalWrite(Back, HIGH);
        digitalWrite(Right, HIGH);
        stringToSend = bckwrdRght + spd + String(motorSpeed) + "\t";
      }

      else if (movment.dir < -50)
      {
        lights_out();
        digitalWrite(Back, HIGH);
        digitalWrite(Left, HIGH);
        stringToSend = bckwrdLft + spd + String(motorSpeed) + "\t";
      }

      else
      {
        lights_out();
        digitalWrite(Back, HIGH);
        stringToSend = bckwrd + spd + String(motorSpeed) + "\t";
      }
    }

    if (movment.backward == 0 && movment.forward == 0) // når begge L2 og R2 verdiene er lave stopper alle motrene
    {
      lights_out();
      digitalWrite(Stop, HIGH);
      stringToSend = stp; // lagrer stringen som skal sendes til feedback
    }

    if (movment.backward == 1 && movment.forward == 1) // når begge L2 og R2 verdiene er høye så vil motorene også stoppe
    {
      lights_out();
      digitalWrite(Stop, HIGH);
      stringToSend = error;
    }
  }

  if (movment.forwardString != "R2:" && movment.forwardString != "") // Hvis stringen som blir sendt i seriell ikke
  {
    lights_out();
    digitalWrite(Stop, HIGH);
    stringToSend = notacmd; // starter med R2 så vil feedbacken sendte stringen Not a command
  }

  if (stringToSend != "") // så lenge tilbakesending av stringen ikke er tom, så vil den returne lengden til stringen samt selve stringen
  {
    Serial.println(stringToSend.length());
    Serial.println(stringToSend);
    stringToSend = ""; // også setter den til ingenting
  }
}

void serial_read()
{
  movment.forward = Serial.readStringUntil(' ').toInt();
  movment.backwardString = Serial.readStringUntil(' ');
  movment.backward = Serial.readStringUntil(' ').toInt();
  movment.dirString = Serial.readStringUntil(' ');
  movment.dir = Serial.readStringUntil(' ').toInt() - 124;
  movment.girString = Serial.readStringUntil(' ');
  movment.gir = Serial.readStringUntil('\0').toInt();
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

