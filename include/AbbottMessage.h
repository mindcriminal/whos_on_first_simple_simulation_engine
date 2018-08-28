#ifndef ABBOTT_MESSAGE_H
#define ABBOTT_MESSAGE_H

#include "Message.h"

class AbbottMessage : public Message
{
    public:
        AbbottMessage()
        {
            topic = "abbott_dialog";
        };

        AbbottMessage( std::time_t st, std::string line )
            : AbbottMessage()
        {
            sendTime = st;
            myLine = line;
        };

        ~AbbottMessage()
        {};

    private:

};

#endif
