#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    pid_t pid[n + 1];

    for (int i = 1; i <= n; i++)
    {
        pid[i] = fork();
        if (pid[i] == 0)
        {
            printf("%d ", i);  // here is problem
            // waitpid(pid[i - 1], NULL, 0);
            printf("Do ");
            // exit(0);
        }
        else
        {
            waitpid(pid[i], NULL, 0);
            exit(0);
        }
    }

    // waitpid(pid[n], NULL, 0);
    // printf("\n");
    return 0;
}

/*

#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

#define Password_Length 5

Servo myservo;
LiquidCrystal lcd(A4, A5, A3, A2, A1, A0);

int pos = 0;

char Data[Password_Length];
char Master[Password_Length] = "9981";
byte data_count = 0, master_count = 0;

bool Pass_is_good;
bool door = false;
char customKey;


/---preparing keypad---/

const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};


byte rowPins[ROWS] = {0, 1, 2, 3};
byte colPins[COLS] = {4, 5, 6};

Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);


/--- Main Action ---/
void setup()
{
  myservo.attach(9, 2000, 2400);
  ServoClose();
  lcd.begin(16, 2);
  lcd.print("Protected Door");
  loading("Loading");
  lcd.clear();
}


void loop()
{
  if (door != true) Open();

}

void loading (char msg[]) {
  lcd.setCursor(0, 1);
  lcd.print(msg);

  for (int i = 0; i < 9; i++) {
    delay(100);
    lcd.print(".");
  }
}

void clearData()
{
  while (data_count != 0)
  { 
    Data[data_count--] = 0;
  }
  return;
}

void ServoClose()
{
  for (pos = 90; pos >= 0; pos -= 10) { 
    myservo.write(pos);
  }
}

void ServoOpen()
{
  for (pos = 0; pos <= 90; pos += 10) {
    myservo.write(pos);  
  }
}

void Open()
{
  lcd.setCursor(0, 0);
  lcd.print("Enter Password");
  
  customKey = customKeypad.getKey();
  if (customKey)
  {
    Data[data_count] = customKey;
    lcd.setCursor(data_count, 1);
    lcd.print(Data[data_count]);
    data_count++;
  }

  if (data_count == Password_Length - 1)
  {
    if (!strcmp(Data, Master))
    {
      lcd.clear();
      ServoOpen();
      lcd.print(" Door is Open ");
      door = true;
      delay(3000);
      loading("Waiting");
      lcd.clear();
      lcd.print(" Door is Closing ");
      delay(1000);
      ServoClose();
      lcd.print(" Door is Closed ");
      delay(1000);
      door = false;      
    }
    else
    {
      lcd.clear();
      lcd.print(" Wrong Password ");
      door = false;
    }
    delay(1000);
    lcd.clear();
    clearData();
  }
}

*/