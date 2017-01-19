void settHovedLys(int farge)
{
  unsigned long tidFor = 0, tidEtter = 0, tidTot = 0;
  tidFor = millis();
  
  if (farge == gronn)
  {
    digitalWrite(hovedGronn, HIGH);
    digitalWrite(hovedRod, LOW);
    digitalWrite(hovedGul, LOW);   
    bluetooth(1);
  }
  
  while (farge == gul)
  {
    digitalWrite(hovedGronn, LOW);
    digitalWrite(hovedRod, LOW);
    digitalWrite(hovedGul, HIGH); 
    bluetooth(3);
    if (tidTot > 1500)
    {
      tidFor = tidEtter;
      farge = hvit;
    }
    tidEtter = millis();
    tidTot = tidEtter - tidFor; 
  }
  
  while (farge == rod)
  {
    digitalWrite(hovedGronn, LOW);
    digitalWrite(hovedRod, HIGH);
    digitalWrite(hovedGul, LOW); 
    bluetooth(2);
    if (tidTot > 1000)
    {
      tidFor = tidEtter;
      farge = hvit;
    }
    tidEtter = millis();
    tidTot = tidEtter - tidFor; 
  }

  while (farge == gulrod)
  {
    tidFor = millis();
    digitalWrite(hovedGronn, LOW);
    digitalWrite(hovedRod, HIGH);
    digitalWrite(hovedGul, LOW); 
    bluetooth(2);
    if (tidTot > 2000)
    {
      tidFor = tidEtter;
      farge = hvit;
    }
    tidEtter = millis();
    tidTot = tidEtter - tidFor; 
  }
}
