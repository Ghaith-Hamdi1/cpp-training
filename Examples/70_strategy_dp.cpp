#include <iostream>
#include <memory>

class TransportStrategy
{
public:
    int cost() const
    {
        return m_cost;
    }

    virtual void travelAlgorithm() = 0;

protected:
    int m_cost;
};

class TravelByBicycle : public TransportStrategy
{
public:
    TravelByBicycle() {
        TransportStrategy::m_cost = 0;
    }

    virtual void travelAlgorithm() override
    {
        std::cout << "Travel by bicycle algorithm" << std::endl;
    }
};

class TravelByTrain : public TransportStrategy
{
public:
    TravelByTrain() {
        TransportStrategy::m_cost = 20;
    }
    virtual void travelAlgorithm() override
    {
        std::cout << "Travel by train algorithm" << std::endl;
    }
};

class TravelByAirplane : public TransportStrategy
{
public:
    TravelByAirplane() {
        TransportStrategy::m_cost = 150;
    }
    virtual void travelAlgorithm() override
    {
        std::cout << "Travel by airplane algorithm" << std::endl;
    }
};

class Context
{
public:
    enum class Error
    {
        kOk = 0,
        kNoMoney,
        kError,
    };

    Context(): m_transportStrategy(nullptr), m_money{0}
    {}

    void setStrategy(std::shared_ptr<TransportStrategy> strategy)
    {
        m_transportStrategy = strategy;
    }

    Error goToDestination()
    {
        if (m_transportStrategy != nullptr)
        {
            if (m_transportStrategy->cost() <= m_money)
            {
                m_transportStrategy->travelAlgorithm();
                return Error::kOk;
            }
            else 
            {
                std::cout << "Error, no enough money for this strategy" << std::endl;
                return Error::kNoMoney;
            }
        }
        else 
        {
            std::cout << "Error, strategy not set" << std::endl;
            return Error::kError;
        }
    }

    void setMoney(int money)
    {
        m_money = money;
    }
private:
    std::shared_ptr<TransportStrategy> m_transportStrategy;
    int m_money;
};

int main()
{
    Context context;
    std::shared_ptr<TravelByBicycle> bicycle = std::make_shared<TravelByBicycle>();
    std::shared_ptr<TravelByTrain> train = std::make_shared<TravelByTrain>();
    std::shared_ptr<TravelByAirplane> airplane = std::make_shared<TravelByAirplane>();
    context.setStrategy(bicycle);
    context.goToDestination();
    context.setMoney(50);
    context.setStrategy(train);
    context.goToDestination();
    context.setMoney(250);
    context.setStrategy(airplane);
    context.goToDestination();

    return 0;
}