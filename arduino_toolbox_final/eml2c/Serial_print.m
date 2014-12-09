
%#codegen
function [ ] = Serial_print(str)

	coder.ceval('Serial.println',str);	
end