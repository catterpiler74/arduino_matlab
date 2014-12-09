%#codegen
function val = mc_gadget_receiver( )
    val=uint8(0);
	val =coder.ceval('IRReceive');
end
