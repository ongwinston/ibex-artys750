#
# FTDI USB Hi-Speed to MPSSE Breakout from Adafruit
#
# This should work for any bare FT232H
#
 
# Setup driver type
adapter driver ftdi
 
# 30000 kHZ -> 30MHz
#adapter speed 30000

# 1000 kHZ -> 1MHz
adapter speed 1000

 
# Using JTAG (also could be SWD)
transport select jtag
 
# Common PID for FT232H
# ftdi_vid_pid 0x0403 0x6014
ftdi vid_pid 0x0403 0x6014
 
# Set sampling to allow higher clock speed
# ftdi_tdo_sample_edge falling
ftdi tdo_sample_edge falling
 
 
# Layout
# On this breakout, the LEDs are on ACBUS8 and ACBUS9, can't assign them
# registers are <ACVALUE><ADVALUE> <ACCONFIG><ADCONFIG>
# so we set 0x0308 to mean only ACBUS nTRST and nSRST, ADBUS3 (TMS) asserted high
# and we set 0x000B to mean only AC3,AC2,AC0 outputs -> (TMS,TD0, TCK)
# ftdi_layout_init 0x0308 0x000b
ftdi layout_init 0x0308 0x000b
 
# Pins
# pin name      | func. |
# --------------|-------|
# ADBUS0        | TCK   |
# ADBUS1        | TDI   |
# ADBUS2        | TDO   |
# ADBUS3        | TMS   |
# ACBUS0        | nTRST |
# ACBUS1        | nSRST |
#---------------|-------|
 
# When data == oe -> pins are switched from output to input to give
# the tri state (L, H, Hi-Z) effect 
# ftdi_layout_signal nTRST -data 0x0100 -oe 0x0100
# ftdi_layout_signal nSRST -data 0x0200 -oe 0x0200
ftdi layout_signal nTRST -data 0x0100 -oe 0x0100
ftdi layout_signal nSRST -data 0x0200 -oe 0x0200



# Configure JTAG chain and the target processor
set _CHIPNAME riscv

# Configure JTAG expected ID
# arty-a7-35t
# set _EXPECTED_ID 0x0362D093 
# arty-a7-100t
# set _EXPECTED_ID 0x13631093 

# jtag newtap $_CHIPNAME cpu -irlen 6 -expected-id $_EXPECTED_ID -ignore-version
jtag newtap $_CHIPNAME cpu -irlen 5
set _TARGETNAME $_CHIPNAME.cpu
target create $_TARGETNAME riscv -chain-position $_TARGETNAME

riscv set_ir idcode 0x01
riscv set_ir dtmcs 0x10
riscv set_ir dmi 0x11

# riscv set_prefer_sba on
# gdb_report_data_abort enable
# gdb_report_register_access_error enable
# gdb_breakpoint_override hard
gdb report_data_abort enable
gdb report_register_access_error enable
gdb breakpoint_override hard

reset_config none

init
halt
