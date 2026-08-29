#include <bits/stdc++.h>

inline namespace IO {
#define SFINAE(x, ...)                                                         \
    template <class, class = void> struct x : std::false_type {};              \
    template <class T> struct x<T, std::void_t<__VA_ARGS__>> : std::true_type {}

SFINAE(DefaultI, decltype(std::cin >> std::declval<T &>()));
SFINAE(DefaultO, decltype(std::cout << std::declval<T &>()));
SFINAE(IsTuple, typename std::tuple_size<T>::type);
SFINAE(Iterable, decltype(std::begin(std::declval<T>())));

template <class T> inline constexpr bool always_false = false;

template <auto &os, bool debug, bool print_nd> struct Writer {
    std::string comma() const { return debug ? "," : ""; }

    template <class T> constexpr char Space(const T &) const {
        return print_nd && (Iterable<T>::value || IsTuple<T>::value) ? '\n'
                                                                     : ' ';
    }

    template <class T> void Impl(T const &t) const {
        if constexpr (DefaultO<T>::value) {
            os << t;
        } else if constexpr (Iterable<T>::value) {
            if (debug) os << '{';
            int i = 0;
            for (auto &&x : t) {
                if (i++) os << comma() << Space(x);
                Impl(x);
            }
            if (debug) os << '}';
        } else if constexpr (IsTuple<T>::value) {
            if (debug) os << '(';
            std::apply(
                [this](auto const &...args) {
                    int i = 0;
                    (((i++ ? (os << comma() << " ") : os), Impl(args)), ...);
                },
                t);
            if (debug) os << ')';
        } else {
            static_assert(always_false<T>, "No matching print operator for this type!");
        }
    }

    template <class T> void ImplWrapper(T const &t) const {
        if (debug) os << "\033[0;31m";
        Impl(t);
        if (debug) os << "\033[0m";
    }

    template <class... Ts> void print(Ts const &...ts) const {
        ((Impl(ts)), ...);
    }

    template <class F, class... Ts>
    void print_with_sep(const std::string &sep, F const &f,
                        Ts const &...ts) const {
        ImplWrapper(f);
        ((os << sep, ImplWrapper(ts)), ...);
        os << '\n';
    }

    void print_with_sep(const std::string &) const { os << '\n'; }
};
}  // namespace IO

inline namespace DBG {
template <typename... Args> void err(Args... args) {
    Writer<std::cerr, true, false>{}.print_with_sep(" | ", args...);
}

template <typename... Args> void errn(Args... args) {
    Writer<std::cerr, true, true>{}.print_with_sep(" | ", args...);
}

void err_prefix(std::string func, int line, std::string args) {
    std::cerr << "\033[0;31m\u001b[1mDEBUG\033[0m"
              << " | "
              << "\u001b[34m" << func << "\033[0m"
              << ":"
              << "\u001b[34m" << line << "\033[0m"
              << " - "
              << "[" << args << "] = ";
}

#ifndef ONLINE_JUDGE
#define dbg(args...) err_prefix(__FUNCTION__, __LINE__, #args), err(args)
#define dbgn(args...) err_prefix(__FUNCTION__, __LINE__, #args), errn(args)
#else
#define dbg(...)
#define dbgn(...)
#endif
}  // namespace Debug
