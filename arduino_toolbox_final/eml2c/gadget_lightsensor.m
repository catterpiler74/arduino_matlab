%#codegen
function val = gadget_lightsensor( )
    val=uint8(0);
	val =coder.ceval('LightSensor');
end
