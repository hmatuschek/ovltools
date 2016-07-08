#ifndef ECHOSTREAM_H
#define ECHOSTREAM_H

#include <ovlnet/crypto.hh>

class EchoStream : public SecureSocket
{
public:
  EchoStream(Network &net);

  void handleDatagram(const uint8_t *data, size_t len);
};

#endif // ECHOSTREAM_H
