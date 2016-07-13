#ifndef ECHOCALLSERVICEPLUGIN_HH
#define ECHOCALLSERVICEPLUGIN_HH

#include <ovlnet/plugin.hh>


class EchoCall: public SecureSocket
{
public:
  EchoCall(Network &net);

  void handleDatagram(const uint8_t *data, size_t len);
};


class EchoCallService: public AbstractService
{
public:
  EchoCallService(Network &node);

  SecureSocket *newSocket();
  bool allowConnection(const NodeItem &peer);
  void connectionStarted(SecureSocket *stream);
  void connectionFailed(SecureSocket *stream);

protected:
  Network &_net;
};


class EchoCallServicePlugin: public QObject, Plugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "io.github.hmatuschek.ovlnet.EchoCallServicePlugin" FILE "echocallservice.json")
  Q_INTERFACES(Plugin)

public:
  explicit EchoCallServicePlugin(QObject *parent=0);
  virtual ~EchoCallServicePlugin();

  void init(PluginLoader &loader);
  bool registerServices(Network &node);
  bool unregisterServices();

protected:
  QList<EchoCallService *> _services;
};

#endif // ECHOCALLSERVICEPLUGIN_HH
