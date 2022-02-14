//Timer interrupts
//by Uttam Basu
//February 2022

//Timer setup for timer1
//For arduino uno or any board
//Timer1 will interrupt at 1Hz

//storage variables
boolean toggle1 = 0;

void setup()
{
  //set pins as outputs
  pinMode(10, OUTPUT);

  //For 1 Second Time Generate on Timer 1.
  cli();                          //stop interrupts
  //set timer1 interrupt at 1Hz
  TCCR1A = 0;                     // set entire TCCR1A register to 0
  TCCR1B = 0;                     // same for TCCR1B
  TCNT1  = 0;                     //initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;                  // = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei();                           //allow interrupts
}

ISR(TIMER1_COMPA_vect)              //Timer1 interrupt 1Hz toggles pin 10 (LED)
{
  //Generates pulse wave of frequency 1Hz/2 = 0.5Hz (takes two cycles for full wave- toggle high then toggle low)
  if (toggle1)
  {
    digitalWrite(10, HIGH);
    toggle1 = 0;
  }
  else
  {
    digitalWrite(10, LOW);
    toggle1 = 1;
  }
}

void loop()
{

}
