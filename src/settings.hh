#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QFile>
#include <QSet>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <ovlnet/buckets.hh>


/** Implements a persistent settings object, collecting the options of several modules and
 * services and keep them in a single file. */
class Settings : public QObject
{
  Q_OBJECT

public:
  /** Loads the settings from the given file (or initializes them with the default ones). */
  explicit Settings(const QString &filename, QObject *parent = 0);

  const QStringList &plugins() const;
  const QList<PeerItem> bootstrap() const;

public slots:
  /** Save the current settings into the file give to the constructor. */
  void save();

protected:
  /** The settings file. */
  QFile _file;
  QStringList _plugins;
  QList<PeerItem> _bootstrap;
};

#endif // SETTINGS_H
