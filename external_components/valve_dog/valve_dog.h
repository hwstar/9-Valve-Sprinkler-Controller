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

#pragma once

#include "esphome.h"
#include "esphome/core/log.h"
#include "esphome/core/gpio.h" // ESPHome Hardware Abstraction Layer

namespace esphome {
namespace valve_dog {

class ValveDog : public Component {
  
 protected:
  sprinkler::Sprinkler *sprc_obj;
  InternalGPIOPin *dog_pin_{nullptr}; // Pointer to the native ESPHome GPIO pin object
  bool pin_state;
  
 public:
  // Constructor
  ValveDog();
    
  void setup() override;

  void loop() override;
  
  void set_sprinkler(sprinkler::Sprinkler *sprinkler_id); 
  
  // Public setter to pass the GPIO configuration down from Python/YAML
  void set_dog_pin(InternalGPIOPin *pin);
  
  void dump_config() override;
};

}  // namespace valve_dog
}  // namespace esphome
