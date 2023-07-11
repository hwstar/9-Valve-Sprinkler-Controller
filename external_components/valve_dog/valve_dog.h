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


#include "esphome.h"
#include "esphome/core/log.h"
#include "valve_dog.h"
namespace esphome {
namespace valve_dog {

#define DOG_PIN 16

class ValveDog : public Component {
  
 protected:
   sprinkler::Sprinkler *sprc_obj;
  
 public:
    
  // Constructor
  ValveDog(sprinkler::Sprinkler *sc_obj){
    this->sprc_obj = sc_obj;
  }
    
    
  void setup() override {
  }

  void loop() override {
  }
  protected:
    bool pin_state;
};
}  // namespace lcd_base
}  // namespace esphome
