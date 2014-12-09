function [] = emc(strFileName,varargin)
%EMC Embedded Matlab to C (AKA: eml2c)
% This function will compile an EMC compliant file to C using CodeWarrior
%
% Example File Format:
%   |%#codegen
%	|%#interrupt RealTimeInterrupt
%	|%#interrupt TC1Interrupt
%   |
%   |function [] = main()
%   |
%   |
%   |end
%
%   Please Note: if interrups are use there must be a corresponding m-file

    try
	
	
    disp('### Starting up...');  % Displays  the string encotted in it
%	strFileName = sprintf('%s.m',strFileName);  % changes on 7/16/12
	
	%new addition 
	strFileRoot = strFileName;
	strFileName = sprintf('%s.m',strFileRoot);
	strFileNameC = sprintf('%s.c',strFileRoot);

%% Initialization %%        
	disp('### Initializing Registers...');
    
        emc_registers;   					% This Initializes all Registers of Dragon 12 board.

 %% Path Variables %%
    disp('### Setting Path Variables...');
        MatlabBase = 'eml2c';
        CwVersionFolder = 'CWS12v5.1';
        
        ProgramFiles = 'C:\Program Files';
        
        CwBase = 'arduino_pro';
        CwHiWave = 'Prog\hiwave.exe';
        CwCmdIDE = 'bin\CmdIDE.exe';
        CwPName = 'arduino_pro';
        
%% Confituration Object %%        
    disp('### Setting configuration options...'); 
        % Configuration Object %
        % This is used for setting options for compiling %   // Have to know about this config file
		%config = coder.config('lib'); % the New Code 
		config =coder.CodeConfig;
        config.Name = 'Real-Time Workshop';
        config.Description = 'Generic Real-Time Target';
        config.TargetLang = 'C';
%         config.ExtMode = 'off';
%         config.ExtModeTransport = 0;
%         config.ExtModeMexArgs = '';
%         config.ExtModeStaticAlloc = 'off';
%         config.ExtModeStaticAllocSize = 1000000;
        config.Verbose = true;%false;
        config.GenCodeOnly = true;
        config.GenerateMakefile = false;
        config.GenerateReport = false;
        config.LaunchReport = false;
%        config.GenerateComments = 'off';
%        config.MATLABSourceComments = 'off';
        config.FilePartitionMethod = 'SingleFile';%temp fix for multiple
                                                  %call to the same func
        config.MaxIdLength = 31;
        config.TargetFunctionLibrary = 'C89/C90 (ANSI)';
        config.CCompilerOptimization = 'off';
        config.CCompilerCustomOptimizations = '';
        config.MakeCommand = 'make_rtw';
        config.TemplateMakefile = 'grt_default_tmf';
        config.PostCodeGenCommand = '';
        config.CustomHeaderCode = '';
        config.CustomSourceCode = sprintf('#include "Arduino.h"');
		
        config.CustomInitializer = '';
        config.CustomTerminator = '';
        config.CustomInclude = '';
        config.CustomSource = '';
        config.CustomLibrary = '';
        config.ReservedNameArray = '';
        config.ConstantFoldingTimeout = 10000;
        config.InlineThreshold = 10;
        config.InlineThresholdMax = 200;
        config.InlineStackLimit = 4000;
        config.SaturateOnIntegerOverflow = true;
        config.StackUsageMax = 200000;
        config.EnableVariableSizing = true;
%        config.EnableMemcpy = 'on';
%        config.MemcpyThreshold = 64;
%        config.InitFltsAndDblsToZero = 'on';
%        config.DynamicMemoryAllocation = 'AllVariableSizeArrays';
  
%% Compiler Options %%
    disp('### Setting compiler options...');
        LogLevel = 0;
        LogFile = 'C:\temp\eml2c.log';
        LogClear = 0;

        ScriptCMD = 'C:\Windows\System32\cmd.exe';
        ScriptWScript = 'WScript'; 
        ScriptVBS = 'scripts\eml2c.vbs';
        
        %outDir = sprintf('%s\\%s\\%s\\Sources\\',matlabroot,MatlabBase,CwPName);
        outDir = sprintf('%s\\%s\\%s\\Sources\\',matlabroot,MatlabBase,CwPName);
