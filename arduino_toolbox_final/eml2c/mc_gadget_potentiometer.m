%#codegen
function val = mc_gadget_potentiometer( )
    val=uint8(0);
	val =coder.ceval('Pot');
end
