int columnas[4] = {6, 5, 4, 3};
int filas[4] = {7, A3, A2, A1}; //A1, A2, A3, 7
int botones[3] = {2, 9, 10};
byte prender[4] = {0, 0, 0, 0};

/*
   __   __
  |B2| |B1|
      _      _    __
F3   |_|  _ |_|  |B0|
F2 _ |_| |_||_|
F1|_||_| |_||_|
F0|_||_|:|_||_|
  C3 C2  C1 C0


*/

int b1 = 0;
int b2 = 0;
int b3 = 0;

int bk1 = 0;
int bk2 = 0;

int contador = 0;
int estado = 0;

int setHrs = 0;
int setMin = 0;
int setSeg = 0;

void apagarTodo()
{

  for(int i = 0; i < 4; i++)
  {
  
    digitalWrite(columnas[i], HIGH);
    digitalWrite(filas[i], LOW);
  
  }
  
}

void prenderLED(int columna, byte fila)
{
  
  apagarTodo();
  
  digitalWrite(columnas[columna], LOW);
  for(int i = 0; i < 4; i++)
    digitalWrite(filas[i], bitRead(fila, i));
  
}

void debugHora(int mn, int seg)
{

  Serial.print("millis: ");
  Serial.print(millis());
  Serial.print("\tHora: ");
  Serial.print(mn);
  Serial.print(":");
  Serial.println(seg);
  
}

void debugBotones()
{
  
  apagarTodo();
  if(!digitalRead(botones[0]))
    prenderLED(0, 1);

  if(!digitalRead(botones[1]))
    prenderLED(1, 1);

  if(!digitalRead(botones[2]))
    prenderLED(2, 1);  
  
}

void setup()
{

  //Serial.begin(9600);
  
  for(int i = 0; i < 4; i++)
  {
  
    pinMode(columnas[i], OUTPUT);
    pinMode(filas[i], OUTPUT);
  
  }
  
  for(int i = 0; i < 3; i++)
    pinMode(botones[i], INPUT_PULLUP);

  apagarTodo();

}

void loop()
{
  
  int seg = ((millis() - setSeg) / 1000) % 60; //sacamos los segundos de la funcion millis
  int mn = (((millis() - setSeg) / 1000) + setMin) / 60;   //sacamos los minutos de la funcion millis
  int hrs = ((mn / 60) + setHrs) % 24;

  prender[0] = 0;
  prender[1] = 0;
  prender[2] = 0;
  prender[3] = 0;

  //debugBotones();
  //debugHora(mn, seg);

  if(!digitalRead(botones[0]) && b1 == 0)
    b1 = 1;

  if(digitalRead(botones[0]) && b1 == 1)
  {
    
    estado++;

    if(estado > 3)
      estado = 0;

    b1 = 0;
    
  }

  if(estado == 0) //Muestra horas y minutos
  {
    
    prender[0] = mn % 10;
    prender[1] = (mn / 10) % 6;
    prender[2] = hrs % 10;
    prender[3] = hrs / 10;

    if(mn == 0 && hrs == 0) //Easter Egg
    {
      
      prender[0] = 15;
      prender[1] = 15;
      prender[2] = 15;
      prender[3] = 15;
      
    }
    
  }

  else if(estado == 1) //Segundos
  {
    
    prender[0] = seg % 10; //digito 1 de los segundos
    prender[1] = seg / 10; //digito 2 de los segundos
    prender[2] = 0;
    prender[3] = 0;

    if(!digitalRead(botones[1]) && bk1 == 0)
      bk1 = 1;

    if(digitalRead(botones[1]) && bk1 == 1)
    {

      estado--;
      bk1 = 0;
      
    }
  
  }

  else if(estado == 2) //Animacion
  {

    prender[0] = 7;
    prender[1] = 3;
    prender[2] = 15;
    prender[3] = 1;

    if(!digitalRead(botones[1]) && bk2 == 0)
      bk2 = 1;

    if(digitalRead(botones[1]) && bk2 == 1)
    {

      estado--;
      bk2 = 0;
      
    }
    
  }

  else if(estado == 3)
  {

    prender[0] = mn % 10;
    prender[1] = (mn / 10) % 6;
    prender[2] = hrs % 10;
    prender[3] = hrs / 10;

    if(!digitalRead(botones[1]) && b2 == 0)
      b2 = 1;

    if(digitalRead(botones[1]) && b2 == 1)
    {

      setMin += 60;
      b2 = 0;
      
    }

    if(!digitalRead(botones[2]) && b3 == 0)
      b3 = 1;

    if(digitalRead(botones[2]) && b3 == 1)
    {

      setHrs++;
      b3 = 0;
      
    }
    
    setSeg = millis();
    
  }
  
  prenderLED(contador, prender[contador]);

  //prenderLED(1, 15);
  //prenderLED(2, 2);

  contador++;
  
  if(contador > 3)
    contador = 0;
    
}
