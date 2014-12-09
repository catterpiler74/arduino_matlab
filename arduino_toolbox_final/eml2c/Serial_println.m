
%#codegen
function [ ] = Serial_println( str_Text)
	coder.allowpcode('plain')
	tempStr = coder.opaque('char*','(char*)calloc(sizeof(char*),17)');
	str = coder.opaque('char*','"%-16s"');
    str2 = coder.opaque('char*',['"' str_Text '"']);
	
    coder.ceval('sprintf',tempStr,str,str2);
	coder.ceval('Serial.println',tempStr);	
end