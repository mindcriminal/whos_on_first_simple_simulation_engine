#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include "Message.h"
#include <deque>

class MessageQueue
{
    public:
        static MessageQueue* getInstance();
        void sendMessage( Message* m );
        Message* popMessage();
        bool isEmpty() {return messageQueue.empty();}

    private:
        static MessageQueue* instance;
        MessageQueue();
        std::deque<Message*> messageQueue;

};

#endif
