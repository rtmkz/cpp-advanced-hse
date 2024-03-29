template<bool f, int a, int b>
struct Condition {
    static const int value = a;
};
template<int a, int b>
struct Condition<false, a, b> {
    static const int value = b;
};

template<int N, int l, int r>
struct Bs {
    static const long long int mid = (l + r) / 2;
    static const int nextL = Condition<(mid * mid < N), mid + 1, l>::value;
    static const int nextR = Condition<(mid * mid < N), r, mid>::value;
    static const int value = Bs<N, nextL, nextR>::value;
};

template<int N, int l>
struct Bs<N, l, l> {
    static const int value = l;
};

template<int N>
struct Sqrt {
    static const int value = Bs<N, 1, N>::value;
};
