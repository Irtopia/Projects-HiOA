//funksjonen skrur av alle lys for sidegate, for deretter å sette lyset grønt, rødt, gulrødt eller gult, ettersom hvilken farge som angis når funksjonen kalles fra void loop

void settSideLys(int farge)
{
 digitalWrite(sideGronn, LOW);
 digitalWrite(sideGul, LOW);
 digitalWrite(sideRod, LOW);
 if (farge == gronn)
 {
  digitalWrite(sideGronn, HIGH);
 }
 else if (farge == gul)
 {
  digitalWrite(sideGul, HIGH);
 }
 else if (farge == rod)
 {
  digitalWrite(sideRod, HIGH);
 }
 else if (farge == gulrod)
 {
  digitalWrite(sideRod, HIGH);
  digitalWrite(sideGul, HIGH);
 }
}
