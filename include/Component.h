#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>
#include <string>
#include <deque>

class Message;

class Component
{
    public:
        Component()
        {};

        virtual ~Component()
        {};

        virtual bool initialize() = 0;
        virtual bool registerSubscriptions() = 0;
        virtual bool readLines() = 0;
        virtual void receiveMessage(Message* m) = 0;
        virtual void sendMessage( Message* m ) = 0;

        virtual std::string getId() {return id;}
        virtual std::vector<std::string> getMySubscriptions() {return mySubscriptions;}
        void setComedicDelay( double delay ) {comedicDelay = delay;}
        int getComedicDelay() {return comedicDelay;}

        std::string id;
        int comedicDelay;
        std::vector<std::string> mySubscriptions;
        std::deque<std::string> myLines;

    private:


};

#endif
