#-------------------------------------------------
#
# Project created by QtCreator 2017-01-28T19:39:10
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProfessionalQualitiesAdmin
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
    Entities/User/User.cpp \
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
    Modules/Users/View/UsersForm.cpp \
    Entities/Entity/Entity.cpp \
    Entities/Gender/Gender.cpp \
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
    NamedValue/NamedValue.cpp \
    Modules/Correlations/Model/CorrelationsModel.cpp \
    Entities/Statistics/CorrelationValue/CorrelationValue.cpp \
    Entities/Statistics/GroupCorrelations/GroupCorrelations.cpp \
    Modules/Correlations/Service/CorrelationsService.cpp \
    Modules/Correlations/Assembler/CorrelationsAssembler.cpp \
    Modules/GroupsResults/Model/GroupsResultsModel.cpp \
    Modules/GroupsResults/Assembler/GroupsResultsAssembler.cpp \
    Modules/Correlations/View/CorrelationsForm.cpp \
    Entities/Statistics/GroupsResultsTree/GroupsResultsTree.cpp \
    NamedValues/NamedValues.cpp \
    Forms/UserDataForm/UserDataForm.cpp \
    Entities/UserRole/UserRole.cpp \
    Entities/UserRole/Model/UserRoleModel.cpp \
    Modules/AddUser/Controller/AddUserController.cpp \
    Modules/AddUser/View/AddUserView.cpp \
    Modules/AddUser/Service/AddUserService.cpp \
    Modules/AddUser/Assembler/AddUserAssembler.cpp \
    Forms/PersonalDataForm/PersonalDataForm.cpp \
    Modules/Professions/Model/ProfessionsListModel.cpp \
    Modules/Professions/Service/ProfessionsService.cpp \
    Modules/Professions/Assembler/ProfessionsAssembler.cpp \
    Forms/EditUserDataForm/EditUserDataForm.cpp \
    Modules/EditUser/View/EditUserView.cpp \
    Forms/TemplateUserForm/TemplateUserForm.cpp \
    Modules/EditUser/Controller/EditUserController.cpp \
    Entities/User/Builder/UserBuilder.cpp \
    Modules/EditUser/Service/EditUserService.cpp \
    Modules/EditUser/Assembler/EditUserAssembler.cpp \
    Navigation/NavigationView.cpp \
    Modules/Users/Controller/UsersController.cpp \
    Modules/Users/Model/UsersModel.cpp \
    Modules/Users/Service/UsersService.cpp \
    Modules/Users/Assembler/UsersAssembler.cpp \
    Modules/Tests/Assembler/TestsAssembler.cpp \
    Modules/Tests/Controller/TestsController.cpp \
    Modules/Tests/Model/TestsModel.cpp \
    Modules/Tests/Service/TestsService.cpp \
    Modules/Tests/View/TestsForm.cpp \
    Modules/AddUser/Output/AddUserOutput.cpp \
    Modules/EditUser/Output/EditUserOutput.cpp \
    EntitesOutput/EntitiesOutput.cpp

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
    Entities/User/User.h \
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
    Modules/Users/View/UsersForm.h \
    Entities/Entity/Entity.h \
    Entities/Gender/Gender.h \
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
    Tree.h \
    NamedValue/NamedValue.h \
    Modules/Correlations/View/CorrelationsForm.h \
    Modules/Correlations/Model/CorrelationsModel.h \
    Entities/Statistics/CorrelationValue/CorrelationValue.h \
    Entities/Statistics/GroupCorrelations/GroupCorrelations.h \
    Modules/Correlations/Service/CorrelationsService.h \
    Modules/Correlations/Assembler/CorrelationsAssembler.h \
    Modules/GroupsResults/Model/GroupsResultsModel.h \
    Modules/GroupsResults/View/GroupsResultsForm.h \
    Modules/GroupsResults/Assembler/GroupsResultsAssembler.h \
    Modules/ScaleStatistics/Model/ScaleStatisticsTabIndex.h \
    Entities/Statistics/GroupsResultsTree/GroupsResultsTree.h \
    NamedValues/NamedValues.h \
    Forms/UserDataForm/UserDataForm.h \
    Entities/UserRole/UserRole.h \
    Entities/UserRole/Model/UserRoleModel.h \
    Modules/AddUser/Controller/AddUserController.h \
    Modules/AddUser/View/AddUserView.h \
    Forms/UserDataForm/PasswordsHintStatus.h \
    Modules/AddUser/Service/AddUserService.h \
    Modules/AddUser/Assembler/AddUserAssembler.h \
    Forms/PersonalDataForm/PersonalDataForm.h \
    Modules/Professions/Model/ProfessionsListModel.h \
    Modules/Professions/Service/ProfessionsService.h \
    Modules/Professions/Assembler/ProfessionsAssembler.h \
    Forms/EditUserDataForm/EditUserDataForm.h \
    Modules/EditUser/View/EditUserView.h \
    Forms/TemplateUserForm/TemplateUserForm.h \
    Modules/EditUser/Controller/EditUserController.h \
    Entities/User/Builder/UserBuilderXMacros.h \
    Modules/EditUser/Service/EditUserService.h \
    Modules/EditUser/Assembler/EditUserAssembler.h \
    Navigation/INavigation.h \
    Navigation/NavigationView.h \
    Modules/Users/Controller/UsersController.h \
    Modules/Users/Model/UsersModel.h \
    Modules/Users/Service/UsersService.h \
    Modules/Users/Assembler/UsersAssembler.h \
    Modules/Tests/Assembler/TestsAssembler.h \
    Modules/Tests/Controller/TestsController.h \
    Modules/Tests/Model/TestsModel.h \
    Modules/Tests/Service/TestsService.h \
    Modules/Tests/View/TestsForm.h \
    Modules/AddUser/Output/AddUserOutput.h \
    Modules/EditUser/Output/EditUserOutput.h \
    EntitesOutput/EntitiesOutput.h

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
    Forms/EntitiesForm/EntitiesForm.ui \
    Modules/PassedTests/View/PassedTestsForm.ui \
    Modules/PassedTest/View/PassedTestForm.ui \
    Modules/ScaleStatistics/View/ScaleStatisticsForm.ui \
    Forms/UserDataForm/UserDataForm.ui \
    Forms/PersonalDataForm/PersonalDataForm.ui \
    Forms/EditUserDataForm/EditUserDataForm.ui \
    Forms/TemplateUserForm/TemplateUserForm.ui

# Для статической сборки
QMAKE_LFLAGS_RELEASE += -static -static-libgcc

RESOURCES += \
    resources/images/images.qrc
