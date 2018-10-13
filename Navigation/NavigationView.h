#pragma once

#include <QWidget>

class INavigation;

class NavigationView : public QWidget {
public:
    explicit NavigationView(QWidget *parent = nullptr);

    void push(QWidget *widget);
    void pop();

    static INavigation *getNavigation();
    static void setNavigation(INavigation *navigation);

private:
    static INavigation *m_navigation;
};
