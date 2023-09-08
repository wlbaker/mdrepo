#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>

#include "InfluxDBAccessor.h"

// Resource Acquisition is Initialization (RAII)
InfluxDBAccessor::InfluxDBAccessor()
{
    manager.reset(new QNetworkAccessManager);
    connect(manager.data(), SIGNAL(finished(QNetworkReply*)), this, SLOT(onPostAnswer(QNetworkReply*)));
    // In the future we should probably receive the user and password by parameter here in the constructor
    url = QUrl("http://gigawatt-futureboy-1.c.influxdb.com:8086/db/intellivuestreaming/series?u=root&p=814b7c96483ad107");
}

void InfluxDBAccessor::onPostAnswer(QNetworkReply *reply)
{
    QByteArray bytes = reply->readAll();
    QString str = QString::fromUtf8(bytes.data(), bytes.size());
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    qDebug() << QVariant(statusCode).toString();
}

void InfluxDBAccessor::onError(QNetworkReply::NetworkError error)
{
    qDebug() << error;
}

void InfluxDBAccessor::postData(QByteArray *dataByteArray) {

    QNetworkRequest request(this->url);
    request.setRawHeader("User-Agent", "ApplicationNameV01");
    request.setRawHeader("Content-Type", "application/json");

    QByteArray postDataSize = QByteArray::number(dataByteArray->size());
    qDebug() << "Data size Enviando a InfluxDB:" << dataByteArray->size();
    request.setRawHeader("Content-Length", postDataSize);

    QNetworkReply *reply = manager->post(request, *dataByteArray);
    // This is a SIGNAL->SLOT Qt connection; this connect does not have anything to do with TCP connection.
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
}

