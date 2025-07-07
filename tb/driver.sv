`include "transaction.sv"

class driver;

  // Creating virtual interface handle
  virtual jtag_intf jtag_vif;

  // Creating mailbox handle
  mailbox gen2driv;

  // Constructor
  function new(virtual jtag_intf jtag_vif, mailbox gen2driv);
    // getting the interface
    this.jtag_vif = jtag_vif;

    // Getting the mailbox handle from environment
    this.gen2driv = gen2driv;
  endfunction


  // Reset the interface signals
  task reset;
    wait(jtag_vif.reset);
    wait(!jtag_vif.reset);
  endtask

  task drive;
    transaction trans;
    gen2driv.get(trans);
  endtask


  task main;
    forever begin
      fork
        begin
          wait(jtag_vif.reset);
        end
        begin
          forever
            drive();
        end
      join_any
      disable fork;
    end
  endtask

endclass