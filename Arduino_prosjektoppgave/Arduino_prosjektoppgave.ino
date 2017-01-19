/*
 * Vi skal lage en "lysreklame" med 8 lysdioder og 2 7-segments diplays (tall). Vi har brukt:
 *  - Lysdiodene drives med skiftregister 74HCT595, og kobles til den med 8 motstander på 220 Ohm hver;
 *  - Displayene drives med to BCD-decoder 74HC4511, og kobles til de med 14 motstander (totalt) på 1 kOhm hver;
 *  - 13 pins fra Arduino Uno brukes for å styre totalt 24 inn/utganger;
 *  - To kblingsbrett og ledninger;
 *  - Open-source Arduino Software IDE til å programmere.
 * 
 * I dette programmet skjer:
 *  - count down fra "10" til "0";
 *  - etterfulgt av LED-ene av og på i en viss rekkefølge, 4 ganger;
 *  - tilfeldig tall på displayene;
 *  - tilbake til "10".
 *  
 * Vi har to knapper:
 *  - button1 av: ingenting skjer, diplay1 viser 0, display2 viser 1 ("10");
 *  - button1 på (en gang): loop-en kjøres automatisk, i det uendelige;
 *  - button1 på ved siste steg (etter rand_Disp() fksjn): gir overgang til button2;
 *  - button2: trykk gir overgang til neste tilstand isekvensen.
 *  - button1 på når som helst: starter loop-en fra "10", til vi trykker på den igjen, ved siste steg.
*/

//Display nr 1, fra Arduino til BCD-dekoder (74HC4511):
const int disp2a = 13;
const int disp2b = 12;
const int disp2c = 11;
const int disp2d = 10;
//Display nr 2, fra Arduino til BCD-dekoder (74HC4511):
const int disp1a = 9;
const int disp1b = 8;
const int disp1c = 7;
const int disp1d = 6;
//Lysdiodene, fra Arduino til skiftregisteret (74HCT595):
const int SH_CP = 5;
const int ST_CP = 4;
const int DS = 3;
//Knapper:
const int button1 = 1; //grønn
const int button2 = 2; //hvit
//Øvrige variabler som brukes over hele programmet:
int button1State;
int counter1;
int button2State;
int counter2;

void setup()
{
  //Display-ene (74HC4511):
  pinMode(disp1a, OUTPUT); //Display nr 1 som outputs
  pinMode(disp1b, OUTPUT);
  pinMode(disp1c, OUTPUT);
  pinMode(disp1d, OUTPUT);
  pinMode(disp2a, OUTPUT); //Display nr 2 som outputs
  pinMode(disp2b, OUTPUT);
  pinMode(disp2c, OUTPUT);
  pinMode(disp2d, OUTPUT);
  //Skiftregister (74HCT595):
  pinMode(SH_CP, OUTPUT); //ClockPin
  pinMode(ST_CP, OUTPUT); //LatchPin
  pinMode(DS, OUTPUT); //DataPin
  pinMode(button1, INPUT_PULLUP); //Knapper som inputs
  pinMode(button2, INPUT_PULLUP);
  write_reg(); //Setter standardverdi av alle lysdiodene til LAV
  disp2_1(); //Setter standardverdi av displayene til "10" (disp2 = 1, disp1 = 0)
  disp1_0();
  counter1 = 0; //Setter standardverdi av counter1&2 til null
  counter2 = 0;
}

boolean registers[8]; //8 pins fra skiftregisteret = 8 "adresser" i minnen

void loop()
{
  int waitCount = 400;
  button1State = digitalRead(button1);
  button2State = digitalRead(button2);
  if (button1State == LOW)
  {
    counter1++;
    delay(waitCount);
    if (counter1 > 1)
    {
      counter1 = 0;
    }
  }
  while ((button1State == HIGH)&&(counter1 == 1))
  {
    automatic();
    return;
  }
  if (button2State == LOW)//&&(counter1 >= 1))
  {
    counter2++;
    delay(waitCount);
  }
  controlled();
}
