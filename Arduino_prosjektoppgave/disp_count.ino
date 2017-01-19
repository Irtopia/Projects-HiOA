void from10to0()
{
  int waitDisp = 500;
  disp2_1();
  disp1_0();
  delay(1000);
  disp2_0();
  disp1_9();
  delay(waitDisp);
  disp1_8();
  delay(waitDisp);
  disp1_7();
  delay(waitDisp);
  disp1_6();
  delay(waitDisp);
  disp1_5();
  delay(waitDisp);
  disp1_4();
  delay(waitDisp);
  disp1_3();
  delay(waitDisp);
  disp1_2();
  delay(waitDisp);
  disp1_1();
  delay(waitDisp);
  disp1_0();
  delay(waitDisp);
}

//Funksjoner for tall på displayene i form av BCD-koder:
void disp1_9()
{
    digitalWrite(disp1a, HIGH);
    digitalWrite(disp1b, LOW);
    digitalWrite(disp1c, LOW);
    digitalWrite(disp1d, HIGH);  
}

void disp1_8()
{ 
  digitalWrite(disp1a, LOW);
  digitalWrite(disp1b, LOW);
  digitalWrite(disp1c, LOW);
  digitalWrite(disp1d, HIGH); 
}

void disp1_7()
{
  digitalWrite(disp1a, HIGH);
  digitalWrite(disp1b, HIGH);
  digitalWrite(disp1c, HIGH);
  digitalWrite(disp1d, LOW);
}

void disp1_6()
{
  digitalWrite(disp1a, LOW);
  digitalWrite(disp1b, HIGH);
  digitalWrite(disp1c, HIGH);
  digitalWrite(disp1d, LOW);
}

void disp1_5()
{
  digitalWrite(disp1a, HIGH);
  digitalWrite(disp1b, LOW);
  digitalWrite(disp1c, HIGH);
  digitalWrite(disp1d, LOW);  
}

void disp1_4()
{
  digitalWrite(disp1a, LOW);
  digitalWrite(disp1b, LOW);
  digitalWrite(disp1c, HIGH);
  digitalWrite(disp1d, LOW);
}

void disp1_3()
{
  digitalWrite(disp1a, HIGH);
  digitalWrite(disp1b, HIGH);
  digitalWrite(disp1c, LOW);
  digitalWrite(disp1d, LOW);
}

void disp1_2()
{
  digitalWrite(disp1a, LOW);
  digitalWrite(disp1b, HIGH);
  digitalWrite(disp1c, LOW);
  digitalWrite(disp1d, LOW);
}

void disp1_1()
{
  digitalWrite(disp1a, HIGH);
  digitalWrite(disp1b, LOW);
  digitalWrite(disp1c, LOW);
  digitalWrite(disp1d, LOW);
}

void disp1_0()
{
  digitalWrite(disp1a, LOW);
  digitalWrite(disp1b, LOW);
  digitalWrite(disp1c, LOW);
  digitalWrite(disp1d, LOW);
}

void disp2_9()
{
  digitalWrite(disp2a, HIGH);
  digitalWrite(disp2b, LOW);
  digitalWrite(disp2c, LOW);
  digitalWrite(disp2d, HIGH);  
}

void disp2_8()
{
  digitalWrite(disp2a, LOW);
  digitalWrite(disp2b, LOW);
  digitalWrite(disp2c, LOW);
  digitalWrite(disp2d, HIGH);  
}

void disp2_7()
{
  digitalWrite(disp2a, HIGH);
  digitalWrite(disp2b, HIGH);
  digitalWrite(disp2c, HIGH);
  digitalWrite(disp2d, LOW);  
}

void disp2_6()
{
  digitalWrite(disp2a, LOW);
  digitalWrite(disp2b, HIGH);
  digitalWrite(disp2c, HIGH);
  digitalWrite(disp2d, LOW);  
}

void disp2_5()
{
  digitalWrite(disp2a, HIGH);
  digitalWrite(disp2b, LOW);
  digitalWrite(disp2c, HIGH);
  digitalWrite(disp2d, LOW);  
}

void disp2_4()
{
  digitalWrite(disp2a, LOW);
  digitalWrite(disp2b, LOW);
  digitalWrite(disp2c, HIGH);
  digitalWrite(disp2d, LOW);  
}

void disp2_3()
{
  digitalWrite(disp2a, HIGH);
  digitalWrite(disp2b, HIGH);
  digitalWrite(disp2c, LOW);
  digitalWrite(disp2d, LOW);  
}

void disp2_2()
{
  digitalWrite(disp2a, LOW);
  digitalWrite(disp2b, HIGH);
  digitalWrite(disp2c, LOW);
  digitalWrite(disp2d, LOW);  
}

void disp2_1()
{
  digitalWrite(disp2a, HIGH);
  digitalWrite(disp2b, LOW);
  digitalWrite(disp2c, LOW);
  digitalWrite(disp2d, LOW);  
}

void disp2_0()
{
  digitalWrite(disp2a, LOW);
  digitalWrite(disp2b, LOW);
  digitalWrite(disp2c, LOW);
  digitalWrite(disp2d, LOW);  
}

//Viser random tall på begge Display-er:
void rand_disp()
{
  const int waitLED = 60;
  int counterDisp = 0;
  while (counterDisp < 10)
  {
    int x1 = random(0, 9);
    int x2 = random(0, 9);
    switch (x1)
    {
      case 0:
      disp1_0();
      delay(waitLED);
      break;
      case 1:
      disp1_1();
      delay(waitLED);
      break;
      case 2:
      disp1_2();
      delay(waitLED);
      break;
      case 3:
      disp1_3();
      delay(waitLED);
      break;
      case 4:
      disp1_4();
      delay(waitLED);
      break;
      case 5:
      disp1_5();
      delay(waitLED);
      break;
      case 6:
      disp1_6();
      delay(waitLED);
      break;
      case 7:
      disp1_7();
      delay(waitLED);
      break;
      case 8:
      disp1_8();
      delay(waitLED);
      break;
      case 9:
      disp1_9();
      delay(waitLED);
      break;
    }
    switch (x2)
    {
      case 0:
      disp2_0();
      delay(waitLED);
      break;
      case 1:
      disp2_1();
      delay(waitLED);
      break;
      case 2:
      disp2_2();
      delay(waitLED);
      break;
      case 3:
      disp2_3();
      delay(waitLED);
      break;
      case 4:
      disp2_4();
      delay(waitLED);
      break;
      case 5:
      disp2_5();
      delay(waitLED);
      break;
      case 6:
      disp2_6();
      delay(waitLED);
      break;
      case 7:
      disp2_7();
      delay(waitLED);
      break;
      case 8:
      disp2_8();
      delay(waitLED);
      break;
      case 9:
      disp2_9();
      delay(waitLED);
      break;
    }
    counterDisp ++;
  }
  disp2_1();
  disp1_0();
}
