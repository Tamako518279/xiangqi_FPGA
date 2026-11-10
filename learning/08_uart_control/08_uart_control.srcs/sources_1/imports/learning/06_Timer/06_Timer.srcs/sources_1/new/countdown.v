`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/11/02 23:41:19
// Design Name: 
// Module Name: countdown
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


module countdown(
  input tick_1s,
  input clk,
  input rst,
  input start_pause_pulse,
  input wire load_inital,

  output  running,
  output [15:0] display_data,
  output [1:0] status_data
    );

localparam IDLE     = 2'b00;
localparam RUNNING  = 2'b01;
localparam PAUSED   = 2'b10;
localparam FINISHED = 2'b11;

   reg [1:0] state;
   reg [1:0] next_state;
   
reg [3:0] minute_tens = 4'd0;
reg [3:0] minute_ones = 4'd1;
reg [3:0] second_tens = 4'd0;
reg [3:0] second_ones = 4'd0;
   
   assign display_data = {minute_tens, minute_ones, second_tens, second_ones};
   assign running = (state == RUNNING);
   assign status_data = state;
   
  always @(*) begin
    next_state = state;

   
    
    case(state)

        IDLE: begin
            if(start_pause_pulse)
                next_state = RUNNING;
        end

        RUNNING: begin
            if(start_pause_pulse)
                next_state = PAUSED;
            else if(display_data == 16'h0000)
                next_state = FINISHED;
            else if(tick_1s && display_data == 16'h0001)
                next_state = FINISHED;
        end

        PAUSED: begin
            if(start_pause_pulse)
                next_state = RUNNING;
        end

        FINISHED: begin
            next_state = FINISHED;
        end

        default: begin
            next_state = IDLE;
        end

    endcase
end

  always @(posedge clk or posedge rst) begin
    if(rst) begin
        state <= IDLE;
        minute_tens <= 4'd0;
        minute_ones <= 4'd1;
        second_tens <= 4'd0;
        second_ones <= 4'd0;
    end else if(load_inital) begin
        state <= IDLE;
        minute_tens <= 4'd0;
        minute_ones <= 4'd1;
        second_tens <= 4'd0;
        second_ones <= 4'd0;
     end else begin
        state <= next_state;
        if (state == RUNNING && tick_1s &&
            !start_pause_pulse && display_data != 16'h0000) begin
           if(second_ones > 0) begin
    second_ones <= second_ones - 1'b1;
end

    else begin
       second_ones <= 4'd9;

    if(second_tens > 0) begin
        second_tens <= second_tens - 1'b1;
    end

    else begin
        second_tens <= 4'd5;

        if(minute_ones > 0) begin
            minute_ones <= minute_ones - 1'b1;
        end

        else begin
            minute_ones <= 4'd9;

            if(minute_tens > 0) begin
                minute_tens <= minute_tens - 1'b1;
            end

        end
    end
end
        end
    end
end

 
endmodule
