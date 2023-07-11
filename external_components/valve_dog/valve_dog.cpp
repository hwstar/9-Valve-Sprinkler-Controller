//
// This external component  controls the valve watchdog relay.
// The point of it is to prevent overwatering if the code locks up for some reason.
// The way it works is it sends out a low frequency AC signal
// by toggling the "DOG_PIN". The DOG_PIN drives a charge pump and a MOSFET
// relay driver. 
//
// The low frequency AC signal is turned on when the sprinkler controller is active.
// and turned off when the sprinkler controller is inactive.
// This class requires visibility into the sprinkler controller class in order to 
// work properly. Visibility is accomplished through the use of the id()
// function with the sprinkler controller name passed as an argument.
// Refer to the note below.

namespace esphome {
namespace valve_dog {

#include "esphome.h"

#define DOG_PIN 16

static const char *TAG = "valve_dog.component";


void ValveDog::setup(){
  // Called once
  this->pin_state = false;
  pinMode(DOG_PIN, OUTPUT);
  digitalWrite(DOG_PIN, pin_state);
}

//  Enable or disable the valve watchdog


void ValveDog::loop() {
  // Called repeatedly at appx. 60Hz

  //if(this->sprc_obj->active_valve().has_value()){ // Sprinkler controller must be active
  if(this->sprc_obj->any_controller_is_active()){ // If any sprinkler controller is active
        // Toggle the valve watchdog pin if enabled
        pin_state = !pin_state;
        digitalWrite(DOG_PIN, pin_state);
  }
  else {
   // Force  the valve watchdog pin low
   this->pin_state = false;
   digitalWrite(DOG_PIN, pin_state);
  }
}

