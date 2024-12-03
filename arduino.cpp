#include "arduino.h"
#include <QDebug>

QSerialPort serial;

void initializeArduino() {
    serial.setPortName("COM6"); // Change COM3 to match your Arduino's port
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    if (!serial.open(QIODevice::WriteOnly)) {
        qDebug() << "Error opening port:" << serial.errorString();
    } else {
        qDebug() << "Arduino connected successfully.";
    }
}

void sendBuzzCommand() {
    if (serial.isOpen() && serial.isWritable()) {
        serial.write("start_buzz\n"); // Send the command to Arduino
        serial.flush();
    } else {
        qDebug() << "Failed to send buzz command.";
    }
}
