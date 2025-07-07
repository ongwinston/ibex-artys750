`include "environment.sv"

program test(jtag_intf intf);

  class my_trans extends transaction;

    bit [1:0] count;

  endclass


  environment env;
  my_trans my_tr;

  initial begin
    env = new(intf);
    my_tr = new();

    env.gen.repeat_count = 4;
    env.gen.trans = my_tr;

    env.run();
  end

endprogram