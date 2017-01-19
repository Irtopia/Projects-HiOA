void controlled()
{
  int counter = 0;
  switch (counter2)
  {
    case 1:
    disp2_0();
    disp1_9();
    break;
    case 2:
    disp1_8();
    break;
    case 3:
    disp1_7();
    break;
    case 4:
    disp1_6();
    break;
    case 5:
    disp1_5();
    break;
    case 6:
    disp1_4();
    break;
    case 7:
    disp1_3();
    break;
    case 8:
    disp1_2();
    break;
    case 9:
    disp1_1();
    break;
    case 10:
    disp1_0();
    break;
    case 11:
    while (counter < 1)
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
      counter++;
    }
    break;
    case 12:
    rand_disp();
    counter2 = 0;
    counter1 = 2;
    break;
  }
}
