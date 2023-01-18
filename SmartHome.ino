#include <Keypad.h> // Author Bruma Mihai, November 2022
#include <Wire.h>                 
#include <LiquidCrystal.h> 
#include<EEPROM.h>
#define rs 13
#define en 11
#define d4 12
#define d5 10
#define d6 7
#define d7 6
#define hs 0
#define ms 1
#define LED_RED 8
#define LED_Green 9

int h = 12;
int m = 0;
int s = 0;
int flag = 0;
int TIME = 0;
int state1 = 0;
int state2 = 0;
char password[4];
char initial_password[4],new_password[4];
static int i;
char key_pressed=0;
const byte rows = 4; 
const byte columns = 4; 
char hexaKeys[rows][columns] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

void change();
void initialpassword();
byte row_pins[rows] = {A0,A1,A2,A3};
byte column_pins[columns] = {A4,A5,3,2};   
Keypad keypad_key = Keypad( makeKeymap(hexaKeys), row_pins, column_pins, rows, columns);
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

void setup(){
  
lcd.begin(16, 2);
lcd.print("Welcome back");
delay(5000);
lcd.clear();
lcd.print("Home-User:Mihai");
lcd.setCursor(0,1);
lcd.print("Password :");
digitalWrite(LED_RED,HIGH);
Serial.begin(9600);
initialpassword();
pinMode(hs,INPUT_PULLUP);
pinMode(ms,INPUT_PULLUP);
  
}
  
void loop(){ 
key_pressed = keypad_key.getKey();
if(key_pressed=='#')
change();
if (key_pressed)
{
 password[i++]=key_pressed;
lcd.print(key_pressed);
}
if(i==5)
{
delay(200);
for(int j=0;j<=5;j++)
initial_password[j]=EEPROM.read(j);
if(!(strncmp(password, initial_password,4)))
{
lcd.clear();
lcd.print("Password");
lcd.setCursor(0,1);
lcd.print("Accepted!,Mihai");
digitalWrite(LED_RED,LOW);
digitalWrite(LED_Green,HIGH);
delay(1000);
lcd.clear();
lcd.setCursor(1,0);
//lcd.print("Pres # to change");
//change();
delay(2000);
lcd.clear();
i=0;
lcd.setCursor(0,1);
lcd.print("T(*C)=15.5[room]");
lcd.setCursor(0, 0);
for(;;){
s = s + 1;
lcd.print("TIME:" );
lcd.print(h);
lcd.print(":");
lcd.print(m);
lcd.print(":");
lcd.print(s);
if (flag < 12) lcd.print(" AM");
if (flag == 12) lcd.print(" PM");
if (flag > 12) lcd.print(" PM");
if (flag == 24) flag = 0;
delay(1000);
if (s == 60)
{
s = 0;
m = m + 1;
}
if (m == 60)
{
m = 0;
h = h + 1;
flag = flag + 1;
}
if (h == 13)
{
h = 1;
}
lcd.setCursor(0, 0);  
state1 = digitalRead(hs);
if (state1 == 0)
{
h = h + 1;
flag = flag + 1;
if (flag < 12) lcd.print(" AM");
if (flag == 12) lcd.print(" PM");
if (flag > 12) lcd.print(" PM");
if (flag == 24) flag = 0;
if (h == 13) h = 1;
}
state2 = digitalRead(ms);
if (state2 == 0)
{
s = 0;
m = m + 1;
}}
}
else
{
lcd.clear();
lcd.print("Wrong Password");
lcd.setCursor(0,1);
delay(2000);
//lcd.print("Wrong Password");
lcd.clear();
lcd.print("Enter Password");
lcd.setCursor(0,1);
i=0;
}
}}
  void change(){
  int j=0;
  lcd.clear();
  lcd.print("Current Password");
  lcd.setCursor(0,1);
  while(j<=5)
  {
    char key=keypad_key.getKey();
    if(key)
    {
      new_password[j++]=key;
      lcd.print(key);
    }
    key=0;
    //j++;
  }
  delay(500);
  if((strncmp(new_password, initial_password, 5)))
  {
    lcd.clear();
    lcd.print("Wrong Password");
    lcd.setCursor(0,1);
    lcd.print("Try Again");
    delay(1000);
  }
  else
  {
    j=0;
    lcd.clear();
    lcd.print("New Password:");
    lcd.setCursor(0,1);
    while(j<=5)
    {
      char key=keypad_key.getKey();
      if(key)
      {
        initial_password[j]=key;
        lcd.print(key);
        EEPROM.write(j,key);
        j++;
      }
    }
    lcd.print("Password Changed");
    delay(1000);
  }
  lcd.clear();
  lcd.print("Enter Password");
  lcd.setCursor(0,1);
  key_pressed=0;
  }

void initialpassword(){
  for(int j=0;j<=5;j++)
    EEPROM.write(j, j+49);
  for(int j=0;j<=5;j++)
    initial_password[j]=EEPROM.read(j);
}

