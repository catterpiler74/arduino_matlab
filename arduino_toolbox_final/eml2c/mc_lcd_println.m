%#codegen
function [ ] = mc_lcd_println( str_Text, varargin)
	coder.allowpcode('plain')
	if isempty(coder.target) 
	%% MATLAB %%
		tempStr = '';
        int_Line = varargin{nargin-1};
        if( nargin > 2)
            str = sprintf(str_Text,varargin{1,nargin-2});
        else
            str = str_Text;
        end
        if( int_Line == 0)
            tempStr = sprintf('0: %s\n1: %s',str,'(Unchanged)');
        elseif( int_Line == 1)
            tempStr = sprintf('0: %s\n1: %s','(Unchanged)',str);
        end
        disp('--------LCD--------');
        disp(tempStr);
        disp('-------------------');
        disp(' ');
	else 
	%% C %%
        tempStr = coder.opaque('char*','(char*)calloc(sizeof(char*),17)');
        if( nargin > 2 )
            str = coder.opaque('char*',['"' str_Text '"']);
            coder.ceval('sprintf',tempStr,str,varargin{1:nargin-2});
        else
            str = coder.opaque('char*','"%-16s"');
            str2 = coder.opaque('char*',['"' str_Text '"']);
            coder.ceval('sprintf',tempStr,str,str2);
        end
        line_num = int16(varargin{nargin-1});
        coder.ceval('writeLine',tempStr, line_num);
        coder.ceval('free',tempStr);
	end
end
