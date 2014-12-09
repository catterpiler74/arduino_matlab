%#codegen 
function  []= mc_digitalWrite( pin, state )
    coder.ceval('digitalWrite',pin,state);
end