//11010000 10111111 11010001 10000000 11010000 10111110 11010000 10110101 11010000 10111010 11010001 10000010 100000 11010000 10011100 11010000 10110000
//11010001 10000001 11010000 10111011 11010000 10111110 11010000 10110010 11010000 10110000 101110 11010000 10011000 101110 11010000 10010000 101110

unsigned char i;
unsigned char j;
int CLK = 10;
int CS = 9;
int DIN = 8;

int com = 0;
int x = 0;
int y = 0;
int values[10][10] = {
  {1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1}, 
  {1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,2,0,0,0,0,1}, // 2 - точка отсчета.
  {1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1}
};

unsigned char znach[8] = {
     0x80, 0x40, 
     0x20, 0x10, 
     0x08, 0x04, 
     0x02, 0x01 
    };

void setup() 
{
    pinMode(CLK, OUTPUT);
    pinMode(CS, OUTPUT);
    pinMode(DIN, OUTPUT);
     Serial.begin(9600);

}

 void vid()
      {
        Serial.println("");
        Serial.println("Заполненность массива: ");
        for(int i = 0; i<10; i++) 
      {
          for(int j = 0; j<10; j++)
          {
            Serial.print(values[i][j]);
          }
            //delay(0);
            Serial.println("");
      }
    Serial.println("----------");
    //delay(400); //------------------------------------------------
  }

  void search()
    {
      Serial.println("Проверка_ячеек: ");
      for(int i = 0; i<10; i++) 
      {
          for(int j = 0; j<10; j++)
          {
            if(values[i][j] == 2)
            { 
              Serial.print(" ПРОГРЕСС ");
              Serial.print("x:");
              Serial.print(i);
              Serial.print(" y:");
              Serial.print(j);
              x = i;
              y = j;
            }
              else if(values[i][j] == 1)
                  {
                    Serial.print(" барьер ");
                    Serial.print("x:");
                    Serial.print(i);
                    Serial.print(" y:");
                    Serial.print(j);
                    
                  }
              else{Serial.print(" error");}
          }
            //delay(250); //------------------------------------------------------
            Serial.println("");
      }
      Serial.print("-------------");
    }

void control() // управление за счет клавишь(asdw) в порт.
{
  com = 0;
  //delay(300); //-------------------------------------------------------------------
  com = Serial.read() - '0'; 
  Serial.println("");
  Serial.print("Введенное значение = ");
  Serial.print(com); //ВАЖНО!!!! выводит все значения по таблице ASCII, но если указать Serial.read() - '0'; то инвертирует их обратно в десятичную. 
  if(com == 71) // 71 = w
      {
        Serial.println("");
        Serial.print("Положение ");
        Serial.print("x:");
        Serial.print(x);
        Serial.print(" y:");
        Serial.print(y);
          if(values[x-1][y]==0)
        {
          values[x][y] = 0;
          x=x-1;
          values[x][y] = 2;
          Serial.println("");
          Serial.print("Новое Положение ");
          Serial.print("x:");
          Serial.print(x);
          Serial.print(" y:");
          Serial.print(y);
          Serial.println("");
        }
          else{Serial.println("");Serial.print("ОШИБКА, стена");}
      }
        else if(com == 67) // 67 = s
            {
              Serial.println("");
              Serial.print("Положение ");
              Serial.print("x:");
              Serial.print(x);
              Serial.print(" y:");
              Serial.print(y);
                if(values[x+1][y]==0)
               {
                 values[x][y] = 0;
                 x=x+1;
                 values[x][y] = 2;
                 Serial.println("");
                 Serial.print("Новое положение ");
                 Serial.print("x:");
                 Serial.print(x);
                 Serial.print(" y:");
                 Serial.print(y);
                 Serial.println("");
               }
                 else{Serial.println("");Serial.print("ОШИБКА, стена");}
            }
              else if(com == 49) // 49 = a
                  {
                    Serial.println("");
                    Serial.print("Положение ");
                    Serial.print("x:");
                    Serial.print(x);
                    Serial.print(" y:");
                    Serial.print(y);
                      if(values[x][y-1]==0)
                    {
                      values[x][y] = 0;
                      y=y-1;
                      values[x][y] = 2;
                      Serial.println("");
                      Serial.print("Новое положение ");
                      Serial.print("x:");
                      Serial.print(x);
                      Serial.print(" y:");
                      Serial.print(y);
                      Serial.println("");
                    }
                      else{Serial.println("");Serial.print("ОШИБКА, стена");}
                  }
                     else if(com == 52) // 52 = d
                         {
                           Serial.println("");
                           Serial.print("Положение ");
                           Serial.print("x:");
                           Serial.print(x);
                           Serial.print(" y:");
                           Serial.print(y);
                            if(values[x][y+1]==0)
                          {
                            values[x][y] = 0;
                            y=y+1;
                            values[x][y] = 2;
                            Serial.println("");
                            Serial.print("Новое положение ");
                            Serial.print("x:");
                            Serial.print(x);
                            Serial.print(" y:");
                            Serial.print(y);
                            Serial.println("");
                         }
                            else{Serial.println("");Serial.print("ОШИБКА, стена");}
                         }
  
}

  void M7219byte(unsigned char DATA) 
    {
        unsigned char i;
        digitalWrite(CS, LOW);
        for (i = 8; i >= 1; i--) 
       {
        digitalWrite(CLK, LOW);
        digitalWrite(DIN, DATA & 0x80);
        DATA = DATA << 1;
        digitalWrite(CLK, HIGH);
       }
    }
                    
      void M7219(unsigned char address, unsigned char dat) 
       {
        digitalWrite(CS, LOW);
        M7219byte(address);
        M7219byte(dat);
        digitalWrite(CS, HIGH);
       }
       
void loop() {
//  int a = analogRead(A0);
//  int b = analogRead(A1);
//  float v = b * (10.0 / 1023.0);
//  float v1 = a * (10.0 / 1023.0);
//  int out = v;
//  int out1 = v1;
//  Serial.print(" x:");
//  Serial.print(out);
//  Serial.println();
//  Serial.print(" y:");
//  Serial.print(out1);

  vid();
  search();
  control(); 
  Serial.println("");
  Serial.print("Дублирование ввода ");
  Serial.print(com);
  
    for (i = 1; i < 9; i++) //чистит дисплей
      {
        M7219(i, 0x00);
      }
        M7219(x, znach[y-1]);
      /*
      если поставить 0xFF загорится вся строка с (кординатой x) по координатам y. 
      0x01 - для данного массива и дисплея максимальная точка y(8).
      все это описано в массиве выше.
      -----------
      0x80 - y(1)
      0x40 - y(2)
      0x20 - y(3)
      0x10 - y(4)
      0x08 - y(5)
      0x04 - y(6)
      0x02 - y(7)
      0x01 - y(8)
      -----------
      */
    
      Serial.println("");
      Serial.print("Значение массива znach, которое выводится в 10 - ном виде = "); //этот массив записан в 16 - ном виде.
      Serial.print(znach[7]);
      //Write_Max7219(6, 0x02);

  
}
  
 
