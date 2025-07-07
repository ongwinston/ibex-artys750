

interface jtag_intf(
  input logic clk,
  input logic reset
);

  // Declare the JTAG signals
  logic tck;
  logic tdi;
  logic tdo;
  logic tms;
  logic trstn;


  // driver clocking block
  clocking driver_cb @(posedge clk);
    default input #1 output #1;
    output tck;
    output tdi;
    output tms;
    input tdo;
    output trstn;
  endclocking

  // driver modport
  modport DRIVER(clocking driver_cb, input clk, reset);

  // monitor modport
  // modport MONITOR (clocking monitor_cb, input clk, reset);


endinterface