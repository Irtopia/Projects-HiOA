//funksjonen skrur av alle lys for hovedgate, for deretter å sette lyset grønt, rødt , gulrødt eller gult, ettersom hvilken farge som angis når funksjonen kalles fra void loop

void settHovedLys(int farge)
{
 digitalWrite(hovedGronn, LOW);  
 digitalWrite(hovedRod, LOW);
 digitalWrite(hovedGul, LOW);     
 if (farge == gronn)
 {
  digitalWrite(hovedGronn, HIGH);
 }
 else if(farge == gul)
 {
  digitalWrite(hovedGul, HIGH);
 }
 else if (farge == rod)
 {
  digitalWrite(hovedRod, HIGH);
 }
 else if (farge == gulrod)
 {
  digitalWrite(hovedGul, HIGH);
  digitalWrite(hovedRod, HIGH);
 }

}
