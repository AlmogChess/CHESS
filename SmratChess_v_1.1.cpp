// C++ code
//
#include <LiquidCrystal.h>
int Const = 75;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Pieces Symbols
//0 = empty
//1 = poneW
//2 = knightW
//3 = bishopW
//5 = rookW
//8 = qW
//9 = kingW
//11=phoneB
//12 = knightB
//13 = bishopB
//15 = rookB
//18 = qB
//19 = kingB


int invalid = 13;
int v = 0;
volatile int PassT = 17;
volatile int Time1m = 18;
volatile int Time2m = 20;
volatile int Time3m = 21;


int timeFlag = 0;

void setup()
{
  Serial.begin(9600); // rate in bps
  analogWrite(6, Const); //this is the brightness of the lcd
  lcd.begin(16, 2);
  lcd.print("Chess Ai!");


  //sensors (32)
  pinMode(22, INPUT); pinMode(23, INPUT); pinMode(24, INPUT);
  pinMode(25, INPUT); pinMode(26, INPUT); pinMode(27, INPUT);
  pinMode(28, INPUT); pinMode(29, INPUT); pinMode(30, INPUT);
  pinMode(31, INPUT); pinMode(32, INPUT); pinMode(33, INPUT);
  pinMode(34, INPUT); pinMode(35, INPUT); pinMode(36, INPUT);
  pinMode(37, INPUT); pinMode(38, INPUT); pinMode(39, INPUT);
  pinMode(40, INPUT); pinMode(41, INPUT); pinMode(42, INPUT);
  pinMode(43, INPUT); pinMode(44, INPUT); pinMode(45, INPUT);
  pinMode(46, INPUT); pinMode(47, INPUT); pinMode(48, INPUT);
  pinMode(49, INPUT); pinMode(50, INPUT); pinMode(51, INPUT);
  pinMode(52, INPUT); pinMode(53, INPUT);



  pinMode(invalid, OUTPUT);
  pinMode(PassT, INPUT_PULLUP);  pinMode(Time1m, INPUT_PULLUP);
  pinMode(Time2m, INPUT_PULLUP);   pinMode(Time3m, INPUT_PULLUP);


  attachInterrupt(digitalPinToInterrupt(PassT), validate, CHANGE);
  attachInterrupt(digitalPinToInterrupt(Time1m), start1min, CHANGE);
  attachInterrupt(digitalPinToInterrupt(Time2m), start2min, CHANGE);
  attachInterrupt(digitalPinToInterrupt(Time3m), start3min, CHANGE);


}

void loop()
{
  //SET BOARD
  int y[8][8];
  int x[8][8];
  int board[8][8] = {{15, 12, 13, 18, 19, 13, 12, 15},   //set the first board setup.
    {11, 11, 11, 11, 11, 11, 11, 11},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {5, 2, 3, 8, 9, 3, 2, 5}
  };
//  getDATA(x);
//  Serial.println("start validatin in 30sec");
//  delay(30000);
//  getNewDATA(y);
//  validate(x, y, board, v);


}

void start1min(int x[8][8], int y[8][8], int board[8][8], int v)
{
  lcd.print("starting game");
  delay(1500);
  lcd.clear();
  lcd.print(millis() / 1000); //time
  getDATA(x);
  if (digitalRead(PassT) == HIGH)
  {
    getNewDATA(y);
    validate(x, y, board, v);
    if (v == 1)
    {
      lcd.print("done!");
      delay(250);
      start1min(x, y, board, v);
    }
    else
    {
      lcd.clear();
      lcd.print("waiting for fix");
      start1min(x, y, board, v);
    }
  }
  else
  {
    start1min(x, y, board, v);
  }
}

void start2min(int x[8][8], int y[8][8], int board[8][8], int v)
{
  lcd.print("starting game");
  delay(1500);
  lcd.clear();
  lcd.print(millis() / 1000); //time
  getDATA(x);
  if (digitalRead(PassT) == HIGH)
  {
    getNewDATA(y);
    validate(x, y, board, v);
    if (v == 1)
    {
      lcd.print("done!");
      delay(250);
      start1min(x, y, board, v);
    }
    else
    {
      lcd.clear();
      lcd.print("waiting for fix");
      start1min(x, y, board, v);
    }
  }
  else
  {
    start1min(x, y, board, v);
  }
}

void start3min(int x[8][8], int y[8][8], int board[8][8], int v)
{
  lcd.print("starting game");
  delay(1500);
  lcd.clear();
  lcd.print(millis() / 1000); //time
  getDATA(x);
  if (digitalRead(PassT) == HIGH)
  {
    getNewDATA(y);
    validate(x, y, board, v);
    if (v == 1)
    {
      lcd.print("done!");
      delay(250);
      start1min(x, y, board, v);
    }
    else
    {
      lcd.clear();
      lcd.print("waiting for fix");
      start1min(x, y, board, v);
    }
  }
  else
  {
    start1min(x, y, board, v);
  }
}



void getDATA(int x[8][8]) {
  for (int p = 22; p <= 53; p++) //p= port number
  {
    for (int i = 2; i <= 5; i++)
    {
      for (int j = 0; j <= 7; j++)
      {
        if (digitalRead(p) == HIGH)
        {
          x[i][j] = 1;
          Serial.println("X (x,y)(" + String(i) + "," + String(j) + ") = " + "1");
        }
        else if (digitalRead(p) == LOW)
        {
          x[i][j] = 0;
          Serial.println("X (x,y)(" + String(i) + "," + String(j) + ") = " + "0");
        }
      }
    }
  }
}


void getNewDATA(int y[8][8]) {
  for (int p = 22; p <= 53; p++) //p= port number
  {
    for (int i = 2; i <= 5; i++)
    {
      for (int j = 0; j <= 7; j++)
      {
        if (digitalRead(p) == HIGH)
        {
          y[i][j] = 1;
          Serial.println("Y (x,y)(" + String(i) + "," + String(j) + ") = " + "1");
        }
        else if (digitalRead(p) == LOW)
        {
          y[i][j] = 0;
          Serial.println("Y (x,y)(" + String(i) + "," + String(j) + ") = " + "0");
        }
      }
    }
  }
}


