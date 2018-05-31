#include "NamedValue.h"

bool operator ==(const NamedValue &lhs, const NamedValue &rhs) {
    return lhs.name == rhs.name && lhs.value == rhs.value;
}
