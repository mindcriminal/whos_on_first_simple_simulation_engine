#ifndef JOE_H
#define JOE_H

#include "Component.h"

class Joe : public Component
{
    public:
        Joe()
        {
            id = "joe";
        };

        virtual ~Joe()
        {};

        virtual bool initialize();
        virtual bool registerSubscriptions();
        virtual bool readLines();
        virtual void receiveMessage( Message* m );
        virtual void sendMessage( Message* m );

    private:

};

#endif
