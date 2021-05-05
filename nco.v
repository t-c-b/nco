module nco(input clk, input reset, input [7:0] m_reset,  output [3:0] out);
  reg [7:0] phi_acc;
  reg [7:0] m = 19;
  
  always @ (posedge clk)
  begin
    if (reset ==  1)
    begin
      m <= m_reset;
    end
    phi_acc <= phi_acc + m;
  end

  //assign out = phi_acc[7:4]; // saw
  //assign out = {phi_acc[7], 3'b000}; // square
  assign out = (phi_acc[7] == 1) ? phi_acc[6:3] : 15 - phi_acc[6:3]; // tri
  // tri

endmodule
