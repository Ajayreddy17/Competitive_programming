// long でも大丈夫
// (val * x - 1) が mod の倍数になるようにする
// 特に mod=0 なら x=0 が満たす
long long mod_inv(long long val, long long mod) {
    if (mod == 0) return 0;
    mod = abs(mod);
    val %= mod;
    if (val < 0) val += mod;
    long long a = val, b = mod, u = 1, v = 0, t;
    while (b > 0) {
        t = a / b;
        swap(a -= t * b, b), swap(u -= t * v, v);
    }
    if (u < 0) u += mod;
    return u;
}
