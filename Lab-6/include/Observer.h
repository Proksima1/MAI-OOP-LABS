#pragma once
#include <string>

class Observer {
public:
    virtual void update(const std::string& event) = 0;
    virtual ~Observer() = default;
};

class FileObserver : public Observer {
public:
    void update(const std::string& event) override;
};

class ConsoleObserver : public Observer {
public:
    void update(const std::string& event) override;
};

