%#codegen
function val = attach( pin)
    val=uint8(0);
	val =coder.ceval('attach',pin);
end
