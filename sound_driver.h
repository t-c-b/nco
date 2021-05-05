#ifndef SOUND_DRIVER_APLAY_H
#define SOUND_DRIVER_APLAY_H

#include <cstddef>

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
