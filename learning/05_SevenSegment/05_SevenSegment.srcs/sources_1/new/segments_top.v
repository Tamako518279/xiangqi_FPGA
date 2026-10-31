`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/10/23 22:10:44
// Design Name: 
// Module Name: seven_segments
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


module segments_top(
   input clk,
   input rst,
   input key,
   output wire [3:0] digit_en,
   output wire [7:0] seg
    );
    wire [15:0] bin;
    wire stable_key;
    wire pulse;
    wire rst_active;
    wire [15:0] bcd;
    wire [3:0]current_hex;
    reg [15:0] count = 16'b0000000000000000;
   
    assign rst_active = ~rst;
    assign bin = count;
    
    always @(posedge clk or posedge rst_active) begin
        if (rst_active) begin
            count <= 16'b0000000000000000;
        end else if (pulse) begin
            if(count == 16'd9999) begin
                count <= 16'b0000000000000000;
            end else begin
                count <= count + 1;
            end
            
    end
    end
   
   Debounce key_debounce_inst(
        .clk(clk),
        .rst(rst_active),
        .key(key),
        .stable_key(stable_key)
    );
   
   Edge_test edge_test_inst(
        .clk(clk),
        .rst(rst_active),
        .stable_key(stable_key),
        .pulse(pulse)
    );
    
    sevenseg_scan sevenseg_scan_inst(
        .clk(clk),
        .bcd(bcd),
        .current_hex(current_hex),
        .digit_en(digit_en)
    );
    hex7seg hex7seg_inst(
        .hex(current_hex),
        .seg(seg)
    );
    bin_to_bcd bin_to_bcd_inst(
        .bin(bin),
        .bcd(bcd)
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
