
// 20ns clock - 50MHz
`define HALF_CLK_PERIOD 10ns
// 1Mhz = 1000ns
// `define JTAG_HALF_CLK_PERIOD 500ns
// Simulation JTAG clock period run at 10Mhz
` define JTAG_HALF_CLK_PERIOD 50ns


// `timescale 1ns/1ps


module tb_arty_s7
(

);

  logic clk = 1'b0;
  logic reset_n = 1'b0;

  logic tck,tms,trst_n,tdi,tdo;

  localparam GPI_WIDTH = 8;
  localparam GPO_WIDTH = 16;
  localparam PWM_WIDTH = 12;
  localparam CLOCK_FREQ = 50_000_000;
  localparam BAUD_RATE = 115_200;

  

  //----------------------------------
  // JTAG sequences
  //----------------------------------

  // JTAG Reset
  task jtag_rst();
    tms = 1'b1;
    trst_n = 1'b0;
    // Hold reset for 10 jtag cycles
    for (int i=0; i < 20; i = i+1) begin
      #`JTAG_HALF_CLK_PERIOD tck = ~tck;
    end
  endtask

  task jtag_select_ir_scan();
    tms = 1'b1;
    #`JTAG_HALF_CLK_PERIOD tck = ~tck;
    #`JTAG_HALF_CLK_PERIOD tck = ~tck;
    tms = 1'b0;
  endtask

  //----------------------------------
  // Clock and Reset driving logic
  //----------------------------------

  // Reset
  task hw_reset();
    reset_n = 1'b1;
    @ (negedge clk);
    reset_n <= 1'b0;
    @ (negedge clk);
    @ (negedge clk);
    reset_n <= 1'b1;
  endtask: hw_reset

  // Clocking
  initial begin
    forever begin
      #`HALF_CLK_PERIOD clk = ~clk;
    end
  end


  //----------------------------------
  // Testbench
  //----------------------------------
  initial begin
    tck = 1'b0;
    tms = 1'b0;
    trst_n = 1'b1;
    tdi = 1'b0;

    hw_reset();

    // Wait 10 cycles after the hw reset
    repeat (10) @(posedge clk);
    jtag_rst();

    // Select IR-SCAN
    jtag_select_ir_scan();

    // Now do the Jtag Reset sequence

    #10us $finish();
  end



  //---------------------
  // Waveform dump
  //---------------------
  initial begin
    $dumpfile("dump.vcd");
    $dumpvars(0, tb_arty_s7);
  end


  //---------------------
  // DUT
  //---------------------

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

    .tck_i           (tck),    // JTAG test clock pad
    .tms_i           (tms),    // JTAG test mode select pad
    .trst_ni         (trst_n),  // JTAG test reset pad
    .td_i            (tdi),     // JTAG test data input pad
    .td_o            (tdo)      // JTAG test data output pad
  );



endmodule
