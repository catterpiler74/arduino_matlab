%#codegen
function val = microphone_amplitude()
    val = uint8(0);
    val = coder.ceval('MicrophoneAmplitude');
end
