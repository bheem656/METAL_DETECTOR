
#include <LiquidCrystal.h>

/**************** LCD VARIABLES ***************************/
const int rs = 9, en = 10, d4 = 8, d5 = 7, d6 = 6, d7 = 5;
//int ol = 4;
// int count;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


/**************** prototype functions ***************************/
void lcd_print(void);
void lcd_default(void);
void  master_isr(void);
void  slave_isr(void);

//byte smiley[8] = {
//  0b00000,
//  0b00000,
//  0b01010,
//  0b00000,
//  0b00000,
//  0b10001,
//  0b01110,
//  0b00000
//};


/*********************  sensor intrup pin *********************/
uint8_t master_pin = 14; //D5; gpio 4
uint8_t slave_pin  = 12; //D6; gpio 2

unsigned long prvMillis = millis();
//unsigned int last_master_intrupt ;
//unsigned int last_slave_intrupt ;
unsigned long prvtMillis_mst = millis();
unsigned long prvMillis_slv = millis();

volatile int out = 0;
volatile int in = 0;
const long interval = 1000;  

volatile uint8_t flag_slv = 0;
volatile uint8_t flag_mst = 0;






 
void setup()
{
  Serial.begin(9600);

  lcd.begin(16, 2);
  
  pinMode(master_pin, INPUT);
  pinMode(slave_pin, INPUT); 


  attachInterrupt(digitalPinToInterrupt(master_pin), master_isr, HIGH);
  attachInterrupt(digitalPinToInterrupt(slave_pin), slave_isr, HIGH);
  lcd_default();
}

 uint8_t timeout = 0;
void loop()
{
  if(flag_slv)
  {
    
      prvtMillis_mst = millis();
      while(millis() - prvtMillis_mst <= 1500) // 2000 -2000
      {
        if(flag_mst)
        {
          in++;
          break;
          }
        if(millis() - prvtMillis_mst >= 1200)
        {
          timeout = 1;
          break;
          }         
          
        }
      if(timeout )
        {
          out++;  
          timeout = 0;        
          }        
     flag_mst = 0;
    
    }

   if(flag_mst)
   {

      prvtMillis_mst = millis();
      while(millis() - prvtMillis_mst <= 1500) // 2000 -2000
      {
        if(flag_slv)
        {
          out++;
          break;
          }
        if(millis() - prvtMillis_mst >= 1200)
        {
          timeout = 1;
          break;
          }         
          
        }
      if(timeout )
        {
          in++;  
          timeout = 0;        
          } 
//    out++;
//    while(millis() - prvMillis_mst <= interval);
//   //delay(interval);
//   flag_slv = 0;
   
    }

  flag_slv = 0;
  flag_mst = 0;
  Serial.print("TOTAL : "); Serial.print(in+out); Serial.print("  --- >>>  "); Serial.print("IN : "); Serial.print(in); Serial.print("  ||  "); Serial.print("OUT : "); Serial.println(out);  

  lcd_print();
 
 // delay(500);
}



/******************* intrupt isr ******************************/
void  master_isr()
{
  //out++;
  flag_mst = 1;
////noInterrupts();
//detachInterrupt(digitalPinToInterrupt(slave_pin));
//  out++;
//  while(millis() - prvtMillis_mst <= interval);
//  prvtMillis_mst = millis();  
//attachInterrupt(digitalPinToInterrupt(slave_pin), master_isr, HIGH);
 

 
 }


void  slave_isr()
  {
flag_slv = 1;
   // in++;
////noInterrupts();
//detachInterrupt(digitalPinToInterrupt(master_pin));
//while(millis() - prvtMillis_mst <= interval);
//  in++;
//  prvtMillis_mst = millis();  
// attachInterrupt(digitalPinToInterrupt(master_pin), master_isr, HIGH);
  
  }



/************************** LCD function *****************************/

void lcd_print()
{

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("HOPE SEC EQP PVT LTD");
  lcd.setCursor(0,1);
  lcd.print("IN ");
  lcd.setCursor(6,1);
  lcd.print(in);
  lcd.setCursor(0,2);
  lcd.print("OUT ");
  lcd.setCursor(6,2);
  lcd.print(out);
  lcd.setCursor(0,3);
  lcd.print("NET ");
//  count= count_in-count_out;
  lcd.setCursor(6,3);
  lcd.print(in+out);

}

void lcd_default()
{

  lcd.begin(20, 4);
  lcd.setCursor(0,0);
  lcd.print("HOPE SEC EQP PVT LTD");
  lcd.setCursor(0,1);
  lcd.print("IN ");
  lcd.setCursor(6,1);
  lcd.print(0);
  lcd.setCursor(0,2);
  lcd.print("OUT ");
  lcd.setCursor(6,2);
  lcd.print(0);
  lcd.setCursor(0,3);
  lcd.print("NET ");
  lcd.setCursor(6,3);
  lcd.print(0);
}

/****************************** end of code *****************/
