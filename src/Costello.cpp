#include <fstream>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include "CostelloMessage.h"
#include "Costello.h"
#include "MessageQueue.h"

bool Costello::initialize()
{
    return registerSubscriptions() && readLines();
}

bool Costello::registerSubscriptions()
{
    bool success( true );

    // read topic subscriptions
    std::ifstream in;
    in.open( "./input/costello.sub", std::ifstream::in );

    if( !in )
    {
        std::cout << "Cannot open costello subscriptions file!" << std::endl;
        success = false;
    }
    else
    {
        // register topic subscriptions
        std::string subscriptionTopic;
        while ( std::getline( in, subscriptionTopic ) )
        {
            std::cout << "Costello subscribed to " << subscriptionTopic << std::endl;
            mySubscriptions.push_back( subscriptionTopic );
        }
    }

    return success;
}

bool Costello::readLines()
{
    bool success( true );

    // read lines
    std::ifstream in;
    in.open( "./input/costello.lines", std::ifstream::in );

    if( !in )
    {
        std::cout << "Cannot open costello lines file!" << std::endl;
        success = false;
    }
    else
    {
        std::string line;
        while ( std::getline( in, line ) )
        {
           myLines.push_back( line );
        }
    }

    return success;
}

void Costello::receiveMessage( Message* m )
{
    // print the line
    m->deliverLine();

    // send next line of dialog if there are still lines
    // origination of message memory
    if( myLines.begin() != myLines.end() )
    {
        CostelloMessage* nextLine = new CostelloMessage( 
                std::chrono::system_clock::to_time_t(std::chrono::system_clock::now() + std::chrono::seconds( getComedicDelay() )), 
                myLines.front() );
        
        sendMessage( nextLine );
        myLines.pop_front();
    }
}

void Costello::sendMessage( Message* m )
{
    MessageQueue::getInstance()->sendMessage( m );
}
