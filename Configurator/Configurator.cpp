#include "Configurator.h"

#include <QFile>
#include <QMap>
#include <QPair>
#include <QString>
#include <QTextStream>

//  :: Constants ::

const QString CONFIG_FILE_NAME = "config.ini";

const QString HOST_NAME_KEY = "HOST_NAME";
const QString PORT_KEY = "PORT";

const QString DEFAULT_HOST_NAME = "localhost";

#ifdef QT_DEBUG
const QString DEFAULT_PORT = "51971";
#else
const QString DEFAULT_PORT = "5000";
#endif

//  :: Static fields ::

QMap<QString, QString> Configurator::m_configurations {
    {HOST_NAME_KEY, DEFAULT_HOST_NAME},
    {PORT_KEY, DEFAULT_PORT}
};

//  :: Public methods ::

void Configurator::readConfigurations() {
    QFile file(CONFIG_FILE_NAME);
    if(file.open(QIODevice::ReadOnly)) {
        QTextStream fstream(&file);
        while(!fstream.atEnd()) {
            QString line = fstream.readLine();
            auto keyValue = handleLine(line);

            QMap<QString, QString>::iterator iter;
            iter = m_configurations.find(keyValue.first);
            if(iter != m_configurations.end()) {
                *iter = keyValue.second;
            }
        }
        file.close();
    } else {
        writeDefaultConfigurationsFile();
    }
}

QString Configurator::getHostName() {
	return m_configurations[HOST_NAME_KEY];
}

int Configurator::getPort() {
	return m_configurations[PORT_KEY].toInt();
}

//  :: Private methods ::

QPair<QString, QString> Configurator::handleLine(QString line) {
    QString key, value;
    line = line.trimmed();

    int separatorPos = line.indexOf('=');
    if(separatorPos < 0) {
        // Попробуем найти хотя бы пробел
        separatorPos = line.indexOf(' ');
        if(separatorPos < 0) {
            line.clear();
        }
    }

    key = value = line;
    key.remove(separatorPos, line.size());
    value.remove(0, separatorPos + 1);

	return qMakePair(key.trimmed(), value.trimmed());
}

void Configurator::writeDefaultConfigurationsFile() {
    QFile file(CONFIG_FILE_NAME);
    file.open(QIODevice::WriteOnly);
    QTextStream fstream(&file);
    auto iter = m_configurations.cbegin();
    while(iter != m_configurations.cend()) {
        fstream << iter.key() << " = " << *iter << "\r\n";
        iter++;
    }
    file.close();
}
