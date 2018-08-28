#ifndef ABBOTT_H
#define ABBOTT_H

#include "Component.h"

class Abbott : public Component
{
    public:
        Abbott()
        {
            id = "abbott";
        };

        virtual ~Abbott()
        {};

        virtual bool initialize();
        virtual bool registerSubscriptions();
        virtual bool readLines();
        virtual void receiveMessage( Message* m );
        virtual void sendMessage( Message* m );

    private:

};

#endif
