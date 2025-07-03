

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

endclass