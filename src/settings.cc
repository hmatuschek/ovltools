#include "settings.hh"
#include <ovlnet/logger.hh>
#include <QJsonArray>


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
  QJsonDocument doc(obj);
  _file.write(doc.toJson());
  _file.close();
}

const QStringList &
Settings::plugins() const {
  return _plugins;
}
