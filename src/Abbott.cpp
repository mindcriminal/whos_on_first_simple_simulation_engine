#include <fstream>
#include <chrono>
#include "AbbottMessage.h"
#include "Abbott.h"
#include "MessageQueue.h"

bool Abbott::initialize()
{
    bool success( true );

    // Abbott starts the script!
    if( registerSubscriptions() && readLines() )
    {
        // send first line of dialog
        // origination of message
        AbbottMessage* firstLine = new AbbottMessage( 0, myLines.front() );
        sendMessage( firstLine );
        myLines.pop_front();
    }
    else
    {
        success = false;
    }

    return success;
}

bool Abbott::registerSubscriptions()
{
    bool success( true );

    // read topic subscriptions
    std::ifstream in;
    in.open( "./input/abbott.sub", std::ifstream::in );

    if( !in )
    {
        std::cout << "Cannot open abbott subscriptions file!" << std::endl;
        success = false;
    }
    else
    {
        // register topic subscriptions
        std::string subscriptionTopic;
        while ( std::getline( in, subscriptionTopic ) )
        {
            std::cout << "Abbott subscribed to " << subscriptionTopic << std::endl;
            mySubscriptions.push_back( subscriptionTopic );
        }
    }

    return success;
}

bool Abbott::readLines()
{
    bool success( true );

    // read lines
    std::ifstream in;
    in.open( "./input/abbott.lines", std::ifstream::in );

    if( !in )
    {
        std::cout << "Cannot open abbott lines file!" << std::endl;
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

void Abbott::receiveMessage( Message* m )
{
    // print the line
    m->deliverLine();

    // speak the line
    std::string command = "espeak -ven-us+f1 \"" + m->getLine() + "\" &";
    system( command.c_str() );

    // send next line of dialog if there are still lines
    // origination of message memory
    if( myLines.begin() != myLines.end() )
    {
        AbbottMessage* nextLine = new AbbottMessage( 
                std::chrono::system_clock::to_time_t(std::chrono::system_clock::now() + std::chrono::seconds( getComedicDelay() )), 
                myLines.front() );

        sendMessage( nextLine );
        myLines.pop_front();
    }
}

void Abbott::sendMessage( Message* m )
{
    MessageQueue::getInstance()->sendMessage( m );

}
