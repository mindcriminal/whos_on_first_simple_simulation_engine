#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <iostream>
#include <ctime>

class Message
{
    public:
        Message()
        {
            sendTime = 0;
        };

        Message( std::string t, std::time_t st, std::string line )
        {
            topic = t;
            sendTime = st;
            myLine = line;
        }

        virtual ~Message()
        {};

        virtual std::string getTopic() {return topic;}
        virtual std::string getLine() {return myLine;}
        virtual std::time_t getSendTime() {return sendTime;}

        void setTopic( std::string t ) {topic = t;}
        void setSendTime( std::time_t t ) {sendTime = t;}
        void setLine( std::string l ) {myLine = l;}

        virtual void deliverLine()
        {
            std::cout << myLine << std::endl;
            std::cout << "\n" << std::endl;
        }

        std::string topic;
        std::string myLine;
        std::time_t sendTime;
};

#endif
