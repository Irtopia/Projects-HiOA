
//en funskjon som tar inn tre verdier som representerer, rødt, gult eller grønt lys i hoved-lyskrysset og sender verdiene videre til nxt-hjernen over bluetooth

void bluetooth(int lys)                                       
{
  if(lys==1)                                                  //hvis lyset er grønt som tilsvarer verdien 1, gå inn i if-setningen
  {
   byte melding1[] = {10, 0, 128, 9, 0, 6, 1, 0, 0, 0, 0, 0}; //setter variabelen melding1 til datatypen byte og tilegner variabelen melding1 et array med 12 bytes med 12 plasser fra 0-11
   Serial.write(melding1,12);                                 //sender arraeyet med 12 bytes som representerer tallet 1 over bluetooth til nxt-hjernen
   delay(200);                                                //venter 200 milisekunder
  }
  
  if (lys==2)                                                 //hvis lyset er rødt som tilsvarer verdien 2, gå inn i if-setningen
  {
   byte melding2[] = {10, 0, 128, 9, 0, 6, 2, 0, 0, 0, 0, 0}; 
   Serial.write(melding2,12);                                 //sender arraeyet med 12 bytes som representerer tallet 2 over bluetooth til nxt-hjernen
   delay(200);                                                //venter 200 milisekunder
  }
    
  if (lys==3)                                                 //hvis lyset er gult som tilsvarer verdien 3, gå inn i if-setningen
  {
   byte melding3[] = {10, 0, 128, 9, 0, 6, 3, 0, 0, 0, 0, 0};
   Serial.write(melding3,12);                                 //sender arraeyet med 12 bytes som representerer tallet 3 over bluetooth til nxt-hjernen
   delay(200);
  }
}
