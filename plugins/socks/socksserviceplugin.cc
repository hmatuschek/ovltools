#include "socksserviceplugin.hh"
#include "socks.hh"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


/* ********************************************************************************************* *
 * Implementation of SocksServicePlugin
 * ********************************************************************************************* */
SocksServicePlugin::SocksServicePlugin(QObject *parent)
  : QObject(parent), Plugin()
{
  // pass...
}

SocksServicePlugin::~SocksServicePlugin() {
  // pass...
}

void
SocksServicePlugin::init(PluginLoader &loader) {
  _configFilename = loader.baseDirectory() +"/socksservice.conf.json";
  QFile file(_configFilename);
  if (! file.open(QIODevice::ReadOnly)) {
    logInfo() << "Cannot open SocksService settings from "
              << file.fileName() << ": " << file.errorString() << ".";
    createWhitelist();
    return;
  }

  logDebug() << "SocksServiceSettings: Load settings from " << file.fileName();
  QJsonParseError err;
  QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &err);
  file.close();

  if (QJsonParseError::NoError != err.error) {
    logError() << "SocksServiceSettings: Parser error: " << err.errorString() << ".";
    return;
  }

  if (! doc.isObject()) {
    logError() << "SocksServiceSettings: Malformed settings file.";
    return;
  }

  if ((!doc.object().contains("whitelist")) || (!doc.object().value("whitelist").isArray()))  {
    logInfo() << "SocksServiceSettings: Does not contain a whitelist.";
    return;
  }

  QJsonArray whitelist = doc.object().value("whitelist").toArray();
  foreach (QJsonValue id, whitelist) {
    Identifier ident = Identifier::fromBase32(id.toString());
    if (ident.isValid())
      _whitelist.insert(ident);
  }
  logDebug() << "SocksService: Loaded white-list with " << _whitelist.size() << " entries.";
}

bool
SocksServicePlugin::registerServices(Network &net) {
  net.registerService("socks5", new SocksService(*this, net));
  return true;
}

bool
SocksServicePlugin::unregisterServices() {
  return true;
}

bool
SocksServicePlugin::isInWhitelist(const Identifier &id) const {
  return _whitelist.contains(id);
}

void
SocksServicePlugin::createWhitelist() {
  QJsonObject conf;
  conf.insert("whitelist", QJsonArray());
  QJsonDocument doc(conf);
  QFile cfile(_configFilename);
  if (! cfile.open(QIODevice::WriteOnly)) {
    return;
  }
  cfile.write(doc.toJson());
  cfile.close();
}


/* ********************************************************************************************* *
 * Implementation of SocksService
 * ********************************************************************************************* */
SocksService::SocksService(SocksServicePlugin &plugin, Network &net)
  : AbstractService(), _network(net), _plugin(plugin)
{
  // pass...
}

SecureSocket *
SocksService::newSocket() {
  return new SocksOutStream(_network);
}

bool
SocksService::allowConnection(const NodeItem &peer) {
  if (_plugin.isInWhitelist(peer.id())) {
    logDebug() << "SocksService: Allow SOCKS connection from " << peer.id() << ".";
  } else {
    logDebug() << "SocksService: Deny SOCKS connection from " << peer.id() << ".";
  }
  return _plugin.isInWhitelist(peer.id());
}

void
SocksService::connectionStarted(SecureSocket *stream) {
  logDebug() << "SocksService: SOCKS connection to " << stream->peerId() << " started.";
  dynamic_cast<SocksOutStream *>(stream)->open(QIODevice::ReadWrite);
}

void
SocksService::connectionFailed(SecureSocket *stream) {
  logDebug() << "SocksService: SOCKS connection to " << stream->peerId() << " failed.";
  delete stream;
}
