#include <iostream>

class Context // state machine class
{
    class CarState
    {
    public:
        CarState(Context& context) : m_context{context} 
        {}
        virtual void handleState() = 0;
    protected:
        Context& m_context;
    };

    class StateOff : public CarState
    {
    public:
        StateOff(Context& context) : CarState(context), m_cycles{0} 
        {
        }
        virtual void handleState() override 
        {
            std::cout << "Called state StateOff" << std::endl;
            if (m_cycles < 2)
            {
                m_cycles++;
                m_context.trantionTo(m_context.m_stateSandBy);
            }
            else
            {
                // do nothing
                std::cout << "Exit" << std::endl;
            }
        }
    private:
        int m_cycles;
    };

    class StateStandBy : public CarState
    {
    public:
        StateStandBy(Context& context) : CarState(context) 
        {}
        virtual void handleState() override 
        {
            std::cout << "Called state StateStandBy" << std::endl;
            m_context.trantionTo(m_context.m_stateOn);
        }
    };

    class StateOn : public CarState
    {
    public:
        StateOn(Context& context) : CarState(context) 
        {}
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