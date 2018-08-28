#include "ComponentFactory.h"
#include "Engine.h"
#include "Component.h"
#include <fstream>
#include <iostream>

std::vector<Component*> componentList;

// factory produces components based on input file
bool buildComponents()
{
    bool success( true );
    ComponentFactory componentFactory;

    std::ifstream in;
    in.open( "./input/sim.components", std::ifstream::in );

    if( !in )
    {
        std::cout << "Cannot open main conf file!" << std::endl;
        success = false;
    }
    else
    {
        std::string line;
        while ( std::getline( in, line ) )
        {
            Component* newComponent = componentFactory.buildComponent( line );

            if( newComponent )
            {
                componentList.push_back( newComponent );
            }
            else
            {
                success = false;
            }
        }
    }

    return success;
};

int main()
{
    // if factory fails do not move forward
    if( buildComponents() )
    {
        Engine engine;

        // check engine
        if( engine.initialize() )
        {
            // check components
            bool success( true );

            for( auto component : componentList )
            {
                if( component->initialize() )
                {
                    engine.registerComponent( component );
                }
                else
                {
                    // a component failed to initialize
                    success = false;
                }
            }

            // all components ready to go!
            if( success )
            {
                // run!
                engine.execute();
            }
        }
    }

    // cleanup!
    for( auto component : componentList )
    {
        delete component;
        component = 0;
    }

    return 0;
}
