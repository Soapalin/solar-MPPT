#include <PWM.h>
int pin_PWM = 10;
const int pin_ADC1 = A0;  // Input Voltage pin
const int pin_ADC2 = A1; // Output voltage pin
float InputVoltage = 0; // Initialise inputVoltage variable
float OutputVoltage =0; // Imitialise outputVoltage variable
float PVstart = 0; // PV power old value 
float PVPnew = 0; // PV power new value 
int duty = 40; // init duty cycle at 50%
int32_t frequency = 100000;

void setup() {
  // put your setup code here, to run once:
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
  //Serial.print("Input Voltage ");
  //Serial.println(InputVoltage);
  OutputVoltage = analogRead(pin_ADC2)*0.0049; // Read output voltage 
  //Serial.print("Output Voltage ");
  //Serial.println(OutputVoltage);
  delay(200); // delay before operating the values
  PVPnew = InputVoltage * OutputVoltage; // equation from prelab
  
  //Serial.print("PVPnew ");
  //Serial.println(PVPnew);
  
  if(PVPnew >= PVstart) // if the new power is highger than the old power
  {
    duty = duty + 1;  // Increase the duty cycle 
    delay(500); // delay or the circuit to have time to behave
  }
  else if ((PVPnew < PVstart)) // if new power smaller than old power
  {   
    duty = duty - 1; // decrease the duty cycle
    delay(500);
  }

  if(duty > 72) // Limit the duty cycle from 10% to 90%
  {
    duty = 72;
  }
  if(duty < 8)
  {
    duty = 8;
  }
  Serial.print("duty cycle: ");
  Serial.println(duty);
  analogWrite(pin_PWM, duty); // Write new duty cycle
  PVstart = PVPnew; // Record and replace old values with the new one
  delay(500); // delay to give time for the circuit to register the change

}
