#include "sound_driver.h"

#include "Vnco.h"
#include "verilated.h"

int main(int argc, char **argv)
{
  SoundDriver snd;
  Vnco tone;

  tone.clk = 0;
  int count = 0;
  while (!Verilated::gotFinish()) {
    tone.clk = tone.clk ^ 1;
    tone.eval();
    char c = tone.out;
    printf("%d\n", c);
    snd.write(&c, 1);
  }
  return 0;
}
