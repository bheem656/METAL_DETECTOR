


uint16_t interval = 700; // passing speed
uint8_t master_pin = 2; // D5; gpio 4
uint8_t slave_pin = 3;  // D6; gpio 2
volatile int out =0, in =0;
volatile unsigned long currentTime;
// volatile uint8_t flag_mst = 0;
// volatile uint8_t flag_slv = 0;

void master_isr(){
if((millis()- currentTime) > interval)
  out++;
currentTime = millis();
}


void slave_isr()
{
  if((millis()- currentTime) > interval)
  in++;
currentTime = millis();

}

void setup()
{
  pinMode(13,OUTPUT);
  pinMode(3,INPUT);

  attachInterrupt(digitalPinToInterrupt(master_pin), master_isr, LOW);
  attachInterrupt(digitalPinToInterrupt(slave_pin), slave_isr, LOW);
  Serial.begin(115200);
}
void loop()
{
 Serial.print("OUT : ");Serial.println(out);
 Serial.print("IN : ");Serial.println(in);
delay(2000);
  
}