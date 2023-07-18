
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID
from esphome.components import sprinkler

CONF_ID_SPRINKLER='sprinkler_id'
DEPENDENCIES = ["sprinkler"]

valve_dog_ns = cg.esphome_ns.namespace('valve_dog')
ValveDog = valve_dog_ns.class_('ValveDog', cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(ValveDog),
    cv.Required(CONF_ID_SPRINKLER): cv.use_id(sprinkler.Sprinkler)
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    sprinkler = await cg.get_variable(config[CONF_ID_SPRINKLER])
    cg.add(var.set_sprinkler(sprinkler))
    await cg.register_component(var, config)
