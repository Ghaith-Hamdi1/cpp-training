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

class TravelByTrain : public TransportStrategy
{
public:
    TravelByTrain() { TransportStrategy::m_cost = 20; }
    virtual void travelAlgorithm() override
    {
        std::cout << "Travel by train algorithm" << std::endl;
    }
};
// TravelByAirplane (cost 150) follows the same pattern

class Context
{
public:
    enum class Error { kOk, kNoMoney, kError };

    Context() : m_transportStrategy(nullptr), m_money{0} {}

    void setStrategy(std::shared_ptr<TransportStrategy> strategy)
    {
        m_transportStrategy = strategy;
    }

    void setMoney(int money) { m_money = money; }

    Error goToDestination()
    {
        if (m_transportStrategy == nullptr)
        {
            return Error::kError;
        }
        if (m_transportStrategy->cost() > m_money)
        {
            return Error::kNoMoney;
        }
        m_transportStrategy->travelAlgorithm();
        return Error::kOk;
    }
private:
    std::shared_ptr<TransportStrategy> m_transportStrategy;
    int m_money;
};

int main()
{
    Context context;
    context.setMoney(50);
    context.setStrategy(std::make_shared<TravelByBicycle>());
    context.goToDestination();
    context.setStrategy(std::make_shared<TravelByTrain>());
    context.goToDestination();
    return 0;
}
```
