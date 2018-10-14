#pragma once

#include <QWidget>

class INavigation;

class NavigationView : public QWidget {
public:
    explicit NavigationView(QWidget *parent = nullptr);

    void pop();

    static INavigation *getNavigation();
    static void setNavigation(INavigation *navigation);

protected:
    void push(QWidget *widget);

private:
    static INavigation *m_navigation;
};
