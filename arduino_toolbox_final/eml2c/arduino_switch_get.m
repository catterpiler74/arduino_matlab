%#codegen
function val =  arduino_switch_get()	
	coder.allowpcode('plain')
	val = char('0');
	val = coder.ceval('arduino_switch');
end
	