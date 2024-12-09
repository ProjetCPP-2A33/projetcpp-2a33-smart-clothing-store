#include "Arduino.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

Arduino::Arduino()
{
    serial = new QSerialPort;
    arduino_is_available = false;

    connect(serial, &QSerialPort::readyRead, this, &Arduino::read_from_arduino);
}

int Arduino::connect_arduino()
{
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
        if (serialPortInfo.portName() == "COM3") {
            serial->setPortName(serialPortInfo.portName());
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);

            if (serial->open(QIODevice::ReadWrite)) {
                qDebug() << "Connected to Arduino on port" << serialPortInfo.portName();
                arduino_is_available = true;
                return 0; // Success
            } else {
                qDebug() << "Failed to open port:" << serial->errorString();
            }
        }
    }
    qDebug() << "COM3 not found or unavailable.";
    return -1; // Failure
}

int Arduino::close_arduino()
{
    if (serial->isOpen()) {
        serial->close();
        qDebug() << "Serial connection closed";
        arduino_is_available = false;
        return 0;
    }
    return -1;
}

QByteArray Arduino::read_from_arduino()
{
    QByteArray data;
    if (serial && serial->isOpen()) {
        if (serial->isReadable()) {
            data = serial->readAll();
            qDebug() << "Data received from Arduino:" << data;
            emit dataReceived(data); // Emit the dataReceived signal
        } else {
            qDebug() << "Serial port is not readable.";
        }
    } else {
        qDebug() << "Serial port is closed or not available.";
    }
    return data;
}

int Arduino::write_to_arduino(QByteArray data)
{ if (serial->isOpen()) {
        if (serial->isWritable()) {
            qDebug() << "Writing data to Arduino:" << data;
            serial->write(data);
            if (serial->waitForBytesWritten(100)) {
                return 0; // Success
            } else {
                qDebug() << "Write timeout occurred.";
            }
        } else {
            qDebug() << "Serial port is not writable.";
        }
    } else {
        qDebug() << "Serial port is not open. Attempting to reconnect...";
        connect_arduino(); // Attempt to reconnect
    }
    return -1; // Failure
}

void Arduino::setPortName(const QString &portName)
{
    arduino_port_name = portName;
    serial->setPortName(portName);
}

QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}
QSerialPort* Arduino::getserial() {
    return serial;
}
