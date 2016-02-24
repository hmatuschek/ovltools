#include <ovlnet/node.hh>
#include <ovlnet/ntp.hh>
#include <ovlnet/crypto.hh>
#include <ovlnet/logger.hh>

#include "application.hh"
#include <time.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  // init RNG
  qsrand(time(0));
  // Register log handler
  Logger::addHandler(new IOLogHandler(LogMessage::DEBUG));

  Application app(argc, argv);

  app.exec();

  return 0;
}