%% Interrupt Detection %%
    % Get the interrupts specified by the user %
    
    interrupts = emc_getInterrupts(strFileName);

%% Registers and Global Variable Handling %%
	% Get the global variables from the emc_registers
	% This will need to be added to every file after the function definition
	rGlobals = emc_getRegisters();
    globalslist = regexp(rGlobals, '\ ', 'split');
%     disp('#### displaying globalslist ... remove later');
%     disp(globalslist);
% %     for i = 1:length(globalslist)
% %         disp(globalslist{1, i});
% %     end
%     [a b] = strtok(rGlobals);
%     disp('#### strtok works');
%     globalscount = 0;
%     disp('#### globalscount works');
%     globalslist = zeros(50,50);
%     while( size(b,2) > 0)
%         [a b] = strtok(b);
%         globalscount = globalscount + 1;
%         fprintf('#### adding %s to globalslist\r\n',a);
%         globalslist(globalscount) = a;
% %         if strcmp(a,'PORTB')
% %             globalslist = [globalslist; 'PORTB'];
% %         else
% %             globalslist = [globalslist;  a];
% %         end
%     end
%     disp('### showing globalslist ... remove later');
%     disp(globalslist);
	
	% Get the custom globals from the main file
	% This will need to be added to every file after the function definition execpt for the main file.
	cGlobals = emc_getGlobals(strFileName);
    [a b] = strtok(cGlobals);
    while( size(b,2) > 0 )
        [a b] = strtok(b);
        c = sprintf('global %s',a);
		disp(c);    
        evalin('base',c);
        c = sprintf('%s = 0;',a);
        evalin('base',c);
    end

 %% Create Temp Working Directory %%
    % Create a temp folder
	system('mkdir ".tmp"');
	system('copy *.m .tmp\\'); 
   
%% String Manipuation for Interrupts and Globals/Registers %%
	% Create a new file for each file that will be complied
	if length(interrupts) > 0 
		for i = 1:length(interrupts)
			fpout = fopen(sprintf('.tmp\\%s.m',char(interrupts{1,i})),'w');
			fp = fopen(sprintf('%s.m',char(interrupts{1,i})),'r');
			tline = fgetl(fp);
			while (ischar(tline))
				fprintf(fpout,'%s\r\n',char(tline));
				%if( ~isempty(strfind(tline,'function')) ) % made changes 
					if( ~isempty(strfind(tline,'function')) && isempty(strfind(tline,'%')))
                    % check for function declaration but beware of 'function'
                    % appearing in comments
                    % add the registers
					fprintf(fpout,'\r\n%s\r\n%s\r\n',rGlobals,cGlobals);	
                    %fprintf(fpout,'\r\n%s\r\n%s\r\n',rGlobals,cGlobals);	
				end
				tline = fgetl(fp);
			end
			fclose(fp);
			fclose(fpout);
		end
	end
	
	    fpout = fopen(sprintf('.tmp\\%s',strFileName),'w');
	    fp = fopen(strFileName,'r');
		tline = fgetl(fp);
        while ischar(tline)
		    fprintf(fpout,'%s\r\n',char(tline));
		    if( ~isempty(strfind(tline,'function')) && isempty(strfind(tline,'%')))
                % check for function declaration but beware of 'function'
                % appearing in comments
    			% add the registers
		        fprintf(fpout,'\r\n%s\r\n',rGlobals);
                %fprintf(fpout,'\r\n%s\r\n',rGlobals);
			end
		    tline = fgetl(fp);
		end
		fclose(fp);
		fclose(fpout);
