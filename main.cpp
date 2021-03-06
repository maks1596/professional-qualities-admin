#include <QApplication>

#include "Configurator/Configurator.h"
#include "Entities/Test/Test.h"
#include "Entities/User/User.h"
#include "Modules/Autorization/View/LoginForm.h"
#include "MainWindow/MainWindow.h"
#include "Navigation/NavigationView.h"

int main(int argc,  char **argv) {
    QStringList paths = QCoreApplication::libraryPaths();
    paths.append(".");
    paths.append("imageformats");
	paths.append("platforms");
    QCoreApplication::setLibraryPaths(paths);

    qRegisterMetaType<User>("User");
    qRegisterMetaType<Test>("Test");

    QApplication a(argc, argv);
    Configurator::readConfigurations();
    MainWindow mainWindow;
    NavigationView::setNavigation(&mainWindow);

    LoginForm loginForm;
    loginForm.show();

    QObject::connect(&loginForm, &LoginForm::loginSuccessed,
                     &loginForm, &LoginForm::hide);
    QObject::connect(&loginForm, &LoginForm::loginSuccessed,
                     &mainWindow, &MainWindow::show);

    return a.exec();
}
