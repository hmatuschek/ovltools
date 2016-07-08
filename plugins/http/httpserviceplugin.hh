#ifndef __OVLNET_DAEMON_HTTP_STATUS_H__
#define __OVLNET_DAEMON_HTTP_STATUS_H__

#include <ovlnet/httpservice.hh>
#include <ovlnet/plugin.hh>

class HttpStatusHandler: public HttpRequestHandler
{
public:
  HttpStatusHandler(Node &dht);

  bool acceptReqest(HttpRequest *request);
  HttpResponse *processRequest(HttpRequest *request);

protected:
  Node &_dht;
};

class HttpServicePlugin: public QObject, Plugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "io.github.hmatuschek.ovlnet.HttpServicePlugin" FILE "httpservice.json")
  Q_INTERFACES(Plugin)

public:
  explicit HttpServicePlugin(QObject *parent=0);
  virtual ~HttpServicePlugin();

  void init(PluginLoader &loader);
  bool registerServices(Network &net);
  bool unregisterServices();


protected:
  HttpDispatcher *_dispatcher;
};

#endif // __OVLNET_DAEMON_HTTP_STATUS_H__
