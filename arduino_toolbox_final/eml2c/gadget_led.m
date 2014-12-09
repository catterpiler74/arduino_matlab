%#codegen
function val = gadget_led( channel,threshold )
    val = int32(0);
    val = coder.ceval('LED',channel,threshold);
end
