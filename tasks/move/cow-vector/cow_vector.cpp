#include "cow_vector.h"

State::State() : cnt(1) {
}

State::State(const std::vector<std::string>& other) {
    cnt = 1;
    data = other;
}

COWVector::COWVector() : state_(new State) {
    state_->cnt = 1;
}

COWVector::~COWVector() {
    if (--state_->cnt == 0) {
        delete state_;
    }
}

COWVector::COWVector(const COWVector& other) : state_(other.state_) {
    state_->cnt++;
}

COWVector& COWVector::operator=(const COWVector& other) {
    if (this == &other) {
        return *this;
    }
    if (--state_->cnt == 0) {
        delete state_;
    }
    state_ = other.state_;
    state_->cnt++;
    return *this;
}

size_t COWVector::Size() const {
    return COWVector::state_->data.size();
}

void COWVector::Resize(size_t size) {
    if (state_->cnt > 1) {
        state_->cnt--;
        state_ = new State(*state_);
    }
    state_->data.resize(size);
}

const std::string& COWVector::Get(size_t at) {
    return COWVector::state_->data[at];
}
const std::string& COWVector::Back() {
    return COWVector::state_->data.back();
}

void COWVector::PushBack(const std::string& value) {
    if (state_->cnt > 1) {
        state_->cnt--;
        state_ = new State(*state_);
    }
    state_->data.push_back(value);
}

void COWVector::Set(size_t at, const std::string& value) {
    if (state_->cnt > 1) {
        state_->cnt--;
        state_ = new State(*state_);
    }
    state_->data[at] = value;
}