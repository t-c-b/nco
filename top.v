`include "nco.v"

module top (input clk, output [3:0] snd);
reg clk8kHz;
reg [11:0] div;

always @ (posedge clk) 
begin
  div <= div + 1;
  if (div == 1500)
  begin
    div <= 0;
    clk8kHz <= !clk8kHz;
  end
end

nco osc (
  .clk (clk8kHz),
  .reset (0),
  .m_reset (0),
  .out(snd)
);
endmodule
