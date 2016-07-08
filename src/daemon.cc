#include "daemon.hh"
#include "echostream.hh"

#include <QDir>
#include <QFile>

Daemon::Daemon(const QString &base_path, QObject *parent)
  : QObject(parent), _settings(base_path+"/ovldaemon.conf.json")
{
  logDebug() << "Start daemon from " << base_path << ".";
  // Try to load identity from file
  QDir ovlDir(base_path);
  // if deamon directory does not exists -> create it
  if (! ovlDir.exists()) {
    ovlDir.mkpath(ovlDir.absolutePath());
  }

  _dht = new Node(ovlDir.canonicalPath()+"/identity.pem");

  // PluginLoader
  _plugins = new PluginLoader(*_dht, base_path+"/plugins/", this);

  // load all plugins specified in settings
  foreach (QString name, _settings.plugins()) {
    if (! _plugins->isAvailable(name)) {
      logError() << "Cannot load plugin '" << name << "': Plugin not available.";
      continue;
    }
    if (! _plugins->load(name)) {
      logError() << "Cannot load plugin '" << name << "': Failed loading plugin.";
      continue;
    }
    logDebug() << "Loaded plugin '" << name << "...";
  }

}

Node &
Daemon::dht() {
  return *_dht;
}




