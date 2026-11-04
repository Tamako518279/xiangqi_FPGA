`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/10/23 22:10:44
// Design Name: 
// Module Name: timer_top
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


module timer_top(
   input clk,
   input rst,
   input key,
   output wire [3:0] digit_en,
   output wire [7:0] seg
    );
    wire [15:0] display_data;
    wire rst_active;
    wire running;
    wire start_pause_pulse;
    wire stable_key;
    wire pulse;
    wire tick_1s;
    wire enable;
   
    wire [3:0]current_hex;
   
   
    assign rst_active = ~rst;
  
    
  
    sevenseg_scan sevenseg_scan_inst(
        .clk(clk),
        .display_data(display_data),
        .current_hex(current_hex),
        .digit_en(digit_en)
    );
    hex7seg hex7seg_inst(
        .hex(current_hex),
        .seg(seg)
    );
   
    timer_tick timer_tick_inst(
        .clk(clk),
        .rst(rst_active),
       .tick_1s(tick_1s),
       .enable(enable)
    );
    countdown countdown_inst(
        .clk(clk),
        .rst(rst_active),
        .display_data(display_data),
        .running(enable),
        .start_pause_pulse(start_pause_pulse),
        .tick_1s(tick_1s)
    );

    Debounce debounce_inst(
        .clk(clk),
        .rst(rst_active),
        .stable_key(stable_key),
        .key(key)
    );

    Edge_test edge_test_inst(
        .clk(clk),
        .rst(rst_active),
        .pulse(start_pause_pulse),
        .stable_key(stable_key)
    );
    
    /*always @(*) begin
   case (count)
        16'h0: seg = 8'b11111100;
        16'h1: seg = 8'b01100000;
        16'h2: seg = 8'b11011010;
        16'h3: seg = 8'b11110010;
        16'h4: seg = 8'b01100110;
        16'h5: seg = 8'b10110110;
        16'h6: seg = 8'b10111110;
        16'h7: seg = 8'b11100000;
        16'h8: seg = 8'b11111110;
        16'h9: seg = 8'b11110110;
        16'hA: seg = 8'b11101110;
        16'hB: seg = 8'b00111110; // 显示 b
        16'hC: seg = 8'b10011100;
        16'hD: seg = 8'b01111010; // 显示 d
        16'hE: seg = 8'b10011110;
        16'hF: seg = 8'b10001110;
        default: seg = 8'b00000000;
    endcase
end*/
    
endmodule
