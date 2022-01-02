#include <LiquidCrystal.h>

/**************** LCD VARIABLES ***************************/
 const int rs = 9, en = 10, d4 = 8, d5 = 7, d6 = 6, d7 = 5;
//const int rs = 9, en = 10, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
// int ol = 4;
//  int count;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/**************** prototype functions ***************************/
void lcd_print(void);
void lcd_default(void);

uint8_t master_pin = 2; // D5; gpio 4
uint8_t slave_pin = 3;  // D6; gpio 2

const char title[50]  = "HOPE SEC EQP PVT LTD";

unsigned long prvMillis = millis();
// unsigned int last_master_intrupt ;
// unsigned int last_slave_intrupt ;
unsigned long prvtMillis_mst = millis();
unsigned long prvMillis_slv = millis();

volatile int out = 0;
volatile int in = 0;
uint16_t interval = 900; // passing speed

volatile uint8_t flag_slv = 0;
volatile uint8_t flag_mst = 0;
uint8_t first = 1;

uint32_t net = 0;
uint32_t total = 0;

void master_isr()
{
  // out++;
  flag_mst = 1;
}

void slave_isr()
{
  flag_slv = 1;
}

void print02(uint16_t val)
{
char buff[50];
  sprintf(buff, "%06d", val);
  lcd.print(buff);   
}

void setup()
{
  Serial.begin(9600);
  pinMode(master_pin, INPUT_PULLUP);
  pinMode(slave_pin, INPUT_PULLUP);

  // lcd.begin(16, 2);
  // delay(1000);

  lcd_default();
  // delay(2000);

  flag_slv = 0;
  flag_mst = 0;
  lcd_print();
delay(10000);
  attachInterrupt(digitalPinToInterrupt(master_pin), master_isr, CHANGE);
  attachInterrupt(digitalPinToInterrupt(slave_pin), slave_isr, CHANGE);
}


void loop()
{
  if(first)
  {
  prvMillis = millis();

   while ((millis() - prvMillis) <= 10000)

      {
          flag_slv = 0;
          flag_mst = 0;
          in = 0;
          out = 0;
        
        }
     first = 0;

  }

  if (flag_slv)
  {
    // noInterrupts();
    flag_slv = 0;
    prvtMillis_mst = millis();
   // Serial.println("inside slv_mst");
    while ((millis() - prvtMillis_mst) <= interval)
      ;
    in++;
    //    lcd_print();
     flag_mst = 0;
    // interrupts();
    Serial.println("inside slv_mst");

    // Serial.print("TOTAL : "); Serial.print(in+out); Serial.print("  --- >>>  "); Serial.print("IN : "); Serial.print(in); Serial.print("  ||  "); Serial.print("OUT : "); Serial.println(out);
  }

  if (flag_mst)
  {
    // noInterrupts();
    flag_mst = 0;
    prvMillis_slv = millis();
   // Serial.println("inside flag_mst");
    while ((millis() - prvMillis_slv) <= interval)
      ;
    out++;

    //    lcd_print();

     flag_slv = 0;
    // interrupts();
    Serial.println("inside flag_mst");

    // Serial.print("TOTAL : "); Serial.print(in+out); Serial.print("  --- >>>  "); Serial.print("IN : "); Serial.print(in); Serial.print("  ||  "); Serial.print("OUT : "); Serial.println(out);
  }


  lcd_print_data();
  //    flag_mst = 0;
  //    flag_slv = 0;


//scrollInFromLeft(0, title);
}

/************************** LCD function *****************************/

void lcd_print_data()
{
  net = in - out;
  total = in + out;
  // lcd.clear();
  lcd.setCursor(5, 1);
  //lcd.print(in);
  print02(in);

  lcd.setCursor(5, 2);
  //lcd.print(out);
  print02(out);

  //  count= count_in-count_out;
  lcd.setCursor(5, 3);
  print02(net);

  

  lcd.setCursor(14, 3);
  print02(total);
}

void lcd_print()
{
  net = in - out;
  total = in + out;
  lcd.clear();
  lcd.setCursor(0, 0);
 // lcd.scrollDisplayLeft(&title[0]);
 lcd.print("HOPE SEC EQP PVT LTD");
  lcd.setCursor(0, 1);
  lcd.print("IN ");
  lcd.setCursor(5, 1);
//  lcd.print(in);
    print02(in);
  lcd.setCursor(0, 2);
  lcd.print("OUT ");
  lcd.setCursor(5, 2);
 // lcd.print(out);
  print02(out);
  lcd.setCursor(0, 3);
  lcd.print("NET ");  
   lcd.setCursor(5, 3);
  print02(net);
  //lcd.print(0);


  lcd.setCursor(14, 2);
  lcd.print("TOTAL");
  

  lcd.setCursor(14, 3);
  print02(total);
 // lcd.print(0);

}

void lcd_default()
{
  
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  //lcd.scrollDisplayLeft(&title[0]);
  lcd.print("HOPE SEC EQP PVT LTD");
  lcd.setCursor(0, 1);
  lcd.print("IN ");
  lcd.setCursor(5, 1);
 // lcd.print(0);
  print02(0);
  lcd.setCursor(0, 2);
  lcd.print("OUT ");  
  lcd.setCursor(5, 2);
  //lcd.print(0);
  print02(0);
  lcd.setCursor(0, 3);
  lcd.print("NET ");
  lcd.setCursor(5, 3);
 // lcd.print(0);
  print02(0);


  lcd.setCursor(15, 2);
  lcd.print("TOTAL");

  lcd.setCursor(14, 3);
 // lcd.print(0);
  print02(0);
}

/****************************** end of code *****************/
