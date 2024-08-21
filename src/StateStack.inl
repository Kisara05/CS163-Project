template <typename StateType>
void StateStack::registerState(StateIDs stateID) {
    factories[stateID] = [this]() {
        return State::Ptr(new StateType(*this, context));
    };
}