#ifndef INFLUXDBACCESSOR_H
#define INFLUXDBACCESSOR_H

#include <QObject>
#include <QScopedPointer>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class InfluxDBAccessor : public QObject {
    Q_OBJECT
public:
    InfluxDBAccessor();
    void postData(QByteArray *dataByteArray);

private slots:
    void onPostAnswer(QNetworkReply *reply);
    void onError(QNetworkReply::NetworkError error);

private:
    QScopedPointer<QNetworkAccessManager> manager;
    QUrl url;
};

#endif // INFLUXDBACCESSOR_H
