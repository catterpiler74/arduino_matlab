%#codegen
function [  ] = arduino_start( ms )

coder.ceval('Serial.begin',cast(ms,'int32'));
end
