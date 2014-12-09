%#codegen 

function [] = sound_isr()
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
    %global pitch
    
    coder.ceval('tone',cast(pitch,'int32'));

end

