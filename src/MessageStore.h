#pragma once

#include <mutex>

class MessageStore {
public:
    using Messages = std::list<const char*>;

    MessageStore() = default;
    storeMessage(Message);
    Messages getMessages();

private:
    std::mutex _mtx;
    Messages _messages;
};