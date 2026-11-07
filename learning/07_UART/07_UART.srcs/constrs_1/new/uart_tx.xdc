# 100MHz clock
set_property PACKAGE_PIN P17 [get_ports clk]
set_property IOSTANDARD LVCMOS33 [get_ports clk]
create_clock -period 10.000 [get_ports clk]

# UART TX: FPGA -> PC
set_property PACKAGE_PIN T4 [get_ports uart_tx]
set_property IOSTANDARD LVCMOS33 [get_ports uart_tx]

set_property PACKAGE_PIN R15 [get_ports key]
set_property IOSTANDARD LVCMOS33 [get_ports key]
 
set_property PACKAGE_PIN P15 [get_ports rst]
set_property IOSTANDARD LVCMOS33 [get_ports rst]