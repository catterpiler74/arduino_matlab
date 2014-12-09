%#codegen
function val = mc_microphone_aptitude()
    val = uint8(0);
    val = coder.ceval('MicrophoneAmplitude');
end
