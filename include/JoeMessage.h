#ifndef JOE_MESSAGE_H
#define JOE_MESSAGE_H

#include "Message.h"

class JoeMessage : public Message
{
    public:
        JoeMessage()
        {
            topic = "joe_dialog";
        };

        JoeMessage( std::time_t st, std::string line )
            : JoeMessage()
        {
            sendTime = st;
            myLine = line;
        };

        ~JoeMessage()
        {};

    private:

};

#endif
