#pragma once

#include <cpp_redis/cpp_redis>

class RedisHandler {
public:
    RedisHandler() {
        _redisClient.connect();
    }

    void store() {
        std::vector<std::pair<std::string, std::string>> values;
        for (auto var : ProcessVariableStore::getVariables()) {
            switch (var->getType()) {
                case TYPE::DOUBLE :
                    values.push_back({var->getName(), std::to_string(static_cast<ProcessVariable<TYPE::DOUBLE>*>(var)->get())});
                    break;
                case TYPE::INTEGER :
                    values.push_back({var->getName(), std::to_string(static_cast<ProcessVariable<TYPE::INTEGER>*>(var)->get())});
                    break;
                case TYPE::STRING :
                    values.push_back({var->getName(), static_cast<ProcessVariable<TYPE::STRING>*>(var)->get()});
                    break;
                case TYPE::MODE :
                    values.push_back({var->getName(), toString(static_cast<ProcessVariable<TYPE::MODE>*>(var)->get())});
            }
        }
        _redisClient.hmset("brewer_process_data", values);
        _redisClient.sync_commit();
    }

private:
    cpp_redis::client _redisClient;
};