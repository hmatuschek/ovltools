#include "echocallserviceplugin.hh"

/* ********************************************************************************************* *
 * Implementation of EchoCall
 * ********************************************************************************************* */
EchoCall::EchoCall(Network &net)
  : SecureSocket(net)
{
  // pass...
}

void
EchoCall::handleDatagram(const uint8_t *data, size_t len) {
  this->sendDatagram(data, len);
}


/* ********************************************************************************************* *
 * Implementation of EchoCallService
 * ********************************************************************************************* */
EchoCallService::EchoCallService(Network &node)
  : AbstractService(), _net(node)
{
  // pass...
}

SecureSocket *
EchoCallService::newSocket() {
  return new EchoCall(_net);
}

bool
EchoCallService::allowConnection(const NodeItem &peer) {
  logDebug() << "EchoCallService: Allow connection from " << peer.id()
             << " @" << peer.addr() << ".";
  return true;
}

void
EchoCallService::connectionStarted(SecureSocket *stream) {
  logDebug() << "EchoCallService: Connection from " << stream->peerId() << " started.";
  // pass...
}

void
EchoCallService::connectionFailed(SecureSocket *stream) {
  logDebug() << "EchoCallService: Connection from " << stream->peerId() << " failed.";
  delete stream;
}


/* ********************************************************************************************* *
 * Implementation of EchoCallServicePlugin
 * ********************************************************************************************* */
EchoCallServicePlugin::EchoCallServicePlugin(QObject *parent)
  : QObject(parent), Plugin()
{
  // pass...
}

EchoCallServicePlugin::~EchoCallServicePlugin() {
  // pass...
}

void
EchoCallServicePlugin::init(PluginLoader &loader) {
  // pass...
}

bool
EchoCallServicePlugin::registerServices(Network &node) {
  EchoCallService *service = new EchoCallService(node);
  node.registerService("call", service);
  _services.append(service);
  return true;
}

bool
EchoCallServicePlugin::unregisterServices() {
  return true;
}

