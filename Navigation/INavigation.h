#pragma once

class QWidget;

class INavigation {
public:
    virtual void push(QWidget *widget) = 0;
    virtual void pop() = 0;
};
