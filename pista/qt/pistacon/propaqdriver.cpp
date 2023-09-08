#include "propaqdriver.h"

#include <QCoreApplication>
#include <QtCore/QDebug>
#include <QtWebSockets/QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "cJSON.h"


#include <QFile>
#include <iostream>


#define HEARTBEAT_MESSAGE "{\"command\": \"heartbeat\", \"params\": {\"state\": true}}"

PropaqDriver::PropaqDriver(const char *host, const char *user, const char *password) :
    QObject(nullptr),
    m_webSocket()
{
}

PropaqDriver::PropaqDriver(const char *url) :
    QObject(nullptr),
    m_webSocket()
{
    dev_connect(QUrl(QString(url)));
}

PropaqDriver::PropaqDriver(const QUrl &url, QObject *parent) :
    QObject(parent),
    m_webSocket()
{
    dev_connect( url );
}

void PropaqDriver::test_rec( ) {
    QString val;
          QFile file;
          file.setFileName("/home/bbaker/git/pista/qt/pistacon/test.json");
          file.open(QIODevice::ReadOnly | QIODevice::Text);
          val = file.readAll();
          file.close();

          onTextMessageReceived( val );
}

void PropaqDriver::dev_connect(const QUrl &url)
{
    test_rec( );
    qDebug() << "dev_connect called";

    connect(&m_webSocket, &QWebSocket::connected, this, &PropaqDriver::onConnected);
    typedef void (QWebSocket:: *sslErrorsSignal)(const QList<QSslError> &);
    connect(&m_webSocket, static_cast<sslErrorsSignal>(&QWebSocket::sslErrors),
            this, &PropaqDriver::onSslErrors);

    m_webSocket.open(QUrl(url));

   std::cout << "dev_connect complete" << std::endl;
}

void PropaqDriver::onConnected()
{
     std::cout<< "WebSocket connected" << std::endl << std::endl << std::endl;
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &PropaqDriver::onTextMessageReceived);
    m_webSocket.sendTextMessage(QStringLiteral(HEARTBEAT_MESSAGE));
}

void dumpField( const char *field_name, cJSON *v, const char *key ) {
    if( v == NULL ) {
        return;
    }
    cJSON *text = cJSON_GetObjectItem(v, key);
    if( text == NULL ) {
        cJSON *td = cJSON_GetObjectItem(v, "TrendData");
        if( td != NULL ) {
            cJSON *val = cJSON_GetObjectItem(td, "Val");
            if( val != NULL) {
                text = cJSON_GetObjectItem(val, key);
            }
        }

        if( text == NULL ) {
            return;
        }
    }

    if( text->type & cJSON_Number ) {
        //050416 WLB std::cout << "* OBJ2: " << field_name << " val: " << text->valueint << std::endl;
    } else if( text->type & cJSON_String ) {
        //050416 WLB std::cout << "* OBJ2: " << field_name << " val: " << text->valuestring << std::endl;
    } else {
        std::cout << "* OBJ2: " << field_name << " val: !!!!!!!!! type=" << text->type << std::endl;
    }
}

void dumpTrendArray( const char *ref_name, cJSON *trend ) {
    char buf[16];
    for( int i = 0; i < cJSON_GetArraySize(trend); i++) {
            cJSON *obj = cJSON_GetArrayItem( trend, i);
            const char *field;

            if( ref_name == NULL ) {
                field = obj->string;
            } else {
                snprintf(buf, 16, "%s_%d", ref_name, i);
                field = buf;
            }
            if( obj->type & cJSON_Number ) {
                //050416 WLB std::cout << "* OBJ: " << obj->string << " val: " << obj->valueint << std::endl;
            } else if( obj->type & cJSON_String ) {
                //050416 WLB std::cout << "* OBJ: " << obj->string << " val: " << obj->valuestring << std::endl;
            } else if( obj->type & cJSON_Array ) {
                dumpTrendArray( field, obj );  // recurse
            } else if( obj->type & cJSON_Object ) {
                cJSON *td = cJSON_GetObjectItem( obj, "TrendData");
                if( td == NULL ) {
                    // recurse
                    //050416 WLB std::cout << "* no trend??: " << field << std::endl;
                    cJSON *sys = cJSON_GetObjectItem( obj, "Sys");
                    dumpField(".sys", sys, "#text");
                    cJSON *dia = cJSON_GetObjectItem( obj, "Dia");
                    dumpField(".dia", dia, "#text");
                    cJSON *map = cJSON_GetObjectItem( obj, "map");
                    dumpField(".map", map, "#text");
                } else {
                    cJSON *v = cJSON_GetObjectItem(td,"Val");
                    dumpField( field, v, "#text");
                }
            } else {
                std::cout << "*DUMP other typ: " << obj->string << " type=" << obj->type << std::endl;
            }
    }
}

