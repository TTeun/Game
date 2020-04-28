//
// Created by pc on 4/28/20.
//

#ifndef SFML_CONSTPOINTERWRAPPER_H
#define SFML_CONSTPOINTERWRAPPER_H

#include <cassert>

template <class T>
class ConstPointerWrapper {

public:
    explicit ConstPointerWrapper(T * pointer) : m_pointer(pointer)
    {
    }

    explicit operator bool() const
    {
        return (bool)m_pointer;
    }

    const T & get() const
    {
        assert(m_pointer);
        return *m_pointer;
    }

    void set(T * pointer)
    {
        m_pointer = pointer;
    }

private:
    const T * m_pointer;
};

#endif // SFML_CONSTPOINTERWRAPPER_H