%         disp('#### Showing globals .. remove');
%         disp(rGlobals);
  
 %% Compiling in MATLAB %%       
    disp('##### Compiling (MATLAB)...');
        cd '.tmp/';
			if length(interrupts) > 0 
			  for i = 1:length(interrupts)
				 fprintf('#### Compiling %s...\n',char(interrupts{1,i}));
				 if( nargin == 2 && strcmp(varargin{1},'-v') == 1)
				    
					%emlc('-T','MEX','-g','-c','-v','-s','config','-d',outDir,char(interrupts{1,i}));
					codegen('-g','-c','-config','config','-d',outDir,char(interrupts{1,i}));  
                 else
                     emlcStr= sprintf('codegen(''-g'',''-c'',''-config'',''config'',''-d'',''%s'',''%s'');;',outDir,char(interrupts{1,i}));
					 %coder.ceval(emlcStr);
                     evalc(emlcStr);
				 end
			  end
			end
        %config.CustomSourceCode = sprintf('#include "Arduino.h"\n"\n');
		config.CustomSourceCode = sprintf('#include "Arduino.h"\n#include "GadgetShield.h"\n#define char_T char\n#define uint8_T unsigned int\n#define int32_T int\n#define real_T int\nvoid input_ar();\nvoid setup(){ input_ar(); }\nvoid loop(){ output_ar(); }\n');
        fprintf('#### Compiling %s...\n',strFileName);
              
        if( nargin == 2 && strcmp(varargin{1},'-v') == 1)
		   
		    codegen('-g','-c','-v','-config','config','-d',outDir,strFileName);  % completely changed
			
        else
			
		    %emlcStr = sprintf('codegen(''-report'',''-g'',''-c'',''-v'',''-config'',''config'',''-d'',''%s'',''%s'');',outDir,strFileName); % change made here
            emlcStr = sprintf('codegen(''-g'',''-c'',''-v'',''-config'',''config'',''-d'',''%s'',''%s'');',outDir,strFileName); % change made here
          
            evalc(emlcStr);
        end
		
		
		% new addition 
		
		% if main file is not main.m then main.c wasn't generated, so we must 
		% move the file that was generated to main.c, because the Arduino
		% project looks for main.c
		if(strcmp(strFileName, 'main.m') ~= 1)
            targetPath = sprintf('%s\\%s\\%s\\sources\\', matlabroot,MatlabBase,CwPName);
			%disp(targetPath);
			if( nargin == 2 && strcmp(varargin{1},'-v') == 1)
                fprintf('   #### Renaming %s to main.c\n',strFileNameC);
            end
            prevDir = cd(targetPath);
            %disp(pwd);
            %disp(prevDir);
            system(sprintf('move %s main.c', strFileNameC));
            cd(prevDir);
        end
        
        
		cd '..';
 

    disp('### Doing some housekeeping...');
    

	
 %% Fix CodeWarrior Registers/Globals %%
        %skip(1) = 'static';
        %allow(1) = 'g_';
        disp('#### Housekeeping modified -- should it be fixed?');
        output = ' ';
        fid = fopen(sprintf('%smain.c',outDir),'r');
        i = 1;
        tline = fgetl(fid);
        while ischar(tline)
           
              if((i > 0) && (~isempty(strfind(tline, 'static'))) && (isempty(strfind(tline, '_dirty'))))

                    snip = false;
                    for j = 1:length(globalslist)
                        if(strfind(tline,globalslist{j}) > 0) 
                            snip = true;
                            globalmatched = globalslist{j};
                        end
                    end
%                     disp('after global checker');
                    if(~snip)
                        output = sprintf('%s\r\n%s',output,tline);
                    else
                        if( nargin == 2 && strcmp(varargin{1},'-v') == 1)
                            fprintf('#### removed global redeclare of %s at line %d\n', globalmatched, i);
                        end
                    end

            else
                output = sprintf('%s\r\n%s',output,tline);
            end
            
            i = i + 1;
            tline = fgetl(fid);

        end
        fclose(fid);
        
        % Insert Replacements Here %
          
			output = strrep(output,'rt_pow_snf','pow');
            output = strrep(output,'rt_powd_snf','pow');
            output = strrep(output,'rt_roundd_snf','round');
            output = strrep(output,'EnableInterrupts();','EnableInterrupts;');
            output = strrep(output,'static',' ');
			%output = strrep(output,'__interrupt  void RealTimeInterrupt( void ){rti();}','');
            %output = strrep(output,'__interrupt  void TC1Interrupt( void ){}','');
			%output = strrep(output,'__interrupt  void TOIInterrupt( void ){}','');
        % END Replacements %
        
		if length(interrupts) > 0 
			% Get Interrupt Code %
			for i = 1:length(interrupts)
				fileText = fileread(sprintf('%s%s.c',outDir,char(interrupts{1,i})));
				exp = '(void\s.*)';
				m = regexpi(fileText,exp,'tokens');
				output = sprintf('%s\r\n\r\n__interrupt %s',output,char(m{1,1}));
			end
			% End %
		else
			%output = sprintf('%s\r\n\r\n__interrupt  void TC1Interrupt( void ){}',output);
            %output = sprintf('%s\r\n\r\n__interrupt  void TC0Interrupt( void ){}',output);
