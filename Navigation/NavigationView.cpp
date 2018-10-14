#include "NavigationView.h"

#include <cassert>

#include "INavigation.h"

//  :: Static fields ::

INavigation *NavigationView::m_navigation = nullptr;

//  :: Lifecycle ::

NavigationView::NavigationView(QWidget *parent)
    : QWidget(parent) { }

//  :: Public methods ::

void NavigationView::pop() {
    assert(m_navigation != nullptr);
    m_navigation->pop();
}

//  :: Static public methods ::

INavigation *NavigationView::getNavigation() {
    return m_navigation;
}
void NavigationView::setNavigation(INavigation *navigation) {
    m_navigation = navigation;
}

//  :: Protected methdos ::

void NavigationView::push(QWidget *widget) {
    assert(m_navigation != nullptr);
    m_navigation->push(widget);
}
