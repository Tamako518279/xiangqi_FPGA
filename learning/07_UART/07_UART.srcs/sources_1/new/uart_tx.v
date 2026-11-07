`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/11/06 15:59:59
// Design Name: 
// Module Name: uart_tx
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



module uart_tx #(
    parameter CLK_FREQ  = 100_000_000,
    parameter BAUD_RATE = 115_200
)(
    input  wire       clk,
    input  wire       rst,
    input  wire       tx_start,
    input  wire [7:0] tx_data,

    output wire       uart_tx,
    output wire       tx_busy,
    output reg        tx_done
);

    // 一个 UART bit 对应多少个系统时钟周期
    localparam integer CLKS_PER_BIT = CLK_FREQ / BAUD_RATE;

    // 自动计算波特率计数器的位宽
    localparam integer CNT_WIDTH =
        (CLKS_PER_BIT > 1) ? $clog2(CLKS_PER_BIT) : 1;

    // 状态定义
    localparam S_IDLE  = 2'd0;
    localparam S_START = 2'd1;
    localparam S_DATA  = 2'd2;
    localparam S_STOP  = 2'd3;

    // 内部寄存器
    reg [1:0] state;
    reg [CNT_WIDTH-1:0] baud_cnt;
    reg [2:0] bit_index;
    reg [7:0] data_reg;

    // 输出状态
    assign tx_busy = (state != S_IDLE);

    // TX 串行输出
    assign uart_tx =
        (state == S_START) ? 1'b0 :
        (state == S_DATA)  ? data_reg[bit_index] :
                             1'b1;

    // 主时序逻辑
    always @(posedge clk or posedge rst) begin

        if (rst) begin
            state     <= S_IDLE;
            baud_cnt  <= 0;
            bit_index <= 0;
            data_reg  <= 0;
            tx_done   <= 0;
        end

        else begin

            // 默认：没有完成脉冲
            tx_done <= 1'b0;

            case (state)

                S_IDLE: begin
                    baud_cnt  <= 0;
                    bit_index <= 0;

                    if (tx_start) begin
                        data_reg <= tx_data;
                        state    <= S_START;
                    end
                end

                S_START: begin
                    if (baud_cnt == CLKS_PER_BIT - 1) begin
                        baud_cnt <= 0;
                        state    <= S_DATA;
                    end
                    else begin
                        baud_cnt <= baud_cnt + 1'b1;
                    end
                end

                S_DATA: begin
                    if (baud_cnt == CLKS_PER_BIT - 1) begin
                        baud_cnt <= 0;

                        if (bit_index == 3'd7)
                            state <= S_STOP;
                        else
                            bit_index <= bit_index + 1'b1;
                    end
                    else begin
                        baud_cnt <= baud_cnt + 1'b1;
                    end
                end

                S_STOP: begin
                    if (baud_cnt == CLKS_PER_BIT - 1) begin
                        baud_cnt <= 0;
                        state    <= S_IDLE;
                        tx_done  <= 1'b1;
                    end
                    else begin
                        baud_cnt <= baud_cnt + 1'b1;
                    end
                end

                default: begin
                    state <= S_IDLE;
                    baud_cnt <= 0;
                end

            endcase
        end
    end

endmodule
