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

int contador = 0;
int cambio = 0;

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

void debugBotones()
{

  for(int i = 0; i < 3; i++)
  {

    Serial.print(digitalRead(botones[i]));
    Serial.print("\t");
    
  }

  Serial.println();
  
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
  
  int seg = (millis() / 1000) % 60; //sacamos los segundos de la funcion millis
  int mn = (millis() / 1000) / 60;   //sacamos los minutos de la funcion millis

  //debugBotones();

  prender[0] = seg % 10; //digito 1 de los segundos
  prender[1] = seg / 10; //digito 2 de los segundos
  prender[2] = mn % 10;
  prender[3] = mn / 10;
  
  //prenderLED(contador, prender[contador]);

  apagarTodo();

  if(!digitalRead(botones[0]))
    prenderLED(0, 1);

  if(!digitalRead(botones[1]))
    prenderLED(1, 1);

  if(!digitalRead(botones[2]))
    prenderLED(2, 1);

  /*digitalWrite(6, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(7, HIGH);
  delay(500);
  apagarTodo();
  delay(500);*/

  //delayMicroseconds(3);
  contador++;
  
  if(contador > 3)
    contador = 0;
  
  /*Serial.print("millis: ");
  Serial.print(millis());
  Serial.print("\tHora: ");
  Serial.print(m2);
  Serial.print(m1);
  Serial.print(":");
  Serial.print(s2);
  Serial.println(s1);*/

}
