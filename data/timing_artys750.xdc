#
# Timing Constraints file for artys750 Board
#

##############################################
# Create Clocks
##############################################

# IO CLOCK
# - 12 MHZ - 83.33ns
create_clock -name sysclk -period 83.333 [get_ports IO_CLK]
# create_clock -period 83.333 [get_ports clk_in1]
set_input_jitter [get_clocks -of_objects [get_ports IO_CLK]] 0.833

set_property PHASESHIFT_MODE WAVEFORM [get_cells -hierarchical *adv*]

# JTAG CLOCK
# - 8 MHZ - 125ns
create_clock -name jtagclk -period 125 [get_ports JTAG_TCK]

# SPI CLOCK
# 20MHZ - 50ns
create_clock -name spiclk -period 50 [get_ports SPI_SCK]

##############################################
# Input Output Delays
##############################################

# JTAG
# Guessing 5ns min and max delay
set_input_delay -max -clock jtagclk 5 [get_ports JTAG_TMS ]
set_input_delay -max -clock jtagclk 5 [get_ports JTAG_TDI ]
set_input_delay -max -clock jtagclk 5 [get_ports JTAG_TRSTN ]
set_input_delay -min -clock jtagclk 5 [get_ports JTAG_TMS ]
set_input_delay -min -clock jtagclk 5 [get_ports JTAG_TDI ]
set_input_delay -min -clock jtagclk 5 [get_ports JTAG_TRSTN ]

# Output delays
set_output_delay -min -clock jtagclk 5 [get_ports JTAG_TDO ]
set_output_delay -min -clock jtagclk 5 [get_ports JTAG_TDO ]

# SPI


##############################################
# Clock Groups
##############################################

set_clock_groups -group sysclk -group jtagclk -group spiclk -asynchronous

##############################################
# Timing Exceptions
##############################################

set_false_path -from [get_pins {u_ibex_demo_system/gen_dm_top.u_dm_top/dap/i_dmi_cdc/i_cdc_resp/data_q_reg[1]/C}] -to [get_pins {u_ibex_demo_system/gen_dm_top.u_dm_top/dap/dr_q_reg[0]/D}]

get_pins -hierarchical -regexp -nocase -filter { PARENT_CELL =~  ".*i_cdc.*" && NAME =~  ".*data_q_reg.*" }

set_false_path -from [get_clocks jtagclk] -to [get_clocks -of_objects [get_pins clkgen/mmcm_adv_inst/CLKOUT0]]
set_false_path -from [get_clocks -of_objects [get_pins clkgen/mmcm_adv_inst/CLKOUT0]] -to [get_clocks jtagclk]