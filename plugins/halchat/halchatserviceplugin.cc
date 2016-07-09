#include "halchatserviceplugin.hh"

/* ********************************************************************************************* *
 * Implementation of HalChatService
 * ********************************************************************************************* */
HalChatService::HalChatService(Network &node)
  : AbstractService(), _net(node), _model()
{
  // pass...
}

SecureSocket *
HalChatService::newSocket() {
  return new HalChat(_net, _model);
}

bool
HalChatService::allowConnection(const NodeItem &peer) {
  logDebug() << "ChatService: Allow connection from " << peer.id()
             << " @" << peer.addr() << ".";
  return true;
}

void
HalChatService::connectionStarted(SecureSocket *stream) {
  logDebug() << "ChatService: Connection from " << stream->peerId() << " started.";
  static_cast<HalChat *>(stream)->started();
}

void
HalChatService::connectionFailed(SecureSocket *stream) {
  logDebug() << "ChatService: Connection from " << stream->peerId() << " failed.";
  delete stream;
}


/* ********************************************************************************************* *
 * Implementation of HalChatServicePlugin
 * ********************************************************************************************* */
HalChatServicePlugin::HalChatServicePlugin(QObject *parent)
  : QObject(parent), Plugin()
{
  // pass...
}

HalChatServicePlugin::~HalChatServicePlugin() {
  // pass...
}

void
HalChatServicePlugin::init(PluginLoader &loader) {
  // pass...
}

bool
HalChatServicePlugin::registerServices(Network &node) {
  HalChatService *service = new HalChatService(node);
  node.registerService("simplechat", service);
  _services.append(service);
  return true;
}

bool
HalChatServicePlugin::unregisterServices() {
  return true;
}

