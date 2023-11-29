//https://habr.com/ru/post/521058/
#include <coroutine>
#include <memory>
#include <iostream>
//#include <optional>

template <typename T>
struct Generator {
public:
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;
public:
    Generator(handle_type h) : coro(h) {}                       // (3)
    ~Generator() {
        if (coro) {
            coro.destroy();
        }
    }
public:
    Generator(const Generator&) = delete;
    Generator& operator=(const Generator&) = delete;
    Generator(Generator&& other) : coro(other.coro) {
        other.coro = nullptr;
    }
    Generator& operator=(Generator&& other) {
        coro = other.coro;
        other.coro = nullptr;
        return *this;
    }
public:
    handle_type coro;
    std::shared_ptr<T> value;
public:
    T getValue() {
        return coro.promise().current_value;
    }
    bool next() {                                               // (5)
        coro.resume();
        return not coro.done();
    }
    T nextValue() {
        next();
        return getValue();
    }

    struct promise_type {
        promise_type() = default;                               // (1)
        ~promise_type() = default;
        auto initial_suspend() {                                // (4)
            return std::suspend_always{};
        }
        auto final_suspend() noexcept {
            return std::suspend_always{};
        }
        auto get_return_object() {                              // (2)
            return Generator{ handle_type::from_promise(*this) };
        }
        auto return_void() {
            return std::suspend_never{};
        }
        auto yield_value(T value) {                             // (6)
            current_value = value;
            return std::suspend_always{};
        }
        void unhandled_exception() {
            std::exit(1);
        }
        T current_value;
    };
};

