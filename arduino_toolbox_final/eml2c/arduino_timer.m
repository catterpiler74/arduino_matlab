%#codegen
function val = arduino_timer( )
    val=0;
	val =coder.ceval('millis');
end
