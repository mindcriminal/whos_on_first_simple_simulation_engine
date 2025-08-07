#include <fstream>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include "JoeMessage.h"
#include "Joe.h"
#include "MessageQueue.h"

bool Joe::initialize()
{
    bool success( true );

    if( !registerSubscriptions() || !readLines() )
    {
        success = false;
    }

    return success;
}

bool Joe::registerSubscriptions()
{
    bool success( true );

    // read topic subscriptions
    std::ifstream in;
    in.open( "./input/joe.sub", std::ifstream::in );

    if( !in )
    {
        std::cout << "Cannot open joe subscriptions file!" << std::endl;
        success = false;
    }
    else
    {
        // register topic subscriptions
        std::string subscriptionTopic;
        while ( std::getline( in, subscriptionTopic ) )
        {
            std::cout << "Joe subscribed to " << subscriptionTopic << std::endl;
            mySubscriptions.push_back( subscriptionTopic );
        }
    }

    return success;
}

bool Joe::readLines()
{
    bool success( true );

    // read lines
    std::ifstream in;
    in.open( "./input/joe.lines", std::ifstream::in );

    if( !in )
    {
        std::cout << "Cannot open joe lines file!" << std::endl;
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

void Joe::receiveMessage( Message* m )
{
    // print the line
    m->deliverLine();

    // send next line of dialog if there are still lines
    // origination of message memory
    if( myLines.begin() != myLines.end() )
    {
        JoeMessage* nextLine = new JoeMessage(
                std::chrono::system_clock::to_time_t(std::chrono::system_clock::now() + std::chrono::seconds( getComedicDelay() )),
                myLines.front() );

        sendMessage( nextLine );
        myLines.pop_front();
    }
}

void Joe::sendMessage( Message* m )
{
    MessageQueue::getInstance()->sendMessage( m );
}
