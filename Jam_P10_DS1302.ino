// Jam digital P10 DS1302 by Rino DC @micropwr

#include "DS1302.h"
DS1302 rtc(A5,A4,A3); // (CE,IO,SCLK)
Time t;
#include <SPI.h>   
#include <DMD.h>   
#include <TimerOne.h>
#include "SystemFont5x7.h"
#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1
#define SETTING 4
#define UP 3
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

unsigned long previousMillis = 0; 
unsigned long currentMillis;
const int interval = 1000;

boolean colon;
byte count;
byte mode = 0;

byte tjam;
byte tmenit;
byte ttanggal;
byte tbulan;
int ttahun;

void ScanDMD()
{ 
  dmd.scanDisplayBySPI();
}

void modeNormal()
{
    currentMillis = millis();
   if (currentMillis - previousMillis >= interval)
   {
    previousMillis = currentMillis; 
    dmd.clearScreen( true );
    tampilJam();
      count++;
    if(count<=20)
     {
      tampilHari();
     }
    else if(count>20&&count<=35)
     tampilTanggal();
    else
      tampilTahun();
      
     if(count==40)
     {
      count=0;
     }
   }
}

void modeSetMenit()
{   
    if(tmenit <= 9)
    {
      char menit[3];
      String smenit;
      smenit = String(tmenit);
      smenit.toCharArray(menit,3);
      dmd.drawChar(19,0,'0', GRAPHICS_NORMAL);
      dmd.drawMarquee(menit,3,25,0);
    }
    else
    {
      char menit[3];
      String smenit;
      smenit = String(tmenit);
      smenit.toCharArray(menit,3);
      dmd.drawMarquee(menit,3,19,0);
    }
    if(digitalRead(UP)==LOW)
    { 
      delay(250);
      tmenit++;
      dmd.clearScreen( true );
      if(tmenit>59)
        tmenit=0;
    }
}

void modeSetJam()
{
    if(tjam <= 9)
    {
      char jam[3];
      String sjam;
      sjam = String(tjam);
      sjam.toCharArray(jam,3);
      dmd.drawChar(2,0,'0', GRAPHICS_NORMAL);
      dmd.drawMarquee(jam,3,8,0);
    }
    else
    {
      char jam[3];
      String sjam;
      sjam = String(tjam);
      sjam.toCharArray(jam,3);
      dmd.drawMarquee(jam,3,2,0);
    }
    if(digitalRead(UP)==LOW)
    {
      delay(250);
      tjam++;
      dmd.clearScreen( true );
      if(tjam>23)
      tjam=0;
    }
}

void modeSetHari()
{  

  t = rtc.getTime();
  byte thari = t.dow;
  if (t.dow == 1)
  dmd.drawMarquee("Senin",5,1,9);
  if (t.dow == 2)
  dmd.drawMarquee("Slasa",5,1,9);
  if (t.dow == 3)
  dmd.drawMarquee("Rabu",5,1,9);
  if (t.dow == 4)
  dmd.drawMarquee("Kamis",5,1,9);
  if (t.dow == 5)
  dmd.drawMarquee("Jumat",5,1,9);
  if (t.dow == 6)
  dmd.drawMarquee("Sabtu",5,1,9);
  if (t.dow == 7)
  dmd.drawMarquee("Ahad",5,1,9);
  
  if(digitalRead(UP)==LOW)
  {
    delay(250);
    thari++;
    dmd.clearScreen( true );
    if(thari==8)
    thari=1;
    rtc.setDOW(thari);
  }
  
}

void modeSetTanggal()
{
  if(ttanggal<10)
  {
    char tanggal[3];
    String stanggal;
    stanggal = String(ttanggal);
    stanggal.toCharArray(tanggal,3);
    dmd.drawChar(1,9,'0', GRAPHICS_NORMAL);
    dmd.drawMarquee(tanggal,3,7,9);
  }
  else
  {
  char tanggal[3];
  String stanggal;
  stanggal = String(ttanggal);
  stanggal.toCharArray(tanggal,3);
  dmd.drawMarquee(tanggal,3,1,9); 
  }
  if(digitalRead(UP)==LOW)
  {
    delay(250);
    ttanggal++;
    dmd.clearScreen( true );
    rtc.setDate(ttanggal, tbulan, ttahun);
    if(ttanggal>31)
    ttanggal=1;
    
  }
}

void modeSetBulan()
{
    if(tbulan<10)
  {
  char bulan[3];
  String sbulan;
  sbulan = String(tbulan);
  sbulan.toCharArray(bulan,3);
  dmd.drawChar(19,9,'0', GRAPHICS_NORMAL);
  dmd.drawMarquee(bulan,3,25,9); 
  }
  else
  {
  char bulan[3];
  String sbulan;
  sbulan = String(tbulan);
  sbulan.toCharArray(bulan,3);
  dmd.drawMarquee(bulan,3,19,9); 
  }
  if(digitalRead(UP)==LOW)
  {
    delay(250);
    tbulan++;
    dmd.clearScreen( true );
    rtc.setDate(ttanggal, tbulan, ttahun);
    if(tbulan>12)
    tbulan=1;
  }
}

void modeSetTahun()
{
  char tahun[6];
  String stahun;
  stahun = String(ttahun);
  stahun.toCharArray(tahun,6);
  dmd.drawMarquee(tahun,6,4,9); 
  if(digitalRead(UP)==LOW)
  {
    delay(250);
    ttahun++;
    dmd.clearScreen( true );
    rtc.setDate(ttanggal, tbulan, ttahun);
    if(ttahun>2100)
    ttahun=2010;
  }
}

