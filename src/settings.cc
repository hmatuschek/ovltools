#include "settings.hh"
#include <ovlnet/logger.hh>
#include <QJsonArray>
#include <QHostInfo>


/* ********************************************************************************************* *
 * Implementation of Settings
 * ********************************************************************************************* */
Settings::Settings(const QString &filename, QObject *parent)
  : QObject(parent), _file(filename)
{
  if (!_file.open(QIODevice::ReadOnly)) { return; }
  logDebug() << "Settings: Load settings from " << filename;
  QJsonParseError err;
  QJsonDocument doc = QJsonDocument::fromJson(_file.readAll(), &err);
  _file.close();

  if (QJsonParseError::NoError != err.error) {
    logError() << "Settings: Parser error: " << err.errorString() << ".";
    return;
  }

  if (! doc.isObject()) {
    logError() << "Settings: Malformed settings file.";
    return;
  }

  // Get plugin list
  if (doc.object().contains("plugins") && doc.object().value("plugins").isArray()) {
    QJsonArray plugins = doc.object().value("plugins").toArray();
    foreach (QJsonValue plugin, plugins) {
      QString name = plugin.toString();
      if (name.isEmpty() || name.isNull() || _plugins.contains(name))
        continue;
      _plugins.append(name);
    }
  }

  // Get boot strap nodes
  if (doc.object().contains("bootstrap") && doc.object().value("bootstrap").isArray()) {
    QJsonArray bootstrap = doc.object().value("bootstrap").toArray();
    foreach (QJsonValue peer, bootstrap) {
      if ((! peer.isObject()) || !peer.toObject().contains("host"))
        continue;
      QString host = peer.toObject().value("host").toString();
      uint16_t port = 7741;
      if (peer.toObject().contains("port"))
        port = peer.toObject().value("port").toInt(7741);
      // resolve hostname
      QHostInfo info = QHostInfo::fromName(host);
      foreach (QHostAddress addr, info.addresses()) {
        _bootstrap.append(PeerItem(addr, port));
      }
    }
  }
}

void
Settings::save() {
  if (! _file.open(QIODevice::WriteOnly)) {
    logWarning() << "Settings: Cannot save settings to " << _file.fileName()
                 << ": " << _file.errorString();
    return;
  }

  QJsonObject obj;

  QJsonArray plugins;
  foreach(QString plugin, _plugins) {
    plugins.append(plugin);
  }
  obj.insert("plugins", plugins);

  QJsonArray bootstrap;
  foreach(PeerItem peer, _bootstrap) {
    QJsonObject host;
    host.insert("addr", peer.addr().toString());
    host.insert("port", peer.port());
    bootstrap.append(host);
  }
  obj.insert("boostrap", bootstrap);

  QJsonDocument doc(obj);
  _file.write(doc.toJson());
  _file.close();
}

const QStringList &
Settings::plugins() const {
  return _plugins;
}

const QList<PeerItem>
Settings::bootstrap() const {
  return _bootstrap;
}
