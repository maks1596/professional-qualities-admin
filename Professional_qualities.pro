#-------------------------------------------------
#
# Project created by QtCreator 2017-01-28T19:39:10
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Professional_qualities
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    MainWindow/MainWindow.cpp \
    TestReader/TestReader.cpp \
    Entities/Test/Test.cpp \
    Entities/Question/Question.cpp \
    Forms/AnswerOptionsContainer/AnswerOptionsContainer.cpp \
    Forms/QuestionForm/QuestionForm.cpp \
    Forms/FormulationForm/FormulationForm.cpp \
    Forms/EditFormulationForm/EditFormulationForm.cpp \
    Forms/QuestionsContainer/QuestionsContainer.cpp \
    Entities/Scale/Scale.cpp \
    Forms/TestMainForm/TestMainForm.cpp \
    Modules/TestEditing/View/TestEditingForm.cpp \
    Forms/AddGeneralAnswerOptionsPartOfKeyForm/AddGeneralAnswerOptionsPartOfKeyForm.cpp \
    Forms/AddUniqueAnswerOptonsPartOfKeyForm/AddUniqueAnswerOptonsPartOfKeyForm.cpp \
    Forms/ScalesContainer/ScalesContainer.cpp \
    Forms/KeyForm/KeyForm.cpp \
    Forms/GeneralAnswerOptionsKeyForm/GeneralAnswerOptionsKeyForm.cpp \
    Forms/UniqueAnswerOptionsKeyForm/UniqueAnswerOptionsKeyForm.cpp \
    Forms/AddPartOfKeyForm/AddPartOfKeyForm.cpp \
    Forms/EvaluationMapForm/EvaluationMapForm.cpp \
    Forms/AddAppraisedRangeForm/AddAppraisedRangeForm.cpp \
    Configurator/Configurator.cpp \
    Modules/Autorization/View/LoginForm.cpp \
    Entities/AnswerOption/AnswerOption.cpp \
    Forms/AnswerOptionForm/AnswerOptionForm.cpp \
    Modules/Tests/View/TestsForm.cpp \
    Entities/User/User.cpp \
    Forms/UserForm/UserForm.cpp \
    Forms/EntitiesForm/EntitiesForm.cpp \
    Requester/Requester.cpp \
    Entities/AnswerOption/Type/AnswerOptionsType.cpp \
    Entities/Key/Key.cpp \
    Serializable/Object/SerializableObject.cpp \
    Serializable/Array/SerializableArray.cpp \
    Entities/EvaluationMap/EvaluationMap.cpp \
    Entities/Range/Appraised/AppraisedRange.cpp \
    Entities/Key/GeneralAnswerOptions/GeneralAnswerOptionsKey.cpp \
    Entities/Key/UniqueAnswerOptions/UniqueAnswerOptionsKey.cpp \
    Entities/Key/PartOfKey/PartOfKey.cpp \
    Entities/Key/GeneralAnswerOptions/PartOfKey/PartOfGeneralAnswerOptionsKey.cpp \
    Entities/Key/UniqueAnswerOptions/PartOfKey/PartOfUniqueAnswerOptionsKey.cpp \
    Modules/Users/Model/UsersModel.cpp \
    Modules/Users/View/UsersForm.cpp \
    Entities/Entity/Entity.cpp \
    Entities/Gender/Gender.cpp \
    Modules/CreateUser/Model/CreateUserModel.cpp \
    Modules/UpdateUserData/Model/UpdateUserDataModel.cpp \
    Modules/Tests/Model/TestsModel.cpp \
    Entities/ShortTestInfo/ShortTestInfo.cpp \
    Modules/TestEditing/Model/TestEditingModel.cpp \
    Modules/Autorization/Model/AutorizationModel.cpp \
    Entities/AutorizationData/AutorizationData.cpp \
    Modules/PassedTests/View/PassedTestsForm.cpp \
    Modules/PassedTests/Model/PassedTestsModel.cpp \
    Entities/Statistics/PassedTestPreview/PassedTestPreview.cpp \
    Modules/PassedTests/Service/PassedTestsService.cpp \
    BaseService/BaseService.cpp \
    Modules/PassedTests/Assembler/PassedTestsAssembler.cpp \
    Modules/PassedTest/View/PassedTestForm.cpp \
    Modules/PassedTest/Assembler/PassedTestAssembler.cpp \
    Entities/Statistics/PassedTest/PassedTest.cpp \
    Entities/Statistics/ScaleStatistics/ScaleStatistics.cpp \
    Entities/Statistics/ResultStatistics/ResultStatistics.cpp \
    Entities/Statistics/GroupResults/GroupResults.cpp \
    Entities/Statistics/IndicatorGroup/IndicatorGroup.cpp \
    Entities/Statistics/Indicator/Indicator.cpp \
    Modules/PassedTest/Model/PassedTestModel.cpp \
    Modules/ScaleStatistics/View/ScaleStatisticsForm.cpp \
    Modules/ScaleStatistics/Assembler/ScaleStatisticsAssembler.cpp \
    Modules/ScaleStatistics/Model/ScaleStatisticsModel.cpp \
    Modules/GroupResults/Model/GroupResultsModel.cpp

