#include <ovlnet/node.hh>
#include <ovlnet/ntp.hh>
#include <ovlnet/crypto.hh>
#include <ovlnet/logger.hh>
#include <ovlnet/optionparser.hh>

#include <QCoreApplication>

#include "daemon.hh"
#include <time.h>
#include <stdio.h>
#include <iostream>


int main(int argc, char *argv[])
{
  // init RNG
  qsrand(time(0));

  // Register log handler
  Logger::addHandler(new IOLogHandler(LogMessage::DEBUG));
  QCoreApplication app(argc, argv);

  OptionParser parser;
  parser.add("base-path");
  if (! parser.parse(argc, argv)) {
    std::cerr << "Usage: ovldaemon [--base-path=PATH]" << std::endl;
    return -1;
  }

  QString base_path = "/usr/share/ovlnet";
  if (parser.hasOption("base-path")) {
    base_path = parser.option("base-path");
  }

  Daemon daemon(base_path);

  app.exec();

  return 0;
}
