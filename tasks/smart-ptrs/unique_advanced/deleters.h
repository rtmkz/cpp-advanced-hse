#include <cassert>
#include <type_traits>
#include <utility>

template <class T>
class Deleter {
    int state_;

    Deleter(const Deleter&);
    Deleter& operator=(const Deleter&);

public:
    Deleter(Deleter&& r) : state_(r.state_) {
        r.state_ = 0;
    }
    Deleter& operator=(Deleter&& r) {
        state_ = r.state_;
        r.state_ = 0;
        return *this;
    }

    Deleter() : state_(0) {
    }
    explicit Deleter(int s) : state_(s) {
    }
    ~Deleter() {
        assert(state_ >= 0);
        state_ = -1;
    }

    template <class U>
    Deleter(Deleter<U>&& d, typename std::enable_if<!std::is_same<U, T>::value>::type* = 0)
        : state_(d.state()) {
        d.set_state(0);
    }

private:
    template <class U>
    Deleter(const Deleter<U>& d, typename std::enable_if<!std::is_same<U, T>::value>::type* = 0);

public:
    int state() const {
        return state_;
    }
    void set_state(int i) {
        state_ = i;
    }

    void operator()(T* p) {
        delete p;
    }
};

template <class T>
class Deleter<T[]> {
    int state_;

    Deleter(const Deleter&);
    Deleter& operator=(const Deleter&);

public:
    Deleter(Deleter&& r) : state_(r.state_) {
        r.state_ = 0;
    }
    Deleter& operator=(Deleter&& r) {
        state_ = r.state_;
        r.state_ = 0;
        return *this;
    }

    Deleter() : state_(0) {
    }
    explicit Deleter(int s) : state_(s) {
    }
    ~Deleter() {
        assert(state_ >= 0);
        state_ = -1;
    }

    int state() const {
        return state_;
    }
    void set_state(int i) {
        state_ = i;
    }

    void operator()(T* p) {
        delete[] p;
    }
};

template <class T>
void swap(Deleter<T>& x, Deleter<T>& y) {
    Deleter<T> t(std::move(x));
    x = std::move(y);
    y = std::move(t);
}

template <class T>
class CDeleter {
    int state_;

public:
    CDeleter() : state_(0) {
    }
    explicit CDeleter(int s) : state_(s) {
    }
    ~CDeleter() {
        assert(state_ >= 0);
        state_ = -1;
    }

    template <class U>
    CDeleter(const CDeleter<U>& d) : state_(d.state()) {
    }

    int state() const {
        return state_;
    }
    void set_state(int i) {
        state_ = i;
    }

    void operator()(T* p) {
        delete p;
    }
};

template <class T>
class CDeleter<T[]> {
    int state_;

public:
    CDeleter() : state_(0) {
    }
    explicit CDeleter(int s) : state_(s) {
    }
    template <class U>
    CDeleter(const CDeleter<U>& d) : state_(d.state()) {
    }

    ~CDeleter() {
        assert(state_ >= 0);
        state_ = -1;
    }

    int state() const {
        return state_;
    }
    void set_state(int i) {
        state_ = i;
    }

    void operator()(T* p) {
        delete[] p;
    }
};

template <class T>
void swap(CDeleter<T>& x, CDeleter<T>& y) {
    CDeleter<T> t(std::move(x));
    x = std::move(y);
    y = std::move(t);
}

// Non-copyable deleter
template <class T>
class NCDeleter {
    int state_;
    NCDeleter(NCDeleter const&);
    NCDeleter& operator=(NCDeleter const&);

public:
    NCDeleter() : state_(0) {
    }
    explicit NCDeleter(int s) : state_(s) {
    }
    ~NCDeleter() {
        assert(state_ >= 0);
        state_ = -1;
    }

    int state() const {
        return state_;
    }
    void set_state(int i) {
        state_ = i;
    }

    void operator()(T* p) {
        delete p;
    }
};

template <class T>
class NCDeleter<T[]> {
    int state_;
    NCDeleter(NCDeleter const&);
    NCDeleter& operator=(NCDeleter const&);

public:
    NCDeleter() : state_(0) {
    }
    explicit NCDeleter(int s) : state_(s) {
    }
    ~NCDeleter() {
        assert(state_ >= 0);
        state_ = -1;
    }

