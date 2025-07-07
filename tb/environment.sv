`include "transaction.sv"
`include "generator.sv"
`include "driver.sv"

class environment;

  // Generator and driver instance
  generator gen;
  driver driv;

  // mailbox handle
  mailbox gen2driv;

  event gen_ended;

  // virtual interface
  virtual jtag_intf jtag_vif;


  // Constructor
  function new(virtual jtag_intf jtag_vif);
    // get the interface from test
    this.jtag_vif = jtag_vif;

    // creating the mailbox
    gen2driv = new();

    // creating generator and driver
    gen = new(gen2driv, gen_ended);
    driv = new(jtag_vif, gen2driv);
  endfunction


  task pre_test();
    driv.reset();
  endtask

  task test();
    fork
      gen.main();
      driv.main();
    join_any
  endtask

  task post_test();
    wait(gen_ended.triggered);
    // wait(gen.repeat_count == driv.no_transactions);
  endtask

  // run task
  task run;
    pre_test();
    test();
    post_test();
    $finish();
  endtask

endclass
