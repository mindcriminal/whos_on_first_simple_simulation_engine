#include "Engine.h"
#include "Component.h"
#include "MessageQueue.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
#include <fstream>

bool Engine::initialize()
{
    bool success( true );

    //read input file for timing
    std::ifstream in;
    in.open( "./input/sim.timing", std::ifstream::in );

    if( !in )
    {
        std::cout << "Cannot open timing file!" << std::endl;
        success = false;
    }
    else
    {
        std::string line;

        if( std::getline( in, line ) )  
        {
            comedicDelay = std::stoi( line );
        }
    }
    return success;
}

void Engine::registerComponent( Component* c )
{
    std::cout << "Registering " << c->getId() << std::endl;
    std::cout << "\n" << std::endl;
    registeredComponents.push_back( c );
    c->setComedicDelay( comedicDelay );

    // map topic to subscriber
    for( auto topicSubscriptions : c->getMySubscriptions() )
    {
        auto search = topicComponentMap.find( topicSubscriptions );

        if( search != topicComponentMap.end() )
        {
            // not the first subscriber to this topic
            search->second.push_back( c );
        }
        else
        {
            // first subscriber to this topic
            std::vector<Component*> components;
            components.push_back( c );
            topicComponentMap.insert( std::pair<std::string, std::vector<Component*>>
                                      ( topicSubscriptions, components ) );
        }
    }
}

void Engine::sendMessageToSubscribers( Message* m )
{
    // call subscribing components
    auto search = topicComponentMap.find( m->getTopic() );
    {
        if( search != topicComponentMap.end() )
        {
            for( auto subscribingComponents : search->second )
            {
                subscribingComponents->receiveMessage( m );

                // termination of message memory
                delete m;
                m = 0;
            }
        }
        else
        {
            // TODO: No one cares about this topic
        }
    }
}

void Engine::execute()
{
    while( !MessageQueue::getInstance()->isEmpty() )
    {
        Message * m( MessageQueue::getInstance()->popMessage() );
        while( std::chrono::system_clock::to_time_t( std::chrono::system_clock::now() ) <= 
                m->getSendTime() )
        {
            // Sleep until its time to send this message
            std::this_thread::sleep_for( std::chrono::seconds(1) );
        }
        
        // Time to send!
        sendMessageToSubscribers( m );
    }

    std::cout << "That's All Folks!" << std::endl;
}
