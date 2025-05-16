###########################################################################
# Icarus Simulator Makefile
#
# iverilog is the compiler
# vvp is the simulation runtime engine
###########################################################################
FILELIST=filelist.mk
VERILOG_STANDARD=2012
OUT_FILE=wb.icarus_sim
UVM_PATH=/home/winston/Projects/tool-repos/UVM-1800.2-2020.3.1/1800.2-2020.3.1

# Specify Include dir
# ARGS += -I$(UVM_PATH)/src

# Add the specified file to the list of source files
# ARGS += -l $(UVM_PATH)/src/uvm_macros.svh

# ARGS += -v $(UVM_PATH)/src/uvm_pkg.sv
# ARGS += -L$(UVM_PATH)/src/dpi

# Specify top level
ARGS += -s tb_wbxbar_wrapper

ARGS += -DUVM_HDL_NO_DPI=1
ARGS += -DUVM_CMDLINE_NO_DPI=1
ARGS += -Wall

icarus:
	iverilog -v -g$(VERILOG_STANDARD) $(ARGS)  -c $(FILELIST) -o $(OUT_FILE) -v

icarus_sim: icarus
	vvp $(OUT_FILE) -fst

clean_icarus:
	@rm -f $(OUT_FILE) || echo -c
