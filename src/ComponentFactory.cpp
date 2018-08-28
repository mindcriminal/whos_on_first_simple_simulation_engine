#include "ComponentFactory.h"
#include "Abbott.h"
#include "Costello.h"
#include <iostream>

Component* ComponentFactory::buildComponent( const std::string &type )
{
    Component* newComponent( 0 );

    if( type == "abbott" )
    {
        newComponent = new Abbott();
    }
    else if( type == "costello" )
    {
        newComponent = new Costello();
    }
    else
    {
        // TODO: Error - unknown component
        std::cout << "Error building unknown component " << type << std::endl;
    }

    return newComponent;
}
