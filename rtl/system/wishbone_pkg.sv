

  // Wishbone Interface
interface wb_bus_if (input logic clk);
  logic [31:0] wb_data;
  logic [31:0] wb_addr;
  logic        wb_cyc;
  logic        wb_we;
  logic        wb_stb;
  logic        wb_err;
  logic        wb_stall;
  logic [3:0]  wb_be;
  logic        wb_sel;

  modport Master(
    output wb_data,
    output wb_addr,
    output wb_cyc,
    output wb_we,
    output wb_stb,
    input wb_err,
    input wb_stall,
    output wb_be,
    output wb_sel
  );

  modport Slave (
    input wb_data,
    input wb_addr,
    input wb_cyc,
    input wb_we,
    input wb_stb,
    output wb_err,
    output wb_stall,
    input wb_be,
    output wb_sel
  );

endinterface

package wishbone_interface;

endpackage
