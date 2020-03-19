//---------------------------------------------------------------------------------------------------------------------
// three point PO
// track MPP despite sudden changes of temperature and radiation. Check twith two old values to identify sign of disturbances
// thus, sudden changes of ambient conditions will be eliminated considerably 
//---------------------------------------------------------------------------------------------------------------

#include <PWM.h>
int pin_PWM = 10;
const int pin_ADC1 = A0;  // Input Voltage pin
const int pin_ADC2 = A1; // Output voltage pin
float InputVoltage = 0; // Initialise inputVoltage variable
int point = 0;
float power[3];
float OutputVoltage =0; // Imitialise outputVoltage variable
float PVstart = 0; // PV power old value 
float PVPnew = 0; // PV power new value 
int duty = 56; // init duty cycle at 50%
int32_t frequency = 100000;
int M = 0;

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
  switch(point)
  {
    case 0:
    {
        power[0]= PVPnew;
    }
    case 1:
    {
      duty++;     
    }
    case 2: 
    {
      power[1] = PVPnew;
    }
    case 3: 
    {
      duty = duty - 2;
    }
    case 4:
    {
      power[2] = PVPnew;
    }
  }
  delay(250);
  
  

  point++;
  if(point == 5)
  {
    point = 0;
    if(power[1] >= power[0])
    {
      M++;
    }
    else
    {
      M--;
    }

    if(power[0] >= power[2])
    {
      M++;
    }
    else
    {
      M--;
    }

    if(M = 2) //
    {
      duty + 2;
    }
    if(M = -2)
    {
     // do nothing 
    }
    else
    {
      duty++;
      M = 0;
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
  Serial.print("duty cycle: ");
  Serial.println(duty);
  analogWrite(pin_PWM, duty); // Write new duty cycle
  PVstart = PVPnew; // Record and replace old values with the new one
  delay(500); // delay to give time for the circuit to register the change
}
