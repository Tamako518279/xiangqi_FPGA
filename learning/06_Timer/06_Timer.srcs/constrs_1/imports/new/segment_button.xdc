 set_property PACKAGE_PIN P17 [get_ports {clk}];
set_property IOSTANDARD LVCMOS33 [get_ports {clk}];
create_clock -period 10.000 -name clk [get_ports {clk}];

set_property PACKAGE_PIN R15 [get_ports {key}];
set_property IOSTANDARD LVCMOS33 [get_ports {key}];

set_property PACKAGE_PIN P15 [get_ports {rst}];
set_property IOSTANDARD LVCMOS33 [get_ports {rst}];

set_property PACKAGE_PIN B4 [get_ports {seg[7]}]
set_property IOSTANDARD LVCMOS33 [get_ports {seg[7]}]

set_property PACKAGE_PIN A4 [get_ports {seg[6]}]
set_property IOSTANDARD LVCMOS33 [get_ports {seg[6]}]

set_property PACKAGE_PIN A3 [get_ports {seg[5]}]
set_property IOSTANDARD LVCMOS33 [get_ports {seg[5]}]

set_property PACKAGE_PIN B1 [get_ports {seg[4]}]
set_property IOSTANDARD LVCMOS33 [get_ports {seg[4]}]

set_property PACKAGE_PIN A1 [get_ports {seg[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {seg[3]}]

set_property PACKAGE_PIN B3 [get_ports {seg[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {seg[2]}]

set_property PACKAGE_PIN B2 [get_ports {seg[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {seg[1]}]

set_property PACKAGE_PIN D5 [get_ports {seg[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {seg[0]}]

set_property PACKAGE_PIN G2 [get_ports {digit_en[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {digit_en[0]}]

set_property PACKAGE_PIN C2 [get_ports {digit_en[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {digit_en[1]}]

set_property PACKAGE_PIN C1 [get_ports {digit_en[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {digit_en[2]}]

set_property PACKAGE_PIN H1 [get_ports {digit_en[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {digit_en[3]}]
