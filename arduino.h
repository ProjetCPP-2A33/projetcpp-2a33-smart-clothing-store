// Arduino.h
#ifndef ARDUINO_H
#define ARDUINO_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

const quint16 arduino_uno_vendor_id = 0x2341; // ID du vendeur de l'Arduino Uno
const quint16 arduino_uno_product_id = 0x0043; // ID du produit de l'Arduino Uno

class Arduino
{
public:
    Arduino();
    int connect_arduino(); // permet de connecter le PC à Arduino
    int close_arduino(); // permet de fermer la connexion
    void write_to_arduino(QByteArray); // envoyer des données vers arduino
    QByteArray read_from_arduino();  // recevoir des données de la carte Arduino
    QSerialPort* getserial();   // accesseur
    QString getarduino_port_name();
    void write(const QByteArray &data) {
        serial->write(data);
    }

    QByteArray readAll() {
        return serial->readAll();
    }

    bool bytesAvailable() const {
        return serial->bytesAvailable() > 0;
    }

private:
    QSerialPort * serial; // Cet objet rassemble des informations (vitesse, bits de données, etc.)
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_product_id = 67;
    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray data;  // contenant les données lues à partir d'Arduino

signals:
    void errorOccurred(const QString &error);  // Déclaration du signal errorOccurred
};

#endif // ARDUINO_H
