//funksjonen skrur av begge lys for gående, for deretter å sette lyset grønt, rødt eller blinke grønt, ettersom hvilken farge som angis når funksjonen kalles fra void loop

void settGoendeLys(int farge)
{
  digitalWrite(goendeGronn, LOW);
  digitalWrite(goendeRod, LOW);
  if (farge == gronn)
  {
    digitalWrite(goendeGronn, HIGH);
  }
  else if (farge == rod)
  {
    digitalWrite(goendeRod, HIGH);
  }
  else if (farge == gronnBlink)
  {
    int teller = 0;
    while (teller < 8)
    {
      digitalWrite(goendeGronn,HIGH);
      delay(200);
      digitalWrite(goendeGronn,LOW);
      delay(200);      
      teller = teller+1;
    }
  }
}
