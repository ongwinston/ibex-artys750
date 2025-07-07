`include "transaction.sv"


class generator;

  // Declare the transactor
  rand transaction trans;


  // Mailbox declaration which drives the transaction to the driver
  mailbox gen2driv;

  // repeat number of items to generate
  int repeat_count;

  // event
  event ended;

  // Constructor
  function new(mailbox gen2driv, event ended);
    // Getting mailbox handle from env
    this.gen2driv = gen2driv;
    this.ended = ended;
    trans = new();
  endfunction

  // Main task
  task main();
    trans = new();
    if (!trans.randomize()) $fatal("Gen randomization failed");
    gen2driv.put(trans);
  endtask

endclass