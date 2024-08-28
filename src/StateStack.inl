template <typename StateType>
void StateStack::registerState(StateIDs stateID) {
    mFactories[stateID] = [this]() {
        return State::Ptr(new StateType(*this, mContext));
    };
}