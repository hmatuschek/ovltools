#ifndef HALCHAT_H
#define HALCHAT_H

#include <ovlnet/node.hh>
#include <ovlnet/crypto.hh>
#include "qhal.hh"

#include <QObject>
#include <QTimer>


class HalChat : public QObject, public SecureSocket
{
  Q_OBJECT

public:
  explicit HalChat(Network &net, QHalModel &model,QObject *parent = 0);

  void started();

protected:
  void handleDatagram(const uint8_t *data, size_t len);

protected slots:
  void _onKeepAlive();
  void _onTimeout();

protected:
  QHalModel &_model;
  QTimer     _keepAlive;
  QTimer     _timeout;
};

#endif // HALCHAT_H
