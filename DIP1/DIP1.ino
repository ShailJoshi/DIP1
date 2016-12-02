//#define F_CPU 16000000
#include <openGLCD.h>
#include <bitmaps/tklogo.h>
#include "string.h"
#include "stdio.h"
#define RPMBAR 62
#define TBAR   48
#define FBAR   48
#define MAXLEN 33
char received_string[MAXLEN+1]; 
int data[6];
int i,j,k;
boolean detA=false;
gText RPMtext(GLCD.Left, GLCD.Top + 5, GLCD.Left + 25, GLCD.Top + 18);
gText SPDtext(GLCD.Left, GLCD.Top + 19, GLCD.Left + 25, GLCD.Top + 34);
gText Geartext(GLCD.Left, GLCD.Top + 35, GLCD.Left + 34, GLCD.Top + 50);
gText Temptext(GLCD.Left, GLCD.Top + 51, GLCD.Left + 8, GLCD.Top + 64);
gText Fueltext(GLCD.CenterX, GLCD.Top + 51, GLCD.Left + 8, GLCD.Top + 64);
gText RPMno(GLCD.CenterX, GLCD.Top + 6, GLCD.Right, GLCD.Top + 20);
gText SPDno(GLCD.CenterX - 21, GLCD.Top + 21, GLCD.CenterX-1, GLCD.Top + 36);
gText Gearno(GLCD.CenterX + 2, GLCD.Top + 36, GLCD.CenterX + 8, GLCD.Top + 50);
gText GearBound(GLCD.CenterX, GLCD.Top + 33, GLCD.CenterX + 10, GLCD.Top + 50);
gText RPMbar(GLCD.Left,GLCD.Top,GLCD.Right,GLCD.Top+5);
//gText Tbar(GLCD.Left+11,GLCD.Top+56,GLCD.CenterX-5,GLCD.Top+60);
//gText Fbar(GLCD.CenterX+11,GLCD.Top+56,GLCD.Right-5,GLCD.Top+60);
void setup() {
Serial1.begin(57600);
Serial.begin(57600);
  GLCD.Init();
  GLCD.DrawBitmap(tklogo, GLCD.Left, GLCD.CenterY - 8);
  delay(400);
  GLCD.ClearScreen();
  RPMtext.SelectFont(utf8font10x16);
  SPDtext.SelectFont(utf8font10x16);
  Geartext.SelectFont(utf8font10x16);
  Temptext.SelectFont(utf8font10x16);
  Fueltext.SelectFont(utf8font10x16);
  RPMno.SelectFont(fixednums7x15);
  SPDno.SelectFont(fixednums7x15);
  Gearno.SelectFont(fixednums7x15);
  Gearno.SetFontColor(WHITE);
  Gearno.ClearArea();
  GearBound.SelectFont(fixednums7x15);
  GearBound.SetFontColor(WHITE);
  GearBound.ClearArea();
  RPMtext.print("RPM");
  SPDtext.print("SPD");
  Geartext.print("GEAR");
  Temptext.print("T");
  Fueltext.print("F");

}

void loop() {
while(Serial1.available()==0);
static uint8_t cnt = 0;
char c=Serial1.read();

if( (c != '\r') && (cnt < MAXLEN) ) 
{
      if(c==' ') c='0';
      if(c=='A') detA=true;
      if(detA==true){
      received_string[cnt] = c;
      cnt++;}
    
}
else{
detA=false;
Serial.print(received_string);
cnt=0;
for(i=0;i<6;i++){
  data[i]=0;
  for(j=0;j<4;j++){
    data[i]+=(received_string[j+i*5+1]-'0')*pow(10,3-j);
    Serial.print(data[i]);
    Serial.print(' ');
    Serial.print(received_string[j+i*5+1]);
    Serial.print('\n');
  }
}
/*Serial1.write("1");
while(Serial1.available()==0){}
char rpm[5]=Serial1.read();
RPMno.ClearArea();
RPMno.print(rpm);
Serial.println(rpm);
Serial1.write("2");
while(Serial1.available()==0){}
char spd[3]=Serial1.read();
  SPDno.ClearArea();
  SPDno.print(spd);
Serial.println(spd);
Serial.write="3";
while(Serial1.available()==0){}
char gear[2]=Serial1.read();
  Gearno.ClearArea();
  Gearno.print(gear);
Serial.println(gear);
Serial.write("3");
while(Serial1.available()==0){}
char rpmbar=[*/

  GLCD.DrawHBarGraph(GLCD.Left, GLCD.Top, GLCD.Width, 5, 1, 0, RPMBAR, data[0]);
GLCD.DrawHBarGraph(GLCD.Left + 11, GLCD.Top + 56, 50, 5, 1, 0, TBAR, data[1]);
GLCD.DrawHBarGraph(GLCD.CenterX + 11, GLCD.Top + 56, 50, 5, 1, 0, FBAR, data[2]);
RPMno.ClearArea();
RPMno.print(data[3]);
 SPDno.ClearArea();
  SPDno.print(data[4]);
Gearno.ClearArea();
Gearno.print(data[5]);
}
}
