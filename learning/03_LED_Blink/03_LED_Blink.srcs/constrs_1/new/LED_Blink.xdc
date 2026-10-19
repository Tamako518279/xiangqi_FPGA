set_property PACKAGE_PIN P17 [get_ports {clk}]
set_property IOSTANDARD LVCMOS33 [get_ports {clk}]

set_property PACKAGE_PIN K3 [get_ports {LED_State}]
set_property IOSTANDARD LVCMOS33 [get_ports {LED_State}]

create_clock -name clk -period 10.000 [get_ports {clk}]