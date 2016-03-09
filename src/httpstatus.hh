#ifndef __OVLNET_DAEMON_HTTP_STATUS_H__
#define __OVLNET_DAEMON_HTTP_STATUS_H__
#include <ovlnet/httpservice.hh>

class HttpStatus: public HttpRequestHandler
{
public:
  HttpStatus(Node &dht);

  bool acceptReqest(HttpRequest *request);
  HttpResponse *processRequest(HttpRequest *request);

protected:
  Node &_dht;
};

#endif // __OVLNET_DAEMON_HTTP_STATUS_H__
