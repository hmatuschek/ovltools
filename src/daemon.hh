#ifndef DAEMON_H
#define DAEMON_H

#include <ovlnet/crypto.hh>
#include <ovlnet/node.hh>
#include <ovlnet/plugin.hh>
#include "settings.hh"


class Daemon : public QObject
{
  Q_OBJECT

public:
  explicit Daemon(const QString &base_path, QObject *parent=0);

  Node &dht();

protected:
  Node *_dht;
  PluginLoader *_plugins;
  Settings _settings;
};

#endif // APPLICATION_H
