#ifndef COMPONENT_FACTORY_H
#define COMPONENT_FACTORY_H

#include "Component.h"
#include <string>

class ComponentFactory
{
    public:
        ComponentFactory()
        {};

        ~ComponentFactory()
        {};

        Component* buildComponent( const std::string &type );

    private:
};

#endif
