%#codegen
function randomSeed()

   val = int8(0);
   val = coder.ceval('LightSensor');
   coder.ceval('randomSeed',val); 
end