void tampilJam()
{
    t = rtc.getTime();
    ttanggal= t.date;
    tbulan= t.mon;
    ttahun= t.year;
    tjam = t.hour;
    
    if(tjam <= 9)
    {
      char jam[3];
      String sjam;
      sjam = String(tjam);
      sjam.toCharArray(jam,3);
      dmd.drawChar(2,0,'0', GRAPHICS_NORMAL);
      dmd.drawMarquee(jam,3,8,0);
    }
    else
    {
      char jam[3];
      String sjam;
      sjam = String(tjam);
      sjam.toCharArray(jam,3);
      dmd.drawMarquee(jam,3,2,0);
    }
  
    tmenit = t.min;
    if(tmenit <= 9)
    {
      char menit[3];
      String smenit;
      smenit = String(tmenit);
      smenit.toCharArray(menit,3);
      dmd.drawChar(19,0,'0', GRAPHICS_NORMAL);
      dmd.drawMarquee(menit,3,25,0);
    }
    else
    {
      char menit[3];
      String smenit;
      smenit = String(tmenit);
      smenit.toCharArray(menit,3);
      dmd.drawMarquee(menit,3,19,0);
    }


  
    colon = !colon;
    if( colon == true )
      dmd.drawChar(14, 0, ':', GRAPHICS_OR );
    else
      dmd.drawChar(14, 0, ':', GRAPHICS_NOR );  
}

void tampilHari()
{
  t = rtc.getTime();
  if (t.dow == 1)
  dmd.drawMarquee("Senin",5,1,9);
  if (t.dow == 2)
  dmd.drawMarquee("Slasa",5,1,9);
  if (t.dow == 3)
  dmd.drawMarquee("Rabu",5,1,9);
  if (t.dow == 4)
  dmd.drawMarquee("Kamis",5,1,9);
  if (t.dow == 5)
  dmd.drawMarquee("Jumat",5,1,9);
  if (t.dow == 6)
  dmd.drawMarquee("Sabtu",5,1,9);
  if (t.dow == 7)
  dmd.drawMarquee("Ahad",5,1,9);
}

void tampilTanggal()
{
  
  if(ttanggal<10)
  {
    char tanggal[3];
    String stanggal;
    stanggal = String(ttanggal);
    stanggal.toCharArray(tanggal,3);
    dmd.drawChar(1,9,'0', GRAPHICS_NORMAL);
    dmd.drawMarquee(tanggal,3,7,9);
  }
  else
  {
  char tanggal[3];
  String stanggal;
  stanggal = String(ttanggal);
  stanggal.toCharArray(tanggal,3);
  dmd.drawMarquee(tanggal,3,1,9); 
  }
  dmd.drawChar(13, 9, '/', GRAPHICS_NORMAL );
  
  if(tbulan<10)
  {
  char bulan[3];
  String sbulan;
  sbulan = String(tbulan);
  sbulan.toCharArray(bulan,3);
  dmd.drawChar(19,9,'0', GRAPHICS_NORMAL);
  dmd.drawMarquee(bulan,3,25,9); 
  }
  else
  {
  char bulan[3];
  String sbulan;
  sbulan = String(tbulan);
  sbulan.toCharArray(bulan,3);
  dmd.drawMarquee(bulan,3,19,9);
  }
  
}

void tampilTahun()
{
  char tahun[6];
  String stahun;
  stahun = String(ttahun);
  stahun.toCharArray(tahun,6);
  dmd.drawMarquee(tahun,6,4,9); 
}

void setup(void)
{
  pinMode(SETTING, INPUT_PULLUP);
  pinMode(UP, INPUT_PULLUP);
  pinMode(A2, OUTPUT);
  digitalWrite(A2, LOW); // GND RTC
  pinMode(A1, OUTPUT);
  digitalWrite(A1, HIGH); // VCC RTC
  rtc.halt(false);
  rtc.writeProtect(false);
    
  // Setup Serial connection
  //Serial.begin(9600);
   
 

   Timer1.initialize( 2000 );           //period in microseconds to call ScanDMD. Anything longer than 5000 (5ms) and you can see flicker.
   Timer1.attachInterrupt( ScanDMD );   //attach the Timer1 interrupt to ScanDMD which goes to dmd.scanDisplayBySPI()

   dmd.clearScreen( true );   
   dmd.selectFont(SystemFont5x7);

}

void loop(void)
{ 
  //Serial.println(mode);
  if(digitalRead(SETTING) == LOW)
  {
    delay(250);
    dmd.clearScreen( true );
    mode++;
  }
  if(mode==0)
  {
    modeNormal();
  }
  if(mode==1)
  {
    modeSetMenit();
    rtc.setTime(tjam, tmenit, t.sec);
  }
  if(mode==2)
  {
    modeSetJam();
    rtc.setTime(tjam, tmenit, t.sec);
  }
  if(mode==3)
  {
    modeSetHari();
  }
  if(mode==4)
  {
    modeSetTanggal();
  }
  if(mode==5)
  {
    modeSetBulan();
  }
  if(mode==6)
  {
    modeSetTahun();
  }
  if(mode>=7)
  {
    mode=0;
  }
}
