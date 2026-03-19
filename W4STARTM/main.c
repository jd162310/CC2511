/**************************************************************
 * main.c
 * rev 1.0 19-Mar-2026 bjays
 * W4STARTM
 * ***********************************************************/

#include "pico/stdlib.h"
#include <stdbool.h>
#include <stdio.h>

// global variables
int high_delay_us = 1; // microseconds
int low_delay_us = 1; // microseconds 

// Function for pin initialization
int init_stepper_pins() {
  // Define pins
  #define STEP 14
  #define DIR 15
  #define ENABLE 22
  // set the pins to output
  gpio_init(ENABLE);
  gpio_set_dir(ENABLE, GPIO_OUT);
  gpio_put(ENABLE, 1);
  gpio_init(STEP);
  gpio_init(DIR);
  gpio_set_dir(STEP, GPIO_OUT);
  gpio_set_dir(DIR, GPIO_OUT);
}

// Function to send pulse signal to stepper motor
int send_pulse_to_stepper() {
  gpio_put(STEP, 1); // Step
  sleep_us(high_delay_us); // Short delay
  gpio_put(STEP, 0); // Clear step
  sleep_us(low_delay_us); // Short delay
}

// Function to execute a number of steps
int execute_n_steps(int steps) {
  for (int i = 0; i < steps; i++) {
    send_pulse_to_stepper();
  }
}
int main(void) {

  stdio_init_all(); 

  init_stepper_pins(); // initalizes pins inside main() with function call

  while (true) {
    // obtains user input
    int c = getchar_timeout_us(0);
    if (c != PICO_ERROR_TIMEOUT) {
      switch(c) {
          case 'f':
          case 'F':
          execute_n_steps(1);
          break;
          case 'g':
          case 'G':
          execute_n_steps(10);
          break;
          case 'h':
          case 'H':
          execute_n_steps(100);
          break;
          case 'j':
          case 'J':
          execute_n_steps(200);
          break;
          default:
          printf("Invalid inout");
      }
      

  }
}
  return 0;
}
