%#codegen
function val = mc_gadget_transmit(pin,pot_value )
    val=0;
	val =coder.ceval('IRTransmit',pin,pot_value);
end
