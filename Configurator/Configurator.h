#pragma once

template <class Key, class T>
class QMap;

template <class T1, class T2>
class QPair;

class QString;

class Configurator {
public:
    static void readConfigurations();

    static QString getHostName();
    static int getPort();

private:
	static QPair<QString, QString> handleLine(QString line);
    static void writeDefaultConfigurationsFile();

    static QMap<QString, QString> m_configurations;
};
