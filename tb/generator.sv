class generator;

  // Declare the transactor
  rand transaction trans;


  // Mailbox declaration
  mailbox gen2driv;

  // repeat number of items to generate
  // int repeat_count;

  // event
  event ended;

  // Constructor
  function new(mailbox gen2driv);
    // Getting mailbox handle from env
    this.gen2driv = gen2driv;
    this.ended = ended;
  endfunction

  // Main task
  task masin();
    trans = new();
  endtask

endclass