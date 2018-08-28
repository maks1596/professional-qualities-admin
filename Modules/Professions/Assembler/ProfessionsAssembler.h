#pragma once

class QObject;
class ProfessionsListModel;

namespace ProfessionsAssembler {

ProfessionsListModel *assembly(QObject *parent = nullptr);
ProfessionsListModel *assemblyAndStart(QObject *parent = nullptr);

}
