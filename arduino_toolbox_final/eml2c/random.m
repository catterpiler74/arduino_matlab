%#codegen
function val = random(val)
    val = uint8(0);
    val = coder.ceval('random',val);
end