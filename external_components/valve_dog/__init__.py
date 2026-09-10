import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_PIN
from esphome.components import sprinkler
from esphome import pins  # Imported to handle native GPIO pins

CONF_ID_SPRINKLER = 'sprinkler_id'
DEPENDENCIES = ["sprinkler"]

valve_dog_ns = cg.esphome_ns.namespace('valve_dog')
ValveDog = valve_dog_ns.class_('ValveDog', cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(ValveDog),
    cv.Required(CONF_ID_SPRINKLER): cv.use_id(sprinkler.Sprinkler),
    # Added a pin config schema option that defaults to your original GPIO16 as an output pin
    cv.Optional(CONF_PIN, default=16): pins.gpio_output_pin_schema,
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    
    # Process the native GPIO pin structure and pass it to set_dog_pin()
    pin = await cg.gpio_pin_expression(config[CONF_PIN])
    cg.add(var.set_dog_pin(pin))
    
    sprinkler_var = await cg.get_variable(config[CONF_ID_SPRINKLER])
    cg.add(var.set_sprinkler(sprinkler_var))
    
    await cg.register_component(var, config)
