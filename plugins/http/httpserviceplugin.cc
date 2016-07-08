#include "httpserviceplugin.hh"
#include <ovlnet/node.hh>


/* ********************************************************************************************* *
 * Implementation of HttpStatus
 * ********************************************************************************************* */
HttpStatusHandler::HttpStatusHandler(Node &dht)
  : HttpRequestHandler(), _dht(dht)
{
  // pass...
}

bool
HttpStatusHandler::acceptReqest(HttpRequest *request) {
  if ("/status" == request->uri().path()) {
    logDebug() << "Accept request for " << request->uri().path();
    return true;
  }
  logDebug() << "Deny request for " << request->uri().path();
  return false;
}

HttpResponse *
HttpStatusHandler::processRequest(HttpRequest *request) {
  QString resp =
      "<html> <body> <h1> Status of Node </h1>"
      "<h3> Id: %1</h3>"
      "<table>"
      " <tr><td>Active streams</td> <td>%2</td></tr>"
      " <tr><td>Bytes received</td> <td>%3</td></tr>"
      " <tr><td>Bytes send</td> <td>%4</td></tr>"
      "</table>"
      "</body></html>";
  return new HttpStringResponse(request->version(), HTTP_OK, resp
                                .arg(_dht.id().toBase32())
                                .arg(_dht.numSockets())
                                .arg(_dht.bytesReceived())
                                .arg(_dht.bytesSend()),
                                request->socket(), "text/html");
}


/* ********************************************************************************************* *
 * Implementation of HttpServicePlugin
 * ********************************************************************************************* */
HttpServicePlugin::HttpServicePlugin(QObject *parent)
  : QObject(parent), Plugin(), _dispatcher(0)
{
  // pass...
}

HttpServicePlugin::~HttpServicePlugin() {
  // pass...
}

void
HttpServicePlugin::init(PluginLoader &loader) {
  // pass...
}

bool
HttpServicePlugin::registerServices(Network &net) {
  _dispatcher = new HttpDispatcher();
  HttpService *service = new HttpService(net, _dispatcher);
  _dispatcher->addHandler(new HttpStatusHandler(net.root()));
  net.registerService("http", service);
  return true;
}

bool
HttpServicePlugin::unregisterServices() {
  return true;
}


