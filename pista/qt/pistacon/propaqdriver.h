#ifndef ZOLLDRIVER_H
#define ZOLLDRIVER_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QtNetwork/QSslError>
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QUrl>

class PropaqDriver: public QObject
{
    Q_OBJECT


public:
    explicit PropaqDriver(const char *host, const char *user, const char *password);
    explicit PropaqDriver(const char *uri);
    explicit PropaqDriver(const QUrl &url, QObject *parent = Q_NULLPTR);

    void dev_connect(const QUrl &url);
    void dev_tick();

    void test_rec();

Q_SIGNALS:
    void waveform( int sz, int *ecg );
    // boost style signal
    // signal<void (int, int *ecg)> waveform;

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);
    void onTextMessageReceivedUnused(QString message);
    void onSslErrors(const QList<QSslError> &errors);

private:
    QWebSocket m_webSocket;

};

#endif // ZOLLDRIVER_H
