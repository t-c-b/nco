module nco(
  input clk, 
  input reset, input [7:0] m_reset, 
  input control, input [7:0] control_reset,
  output [3:0] out
);
  reg [7:0] phi_acc;
  reg [7:0] m = 19;
  reg [1:0] wave_sel;// = 3;
  reg [3:0] volume;// = 0;

  wire [3:0] waveforms[3:0];
  assign waveforms[0] = 4'h0;
  assign waveforms[1] = {phi_acc[7], 3'b000}; // square
  assign waveforms[2] = (phi_acc[7] == 1) ? phi_acc[6:3] : 15 - phi_acc[6:3]; // tri
  assign waveforms[3] = phi_acc[7:4]; // saw
  
  always @ (posedge clk)
  begin
    if (reset ==  1)
    begin
      m <= m_reset;
    end
    if (control == 1)
    begin
      wave_sel <= control_reset[1:0];
      volume <= control_reset[5:2];
    end
    phi_acc <= phi_acc + m;
  end

  assign out = waveforms[wave_sel] >> volume;
endmodule
