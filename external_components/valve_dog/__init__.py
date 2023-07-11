
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

valve_dog_ns = cg.esphome_ns.namespace('valve_dog')
ValveDog = empty_component_ns.class_('ValveDog', cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(ValveDog)
}).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
