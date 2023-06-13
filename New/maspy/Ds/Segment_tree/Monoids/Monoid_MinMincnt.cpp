// Minimum value, number of minimum values
template <typename E>
struct Monoid_MinMincnt {
    using value_type = pair<E, E>;
    using X = value_type;
    static X op(X x, X y) {
        auto [xmin, xmincnt] = x;
        auto [ymin, ymincnt] = y;
        if (xmin > ymin) return y;
        if (xmin < ymin) return x;
        return {xmin, xmincnt + ymincnt};
    }
    static constexpr X unit() { return {inf<E>, 0}; }
    static constexpr bool commute = true;
};
