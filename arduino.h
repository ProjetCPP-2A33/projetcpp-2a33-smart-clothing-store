// Arduino.h

#ifndef ARDUINO_H
#define ARDUINO_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QObject>

class Arduino : public QObject
{
    Q_OBJECT

public:

    Arduino();
    int connect_arduino();
    int close_arduino();
    int write_to_arduino(QByteArray data);
    QByteArray read_from_arduino();
    void setPortName(const QString &portName);
    QSerialPort* getserial();
    QString getarduino_port_name();

signals:
    void dataReceived(const QByteArray &data);

private:
    QSerialPort *serial;
    bool arduino_is_available;
    QString arduino_port_name;
    QByteArray data;
    static const quint16 arduino_uno_vendor_id=9025;
    static const quint16 arduino_uno_producy_id=67;



};

#endif // ARDUINO_H
