void automatic()
{
  from10to0();
  int counter = 0;
  while (counter < 4)
  {
    for (int i = 0; i < 8; i++)
    {
      registers[i] = HIGH;
      delay(25);
      write_reg();
    }
    for (int i = 7; i >= 0; i--)
    {
      registers[i] = LOW;
      delay(25);
      write_reg();
    }
    counter ++;
  }
  rand_disp();
  disp2_1();
  disp1_0();
}