    int state() const {
        return state_;
    }
    void set_state(int i) {
        state_ = i;
    }

    void operator()(T* p) {
        delete[] p;
    }
};

// Non-copyable deleter
template <class T>
class NCConstDeleter {
    int state_;
    NCConstDeleter(NCConstDeleter const&);
    NCConstDeleter& operator=(NCConstDeleter const&);

public:
    NCConstDeleter() : state_(0) {
    }
    explicit NCConstDeleter(int s) : state_(s) {
    }
    ~NCConstDeleter() {
        assert(state_ >= 0);
        state_ = -1;
    }

    int state() const {
        return state_;
    }
    void set_state(int i) {
        state_ = i;
    }

    void operator()(T* p) const {
        delete p;
    }
};

template <class T>
class NCConstDeleter<T[]> {
    int state_;
    NCConstDeleter(NCConstDeleter const&);
    NCConstDeleter& operator=(NCConstDeleter const&);

public:
    NCConstDeleter() : state_(0) {
    }
    explicit NCConstDeleter(int s) : state_(s) {
    }
    ~NCConstDeleter() {
        assert(state_ >= 0);
        state_ = -1;
    }

    int state() const {
        return state_;
    }
    void set_state(int i) {
        state_ = i;
    }

    void operator()(T* p) const {
        delete[] p;
    }
};

// Non-copyable deleter
template <class T>
class CopyDeleter {
    int state_;

public:
    CopyDeleter() : state_(0) {
    }
    explicit CopyDeleter(int s) : state_(s) {
    }
    ~CopyDeleter() {
        assert(state_ >= 0);
        state_ = -1;
    }

    CopyDeleter(CopyDeleter const& other) : state_(other.state_) {
    }
    CopyDeleter& operator=(CopyDeleter const& other) {
        state_ = other.state_;
        return *this;
    }

    int state() const {
        return state_;
    }
    void set_state(int i) {
        state_ = i;
    }

    void operator()(T* p) {
        delete p;
    }
};

template <class T>
class CopyDeleter<T[]> {
    int state_;

public:
    CopyDeleter() : state_(0) {
    }
    explicit CopyDeleter(int s) : state_(s) {
    }
    ~CopyDeleter() {
        assert(state_ >= 0);
        state_ = -1;
    }

    CopyDeleter(CopyDeleter const& other) : state_(other.state_) {
    }
    CopyDeleter& operator=(CopyDeleter const& other) {
        state_ = other.state_;
        return *this;
    }

    int state() const {
        return state_;
    }
    void set_state(int i) {
        state_ = i;
    }

    void operator()(T* p) {
        delete[] p;
    }
};

struct test_deleter_base {
    static int count;
    static int dealloc_count;
};

int test_deleter_base::count = 0;
int test_deleter_base::dealloc_count = 0;

template <class T>
class test_deleter : public test_deleter_base {
    int state_;

public:
    test_deleter() : state_(0) {
        ++count;
    }
    explicit test_deleter(int s) : state_(s) {
        ++count;
    }
    test_deleter(const test_deleter& d) : state_(d.state_) {
        ++count;
    }
    ~test_deleter() {
        assert(state_ >= 0);
        --count;
        state_ = -1;
    }

    int state() const {
        return state_;
    }
    void set_state(int i) {
        state_ = i;
    }

    void operator()(T* p) {
        assert(state_ >= 0);
        ++dealloc_count;
        delete p;
    }
    test_deleter* operator&() const = delete;
};

template <class T>
void swap(test_deleter<T>& x, test_deleter<T>& y) {
    test_deleter<T> t(std::move(x));
    x = std::move(y);
    y = std::move(t);
}

struct DeleterCheckConst {
    DeleterCheckConst() {
    }

    void operator()(void*) const {
    }

    int test() {
        return 5;
    }
    int test() const {
        return 6;
    }
};

struct CheckVoidPtrDeleter {
    void operator()(void* ptr) {
        free(ptr);
    }
};

template <typename T>
struct CheckArrayDeleter {
    void operator()(T* ptr) {
        delete[] ptr;
    }
};

template <typename T>
struct CheckArrayDeleterStateful {
    int some_useless_field;

    void operator()(T* ptr) {
        delete[] ptr;
        ++some_useless_field;
    }
};

template <typename T>
void DeleteFunction(T* ptr) {
    delete ptr;
}
