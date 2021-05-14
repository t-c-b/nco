#ifndef SOUND_DRIVER_APLAY_H
#define SOUND_DRIVER_APLAY_H

#include <cstddef>

//8 kHz audio driver
class SoundDriver
{
public:
  SoundDriver();
  ~SoundDriver();
  SoundDriver(const SoundDriver&) =delete;
  SoundDriver& operator=(const SoundDriver&) =delete;

  void write(char * buf, size_t bufsz);
private:
  int fd;
};

#endif
