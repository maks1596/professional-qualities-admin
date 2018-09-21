#include "../User.h"

#define PROCESS(name, Name, type, parameterType) \
User::Builder& User::Builder::set##Name(parameterType name) { \
    m_##name = name;\
    return *this; \
}

#include "UserBuilderXMacros.h"

#undef PROCESS

User User::Builder::build() const {
    User user;

#define PROCESS(name, Name, type, parameterType) user.set##Name(m_##name);
#include "UserBuilderXMacros.h"
#undef PROCESS

    return user;
}
