#include "arduino.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

Arduino::Arduino() {
    data = "";
    arduino_port_name = "";
    arduino_is_available = false;
    serial = new QSerialPort;
}

QString Arduino::getarduino_port_name() {
    return arduino_port_name;
}

QSerialPort *Arduino::getserial() {
    return serial;
}

int Arduino::connect_arduino() {
    // Recherche du port série pour Arduino
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Port disponible: " << serial_port_info.portName();

        // Vérifier si le périphérique est un Arduino en fonction de l'ID du vendeur et du produit
        if (serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()) {
            if (serial_port_info.vendorIdentifier() == arduino_uno_vendor_id &&
                serial_port_info.productIdentifier() == arduino_uno_product_id) {

                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
                break;
            }
        }
    }

    qDebug() << "Nom du port Arduino trouvé :" << arduino_port_name;

    if (arduino_is_available) {
        qDebug() << "Tentative de connexion au port :" << arduino_port_name;
        serial->setPortName(arduino_port_name);

        // Ouverture du port série
        if (serial->open(QIODevice::ReadWrite)) {
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            qDebug() << "Connexion au port série réussie.";

            return 0;  // Connexion réussie
        } else {
            qDebug() << "Échec de l'ouverture du port série : " << serial->errorString();
            return 1;  // Échec de l'ouverture
        }
    } else {
        qDebug() << "Arduino non trouvé ou pas disponible.";
        return -1;  // Arduino non trouvé
    }
}

int Arduino::close_arduino() {
    if (serial->isOpen()) {
        serial->close();  // Fermer le port série
        qDebug() << "Port série fermé.";
        return 0;
    }
    qDebug() << "Le port série était déjà fermé.";
    return 1;  // Le port était déjà fermé
}

QByteArray Arduino::read_from_arduino() {
    if (serial->isReadable()) {
        data = serial->readAll();  // Lire les données disponibles
        qDebug() << "Données reçues : " << data;
        return data;
    } else {
        qDebug() << "Aucune donnée à lire.";
    }
    return QByteArray();
}

void Arduino::write_to_arduino(QByteArray d) {
    if (serial->isOpen()) {
        if (serial->isWritable()) {
            qDebug() << "Envoi de données à Arduino : " << d;
            serial->write(d);  // Écrire les données
            if (serial->waitForBytesWritten(1000)) {
                qDebug() << "Données envoyées avec succès.";
            } else {
                qDebug() << "Erreur lors de l'écriture : " << serial->errorString();
            }
        } else {
            qDebug() << "Le port série n'est pas en mode écriture.";
        }
    } else {
        qDebug() << "Impossible d'écrire : le port série n'est pas ouvert.";
        qDebug() << "Vérifiez que connect_arduino() a été appelé avec succès.";
    }
}
