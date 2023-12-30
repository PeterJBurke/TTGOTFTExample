#include <TFT_eSPI.h>
#include "planes128x128.h"
#include "plane24x24.h"
#include "phonewifi24x24.h"
#include "phonewifi48x48.h"

// Test of github VS code sync 12/30/2023
//#include "oil.h" 
TFT_eSPI tft = TFT_eSPI(); 

// declare functions:


void  drawtextexample();
void  drawgraphicsexample();
void  drawgrid();
void  drawimageexample();
void cyclebetweenscreens();
void drawscreen(int screen_number_to_draw);

int m_cycle_time=3;
int m_cycle=0;
bool m_whethertocycle=true;
int m_current_screen_number=1; // screen # to display
bool m_screen_needs_updating=true;
int m_time_of_last_screendraw;
int debounce=0;
int debounce2=0;

void setup() {
  // set up reading of buttons
  pinMode(35,INPUT_PULLUP);
  pinMode(0,INPUT_PULLUP);

  // initialize serial monitor
  Serial.begin(115200);

  // initialize tft screen
  tft.init();
  //drawscreen(m_current_screen_number);

}


void loop() {


  if(m_screen_needs_updating==true){
    drawscreen(m_current_screen_number);
    m_screen_needs_updating=false;
    return;    
  }




  if(digitalRead(35)==0)
   {
    if(debounce==0){
        debounce=1;
        // do stuff
        if(m_current_screen_number==4){
          m_current_screen_number=1;
        }
        else if(m_current_screen_number!=4){
          m_current_screen_number++;
        }
        m_screen_needs_updating=true;
        delay(100);
        return;
    }
   }else debounce=0;




  if(digitalRead(0)==0)
   {
    if(debounce2==0){
        debounce2=1;
        // do stuff
        m_whethertocycle=!m_whethertocycle; // toggle
        delay(100);
        return;
    }
   }else debounce2=0;



  if(m_whethertocycle==true){
    // if (current time - time of last screen draw > cycle time)
    if((millis()-m_time_of_last_screendraw)>(m_cycle_time*1000)){    // has it been 3 seconds? if so, cycle screen
      if(m_current_screen_number==4){
        m_current_screen_number=1;
      }
      else if(m_current_screen_number!=4){
        m_current_screen_number++;
      }
      m_screen_needs_updating=true;
      return;
    }
  };


}

void cyclebetweenscreens(){


//Serial.print("hello serial: ");  
  if(m_cycle==0){
    drawtextexample();
    sleep(m_cycle_time);
    m_cycle=1;
    return;
    }

  if(m_cycle==1){
    drawgraphicsexample();
    sleep(m_cycle_time);
    m_cycle=2;
    return;
    }

  if(m_cycle==2){
    drawgrid();
    sleep(m_cycle_time);
    m_cycle=3;
    return;
    }

  if(m_cycle==3){
    drawimageexample();
    sleep(m_cycle_time);
    m_cycle=0;
    return;
    }



}

void drawtextexample(){
  tft.fillScreen(TFT_LIGHTGREY);
  tft.setTextColor(TFT_BLUE,TFT_WHITE);
  tft.drawString("Font 1 is 8 pixels.",5,10,1); // font 1 8 pixel
  tft.drawString("Font 2 is 16 pixels.",5,20,2); // font 2 16 pixel
  tft.drawString("Font 4 is 48 pixels.",5,40,4); // font 4 48 pixel




  tft.setTextColor(TFT_GREEN);
  tft.drawString("69",5,70,6); // 48 pixels
  tft.setTextColor(TFT_RED,TFT_BLACK);
  tft.drawString("69",5,110,7); // 48 pixels
  tft.setTextColor(TFT_BLACK,TFT_YELLOW);
  tft.drawString("69",5,160,8); // 75 pixels
  int i=10;
  tft.setTextColor(TFT_BLUE,TFT_YELLOW);
  tft.drawString(String(i),80,90,4); // font 4 48 pixel



}

void drawgraphicsexample(){
  tft.fillScreen(TFT_WHITE);
  tft.drawPixel(100,100,TFT_BLACK);
  tft.drawLine(0,0,100,10,TFT_RED);
  tft.drawCircle(100,100,30,TFT_GOLD);\
  tft.fillCircle(100,50,20,TFT_BROWN);
  tft.fillRoundRect(100,125,40,20,5,TFT_PURPLE);
}

void drawgrid(){
  tft.fillScreen(TFT_WHITE);
  // draw nxmax and nymax hor/ver lines spaced by nxstep,nystep from zero to nxmax*nxstep and nymax*nysetp, respectively
  //int nx,ny=0;
  int nxmax=25;
  int nymax=25;
  int nxstep=10;
  int nystep=10;
  int nxstep2=50;
  int nystep2=50;
  int xs=0;
  int ys=0;
  int xe=0;
  int ye=0;
  //for(nx<nxmax,nx++){// vertical
  for(int nx=1; nx<=nxmax;nx++){// vertical red lines
    xs=nx*nxstep;
    ys=0;
    xe=nx*nxstep;
    ye=nymax*nystep;
    tft.drawLine(xs,ys,xe,ye,TFT_RED);
  }
  for(int nx=1; nx<=nxmax;nx++){// vertical black lines
    xs=nx*nxstep2;
    ys=0;
    xe=nx*nxstep2;
    ye=nymax*nystep2;
    tft.drawLine(xs,ys,xe,ye,TFT_BLACK);
  }
  for(int ny=1; ny<=nymax;ny++){// horizontal red lines
    xs=0;
    ys=ny*nystep;
    xe=nxmax*nxstep;
    ye=ny*nystep;
    tft.drawLine(xs,ys,xe,ye,TFT_RED);
  }
  for(int ny=1; ny<=nymax;ny++){// horizontal black lines
    xs=0;
    ys=ny*nystep2;
    xe=nxmax*nxstep;
    ye=ny*nystep2;
    tft.drawLine(xs,ys,xe,ye,TFT_BLACK);
  }
}

void  drawimageexample(){
    tft.fillScreen(TFT_BLACK);
    tft.setSwapBytes(true);
    tft.pushImage(3,65,128,128,planes128x128);
    tft.setSwapBytes(false);

}


void drawscreen(int screen_number_to_draw){
  // time_of_last_screendraw=currenttime;
  m_time_of_last_screendraw=millis();
  if(screen_number_to_draw==1){
    // draw screen 1
    drawtextexample();
  }
  else if(screen_number_to_draw==2){
    // draw screen 2
    drawgraphicsexample(); 
  }
  else if(screen_number_to_draw==3){
    // draw screen 3
    drawgrid();
  }
  else if(screen_number_to_draw==4){
    // draw screen 4
    drawimageexample();
  }
}
