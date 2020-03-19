#include <PWM.h>
int pin_PWM = 10;
const int pin_ADC1 = A0;  // Input Voltage pin
const int pin_ADC2 = A1; // Output voltage pin
float InputVoltage = 0; // Initialise inputVoltage variable
float OutputVoltage =0; // Imitialise outputVoltage variable
float PVstart = 0; // PV power old value 
float PVPnew = 0; // PV power new value 
int duty = 44; // init duty cycle at 55%, closer to most MPP
int32_t frequency = 100000;
float oldInputVoltage = 0;
int oldDuty1, oldDuty2; // save the old duty cycle 
bool flag; // raised when it is oscillating and has found the MPP
int oscillating = 0; // check the number of times it is oscillating 

void setup() {
  InitTimersSafe();

  bool success = SetPinFrequencySafe(pin_PWM, frequency);
  if(success)
  {
    pinMode(pin_PWM, OUTPUT);
    Serial.begin(9600);
  }
}

void loop() {
  InputVoltage = analogRead(pin_ADC1)*0.0049; // Read input voltage 
  Serial.print("Input Voltage ");
  Serial.println(InputVoltage);
  OutputVoltage = analogRead(pin_ADC2)*0.0049; // Read output voltage 
  Serial.print("Output Voltage ");
  Serial.println(OutputVoltage);
  delay(200); // delay before operating the values
  PVPnew = InputVoltage * OutputVoltage; // equation from prelab
  
  Serial.print("PVPnew ");
  Serial.println(PVPnew);

  
  if(PVPnew >= PVstart) // if the new power is highger than the old power
  {
    duty = duty + 1;  // Increase the duty cycle 
    delay(150); // delay or the circuit to have time to behave
  }
  else if ((PVPnew < PVstart)) // if new power smaller than old power
  { 
      if(oldInputVoltage >= InputVoltage)
      {
        duty = duty - 1; // decrease the duty cycle
        delay(200);
      }
      else
      {
        duty++;
        delay(200);

      }
  }


  if(duty > 72) // Limit the duty cycle from 10% to 90%
  {
    duty = 72;
  }
  if(duty < 8)
  {
    duty = 8;
  }


  if((oldDuty1 == duty)) 
  {
    oscillating++; // if the duty cycle before the last duty cycle is equal to the current, increment
    Serial.print("osccillating :");
    Serial.println(oscillating);
  }
  if(oscillating > 10) // If it is oscillating more than 10 times
  {
    duty = oldDuty2; // make duty constant 
    flag =true; // flag that it is constant duty true 
  }
  if(flag)
  {
    if(abs(PVPnew - PVstart) >= 0.3){ // if sudden change of power
      oscillating = 0;  // oscillation back to zero 
      flag = false; // flag for constant duty false
      duty = 44; // duty back to 55%
      PVPnew = PVstart = 0; // re-init old values 
    }
  }
  
  oldDuty1 = oldDuty2; // save the old duty cycle (sliding window)
  oldDuty2 = duty; 
  Serial.print("old duty");
  Serial.print(oldDuty1);
  Serial.print(" ");
  Serial.println(duty);

  PVstart = PVPnew; // Record and replace old values with the new one
  oldInputVoltage = InputVoltage;
  Serial.print("duty cycle: ");
  Serial.println(duty);
  analogWrite(pin_PWM, duty); // Write new duty cycle

  delay(200); // delay to give time for the circuit to register the change

}
