#ifndef ENGINE_H
#define ENGINE_H

#include <map>
#include <vector>
#include <string>

class Message;
class Component;

class Engine
{
    public:
        Engine()
        {};

        ~Engine()
        {};

        // reads input file
        bool initialize();

        // gives access to components
        void registerComponent( Component* c );

        void sendMessageToSubscribers( Message* m );

        // executes the run
        void execute();

    private:
        // messages are queued here
        std::vector<Component*> registeredComponents;
        // map of components to topic keyed by topic
        std::map<std::string, std::vector<Component*>> topicComponentMap;
        double comedicDelay;
};

#endif
