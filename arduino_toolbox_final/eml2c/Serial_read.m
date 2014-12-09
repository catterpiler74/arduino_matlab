%#codegen
function val = Serial_read(  )
    val=char(' ');
	val =coder.ceval('Serial.read');
end
