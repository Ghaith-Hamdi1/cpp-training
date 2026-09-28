#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <memory>

class IObserver
{
public:
    virtual ~IObserver() = default;
    virtual void onMessageReceived(const std::string& message) = 0;
};

class Observer1 : public IObserver
{
public:
    virtual ~Observer1() = default;
    void onMessageReceived(const std::string& message) override
    {
        std::cout << "Message received by Observer1: " << message << std::endl;
        // todo process received message
    }
};

class Observer2 : public IObserver
{
public:
    virtual ~Observer2() = default;
    void onMessageReceived(const std::string& message) override
    {
        std::cout << "Message received by Observer2: " << message << std::endl;
        // todo process received message
    }
};

class IService
{
public:
    virtual ~IService() = default;
    virtual void addSubscriber(std::shared_ptr<IObserver> observer) = 0;
    virtual void removeSubscriber(std::shared_ptr<IObserver> observer) = 0;
    virtual void removeAllSubscriber() = 0;
    virtual void notifySubscribers() = 0;
};

class Service : public IService
{
public:
    virtual ~Service() = default;
    virtual void addSubscriber(std::shared_ptr<IObserver> observer) override
    {
        m_observers.push_back(observer);
    }
    virtual void removeSubscriber(std::shared_ptr<IObserver> observer) override
    {
        auto it = std::find(m_observers.begin(), m_observers.end(), observer);
        if (it != m_observers.end())
        {
            m_observers.erase(it);
        }
    }
    virtual void removeAllSubscriber() override 
    {
        m_observers.clear();
    }
    virtual void notifySubscribers() override
    {
        std::string message{"Hello from service"};
        std::for_each(m_observers.begin(), m_observers.end(), [&message](std::shared_ptr<IObserver> obs){
            obs->onMessageReceived(message);
        });
    }
private:
    std::vector<std::shared_ptr<IObserver> > m_observers;  
};

int main()
{
    Service service;
    std::shared_ptr<IObserver> obs1 = std::make_shared<Observer1>();
    std::shared_ptr<IObserver> obs2 = std::make_shared<Observer2>();

    std::cout << "Add subscribers" << std::endl;
    service.addSubscriber(obs1);
    service.addSubscriber(obs2);

    std::cout << "Notify subscribers" << std::endl;
    service.notifySubscribers();

    std::cout << "Remove subscriber 1" << std::endl;
    service.removeSubscriber(obs1);

    std::cout << "Notify subscribers" << std::endl;
    service.notifySubscribers();

    std::cout << "Remove all subscribers" << std::endl;
    service.removeAllSubscriber();
    
    std::cout << "Notify subscribers" << std::endl;
    service.notifySubscribers();

    return 0;
}