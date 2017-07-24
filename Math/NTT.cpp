void PreWork()
{
    while(N <= (n << 1)) N <<= 1;

    invN = power(N, Mod - 2);

    g[0] = g[N] = 1, g[1] = power(G, (Mod - 1) / N); 
    for(int i = 2; i < N; i++)
        g[i] = g[i-1] * g[1] % Mod;

}
void NTT(long long a[],int len,int flag)
{
    for(int i = 0; i < len; i++)
    {
        int s = i, p = 0;
    
        for(int j = len >> 1; j > 0; j >>= 1)
            p |= (s & 1) * j, s >>= 1;
    
        if(p > i) std::swap(a[p], a[i]);
    }
    
    for(int L = 2 ; L <= len; L <<= 1)
        for(int i = 0; i < len ; i += L)
            for(int j = 0; j < (L>>1); j++)
            {
                long long w = (flag == 1 ? g[N / L * j] : g[N - N / L * j]);
                long long u = a[i + j], v = a[i + j + (L >> 1)] * w % Mod;
    
                u += v, v = u - (v << 1), a[i + j] = u % Mod;
                a[i + j + (L >> 1)] = (v + Mod) % Mod;
            }

    if(flag == -1)
    {
        for(int i = 0; i < len; i++)
            a[i] = a[i] * invN % Mod;
    }
}
