#include "GroupsResultsTree.h"

#include "../GroupResults/GroupResults.h"
#include "NamedValue/NamedValue.h"
#include "NamedValues/NamedValues.h"

//  :: Private functions headers ::

template<typename T>
Tree::NodePtr<NamedValues> emptyCopy(const Tree::NodePtr<T> &node,
                                     const Tree::NodePtr<NamedValues> &parent = Tree::NodePtr<NamedValues>(nullptr));

void append(const Tree::NodePtr<NamedValues> &valuesNodePtr,
            const Tree::NodePtr<NamedValue> &valueNodePtr);

void appendDummy(const Tree::NodePtr<NamedValues> &valuesNodePtr);

int indexOf(const QList<ResultStatistics> &results, const QString &formulation);

//  :: Public accessors ::

QString GroupsResultsTree::getGroupName(uint index) const {
    return m_groupNames[index];
}

const Tree::NodePtrs<NamedValues> &GroupsResultsTree::getResults() const {
    return m_results;
}

const Tree::NodePtr<NamedValues> &GroupsResultsTree::getResult(uint index) const {
    return m_results.at(index);
}

//  :: Public methods ::

int GroupsResultsTree::groupsCount() const {
    return m_groupNames.size();
}
bool GroupsResultsTree::hasGroups() const {
    return m_groupNames.isEmpty();
}

int GroupsResultsTree::resultsCount() const {
    return m_results.size();
}
bool GroupsResultsTree::hasResults() const {
    return !m_results.isEmpty();
}

void GroupsResultsTree::setGroupsResults(const QList<GroupResults> &groupsResults) {
    m_results.clear();
    m_groupNames.clear();

    for (const auto &groupResults : groupsResults) {
        addGroupResults(groupResults);
    }
}

void GroupsResultsTree::addGroupResults(const GroupResults &groupResults) {
    auto results = groupResults.getResults();

    for (const auto &result : results) {
        if (!hasResult(result.getFormulation())) {
            appendEmptyResult(result);
        }
    }

    for (const auto &existingResultNodePtr : getResults()) {
        auto resultFormulation = existingResultNodePtr->getData().getName();
        int resultIndex = indexOf(results, resultFormulation);

        if (resultIndex > -1) {
            auto newResultNodePtr = results[resultIndex].toTreeNodePtr();
            append(existingResultNodePtr, newResultNodePtr);
        } else {
            appendDummy(existingResultNodePtr);
        }
    }

    m_groupNames.append(groupResults.getGroupName());
}

//  :: Private methods ::

bool GroupsResultsTree::hasResult(const QString &resultFormulation) const {
    for (const auto &resultNodePtr : getResults()) {
        if (resultNodePtr->getData().getName() == resultFormulation) {
            return true;
        }
    }
    return false;
}

void GroupsResultsTree::appendEmptyResult(const ResultStatistics &result) {
    Tree::NodePtr<NamedValues> emptyResult(nullptr);
    if (hasResults()) {
        auto sourceResult = getResults().first();
        emptyResult = emptyCopy(sourceResult);
    } else {
        auto sourceResult = result.toTreeNodePtr();
        emptyResult = emptyCopy(sourceResult);
    }
    emptyResult->getData().setName(result.getFormulation());
    m_results.append(emptyResult);
}

//  :: Private functions ::

template<typename  T>
Tree::NodePtr<NamedValues> emptyCopy(const Tree::NodePtr<T> &node,
                                     const Tree::NodePtr<NamedValues> &parent) {
    NamedValues namedValues(node->getData().getName());
    auto emptyNodePtr = Tree::makeNodePtr(namedValues, parent);

    for (const auto &childNode : node->getChildren()) {
        auto emptyChildNodePtr = emptyCopy(childNode, emptyNodePtr);
        emptyNodePtr->addChild(emptyChildNodePtr);
    }

    return emptyNodePtr;
}

void append(const Tree::NodePtr<NamedValues> &valuesNodePtr,
            const Tree::NodePtr<NamedValue> &valueNodePtr) {
    valuesNodePtr->getData().appendValue(valueNodePtr->getData().getValue());

    uint childrenCount = valuesNodePtr->childrenCount();
    for (uint i = 0; i < childrenCount; ++i) {
        append(valuesNodePtr->child(i), valueNodePtr->child(i));
    }
}

void appendDummy(const Tree::NodePtr<NamedValues> &valuesNodePtr) {
    valuesNodePtr->getData().appendValue(QVariant());

    uint childrenCount = valuesNodePtr->childrenCount();
    for (uint i = 0; i < childrenCount; ++i) {
        appendDummy(valuesNodePtr->child(i));
    }
}

int indexOf(const QList<ResultStatistics> &results, const QString &formulation) {
    auto iter = std::find_if(results.begin(), results.end(),
                 [&formulation](const ResultStatistics &result) {
        return result.getFormulation() == formulation;
    });
    if (iter != results.end()) {
        return iter - results.begin();
    }
    return -1;
}