void validate(int x[8][8], int y[8][8], int board[8][8], int v)
{
  int ChessCode;
  int Quantity;
  int x1, x2, x3, x4, x5, x6, y1, y2, y3, y4, y5;
  int t1, t2, t3, t4, t5;
  for (int q = 1; q < 5; q++)
  {
    for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
      {
        if ((x[i][j] != y[i][j]))  // if x =! y, it is mean that was change, and we need to check which change has done
        {
          switch (q) // q = how meny changes. q=2 - 1 change. q=4 - 4 squares are change
          {
            case 1: //1 change on board
              i = x1;
              j = y1;
              t1 = x[i][j]; // NEED TO SAVE EVERY X AND Y THAT CHANGED
              return;
            case 2:
              i = x2;
              j = y2;
              t2 = x[i][j];
              return;
            case 3:
              i = x3;
              j = y3;
              t3 = x[i][j];
              return;
            case 4:
              i = x4;
              j = y4;
              t4 = x[i][j];
              return;
            case 5:
              i = x5;
              j = y5;
              t5 = x[i][j];
              return;
            default : // q<5 too meny changes
              digitalWrite(invalid, HIGH);
              v = 1;
              lcd.print("invalid move, try again!");
              break;
          }
        }
      }
    }
    int Quantity = q; //need to save how many change was in the chess board
  }

  //time for validate!

  if (Quantity == 2) // if Quantity  = 2 - just 1 piece moved.
  {
    if (t1 = 0) // if t1 = 0  it is mean that x1y1 empty which mean that was a piece there and it been moved.
    {
      ChessCode = board[x1][y1]; //ChessCode is the piece that move; and it was on x1y1. casscode now = to value of board in x1y1
    }
    else if  (t1 = 1) // if t1 = 1  it is mean that x1y1 full which mean that was a piece on x2y2 and it been moved. casscode now = to value of board in x2y2
    {
      ChessCode = board[x2][y2] ; //ChessCode is the piece that move; and it was on x2y2.
    }
  }
  //white castle
  if ((Quantity == 4) && (board[7][7] == 5) && (board[7][4] == 9) && (t1 == 0) && (t2 == 1) && (t3 == 1) && (t4 == 0)  && (y[x2][y2] == y[x3][y3]))
  {
    board[7][7] = 0;
    board[7][4] = 0;
    board[7][5] = 5;
    board[7][6] = 9;
  }
  else if ((Quantity == 5) && (board[7][0] == 5) && (board[7][4] == 9) && (t1 == 0) && (t2 == 0) && (t3 == 1) && (t4 == 1)  && (t5 == 0) && (y[x3][y3] == y[x4][y4]))
  {
    board[7][0] = 0;
    board[7][1] = 0;
    board[7][2] = 9;
    board[7][3] = 5;
    board[7][4] = 0;
  }
  //black castle
  if ((Quantity == 4) && (board[7][0] == 15) && (board[5][0] == 19) && (t1 == 0) && (t2 == 1) && (t3 == 1) && (t4 == 0)  && (y[x2][y2] == y[x3][y3]))
  {
    board[7][0] = 0;
    board[6][0] = 19;
    board[5][0] = 15;
    board[4][0] = 0;
  }
  else if ((Quantity == 5) && (board[0][0] == 15) && (board[7][0] == 9) && (t1 == 0) && (t2 == 0) && (t3 == 1) && (t4 == 1)  && (t5 == 0) && (y[x3][y3] == y[x4][y4]))
  {
    board[0][0] = 0;
    board[1][0] = 0;
    board[2][0] = 19;
    board[3][0] = 15;
    board[4][0] = 0;
  }




  switch (ChessCode)
  {
    case 1: //white pwan move from x to y
      if ((t1 == 0) && (board[x2][y2] == 0) && (board[x1][y1] == board[x1][y1 - 1])) //move to one empty square forword
      {
        board[x2][y2] = 1;
        Serial.println("PW FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); //PW = pawn white
      }
      else if ((t1 == 0) && (board[x2][y2] == 0) && (board[x1][y1] == board[x1][y1 - 2])
               && (x1 == x2) && (y1 == 7)) //move to 2 empty square forword | y1 =1 make sure this is the first move of the pawn
      {
        board[x2][y2] = 1;
        Serial.println("PW FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); //PW = pawn white
      }
      else if ((t1 == 0) && (board[x2][y2] > 10) && (board[x1][y1] == board[x1 - 1][y1])) //pwan white eat black piece **
      {
        board[x2][y2] = 1;
        Serial.println("PW FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); //PW = pawn white
      }
      else
      {
        Serial.println("PB Invalid move");
        lcd.clear();
        lcd.print("RB Invalid move");
        delay(1000);
        digitalWrite(invalid, HIGH);
        v = 1;
      }
      break;
    case 2: //white bishope
      {
        int s = x2 - x1;
        s = s * s; //mul for ignore -
        int w = s / 2;
        int f = y2 - y1;
        f = f * f;
        int l = f / 2;
        if ((l == w) && (t1 == 0)) //t1 = 0 mean move forward   | w = l mean the bishop moved diagonal way.
        {
          for (int p = 0; p < w; p++)
          {
            int temp1 = x2 + p; // temp1 and 2  - to chack all the way is clear.
            int temp2 = y2 + p; // temp1 and 2  - to chack all the way is clear.
            if (((board[x2][y2] > 10) || (board[x2][y2] == 0)) &&  (board[temp1][temp2] == 0)) // if the new position empty or
              //occupied by black piece and all the way empty then the move ligal
            {
              board[x2][y2] = board[x1][y1]; // have to be 2
              Serial.println("BW FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); // pw = pawn white
            }
            else
            {
              Serial.println("BW Invalid move");
              lcd.clear();
              lcd.print("BW Invalid move");
              delay(1000);
              digitalWrite(invalid, HIGH);
              v = 1;
            }
          }
        }
        else if ((l == w) && (t1 == 1)) //t1 = 0 mean move backward   | w = l mean the bishop moved diagonal way.
        {
          {
            for (int p = 0; p < w; p++)
            {
              int temp1 = x1 - p; // temp1 and 2  - to chack all the way is clear.
              int temp2 = y1 - p; // temp1 and 2  - to chack all the way is clear.
              if (((board[x1][y1] > 10) || (board[x1][y1] == 0)) && (board[temp1][temp2] == 0)) // if the new position
                //empty or occupied by black piece and all the way empty then the move ligal
              {
                board[x1][y1] = board[x2][y2]; // have to be 2
                Serial.println("BW FROM " + String(x2) + "," + String(y2) + " TO " + String(x1) + "," + String(y1)); // pw = pawn white
              }
              else
              {
                Serial.println("BW Invalid move");
                lcd.clear();
                lcd.print("BW Invalid move");
                delay(1000);
                digitalWrite(invalid, HIGH);
                v = 1;
              }
            }
          }
        }
      }
      break;
    case 3: // White knight
      if (((board[x2][y2] == 0) || (board[x2][y2] > 10)) && (t1 = 0)) // knight move from x1y1 to x2y2 (t1=0) Moved Forward
      {
        if (board[x2][y2] == board[x1 + 1][y1 + 2]) //+1 , +2
        {
          board[x2][y2] = board[x1][y1]; // have to be 3
          Serial.println("KNW FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); // KNW - White knight
        }
        else if (board[x2][y2] == board[x1 + 1][y1 - 2]) //  +1 , -2
        {
          board[x2][y2] = board[x1][y1]; // have to be 3
          Serial.println("KNW FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); // KNW - White knight
        }
        else if (board[x2][y2] == board[x1 + 1][y1 - 2]) // +1 , -2
        {
          board[x2][y2] = board[x1][y1]; // have to be 3
          Serial.println("KNW FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); // KNW - White knight
        }
        else if (board[x2][y2] == board[x1 - 1][y1 - 2]) // -1 , -2
        {
          board[x2][y2] = board[x1][y1]; // have to be 3
          Serial.println("KNW FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); // KNW - White knight
        }
        else if (board[x2][y2] == board[x1 + 2][y1 + 1]) //  +2 , +1
        {
          board[x2][y2] = board[x1][y1]; // have to be 3
          Serial.println("KNW FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); // KNW - White knight
        }
        else if (board[x2][y2] == board[x1 + 2][y1 - 1]) // +2 , -1
        {
          board[x2][y2] = board[x1][y1]; // have to be 3
          Serial.println("KNW FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); // KNW - White knight
        }
        else if (board[x2][y2] == board[x1 - 2][y1 - 1]) // -2 , -1
        {
          board[x2][y2] = board[x1][y1]; // have to be 3
          Serial.println("KNW FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); // KNW - White knight
        }
        else if (board[x2][y2] == board[x1 - 2][y1 + 1]) // -2 , +1
        {
          board[x2][y2] = board[x1][y1]; // have to be 3
          Serial.println("KNW FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2));// KNW - White knight
        }
        else
        {
          Serial.println("KNW Invalid move");
          lcd.clear();
          lcd.print("KNW Invalid move");
          delay(1000);
          digitalWrite(invalid, HIGH);
          v = 1;
        }
      }
      else if (((board[x2][y2] == 0) || (board[x2][y2] > 10)) && (t1 = 1)) // knight move from x2y2 to x1y1 (t1=1) Moved backward
      {
        if (board[x1][y1] == board[x2 + 1][y2 + 2]) //+1 , +2
        {
          board[x1][y1] = board[x2][y2]; // have to be 3
          Serial.println("KNW FROM " + String(x2) + "," + String(y2) + " TO " + String(x1) + "," + String(y1)); // KNW - White knight
        }
        else if (board[x1][y1] == board[x2 + 1][y2 - 2]) //  +1 , -2
        {
          board[x1][y1] = board[x2][y2]; // have to be 3
          Serial.println("KNW FROM " + String(x2) + "," + String(y2) + " TO " + String(x1) + "," + String(y1)); // KNW - White knight

        }
        else if (board[x1][y1] == board[x2 + 1][y2 - 2]) // +1 , -2
        {
          board[x1][y1] = board[x2][y2]; // have to be 3
          Serial.println("KNW FROM " + String(x2) + "," + String(y2) + " TO " + String(x1) + "," + String(y1)); // KNW - White knight

        }
        else if (board[x1][y1] == board[x2 - 1][y2 - 2]) // -1 , -2
        {
          board[x1][y1] = board[x2][y2]; // have to be 3
          Serial.println("KNW FROM " + String(x2) + "," + String(y2) + " TO " + String(x1) + "," + String(y1)); // KNW - White knight

        }
        else if (board[x1][y1] == board[x2 + 2][y2 + 1]) //  +2 , +1
        {
          board[x1][y1] = board[x2][y2]; // have to be 3
          Serial.println("KNW FROM " + String(x2) + "," + String(y2) + " TO " + String(x1) + "," + String(y1)); // KNW - White knight

        }
        else if (board[x1][y1] == board[x2 + 2][y2 - 1]) // +2 , -1
        {
          board[x1][y1] = board[x2][y2]; // have to be 3
          Serial.println("KNW FROM " + String(x2) + "," + String(y2) + " TO " + String(x1) + "," + String(y1)); // KNW - White knight

        }
        else if (board[x1][y1] == board[x2 - 2][y2 - 1]) // -2 , -1
        {
          board[x1][y1] = board[x2][y2]; // have to be 3
          Serial.println("KNW FROM " + String(x2) + "," + String(y2) + " TO " + String(x1) + "," + String(y1)); // KNW - White knight

        }
        else if (board[x1][y1] == board[x2 - 2][y2 + 1]) // -2 , +1
        {
          board[x1][y1] = board[x2][y2]; // have to be 3
          Serial.println("KNW FROM " + String(x2) + "," + String(y2) + " TO " + String(x1) + "," + String(y1)); // KNW - White knight
        }
        else
        {
          Serial.println("KNW Invalid move");
          lcd.clear();
          lcd.print("KNW Invalid move");
          delay(1000);
          digitalWrite(invalid, HIGH);
          v = 1;
        }
      }
      break;
    case 5: //rook white
      {
        int e = (x2 - x1) / 2 ;
        int z = e * e;
        int g = (y2 - y1) / 2 ;
        int d = g * g;
        //rook move from x1y1 to x2y2 (t1=0) moved forward
        if ((t1 = 0) && (d > 0) && (board[x2][y2] == 0) || (board[x2][y2] > 10))  //d>0 mean that it move in axis Y | Board>10 mean you can eat - <10 it's black piece
        {
          for (int k = 1; k < d; k++)
          {
            if (board[x2][y2 + k] == 0)
            {
              board[x2][y2] = board[x1][y1]; //have to be 5
              Serial.println("RW FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); // RW = rook white
            }
          }
        }
        //rook move from x1y1 to x2y2 t1=0) moved forward
        else if  ((t1 = 0) && (z > 0) && (board[x2][y2] == 0) || (board[x2][y2] > 10)) //z>0 mean that it move in axis X | Board>10 mean you can eat - <10 it's black piece
          for (int k = 1; k < z; k++)
          {
            if (board[x2][y2 + z] == 0)
            {
              board[x2][y2] = board[x1][y1]; //have to be 5
              Serial.println("RW FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); // RW = rook white
            }
          }
        else
        {
          Serial.println("RW Invalid move");
          lcd.clear();
          lcd.print("RW Invalid move");
          delay(1000);
          digitalWrite(invalid, HIGH);
          v = 1;

        }
        //rook move from x2y2 to x1y1 (t1=1) moved backward
        if ((t1 = 1) && (d > 0) && (board[x1][y1] == 0) || (board[x1][y1] > 10)) // d>0 mean that it move in axis Y
        {
          for (int k = 1; k < d; k++)
          {
            if (board[x1][y1 - k] == 0)
            {
              board[x2][y2] = board[x1][y1]; //have to be 5
              Serial.println("RW FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); // RW = rook white
            }
          }
        }
        //rook move from x2y2 to x1y1 (t1=1) moved backward
        else if  ((t1 = 1) && (z > 0) && (board[x1][y1] == 0) || (board[x1][y1] > 10)) // and Z>0 mean that it move in axis X
        {
          for (int k = 1; k < z; k++)
          {
            if (board[x1][y1 - z] == 0)
            {
              board[x1][y1] = board[x2][y2];
              Serial.println("RW FROM " + String(x2) + "," + String(y2) + " TO " + String(x1) + "," + String(y1)); // RW = rook white
            }
          }
        }
        else
        {
          Serial.println("RW Invalid move");
          lcd.clear();
          lcd.print("RW Invalid move");
          delay(1000);
          digitalWrite(invalid, HIGH);
          v = 1;

        }
      }
      break;
    case 8: // Queen White
      {
        int s1 = x2 - x1;
        s1 = s1 * s1; //mul for ignore -
        int w1 = s1 / 2;
        int f1 = y2 - y1;
        f1 = f1 * f1;
        int l1 = f1 / 2;
        int e1 = (x2 - x1) / 2 ;
        int z1 = e1 * e1;
        int g1 = (y2 - y1) / 2 ;
        int d1 = g1 * g1;

        if ((l1 == w1) && (t1 == 0))
        {
          for (int p = 0; p < w1; p++)
          {
            int temp1 = x2 + p;
            int temp2 = y2 + p;
            if (((board[x2][y2] > 10) || (board[x2][y2] == 0)) &&  (board[temp1][temp2] == 0)) // if the new
              //position empty or occupied by black piece and all the way empty then the move is ligal
            {
              board[x2][y2] = board[x1][y1]; // have to be 8
              Serial.println("QW FROM"
                             + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); //QW - qween white
            }
            else
            {
              Serial.println("QW Invalid move");
              lcd.clear();
              lcd.print("QW Invalid move");
              delay(1000);
              digitalWrite(invalid, HIGH);
              v = 1;

            }
          }
        }
        else if ((l1 == w1) && (t1 == 1))
        {
          {
            for (int p = 1; p < w1; p++)
            {
              int temp1 = x1 - p;
              int temp2 = y1 - p;
              if (((board[x1][y1] > 10) || (board[x1][y1] == 0)) &&  (board[temp1][temp2] == 0))
                // if the new position empty or occupied by black piece and all the way empty then the move is ligal
              {
                board[x1][y1] = board[x2][y2]; // have to be 8
                Serial.println("QW FROM " + String(x2) + "," + String(y2) + " TO " + String(x1) + "," + String(y1));
              }
              else
              {
                Serial.println("QW Invalid move");
                lcd.clear();
                lcd.print("QW Invalid move");
                delay(1000);
                digitalWrite(invalid, HIGH);
                v = 1;

              }
            }
          }
        }
        else if ((t1 = 0) && (d1 > 0) && (board[x2][y2] == 0) || (board[x2][y2] > 10))  //d1>0 mean that it move in axis Y
        {
          for (int k = 1; k < d1; k++)
          {
            if (board[x2][y2 - k] == 0)
            {
              board[x2][y2] = board[x1][y1]; //have to be 8
              Serial.println("QW FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2));
            }
          }
        }
        //queen move from x1y1 to x2y2 t1=1)
        else if  ((t1 = 0) && (z1 > 0) && (board[x2][y2] == 0) || (board[x2][y2] > 10)) //z1>0 mean that it move in axis X
          for (int k = 1; k < z1; k++)
          {
            if (board[x2][y2 + z1] == 0)
            {
              board[x2][y2] = board[x1][y1]; //have to be 8
              Serial.println("QW FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2));
            }
          }
        //queen move from x2y2 to x1y1 (t1=0)
        if ((t1 = 1) && (d1 > 0) && (board[x1][y1] == 0) || (board[x1][y1] > 10)) // d1>0 mean that it move in axis Y
        {
          for (int k = 1; k < d1; k++)
          {
            if (board[x1][y1 - k] == 0)
            {
              board[x1][y1] = board[x2][y2]; //have to be 5
              Serial.println("QW FROM " + String(x2) + "," + String(y2) + " TO " + String(x1) + "," + String(y1));
            }
          }
        }
        //queen move from x2y2 to x1y1 (t1=1)
        else if  ((t1 = 1) && (z1 > 0) && (board[x1][y1] == 0) || (board[x1][y1] > 10)) // and Z>0 mean that it move in axis X
        {
          for (int k = 1; k < z1; k++)
          {
            if (board[x1][y1 - z1] == 0)
            {
              board[x1][y1] = board[x2][y2];
              Serial.println("QW FROM " + String(x2) + "," + String(y2) + " TO " + String(x1) + "," + String(y1));
            }
          }
        }
      }
      break;
    case 9: //white king
      if ((t1 = 0) && (board[x2][y2] == 0) || (board[x2][y2] > 10))
      {
        x[x1][y1] = 9;
        x[x2][y2] = 9;

        if ((x[x1][y1] == y[x1 + 1][y1]) || (x[x1][y1] == y[x1 + 1][y1 + 1]) || (x[x1][y1] == y[x1 + 1][y1 - 1])
            || (x[x1][y1] == y[x1 - 1][y1]) ||  (x[x1][y1] == y[x1 - 1][y1 + 1]) ||  (x[x1][y1] == y[x1 - 1][y1 - 1])
            ||  (x[x1][y1] == y[x1][y1 - 1])  ||  (x[x1][y1] == y[x1][y1 + 1]))
        {
          board[x2][y2] = board[x1][y1] ; //must be 9 KING
          Serial.println("KW FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2));  // KW - king white
        }
      }
      else if ((t1 = 1) && (board[x2][y2] == 0) || (board[x1][y1] > 10))
      {
        x[x1][y1] = 9;
        x[x2][y2] = 9;

        if ((x[x2][y2] == y[x2 + 1][y2]) || (x[x2][y2] == y[x2 + 1][y2 + 1]) || (x[x2][y2] == y[x2 + 1][y2 - 1])
            || (x[x2][y2] == y[x2 - 1][y2]) ||  (x[x2][y2] == y[x2 - 1][y2 + 1])
            ||  (x[x2][y2] == y[x2 - 1][y2 - 1]) ||  (x[x2][y2] == y[x2][y2 - 1])  ||  (x[x2][y2] == y[x2][y2 + 1]))
        {
          board[x2][y2] = board[x1][y1] ; //must be 9 KING
          Serial.println("KW FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); // KW -  White knight
        }
      }
      break;





    //black pieces
    case 11: //black pwan move from x to y | just t1=0 - pawn cannot going back
      if ((t1 == 0) && (board[x2][y2] == 0) && (board[x1][y1] == board[x1][y1 + 1])) //move to one empty square forword
      {
        board[x2][y2] = 11;
        Serial.println("PB FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); //PB = PAWN BLACK
      }
      else if ((t1 == 0) && (board[x2][y2] == 0) && (board[x1][y1] == board[x1][y1 + 2])
               && (x1 == x2) && (y1 == 1) && (x1 == x2)) //move to 2 empty square forword, , y1 =1 make sure this is the first move of the pawn
      {
        board[x2][y2] = 11;
        Serial.println("PB FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); //PB = PAWN BLACK
      }
      else if ((t1 == 0) && (board[x2][y2] < 10) && (board[x1][y1] == board[x1 + 1][y1])) //black pwan eat white piece **
      {
        board[x2][y2] = 11;
        Serial.println("PB FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); //PB = PAWN BLACK
      }
      else
      {
        Serial.println("PB Invalid move");
        lcd.clear();
        lcd.print("PB Invalid move");
        delay(1000);
        digitalWrite(invalid, HIGH);
        v = 1;
      }
      break;
    case 12: //black bishope
      {
        int s = x2 - x1;
        s = s * s; //mul for ignore -
        int w = s / 2;
        int f = y2 - y1;
        f = f * f;
        int l = f / 2;
        if ((l == w) && (t1 == 0)) //t1 = 0  mean moved forward | w = l mean the bishop moved diagonal way.
        {
          for (int p = 0; p > w; p++)
          {
            int temp1 = x2 + p;
            int temp2 = y2 + p;
            if (((board[x2][y2] < 10) || (board[x2][y2] == 0)) &&  (board[temp1][temp2] == 0)) // if the new position empty or
              //occupied by white piece and all the way empty then the move ligal
            {
              board[x2][y2] = board[x1][y1]; // have to be 2
              Serial.println("BB FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); //BB = Black bishop
            }
            else
            {
              Serial.println("BB Invalid move");
              lcd.clear();
              lcd.print("BB Invalid move");
              delay(1000);
              digitalWrite(invalid, HIGH);
              v = 1;
            }
          }
        }
        else if ((l == w) && (t1 == 1)) //t1 = 1 mean moved backward   | w = l mean the bishop moved diagonal way.
        {
          {
            for (int p = 0; p < w; p++)
            {
              int temp1 = x1 - p;
              int temp2 = y1 - p;
              if (((board[x1][y1] < 10) || (board[x1][y1] == 0)) && (board[temp1][temp2] == 0)) // if the new position
                //empty or occupied by black piece and all the way empty then the move ligal
              {
                board[x1][y1] = board[x2][y2]; // have to be 2
                Serial.println("BB FROM " + String(x2) + "," + String(y2) + " TO " + String(x1) + "," + String(y1)); //BB = Black bishop
              }
              else
              {
                Serial.println("BB Invalid move");
                lcd.clear();
                lcd.print("BB Invalid move");
                delay(1000);
                digitalWrite(invalid, HIGH);
                v = 1;
              }
            }
          }
        }
      }
      break;
    case 13: // Black knight
      if (((board[x2][y2] == 0) || (board[x2][y2] < 10)) && (t1 = 0)) // knight move from x1y1 to x2y2 (t1=0) | Board<10 mean you can eat - <10 it's white
      {
        if (board[x2][y2] == board[x1 + 1][y1 + 2]) //+1 , +2
        {
          board[x2][y2] = board[x1][y1]; // have to be 3
          Serial.println("KNB FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); // KNB -  Black knight
        }
        else if (board[x2][y2] == board[x1 + 1][y1 - 2]) //  +1 , -2
        {
          board[x2][y2] = board[x1][y1]; // have to be 3
          Serial.println("KNB FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2));  // KNB -  Black knight
        }
        else if (board[x2][y2] == board[x1 + 1][y1 - 2]) // +1 , -2
        {
          board[x2][y2] = board[x1][y1]; // have to be 3
          Serial.println("KNB FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); // KNB -  Black knight
        }
        else if (board[x2][y2] == board[x1 - 1][y1 - 2]) // -1 , -2
        {
          board[x2][y2] = board[x1][y1]; // have to be 3
          Serial.println("KNB FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); // KNB -  Black knight
        }
        else if (board[x2][y2] == board[x1 + 2][y1 + 1]) //  +2 , +1
        {
          board[x2][y2] = board[x1][y1]; // have to be 3
          Serial.println("KNB FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); // KNB -  Black knight
        }
        else if (board[x2][y2] == board[x1 + 2][y1 - 1]) // +2 , -1
        {
          board[x2][y2] = board[x1][y1]; // have to be 3
          Serial.println("KNB FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); // KNB -  Black knight
        }
        else if (board[x2][y2] == board[x1 - 2][y1 - 1]) // -2 , -1
        {
          board[x2][y2] = board[x1][y1]; // have to be 3
          Serial.println("KNB FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); // KNB -  Black knight
        }
        else if (board[x2][y2] == board[x1 - 2][y1 + 1]) // -2 , +1
        {
          board[x2][y2] = board[x1][y1]; // have to be 3
          Serial.println("KNB FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); // KNB -  Black knight
        }
        else
        {
          Serial.println("KNB Invalid move");
          lcd.clear();
          lcd.print("KNB Invalid move");
          delay(1000);
          digitalWrite(invalid, HIGH);
          v = 1;
        }
      } // t1 = 1 .. moved backward
      else if (((board[x2][y2] == 0) || (board[x2][y2] < 10)) && (t1 = 1)) // knight move from x2y2 to x1y1 (t1=1) | Board<10 mean you can eat - <10 it's white
      {
        if (board[x1][y1] == board[x2 + 1][y2 + 2]) //+1 , +2
        {
          board[x1][y1] = board[x2][y2]; // have to be 3
          Serial.println("KNB FROM " + String(x2) + "," + String(y2) + " TO " + String(x1) + "," + String(y1));// KNB -  Black knight
        }
        else if (board[x1][y1] == board[x2 + 1][y2 - 2]) //  +1 , -2
        {
          board[x1][y1] = board[x2][y2]; // have to be 3
          Serial.println("KNB FROM " + String(x2) + "," + String(y2) + " TO " + String(x1) + "," + String(y1));// KNB -  Black knight

        }
        else if (board[x1][y1] == board[x2 + 1][y2 - 2]) // +1 , -2
        {
          board[x1][y1] = board[x2][y2]; // have to be 3
          Serial.println("KNB FROM " + String(x2) + "," + String(y2) + " TO " + String(x1) + "," + String(y1));// KNB -  Black knight

        }
        else if (board[x1][y1] == board[x2 - 1][y2 - 2]) // -1 , -2
        {
          board[x1][y1] = board[x2][y2]; // have to be 3
          Serial.println("KNB FROM " + String(x2) + "," + String(y2) + " TO " + String(x1) + "," + String(y1));// KNB -  Black knight

        }
        else if (board[x1][y1] == board[x2 + 2][y2 + 1]) //  +2 , +1
        {
          board[x1][y1] = board[x2][y2]; // have to be 3
          Serial.println("KNB FROM " + String(x2) + "," + String(y2) + " TO " + String(x1) + "," + String(y1));// KNB -  Black knight

        }
        else if (board[x1][y1] == board[x2 + 2][y2 - 1]) // +2 , -1
        {
          board[x1][y1] = board[x2][y2]; // have to be 3
          Serial.println("KNB FROM " + String(x2) + "," + String(y2) + " TO " + String(x1) + "," + String(y1));// KNB -  Black knight

        }
        else if (board[x1][y1] == board[x2 - 2][y2 - 1]) // -2 , -1
        {
          board[x1][y1] = board[x2][y2]; // have to be 3
          Serial.println("KNB FROM " + String(x2) + "," + String(y2) + " TO " + String(x1) + "," + String(y1));// KNB -  Black knight

        }
        else if (board[x1][y1] == board[x2 - 2][y2 + 1]) // -2 , +1
        {
          board[x1][y1] = board[x2][y2]; // have to be 3
          Serial.println("KNB FROM " + String(x2) + "," + String(y2) + " TO " + String(x1) + "," + String(y1));// KNB -  Black knight
        }
        else
        {
          Serial.println("KNB Invalid move");
          lcd.clear();
          lcd.print("KNB Invalid move");
          delay(1000);
          digitalWrite(invalid, HIGH);
          v = 1;
        }
      }
      break;
    case 15: // rook black
      {
        int e = (x2 - x1) / 2 ;
        int z = e * e;
        int g = (y2 - y1) / 2 ;
        int d = g * g;
        //rook move from x1y1 to x2y2 (t1=0)
        if ((t1 = 0) && (d > 0) && (board[x2][y2] == 0) || (board[x2][y2] < 10))  //d>0 mean that it move in axis Y | board <10 mean it's white piece
        {
          for (int k = 1; k < d; k++)
          {
            if (board[x2][y2 + k] == 0)
            {
              board[x2][y2] = board[x1][y1]; //have to be 5
              Serial.println("RB FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); // RB = rook black
            }
          }
        }
        //rook move from x1y1 to x2y2 t1=0)
        else if  ((t1 = 0) && (z > 0) && (board[x2][y2] == 0) || (board[x2][y2] < 10)) //z>0 mean that it move in axis X | board <10 mean it's white piece
          for (int k = 1; k < z; k++)
          {
            if (board[x2][y2 + z] == 0)
            {
              board[x2][y2] = board[x1][y1]; //have to be 5
              Serial.println("RB FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); // RB = rook black
            }
          }
        else
        {
          Serial.println("RB Invalid move");
          lcd.clear();
          lcd.print("RB Invalid move");
          delay(1000);
          digitalWrite(invalid, HIGH);
          v = 1;
        }
        //rook move from x2y2 to x1y1 (t1=1)
        if ((t1 = 1) && (d > 0) && (board[x1][y1] == 0) || (board[x1][y1] > 10)) // d>0 mean that it move in axis Y
        {
          for (int k = 1; k < d; k++)
          {
            if (board[x1][y1 - k] == 0)
            {
              board[x2][y2] = board[x1][y1]; //have to be 5
              Serial.println("RB FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2)); // RB = rook black
            }
          }
        }
        //rook move from x2y2 to x1y1 (t1=1)
        else if  ((t1 = 1) && (z > 0) && (board[x1][y1] == 0) || (board[x1][y1] > 10)) // and Z>0 mean that it move in axis X
        {
          for (int k = 1; k < z; k++)
          {
            if (board[x1][y1 - z] == 0)
            {
              board[x1][y1] = board[x2][y2];
              Serial.println("RB FROM " + String(x2) + "," + String(y2) + " TO " + String(x1) + "," + String(y1)); // RB = rook black
            }
          }
        }
        else
        {
          Serial.println("RB Invalid move");
          lcd.clear();
          lcd.print("RB Invalid move");
          delay(1000);
          digitalWrite(invalid, HIGH);
          v = 1;

        }
      }
      break;
    case 18: // QW - Queen Black
      {
        int s1 = x2 - x1;
        s1 = s1 * s1; //mul for ignore -
        int w1 = s1 / 2;
        int f1 = y2 - y1;
        f1 = f1 * f1;
        int l1 = f1 / 2;
        int e1 = (x2 - x1) / 2 ;
        int z1 = e1 * e1;
        int g1 = (y2 - y1) / 2 ;
        int d1 = g1 * g1;

        if ((l1 == w1) && (t1 == 0))
        {
          for (int p = 0; p < w1; p++)
          {
            int temp1 = x2 + p;
            int temp2 = y2 + p;
            if (((board[x2][y2] < 10) || (board[x2][y2] == 0)) &&  (board[temp1][temp2] == 0)) // if the new
              //position empty or occupied by black piece and all the way empty then the move is ligal
            {
              board[x2][y2] = board[x1][y1]; // have to be 18
              Serial.println("QW FROM "
                             + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2));
            }
            else
            {
              Serial.println("QB Invalid move");
              lcd.clear();
              lcd.print("QB Invalid move");
              delay(1000);
              digitalWrite(invalid, HIGH);
              v = 1;
            }
          }
        }
        else if ((l1 == w1) && (t1 == 1))
        {
          {
            for (int p = 1; p < w1; p++)
            {
              int temp1 = x1 - p; // temp1 and 2  - to chack all the way is clear.
              int temp2 = y1 - p; // temp1 and 2  - to chack all the way is clear.
              if (((board[x1][y1] < 10) || (board[x1][y1] == 0)) &&  (board[temp1][temp2] == 0))
                // if the new position empty or occupied by black piece and all the way empty then the move is ligal
              {
                board[x1][y1] = board[x2][y2]; // have to be 18
                Serial.println("QW FROM " + String(x2) + "," + String(y2) + " TO " + String(x1) + "," + String(y1));
              }
              else
              {
                Serial.println("QB Invalid move");
                lcd.clear();
                lcd.print("QB Invalid move");
                delay(1000);
                digitalWrite(invalid, HIGH);
                v = 1;
              }
            }
          }
        }
        else if ((t1 = 0) && (d1 > 0) && (board[x2][y2] == 0) || (board[x2][y2] < 10))  //d1>0 mean that it move in axis Y
        {
          for (int k = 1; k < d1; k++)
          {
            if (board[x2][y2 - k] == 0)
            {
              board[x2][y2] = board[x1][y1]; //have to be 18
              Serial.println("QW FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2));
            }
          }
        }
        //queen move from x1y1 to x2y2 t1=1)
        else if  ((t1 = 0) && (z1 > 0) && (board[x2][y2] == 0) || (board[x2][y2] < 10)) //z1>0 mean that it move in axis X
          for (int k = 1; k < z1; k++)
          {
            if (board[x2][y2 + z1] == 0)
            {
              board[x2][y2] = board[x1][y1]; //have to be 18
              Serial.println("QW FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2));
            }
          }
        //queen move from x2y2 to x1y1 (t1=0)
        if ((t1 = 1) && (d1 > 0) && (board[x1][y1] == 0) || (board[x1][y1] < 10)) // d1>0 mean that it move in axis Y
        {
          for (int k = 1; k < d1; k++)
          {
            if (board[x1][y1 - k] == 0)
            {
              board[x1][y1] = board[x2][y2]; //have to be 18
              Serial.println("QW FROM " + String(x2) + "," + String(y2) + " TO " + String(x1) + "," + String(y1));
            }
          }
        }
        //queen move from x2y2 to x1y1 (t1=1)
        else if  ((t1 = 1) && (z1 > 0) && (board[x1][y1] == 0) || (board[x1][y1] > 10)) // and Z>0 mean that it move in axis X
        {
          for (int k = 1; k < z1; k++)
          {
            if (board[x1][y1 - z1] == 0)
            {
              board[x1][y1] = board[x2][y2];
              Serial.println("QB FROM " + String(x2) + "," + String(y2) + " TO " + String(x1) + "," + String(y1));
            }
          }
        }
      }
      break;
    default:
      Serial.println("Invalid move");
      digitalWrite(invalid, HIGH);
      v = 1;
      break;
    case 19: //white king
      if ((t1 = 0) && (board[x2][y2] == 0) || (board[x2][y2] < 10))
      {
        x[x1][y1] = 19;
        x[x2][y2] = 19;

        if ((x[x1][y1] == y[x1 + 1][y1]) || (x[x1][y1] == y[x1 + 1][y1 + 1]) || (x[x1][y1] == y[x1 + 1][y1 - 1])
            || (x[x1][y1] == y[x1 - 1][y1]) ||  (x[x1][y1] == y[x1 - 1][y1 + 1]) ||  (x[x1][y1] == y[x1 - 1][y1 - 1])
            ||  (x[x1][y1] == y[x1][y1 - 1])  ||  (x[x1][y1] == y[x1][y1 + 1]))
        {
          board[x2][y2] = board[x1][y1] ; //must be 9 KING
          Serial.println("KB FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2));
        }
      }
      else if ((t1 = 1) && (board[x2][y2] == 0) || (board[x1][y1] < 10))
      {
        x[x1][y1] = 19;
        x[x2][y2] = 19;

        if ((x[x2][y2] == y[x2 + 1][y2]) || (x[x2][y2] == y[x2 + 1][y2 + 1]) || (x[x2][y2] == y[x2 + 1][y2 - 1])
            || (x[x2][y2] == y[x2 - 1][y2]) ||  (x[x2][y2] == y[x2 - 1][y2 + 1])
            ||  (x[x2][y2] == y[x2 - 1][y2 - 1]) ||  (x[x2][y2] == y[x2][y2 - 1])  ||  (x[x2][y2] == y[x2][y2 + 1]))
        {
          board[x2][y2] = board[x1][y1] ; //must be 19 KING
          Serial.println("KB FROM " + String(x1) + "," + String(y1) + " TO " + String(x2) + "," + String(y2));
        }
      }
      break;
  }
}












//
//void getNewDATA(int y[8][8]) {
//  for (int L = 43; L <= 50; L++)   //for for the registers, L= register port
//  {
//    switch (L)
//    {
//      case 43: //piso number#1 y: 0-1, Y:0-3
//        for (int i = 0; i <= 1; i++)
//        {
//          for (int j = 0; j <= 3; j++)
//          {
//            // Get data from 74HC165
//            digitalWrite(clockIn, HIGH);
//            digitalWrite(clockEnablePin, LOW);
//            byte incoming = shiftIn(dataIn1, clockIn, LSBFIRST);
//            digitalWrite(clockEnablePin, HIGH);
//            if (digitalRead(L) == HIGH)
//            {
//              y[i][j] = 1;
//            }
//            else
//            {
//              y[i][j] = 0;
//            }
//          }
//        }
//        return;
//      case 44: //piso number#2 y: 2-3, Y:0-3
//        for (int i = 2; i <= 3; i++)
//        {
//          for (int j = 0; j <= 3; j++)
//          {
//            // Get data from 74HC165
//            digitalWrite(clockIn, HIGH);
//            digitalWrite(clockEnablePin, LOW);
//            byte incoming = shiftIn(dataIn2, clockIn, LSBFIRST);
//            digitalWrite(clockEnablePin, HIGH);
//            if (digitalRead(L) == HIGH)
//            {
//              y[i][j] = 1;
//            }
//            else
//            {
//              y[i][j] = 0;
//            }
//          }
//        }
//        return;
//      case 45: //piso number#3 y: 4-5, Y:0-3
//        for (int i = 4; i <= 5; i++)
//        {
//          for (int j = 0; j <= 3; j++)
//          {
//            // Get data from 74HC165
//            digitalWrite(clockIn, HIGH);
//            digitalWrite(clockEnablePin, LOW);
//            byte incoming = shiftIn(dataIn3, clockIn, LSBFIRST);
//            digitalWrite(clockEnablePin, HIGH);
//            if (digitalRead(L) == HIGH)
//            {
//              y[i][j] = 1;
//            }
//            else
//            {
//              y[i][j] = 0;
//            }
//          }
//        }
//        return;
//      case 46: //piso number#4 y: 6-7, Y:0-3
//        for (int i = 6; i <= 7; i++)
//        {
//          // Get data from 74HC165
//          digitalWrite(clockIn, HIGH);
//          digitalWrite(clockEnablePin, LOW);
//          byte incoming = shiftIn(dataIn4, clockIn, LSBFIRST);
//          digitalWrite(clockEnablePin, HIGH);
//          for (int j = 0; j <= 3; j++)
//          {
//            if (digitalRead(L) == HIGH)
//            {
//              y[i][j] = 1;
//            }
//            else
//            {
//              y[i][j] = 0;
//            }
//          }
//        }
//        return;
//      case 47:  //piso number#5 y: 0-1, Y:4-7
//        for (int i = 0; i <= 1; i++)
//        {
//          for (int j = 4; j <= 7; j++)
//          {
//            // Get data from 74HC165
//            digitalWrite(clockIn, HIGH);
//            digitalWrite(clockEnablePin, LOW);
//            byte incoming = shiftIn(dataIn5, clockIn, LSBFIRST);
//            digitalWrite(clockEnablePin, HIGH);
//            if (digitalRead(L) == HIGH)
//            {
//              y[i][j] = 1;
//            }
//            else
//            {
//              y[i][j] = 0;
//            }
//          }
//        }
//        return;
//      case 48: //piso number#6 y: 2-3, Y:4-7
//        for (int i = 2; i <= 3; i++)
//        {
//          // Get data from 74HC165
//          digitalWrite(clockIn, HIGH);
//          digitalWrite(clockEnablePin, LOW);
//          byte incoming = shiftIn(dataIn6, clockIn, LSBFIRST);
//          digitalWrite(clockEnablePin, HIGH);
//          for (int j = 4; j <= 7; j++)
//          {
//            if (digitalRead(L) == HIGH)
//            {
//              y[i][j] = 1;
//            }
//            else
//            {
//              y[i][j] = 0;
//            }
//          }
//        }
//        return;
//      case 49://piso number#7 y: 4-5, Y:4-7
//        for (int i = 4; i <= 5; i++)
//        {
//          // Get data from 74HC165
//          digitalWrite(clockIn, HIGH);
//          digitalWrite(clockEnablePin, LOW);
//          byte incoming = shiftIn(dataIn7, clockIn, LSBFIRST);
//          digitalWrite(clockEnablePin, HIGH);
//          for (int j = 4; j <= 7; j++)
//          {
//            if (digitalRead(L) == HIGH)
//            {
//              y[i][j] = 1;
//            }
//            else
//            {
//              y[i][j] = 0;
//            }
//          }
//        }
//        return;
//
//      case 50: //piso number#8 y: 6-7, Y:4-7
//        for (int i = 6; i <= 7; i++)
//        {
//          // Get data from 74HC165
//          digitalWrite(clockIn, HIGH);
//          digitalWrite(clockEnablePin, LOW);
//          byte incoming = shiftIn(dataIn8, clockIn, LSBFIRST);
//          digitalWrite(clockEnablePin, HIGH);
//          for (int j = 4; j <= 7; j++)
//          {
//            if (digitalRead(L) == HIGH)
//            {
//              y[i][j] = 1;
//            }
//            else
//            {
//              y[i][j] = 0;
//            }
//          }
//        }
//        return;
//      default:
//        break;
//    }
//  }
//}

//void getY(int x[8][8], int y[8][8])
//{
//  for (int i = 0; i < 8; i++)
//  {
//    for (int j = 0; j > 8; j ++)
//    {
//      y[i][j] = x[i][j];
//    }
//  }
//}
