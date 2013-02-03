/**
  @file
  @author Stefan Frings
*/

#include "httprequesthandler.h"

HttpRequestHandler::HttpRequestHandler(QObject* parent)
      : QObject(parent)
      {}

HttpRequestHandler::~HttpRequestHandler() {}

void HttpRequestHandler::service(HttpRequest& request, HttpResponse& response)
      {
      response.setStatus(501, "not implemented");
      response.write("501 not implemented", true);
      }

