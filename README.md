# solar-MPPT
MPPT (Maximum Power Point Tracker) using Arduino

## Perturb & Observe

A simple Perturb & Observe algorithm to track the maximum power point of the PV cells, using the input and output voltage. When the MPPT is found, it will oscillate in between 2 duty cycles.

## Improved Perturb & Observe with Reset 

An improved version of Perturb & Observe. 
Once the MPPT is found and 10 oscillations around the same duty cycle occurs, the duty cycle will become fixed and avoid noises.
If the change in output voltage is greater than a certain value, instead of resetting to the initial point (50% duty cycle), it will reset half a step.

## Three Point Perturb & Observe
A Perturb & Observe that is more precise, checking the value when the duty cycle is decreased AND increased. And moving towards the duty cycle with the highest output power.
Although it is more precise, it will considerably increase the time to find the maximum power point. 

Further information can be found in the report attached in the repository.
