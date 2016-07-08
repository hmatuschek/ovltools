#ifndef SOCKSSERVICEPLUGIN_HH
#define SOCKSSERVICEPLUGIN_HH

#include <QObject>
#include "plugin.hh"

class SocksServicePlugin;

class SocksService: public AbstractService
{
  Q_OBJECT

public:
  SocksService(SocksServicePlugin &plugin, Network &net);
  SecureSocket *newSocket();
  bool allowConnection(const NodeItem &peer);
  void connectionStarted(SecureSocket *stream);
  void connectionFailed(SecureSocket *stream);

protected:
  Network &_network;
  SocksServicePlugin &_plugin;
};


class SocksServicePlugin : public QObject, Plugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "io.github.hmatuschek.ovlnet.SocksServicePlugin" FILE "socksservice.json")
  Q_INTERFACES(Plugin)

public:
  explicit SocksServicePlugin(QObject *parent = 0);
  virtual ~SocksServicePlugin();

  void init(PluginLoader &loader);
  bool registerServices(Network &net);
  bool unregisterServices();

  bool isInWhitelist(const Identifier &id) const;

protected:
  void createWhitelist();

protected:
  QString _configFilename;
  QSet<Identifier> _whitelist;
};

#endif // SOCKSSERVICEPLUGIN_HH
