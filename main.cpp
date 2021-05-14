#include "sound_driver.h"

#include "Vnco.h"
#include "verilated.h"

void configure(Vnco& tone, SoundDriver& snd, int waveform, int volume);
void step(Vnco& tone, SoundDriver& snd);

int main(int argc, char **argv)
{
  SoundDriver snd;
  Vnco tone;

  tone.clk = 0;
  int count = 0;

  while (!Verilated::gotFinish()) {
    for(int wav = 1; wav < 4; ++wav) {
      for(int vol = 0; vol < 5; ++vol) {
        configure(tone, snd, wav, vol);
        for(int i = 0; i<1000; ++i){
          step(tone, snd);
        }
      }
    }
  }
  return 0;
}

void configure(Vnco& tone, SoundDriver& snd, int waveform, int volume) {
  char c;
  tone.control = 1;
  tone.control_reset = waveform + (volume << 2);
  tone.clk = tone.clk ^ 1;
  tone.eval();
  c = tone.out;
  snd.write(&c, 1);
  tone.clk = tone.clk ^ 1;
  c = tone.out;
  snd.write(&c, 1);
  tone.eval();
  tone.control = 0;
}

void step(Vnco& tone, SoundDriver& snd) {
  tone.clk = tone.clk ^ 1;
  tone.eval();
  char c = tone.out;
  snd.write(&c, 1);
}
