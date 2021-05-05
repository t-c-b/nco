#include <unistd.h>
#include <cerrno>
#include <system_error>
#include "sound_driver.h"

SoundDriver::SoundDriver()
{
  int pipefd[2];
  pid_t cpid;

  if(pipe(pipefd) == -1) {
    throw std::system_error(errno, std::generic_category());
  }

  cpid = fork();

  if( cpid == -1 ) {
    close(pipefd[0]);
    close(pipefd[1]);
    throw std::system_error(errno, std::generic_category());
  }

  // Child Process
  else if( cpid == 0 ) {
    char * args[] = {(char *) "aplay", NULL};

    close(pipefd[1]);

    dup2(pipefd[0], STDIN_FILENO);
    if( execvp("aplay", args) == -1) {
      close(pipefd[0]);
      throw std::system_error(errno, std::generic_category());
    }
    close(pipefd[0]);
  }

  else {
    close(pipefd[0]);
    fd = pipefd[1];
  }
}

SoundDriver::~SoundDriver()
{
  close(fd);
}

//Blocking Write
void SoundDriver::write(char * buf, size_t bufsz)
{
  ssize_t written = 0;
  while(written < bufsz) {
    buf += written;
    bufsz -= written;
    written = ::write(fd, buf, bufsz);
    if(written == -1) {
      throw std::system_error(errno, std::generic_category());
    }
  }
}
