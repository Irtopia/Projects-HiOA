//Funksjonen som skifter bits i skiftregisteret,
//og tar på eller av enkelte lysdioder:
void write_reg()
{
  digitalWrite(ST_CP, LOW);
  for (int i = 7; i >= 0; i --)
  {
    digitalWrite(SH_CP, LOW);
    digitalWrite(DS, registers[i]);
    digitalWrite(SH_CP, HIGH);
  }
  digitalWrite(ST_CP, HIGH);
}
