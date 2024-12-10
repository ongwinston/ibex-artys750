//
// Wishbone Bridge Master
// Takes Requests from the Ibex Core and converts those data requests to Wishbone
// Compliant requests
//
// * Non Pipelined - Classic Wishbone Master
//

module wb_bridge_master #(
  parameter int unsigned DATA_WIDTH=32,
  parameter int unsigned ADDR_WIDTH=32
) (
  input                     clk_i,
  input                     reset_i,

  // To From Ibex Core
  input                     data_req_i,
  output                    data_gnt_o,
  input                     data_we_i,
  input [3:0]               data_be_i,
  input [ADDR_WIDTH-1:0]    data_addr_i,
  input [DATA_WIDTH-1:0]    data_wdata_i,
  input                     data_wdata_intg_i, // UNUSED

  output [DATA_WIDTH-1:0]   data_rdata_o,
  output                    data_rdata_intg_o, //UNUSED
  output                    data_rvalid_o,
  output                    data_err_o,

  // To Wishbone Xbar Requests
  output                    mcyc_o,
  output                    mstb_o,
  output                    mwe_o,
  output [ADDR_WIDTH-1:0]   maddr_o,
  output [DATA_WIDTH-1:0]   mdata_o,
  output [DATA_WIDTH/8-1:0] msel_o,

  // Wishbone Xbar Response
  input                     mstall_i,
  input                     mack_i,
  input [DATA_WIDTH-1:0]    mdata_i,
  input                     merr_i

);


////////////////////////////////////////
// TODO: Fix outputs
////////////////////////////////////////

  assign data_gnt_o = mack_i & !(mstall_i | merr_i);
  assign data_rdata_o = mdata_i;
  assign data_rdata_intg_o = 'd0;
  assign data_rvalid_o = mack_i & !(mstall_i | merr_i);
  assign data_err_o = merr_i;

  assign mcyc_o = data_req_i;
  assign mstb_o = data_req_i;
  assign mwe_o = data_we_i;
  assign maddr_o = data_addr_i;
  assign mdata_o = data_wdata_i;
  assign msel_o = data_be_i;

endmodule
