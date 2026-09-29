# State

- State design pattern is used to manage object that has internal state change. The typical implementation is used for Finite State Machine FSM
- The idea is to create a context class that stores the initial state and delegate the state related behavior to that states (transition to other states as well)
- All concrete states should inherit from a base interface state
- See examples for typical implementation

```cpp
// Representative example (Examples/04_Templates_And_Design_Patterns/06_design_patterns/69_state_dp.cpp) — Context/CarState FSM
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

    class StateOff : public CarState { /* ... handleState() transitions to StateStandBy ... */ };
    class StateStandBy : public CarState { /* ... handleState() transitions to StateOn ... */ };
    class StateOn : public CarState { /* ... handleState() transitions to StateOff ... */ };

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
```
