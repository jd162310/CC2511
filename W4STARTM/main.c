/**************************************************************
 * main.c
 * rev 1.0 19-Mar-2026 bjays
 * W4STARTM
 * ***********************************************************/

#include "pico/stdlib.h"
#include <stdbool.h>
#include <stdio.h>

// global variables
// Define pins
  #define STEP 5
  #define DIR 6
  #define ENABLE 22
  #define Mode0 2
  #define Mode1 3
  #define Mode2 4
int high_delay_us = 1000; // microseconds
int low_delay_us = 1000; // microseconds

// Function for pin initialization
void init_stepper_pins() {
  // set the pins to output
  gpio_init(ENABLE);
  gpio_set_dir(ENABLE, GPIO_OUT);
  gpio_put(ENABLE, 0);
  gpio_init(STEP);
  gpio_init(DIR);
  gpio_set_dir(STEP, GPIO_OUT);
  gpio_set_dir(DIR, GPIO_OUT);
  gpio_init(Mode0);
  gpio_init(Mode1); 
  gpio_init(Mode2);
  gpio_set_dir(Mode0, GPIO_OUT);
  gpio_set_dir(Mode1, GPIO_OUT);
  gpio_set_dir(Mode2, GPIO_OUT);
}

// Function to send pulse signal to stepper motor
void send_pulse_to_stepper() {
  gpio_put(STEP, 1); // Step
  sleep_us(high_delay_us); // Short delay
  gpio_put(STEP, 0); // Clear step
  sleep_us(low_delay_us); // Short delay
}

// Function to execute a number of steps
void execute_n_steps(int steps) {
  for (int i = 0; i < steps; i++) {
    send_pulse_to_stepper();
  }
}

// function to set the direction of the stepper motor
void set_stepper_direction(bool forward) {
  gpio_put(DIR, forward); // sets direction forward or backward based on user input
}

// function to set up microstepping mode
void set_microstepping_mode(int mode) {
  switch(mode) {
    case 1: // full step
      gpio_put(Mode0, 0);
      gpio_put(Mode1, 0);
      gpio_put(Mode2, 0);
      break;
    case 2: // half step
      gpio_put(Mode0, 1);
      gpio_put(Mode1, 0);
      gpio_put(Mode2, 0);
      break;
    case 4: // quarter step
      gpio_put(Mode0, 0);
      gpio_put(Mode1, 1);
      gpio_put(Mode2, 0);
      break;
    case 8: // eighth step
      gpio_put(Mode0, 1);
      gpio_put(Mode1, 1);
      gpio_put(Mode2, 0);
      break;
    case 16: // sixteenth step
      gpio_put(Mode0, 1);
      gpio_put(Mode1, 1);
      gpio_put(Mode2, 1);
      break;
    case 32: // thirty-second step
      gpio_put(Mode0, 1);
      gpio_put(Mode1, 0);
      gpio_put(Mode2, 1);
      break;    
      default:
      printf("Invalid microstepping mode");
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
          case 'd':
          case 'D':
          set_stepper_direction(true);
          break;
          case 'a':
          case 'A':
          set_stepper_direction(false);
          break;
          case '0':
          set_microstepping_mode(1);
          break;
          case '1':
          set_microstepping_mode(2);
          break;
          case '2':
          set_microstepping_mode(4);
          break;
          case '3':
          set_microstepping_mode(8);
          break;
          case '4':
          set_microstepping_mode(16);
          break;
          case '5':
          set_microstepping_mode(32);
          break;
          default:
          printf("Invalid inout");
      }
      

  }
}
  return 0;
}
