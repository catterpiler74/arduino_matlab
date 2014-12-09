%#codegen
function val = analogRead(pin)
    val=uint8(0);
	val =coder.ceval('analogRead',pin);
end