HEADERS  += MainWindow/MainWindow.h \
    TestReader/TestReader.h \
    Entities/Test/Test.h \
    Entities/Question/Question.h \
    Exception.h \
    Entities/AnswerOption/AnswerOption.h \
    Forms/AnswerOptionsContainer/AnswerOptionsContainer.h \
    Forms/QuestionForm/QuestionForm.h \
    Forms/FormulationForm/FormulationForm.h \
    Forms/EditFormulationForm/EditFormulationForm.h \
    Forms/QuestionsContainer/QuestionsContainer.h \
    Entities/Scale/Scale.h \
    Forms/TestMainForm/TestMainForm.h \
    Modules/TestEditing/View/TestEditingForm.h \
    Forms/AddGeneralAnswerOptionsPartOfKeyForm/AddGeneralAnswerOptionsPartOfKeyForm.h \
    Forms/ScalesContainer/ScalesContainer.h \
    Forms/AddUniqueAnswerOptonsPartOfKeyForm/AddUniqueAnswerOptonsPartOfKeyForm.h \
    Forms/KeyForm/KeyForm.h \
    Forms/GeneralAnswerOptionsKeyForm/GeneralAnswerOptionsKeyForm.h \
    Forms/UniqueAnswerOptionsKeyForm/UniqueAnswerOptionsKeyForm.h \
    Forms/AddPartOfKeyForm/AddPartOfKeyForm.h \
    Forms/EvaluationMapForm/EvaluationMapForm.h \
    Forms/AddAppraisedRangeForm/AddAppraisedRangeForm.h \
    Configurator/Configurator.h \
    Modules/Autorization/View/LoginForm.h \
    Forms/AnswerOptionForm/AnswerOptionForm.h \
    Modules/Tests/View/TestsForm.h \
    Entities/User/User.h \
    Forms/UserForm/UserForm.h \
    Forms/EntitiesForm/EntitiesForm.h \
    Requester/Requester.h \
    Requester/RequestType.h \
    Entities/AnswerOption/Type/AnswerOptionsType.h \
    Entities/Key/Key.h \
    Indexes.h \
    Serializable/Object/SerializableObject.h \
    Serializable/Array/SerializableArray.h \
    Entities/EvaluationMap/EvaluationMap.h \
    Entities/Range/Range.h \
    Entities/Range/Appraised/AppraisedRange.h \
    Entities/Key/GeneralAnswerOptions/GeneralAnswerOptionsKey.h \
    Entities/Key/UniqueAnswerOptions/UniqueAnswerOptionsKey.h \
    Entities/Key/PartOfKey/PartOfKey.h \
    Entities/Key/GeneralAnswerOptions/PartOfKey/PartOfGeneralAnswerOptionsKey.h \
    Entities/Key/UniqueAnswerOptions/PartOfKey/PartOfUniqueAnswerOptionsKey.h \
    Modules/Users/Model/UsersModel.h \
    Modules/Users/View/UsersForm.h \
    Entities/Entity/Entity.h \
    Entities/Gender/Gender.h \
    Modules/CreateUser/Model/CreateUserModel.h \
    Modules/UpdateUserData/Model/UpdateUserDataModel.h \
    Modules/Tests/Model/TestsModel.h \
    Entities/ShortTestInfo/ShortTestInfo.h \
    Modules/TestEditing/Model/TestEditingModel.h \
    Modules/Autorization/Model/AutorizationModel.h \
    Entities/AutorizationData/AutorizationData.h \
    Modules/PassedTests/View/PassedTestsForm.h \
    Modules/PassedTests/Model/PassedTestsModel.h \
    Entities/Statistics/PassedTestPreview/PassedTestPreview.h \
    Modules/PassedTests/Service/PassedTestsService.h \
    BaseService/BaseService.h \
    Modules/PassedTests/Model/PassedTestsColumnIndex.h \
    Modules/PassedTests/Assembler/PassedTestsAssembler.h \
    Modules/PassedTest/View/PassedTestForm.h \
    Modules/PassedTest/Assembler/PassedTestAssembler.h \
    Entities/Statistics/PassedTest/PassedTest.h \
    Entities/Statistics/ScaleStatistics/ScaleStatistics.h \
    JsonArraySerialization.h \
    Entities/Statistics/ResultStatistics/ResultStatistics.h \
    Entities/Statistics/GroupResults/GroupResults.h \
    Entities/Statistics/IndicatorGroup/IndicatorGroup.h \
    Entities/Statistics/Indicator/Indicator.h \
    Modules/PassedTest/Model/PassedTestModel.h \
    Modules/ScaleStatistics/View/ScaleStatisticsForm.h \
    Modules/ScaleStatistics/Assembler/ScaleStatisticsAssembler.h \
    Modules/ScaleStatistics/Model/ScaleStatisticsModel.h \
    Modules/GroupResults/Model/GroupResultsModel.h \
    Tree.h

FORMS    += MainWindow/MainWindow.ui \
    Forms/FormulationForm/FormulationForm.ui \
    Forms/EditFormulationForm/EditFormulationForm.ui \
    Forms/AnswerOptionsContainer/AnswerOptionsContainer.ui \
    Forms/QuestionsContainer/QuestionsContainer.ui \
    Forms/TestMainForm/TestMainForm.ui \
    Modules/TestEditing/View/TestEditingForm.ui \
    Forms/AddGeneralAnswerOptionsPartOfKeyForm/AddGeneralAnswerOptionsPartOfKeyForm.ui \
    Forms/ScalesContainer/ScalesContainer.ui \
    Forms/AddUniqueAnswerOptonsPartOfKeyForm/AddUniqueAnswerOptonsPartOfKeyForm.ui \
    Forms/ScaleForm.ui \
    Forms/AddAppraisedRangeForm/AddAppraisedRangeForm.ui \
    Modules/Autorization/View/LoginForm.ui \
    Forms/UserForm/UserForm.ui \
    Forms/EntitiesForm/EntitiesForm.ui \
    Modules/PassedTests/View/PassedTestsForm.ui \
    Modules/PassedTest/View/PassedTestForm.ui \
    Modules/ScaleStatistics/View/ScaleStatisticsForm.ui

# Для статической сборки
QMAKE_LFLAGS_RELEASE += -static -static-libgcc

RESOURCES += \
    resources/images/images.qrc
