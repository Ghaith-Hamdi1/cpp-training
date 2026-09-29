# Strategy

- Strategy design pattern allows separating the class (client) that does the processing that could be done in different ways from the algorithm of these ways (called strategies). The user of the client is responsible of the selection of the strategy or behavior
- An example of use: a class Travel will be used to manage trip information. A strategy is the mean of transport. The user will have to set the travel mean at each time according to cost, region, ...
- Strategies then will be Bicycle, bus, train, airplane...
- Strategies or behaviors can be changed without changing the context source code

```cpp
// Representative example (Examples/04_Templates_And_Design_Patterns/06_design_patterns/70_strategy_dp.cpp)
class TransportStrategy
{
public:
    int cost() const { return m_cost; }
    virtual void travelAlgorithm() = 0;
protected:
    int m_cost;
};

class TravelByBicycle : public TransportStrategy
{
public:
    TravelByBicycle() { TransportStrategy::m_cost = 0; }
    virtual void travelAlgorithm() override
    {
        std::cout << "Travel by bicycle algorithm" << std::endl;
    }
};
// TravelByTrain (cost 20), TravelByAirplane (cost 150) follow the same pattern

class Context
{
public:
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
            // ... else not enough money / strategy not set ...
        }
    }
private:
    std::shared_ptr<TransportStrategy> m_transportStrategy;
    int m_money;
};
```
