//inkludering av bibliotekene for styring av PS4 Bluetooth Controller
#include <PS4BT.h>
#include <usbhub.h>

#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

int forward = 0, backward = 0, halt = 0;
int valX, speedVal = 1;
int connection = 0;
const String connectON = "Controller connected", connectOFF = "Controller disconnected", request = "Press PS to connect controller";
const String r2 = "R2: ", l2 = " L2: ", x = " X: ", zero = "0 ", speedString = " Sp: ";
String stringToSend;


USB Usb;
BTD Btd(&Usb);
PS4BT PS4(&Btd);

void setup()
{
  // Seriell kommunikasjon må skje raskere enn vanlig, for å lese fra Controlleren
  Serial.begin(115200);
  Serial.setTimeout(5);
  
  #if !defined(__MIPSEL__)
  #endif
  if (Usb.Init() == -1)
  {
    while (1); // Halt
  }
}

void loop()
{
  Usb.Task();
  // Hvis Controlleren er connected
  if (PS4.connected())
  {
    // Skriver det bare en gang
    if (connection == 0 || connection == 2)
    {
      Serial.println(connectON.length());
      Serial.println(connectON);
      delay(1000);
      connection = 1;
    }

    // Vi bestemmer at R2 og L2 skal sende digitale verdier, men joysticken analoge verdier
    valX = PS4.getAnalogHat(LeftHatX);
    forward = PS4.getButtonClick(R2);
    backward = PS4.getButtonClick(L2);

    // Verdien på farten bestemmes 
    if (PS4.getButtonClick(CROSS) == 1)
    {
      speedVal = 1;
    }
    if (PS4.getButtonClick(SQUARE) == 1)
    {
      speedVal = 2;
    }
    if (PS4.getButtonClick(TRIANGLE) == 1)
    {
      speedVal = 3;
    }
    if (PS4.getButtonClick(CIRCLE) == 1)
    {
      speedVal = 4;
    }

    // Sender commandoen
    if (forward > 0 || backward > 0)
    {
      stringToSend =  r2 + String(forward) + l2 + String(backward) + x + String(valX) + speedString + String(speedVal) + "\t";
      Serial.println(stringToSend.length());
      Serial.println(stringToSend);
    }

    // stopper bilen
    if (PS4.getButtonClick(R1) > 0)
    {
      stringToSend =  r2 + zero + l2 + zero + x + String(valX) + speedString + zero + "\t";
      Serial.println(stringToSend.length());
      Serial.println(stringToSend);
    }

    // stopper bilen og kobler Controlleren av
    if (PS4.getButtonClick(PS))
    {
      stringToSend =  r2 + zero + l2 + zero + x + String(valX) + speedString + zero + "\t";
      Serial.println(stringToSend.length());
      Serial.println(stringToSend);
      Serial.println(connectOFF.length());
      Serial.println(connectOFF);
      connection = 0;
      PS4.disconnect();
    }
  }

  // Hvis Controlleren ikke er connected skriver Arduino dette bare en gang
  else if (connection == 0 || connection == 1)
  {
    Serial.println(request.length());
    Serial.println(request);
    connection = 2;
  }
}
