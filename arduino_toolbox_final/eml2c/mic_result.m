%#codegen
function val = mic_result()
    val = uint8(0);
    val = coder.ceval('result');
end
