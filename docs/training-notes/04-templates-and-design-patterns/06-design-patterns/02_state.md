# State

- State design pattern is used to manage object that has internal state change. The typical implementation is used for Finite State Machine FSM
- The idea is to create a context class that stores the initial state and delegate the state related behavior to that states (transition to other states as well)
- All concrete states should inherit from a base interface state
- See examples for typical implementation

```cpp
// Representative example (examples/course/04-templates-and-design-patterns/06-design-patterns/69_state_dp.cpp) — Context/CarState FSM
class Context // state machine class
{
    class CarState
    {
    public:
        CarState(Context& context) : m_context{context} {}
        virtual void handleState() = 0;
    protected:
        Context& m_context;
    };

    class StateOff : public CarState
    {
    public:
        StateOff(Context& context) : CarState(context), m_cycles{0} {}
        virtual void handleState() override
        {
            std::cout << "Called state StateOff" << std::endl;
            if (m_cycles < 2)
            {
                m_cycles++;
                m_context.trantionTo(m_context.m_stateSandBy);
            }
        }
    private:
        int m_cycles;
    };

    class StateStandBy : public CarState
    {
    public:
        StateStandBy(Context& context) : CarState(context) {}
        virtual void handleState() override
        {
            std::cout << "Called state StateStandBy" << std::endl;
            m_context.trantionTo(m_context.m_stateOn);
        }
    };

    class StateOn : public CarState
    {
    public:
        StateOn(Context& context) : CarState(context) {}
        virtual void handleState() override
        {
            std::cout << "Called state StateOn" << std::endl;
            m_context.trantionTo(m_context.m_stateOff);
        }
    };

    StateOff m_stateOff;
    StateStandBy m_stateSandBy;
    StateOn m_stateOn;
    CarState& m_currentState;
public:
    Context() :
                m_stateOff(*this),
                m_stateSandBy(*this),
                m_stateOn(*this),
                m_currentState{m_stateOff}
    {
        trantionTo(m_currentState);
    }

    void trantionTo(CarState& new_state)
    {
        new_state.handleState();
    }
};

int main()
{
    Context fsm;
    return 0;
}
```
