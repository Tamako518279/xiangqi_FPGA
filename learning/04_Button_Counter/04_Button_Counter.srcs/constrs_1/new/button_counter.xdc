set_property PACKAGE_PIN P17 [get_ports {clk}];
set_property IOSTANDARD LVCMOS33 [get_ports {clk}];
create_clock -period 10.000 -name clk [get_ports {clk}];

set_property PACKAGE_PIN R15 [get_ports {key}];
set_property IOSTANDARD LVCMOS33 [get_ports {key}];

set_property PACKAGE_PIN K3 [get_ports {LED[0]}];
set_property IOSTANDARD LVCMOS33 [get_ports {LED[0]}];

set_property PACKAGE_PIN M1 [get_ports {LED[1]}];
set_property IOSTANDARD LVCMOS33 [get_ports {LED[1]}];

set_property PACKAGE_PIN L1 [get_ports {LED[2]}];
set_property IOSTANDARD LVCMOS33 [get_ports {LED[2]}];

set_property PACKAGE_PIN K6 [get_ports {LED[3]}];
set_property IOSTANDARD LVCMOS33 [get_ports {LED[3]}];

set_property PACKAGE_PIN P15 [get_ports {rst}];
set_property IOSTANDARD LVCMOS33 [get_ports {rst}];

