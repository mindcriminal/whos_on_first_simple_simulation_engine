#ifndef COSTELLO_H
#define COSTELLO_H

#include "Component.h"

class Costello : public Component
{
    public:
        Costello()
        {
            id = "costello";
        };

        virtual ~Costello()
        {};

        virtual bool initialize();
        virtual bool registerSubscriptions();
        virtual bool readLines();
        virtual void receiveMessage( Message* m );
        virtual void sendMessage( Message* m );

    private:

};

#endif
