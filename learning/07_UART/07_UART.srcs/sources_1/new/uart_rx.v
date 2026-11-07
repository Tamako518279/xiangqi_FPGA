`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/11/06 23:54:01
// Design Name: 
// Module Name: uart_rx
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


module uart_rx #(
    parameter CLK_FREQ = 100_000_000, // 100 MHz
    parameter BAUD_RATE = 115200
  )(
    input wire clk,
    input wire rst,
    input wire uart_rx,

    output reg [7:0] rx_data,
    output reg rx_valid,
    output wire rx_busy

   );

        localparam integer CLKS_PER_BIT = CLK_FREQ / BAUD_RATE;
        localparam integer HALF_BIT = CLKS_PER_BIT / 2;
        localparam CNT_WIDTH = (CLKS_PER_BIT > 1) ? $clog2(CLKS_PER_BIT) : 1;

        localparam S_IDLE = 2'b00;
        localparam S_START = 2'b01;
        localparam S_DATA = 2'b10;
        localparam S_STOP = 2'b11;

        reg [1:0] state;
        reg [CNT_WIDTH-1:0] baud_cnt;
        reg [2:0] bit_index;
        reg [7:0] rx_shift;

        (* ASYNC_REG = "TRUE" *) reg rx_meta;
        (* ASYNC_REG = "TRUE" *) reg rx_sync;

        assign rx_busy = (state != S_IDLE);

        always @(posedge clk or posedge rst) begin
            if (rst) begin
                rx_meta <= 1'b1;
                rx_sync <= 1'b1;
            end else begin
                rx_meta <= uart_rx;
                rx_sync <= rx_meta;
            end
        end

        always @(posedge clk or posedge rst) begin
            if (rst) begin
                state <= S_IDLE;
                baud_cnt <= 0;
                bit_index <= 0;
                rx_shift <= 0;
                rx_data <= 0;
                rx_valid <= 0;
            end else begin
                case (state)
                    S_IDLE: begin
                        rx_valid <= 0;
                        if (rx_sync == 1'b0) begin // Start bit detected
                            state <= S_START;
                            baud_cnt <= 0;
                        end
                    end

                    S_START: begin
                        if (baud_cnt == HALF_BIT - 1) begin
                            state <= S_DATA;
                            baud_cnt <= 0;
                            bit_index <= 0;
                        end else begin
                            baud_cnt <= baud_cnt + 1;
                        end
                    end

                    S_DATA: begin
                        if (baud_cnt == CLKS_PER_BIT - 1) begin
                            baud_cnt <= 0;
                            rx_shift[bit_index] <= rx_sync; // Sample data bit
                            if (bit_index == 7) begin
                                state <= S_STOP;
                            end else begin
                                bit_index <= bit_index + 1;
                            end
                        end else begin
                            baud_cnt <= baud_cnt + 1;
                        end
                    end

                    S_STOP: begin
                        if (baud_cnt == CLKS_PER_BIT - 1) begin
                            state <= S_IDLE;
                            rx_data <= rx_shift; // Latch received data
                            rx_valid <= 1; // Indicate valid data received
                        end else begin
                            baud_cnt <= baud_cnt + 1;
                        end
                    end

                    default: state <= S_IDLE;

                endcase
            end
        end

        


endmodule