%           output = sprintf('%s\r\n\r\n__interrupt  void TOIInterrupt( void ){}',output);     %twh added this    
 			%output = sprintf('%s\r\n\r\n__interrupt  void RealTimeInterrupt( void ){rti();}',output);
			%output = sprintf('%s\r\n\r\n__interrupt  void sound_isr( void ){tone(pitch);}', output);
            % for now assume sound_isr
        end
        
        %if main file is not main.m, emlc will call the main function
        %something other than main().  We need to fix this.
        if(strcmp(strFileName, 'main.m') ~= 1)
            
        end
        
        
		output = regexprep(output,'/\*([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+/','');
		
        fid = fopen(sprintf('%smain.c',outDir),'w');
        fprintf(fid,'%s',output);        
        fclose(fid);
        
       
		
		disp('### Compiling (Arduino)...');
        cmd = 'cd C:\arduinoUpload\avr\bin';
		run = 'C:\arduinoUpload\compile.bat'
        [a b]= system(cmd);
        if( a == 0 ) % No Errors
            disp('### Compile Successful! (Arduino)');
            disp('### Opening Debugger... (Please close the debugger to continue)');
            [c d] = system('%CD%'); % This is needed to pause the system for a second
            %cmd = sprintf('"%s\\%s\\%s\\%s" "%s\\%s\\%s\\bin\\HCS12_Serial_Monitor.abs" -Prod="%s\\%s\\%s\\HCS12_Serial_Monitor.ini" -Instance=%%currentTargetName',ProgramFiles,CwBase,CwVersionFolder,CwHiWave,matlabroot,MatlabBase,CwPName,matlabroot,MatlabBase,CwPName);
			system(run);
        else
            disp('### Compile Error (Arduino)...');
            fprintf('### Error Code [%d]...Get Help!\n',a);
            fprintf('### More Info... %s\n',cmd);
        end


	post(varargin);
   
    
	
%% ERROR HANDLING %%
    catch ME
        while( findstr('\.tmp',pwd) )
            cd ..
        end
        disp('### MATLAB Compile Error');
        post(varargin);
    end
 %% END EMC %%   
end

%% Get Interrupts from file as String Array %%
function interrupts = emc_getInterrupts(strFile)
	fileText = fileread(strFile);
	exp = '\n+\s*%#interrupt\s*(\w*)';    				%* do not know what is this for *%
	interrupts = regexpi(fileText,exp,'tokens');
end

%% Get Registers from emc_registers.m as String Array %%
function registers = emc_getRegisters()
    fp = fopen('emc_registers.m','r');
    registers = fgetl(fp); % if an error occurs during reading file, fgetl returns an empty string
	fclose(fp);
end

%% Get Global Vars from file as String Array %%
function globs = emc_getGlobals(strFile)
    globs = '';
	fp = fopen(strFile,'r');
    tline = fgetl(fp);
	while ischar(tline) %returns 1 if tline is a character array or 0 otherwise
	    if( length(strfind(tline,'global')) > 0 ) % returns the staring indics of any occurance of 'global' on the text%
		    break;
		end	
        tline = fgetl(fp);
	end
	while ischar(tline)
	    if( length(strfind(tline,'...')) > 0 )
		    globs = strcat(globs,tline);
		else
		    globs = strcat(globs,tline);
   		    break;
		end
        tline = fgetl(fp);
	end
	globs = strrep(globs,'...',' ');
	globs = regexprep(globs,'\s{2,}',' ');
	fclose(fp);
end

%% Post Clean up (ALWAYS RUNS) %%
function post(varargin)
    disp('#### Cleanup removed...remember to put back in.');
    return;
    disp('### Cleaning up...');	
	
    if( nargin == 1)
        system('rmdir /S /Q ".tmp"');
        clear all;
    end
end