enum PropaqRecordEnum { Waveform=26, Trend=33, DispColors=34 };
int seq;
void PropaqDriver::onTextMessageReceived(QString message)
{
    std::string s = message.toStdString();
    const char *my_json_string = s.c_str();
    cJSON *hdr;
    cJSON *id;
    cJSON *root = cJSON_Parse(my_json_string);
    if( root == NULL ) {
        std::cout << "INVALID ROOT" << std::endl;
        return;
    }
    cJSON *alt = cJSON_GetObjectItem(root,"AltHdr");
    if( alt != NULL ) {
        std::cout << "ALT.";
        goto done;
    }
    hdr = cJSON_GetObjectItem(root,"StdHdr");
    if( hdr == NULL ) {
        std::cout << "NO STDHDR: " << my_json_string << std::endl;
        goto done;
    }
    id = cJSON_GetObjectItem(hdr, "RecId");
    if( id == NULL ) {
        std::cout << "NO RecID: " << my_json_string << std::endl;
        goto done;
    }

    if( id->valueint == Waveform ) {
        std::cout << "W.";

        int ecg[30];

        cJSON *wfs;
        cJSON *wf_rec;
        cJSON *item;
        cJSON *wf = cJSON_GetObjectItem(root,"Waveform");
        if( wf == NULL ) {
            goto done;
        }
        wfs = cJSON_GetArrayItem( wf, 0); // "WaveRec");
        if( wfs == NULL ) {
            goto done;
        }
        wf_rec = cJSON_GetObjectItem( wfs, "WaveRec");
        if( wf_rec == NULL ) {
            goto done;
        }
        item = cJSON_GetObjectItem(wf_rec,"UnpackedSamples");
        if( item == NULL ) {
            goto done;
        }

        for (int i = 0 ; i < cJSON_GetArraySize(item) ; i++) {
            cJSON * subitem = cJSON_GetArrayItem(item, i);
            ecg[i] = subitem->valueint;
        }

        waveform(30,ecg);
    } else if( id->valueint == Trend ) {
        std::cout << "T.";

        cJSON *trend = cJSON_GetObjectItem(root,"Trend");
        if( trend == NULL ) {
            std::cout << "TREND w/o trend" << std::endl;
            goto done;
        }
        dumpTrendArray(NULL, trend);
    } else if( id->valueint == DispColors ) {
        std::cout << std::endl << "34 VALUE: " << my_json_string << std::endl;
    } else if( id->valueint == 35 ) {
        std::cout << "DISP.";
    } else {
        std::cout << (int)id->valueint << "." << std::endl;
    }

done:
    cJSON_Delete(root);
}


void PropaqDriver::onTextMessageReceivedUnused(QString message)
{
    std::cout << message.toStdString() << std::endl << std::endl;

    QJsonDocument doc = QJsonDocument::fromJson( message.toUtf8() );
    QJsonObject jobject = doc.object();


    QJsonObject stdHdr = jobject["StdHdr"].toObject();
    int id = stdHdr["RecId"].toInt();
    switch( id ) {
    case 26: {
        QJsonArray wf_arr = jobject["Waveform"].toArray();
        std::cout << "wf count: " << wf_arr.count() << std::endl;
        int ecg[30];
        for( int i = 0; i < wf_arr.count(); i++ ) {
            QJsonObject wf = wf_arr[i].toObject();
            QJsonObject waveRec = wf["WaveRec"].toObject();
            int waveType = waveRec["WaveType"].toInt();
            if( waveType != 3 ) {
                continue;
            }
            int frameSize = waveRec["FrameSize"].toInt();
            if( frameSize != 30 ) {
                std::cerr << "UNEXPECTED FRAME SIZE: " << frameSize << std::endl;
                continue;
            }
            QJsonValue unpackedSamples = waveRec["UnpackedSamples"];
            QJsonArray samples = unpackedSamples.toArray();
            for (int idx = 0; idx < samples.size(); ++idx) {
                ecg[idx] = samples[idx].toInt();
            }
            std::cout << std::endl;
        }
        this->waveform( 30, ecg );
    }
        break;
    default:
        std::cout << "unkown message type: " << id << std::endl << std::endl;
        break;
    }

    // std::cout << message.at(2).toLatin1();
    // seq++;
    // if( (seq % 60) == 0 ) {
    //        std::cout << std::endl;
    // }
}

void PropaqDriver::onSslErrors(const QList<QSslError> &errors)
{
    std::cout<< "Zoll got SSL errors" << std::endl;

    QList<QSslError>::const_iterator i = errors.begin();
    while( i != errors.end() ) {
        std::cout << "* " << (*i).errorString().toStdString() << std::endl;
        i++;
    }

    // WARNING: Never ignore SSL errors in production code.
    // The proper way to handle self-signed certificates is to add a custom root
    // to the CA store.

    m_webSocket.ignoreSslErrors();
}

void PropaqDriver::dev_tick() {
    std::cout << "SENDING TICK" << std::endl;
    m_webSocket.sendTextMessage(QStringLiteral(HEARTBEAT_MESSAGE));
}
