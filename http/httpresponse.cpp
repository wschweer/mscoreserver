/**
  @file
  @author Stefan Frings
*/

#include "httpresponse.h"

HttpResponse::HttpResponse(QTcpSocket* socket) {
      this->socket = socket;
      statusCode = 200;
      statusText = "OK";
      sentHeaders = false;
      sentLastPart = false;
      }

void HttpResponse::setHeader(QByteArray name, QByteArray value) {
      Q_ASSERT(sentHeaders == false);
      headers.insert(name, value);
      }

void HttpResponse::setHeader(QByteArray name, int value) {
      Q_ASSERT(sentHeaders == false);
      headers.insert(name, QByteArray::number(value));
      }

QMap<QByteArray, QByteArray>& HttpResponse::getHeaders() {
      return headers;
      }

void HttpResponse::setStatus(int statusCode, QByteArray description) {
      this->statusCode = statusCode;
      statusText = description;
      }

void HttpResponse::writeHeaders() {
      Q_ASSERT(sentHeaders == false);
      QByteArray buffer;
      buffer.append("HTTP/1.1 ");
      buffer.append(QByteArray::number(statusCode));
      buffer.append(' ');
      buffer.append(statusText);
      buffer.append("\r\n");
      foreach(QByteArray name, headers.keys()) {
            buffer.append(name);
            buffer.append(": ");
            buffer.append(headers.value(name));
            buffer.append("\r\n");
            }
      foreach(HttpCookie cookie, cookies.values()) {
            buffer.append("Set-Cookie: ");
            buffer.append(cookie.toByteArray());
            buffer.append("\r\n");
            }
      buffer.append("\r\n");
      writeToSocket(buffer);
      sentHeaders = true;
      }

//---------------------------------------------------------
//   writeToSocket
//---------------------------------------------------------

bool HttpResponse::writeToSocket(QByteArray data) {
      qint64 remaining = data.size();
      const char* ptr  = data.data();
      while (socket->state() == QAbstractSocket::ConnectedState && remaining > 0) {
            qint64 written = socket->write(ptr, remaining);
            if (written <= 0) {
                  printf("HttpResponse::writeToSocket: failed\n");
                  return false;
                  }

            socket->waitForBytesWritten(2000);
            ptr        += written;
            remaining  -= written;
            }
      if (!socket->state() == QAbstractSocket::ConnectedState)
            printf("HttpResponse::writeToSocket: socket disconnected\n");
      return socket->isOpen();
      }

//---------------------------------------------------------
//   write
//---------------------------------------------------------

bool HttpResponse::write(QByteArray data, bool lastPart) {
      Q_ASSERT(sentLastPart == false);
      if (sentHeaders == false) {
            QByteArray connectionMode = headers.value("Connection");
            if (!headers.contains("Content-Length") && !headers.contains("Transfer-Encoding") && connectionMode != "close" && connectionMode != "Close") {
                  if (!lastPart) {
                        headers.insert("Transfer-Encoding", "chunked");
                        }
                  else {
                        headers.insert("Content-Length", QByteArray::number(data.size()));
                        }
                  }
            writeHeaders();
            }
      bool chunked = headers.value("Transfer-Encoding") == "chunked" || headers.value("Transfer-Encoding") == "Chunked";
      if (chunked) {
            if (data.size() > 0) {
                  QByteArray buffer = QByteArray::number(data.size(), 16);
                  buffer.append("\r\n");
                  if (!writeToSocket(buffer))
                        return false;
                  if (!writeToSocket(data))
                        return false;
                  if (!writeToSocket("\r\n"))
                        return false;
                  }
            }
      else {
            if (!writeToSocket(data))
                  return false;
            }
      if (lastPart) {
            if (chunked) {
                  if (!writeToSocket("0\r\n\r\n"))
                        return false;
                  }
            else if (!headers.contains("Content-Length")) {
                  socket->disconnectFromHost();
                  }
            sentLastPart = true;
            }
      return true;
      }

bool HttpResponse::hasSentLastPart() const {
      return sentLastPart;
      }


void HttpResponse::setCookie(const HttpCookie& cookie) {
      Q_ASSERT(sentHeaders == false);
      if (!cookie.getName().isEmpty()) {
            cookies.insert(cookie.getName(), cookie);
            }
      }

QMap<QByteArray, HttpCookie>& HttpResponse::getCookies() {
      return cookies;
      }
