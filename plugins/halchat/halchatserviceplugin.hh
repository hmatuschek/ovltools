#ifndef HALCHATSERVICEPLUGIN_HH
#define HALCHATSERVICEPLUGIN_HH

#include "plugin.hh"
#include "halchat.hh"


class HalChatService: public AbstractService
{
public:
  HalChatService(Network &node);

  SecureSocket *newSocket();
  bool allowConnection(const NodeItem &peer);
  void connectionStarted(SecureSocket *stream);
  void connectionFailed(SecureSocket *stream);

protected:
  Network &_net;
  QHalModel _model;
};


class HalChatServicePlugin: public QObject, Plugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "io.github.hmatuschek.ovlnet.HalChatServicePlugin" FILE "halchatservice.json")
  Q_INTERFACES(Plugin)

public:
  explicit HalChatServicePlugin(QObject *parent=0);
  virtual ~HalChatServicePlugin();

  void init(PluginLoader &loader);
  bool registerServices(Network &node);
  bool unregisterServices();

protected:
  QList<HalChatService *> _services;
};

#endif // HALCHATSERVICEPLUGIN_HH
