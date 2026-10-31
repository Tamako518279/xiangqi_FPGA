`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/10/29 22:15:25
// Design Name: 
// Module Name: sevenseg_scan
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


module sevenseg_scan( 

  input clk,
  input wire [15:0] bcd,
  output reg [3:0] digit_en,
  output reg [3:0] current_hex
    ); 
 
  reg [1:0] scan_sel = 2'b00;
  reg [16:0] counter = 17'd0;
  always @(*) begin
    case (scan_sel)

    2'b00: begin
        current_hex = bcd[15:12];
        digit_en    = 4'b0001;
    end

    2'b01: begin
        current_hex = bcd[11:8];
        digit_en    = 4'b0010;
    end

    2'b10: begin
        current_hex = bcd[7:4];
        digit_en    = 4'b0100;
    end

    2'b11: begin
        current_hex = bcd[3:0];
        digit_en    = 4'b1000;
    end

endcase
  end

  always @(posedge clk) begin
    if (counter == 17'd99999) begin
        counter <= 0;
        scan_sel <= scan_sel + 1;
    end else begin
        counter <= counter + 1;
    end
  end

 
 
  endmodule
