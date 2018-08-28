#ifndef COSTELLO_MESSAGE_H
#define COSTELLO_MESSAGE_H

#include "Message.h"

class CostelloMessage : public Message
{
    public:
        CostelloMessage()
        {
            topic = "costello_dialog";
        };

        CostelloMessage( std::time_t st, std::string line )
            : CostelloMessage()
        {
            sendTime = st;
            myLine = line;
        };

        ~CostelloMessage()
        {};

    private:

};

#endif
