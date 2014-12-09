Release notes for eml2c 

version 0.75
* added the following registers to emc_registers:
    - PWMDTY01
    - PWMDTY23
    - PWMDTY45
    - PWMDTY67

* reworked static cleaner to only remove lines which contained the keyword 'static' and 
  redeclares one of the global register variables.
  
* added some functions for controlling servo motors.
    - mc_servo_init     used to initialize four servos using 16bit duty cycle encoding
    - mc_servo_pos_init used to initialize four servos for position control
    - mc_servo_pos_set  used to set the position on the given servo
    - mc_servo_vel_init	used to initialize four servos for velocity control
    - mc_servo_vel_set	used to set the velocity on the given servo
    
version 0.7

* renamed a few functions:
    - mc_sw_init -> mc_switch_init
    - mc_get_atd -> mc_atd_get
    
* refactored sound system somewhat
    - added mc_sound_set_pitch to set pitch value
    - variable 'pitch' should now be transparent to users. no need to declare, set, or
    otherwise touch it.  
    - default pitch is 2867 (middle c) until modified.

* fixed bug causing multiple global declarations to appear in c code when the word
  'function' appears in comments.

* fixed bug causing 'symbol main undefined' error when m-file is not called main.
  function contained in m-file should be named indentically to m-file 
  (i.e my_m_file.m should contain a function called my_m_file)
  
* The following interrupts are automatically declared when no user-defined interrupts
  are declared:
    sound_isr
    RealTimeInterrupt
    TOIInterrupt
    TC1Interrupt
  when declaring user defined interrupts, these interrupts must be declared also, and
  the 'vectors.c' file must be modified to account for the user-defined interrupts.
  
