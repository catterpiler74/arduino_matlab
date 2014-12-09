%#codegen
function [  ] = mc_pinMode( pin,output )
    
     coder.ceval('pinMode',pin,output);
end
