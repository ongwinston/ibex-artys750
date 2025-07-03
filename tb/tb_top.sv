

`include "interface.sv"


module tb_top;

  localparam GPI_WIDTH = 8;
  localparam GPO_WIDTH = 16;
  localparam PWM_WIDTH = 12;
  localparam CLOCK_FREQ = 50_000_000;
  localparam BAUD_RATE = 115_200;

  bit clk;
  bit reset;

  // Clock Generatation
  always #5 clk = ~clk;

  // Reset Generation
  initial begin
    reset = 1;
    #5 reset = 0;
  end


  // Interface
  jtag_intf intf(clk, reset);


  //---------------------------------------------------------------------------------------------------------------------------
  // DUT
  //---------------------------------------------------------------------------------------------------------------------------

  ibex_demo_system #(
    .GpiWidth       (GPI_WIDTH),
    .GpoWidth       (GPO_WIDTH),
    .PwmWidth       (PWM_WIDTH),
    .ClockFrequency (CLOCK_FREQ),
    .BaudRate       (BAUD_RATE)
    // .RegFile        (ibex_pkg::RegFileFPGA),
    // .SRAMInitFile   (""),
  ) ibex_demo_system_inst (
    .clk_sys_i       (clk),
    .rst_sys_ni      (reset_n),

    .gp_i            ((GPI_WIDTH)'('d0)),
    .gp_o            (/*UNCONNECTED*/),
    .pwm_o           (/*UNCONNECTED*/),
    .uart_rx_i       (1'd0),
    .uart_tx_o       (/*UNCONNECTED*/),
    .spi_rx_i        (),
    .spi_tx_o        (/*UNCONNECTED*/),
    .spi_sck_o       (/*UNCONNECTED*/),

    .tck_i           (intf.tck),    // JTAG test clock pad
    .tms_i           (intf.tms),    // JTAG test mode select pad
    .trst_ni         (),  // JTAG test reset pad
    .td_i            (intf.tdi),     // JTAG test data input pad
    .td_o            (intf.tdo)      // JTAG test data output pad
  );




  //---------------------
  // Waveform dump
  //---------------------
  initial begin
    $dumpfile("dump.vcd");
    $dumpvars(0);
  end

endmodule