#include "MessageQueue.h"

MessageQueue* MessageQueue::instance = 0;

MessageQueue::MessageQueue()
{}

MessageQueue* MessageQueue::getInstance()
{
    if( instance == 0 )
    {
        instance = new MessageQueue();
    }

    return instance;
}

void MessageQueue::sendMessage( Message* m )
{
    messageQueue.push_back( m );
}

Message* MessageQueue::popMessage()
{
    Message* m = messageQueue.front();
    messageQueue.pop_front();
    return m;
}
