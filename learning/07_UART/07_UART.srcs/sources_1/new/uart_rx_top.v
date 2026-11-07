`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/11/06 23:56:46
// Design Name: 
// Module Name: uart_rx_top
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module uart_rx_top(
  input wire clk,
  input wire rst,
  input wire uart_rx,

  output wire [7:0] seg,
  output wire [3:0] digit_en
    );

   wire [7:0] rx_data;
   wire rx_valid;
   wire rx_busy;
   wire [3:0] current_hex;
   wire rst_active = ~rst;
   
   wire [15:0] display_data = {8'b0, rx_data};

    uart_rx uart_rx_inst(
      .clk(clk),
      .rst(rst_active),
      .uart_rx(uart_rx),
      .rx_data(rx_data),
      .rx_valid(rx_valid),
      .rx_busy(rx_busy)
    );

    hex7seg hex7seg_inst(
      .hex(current_hex),
      .seg(seg)
    );

    sevenseg_scan sevenseg_scan_inst(
      .clk(clk),
      .display_data(display_data),
      .digit_en(digit_en),
      .current_hex(current_hex)
    );
endmodule
