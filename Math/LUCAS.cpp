void prework(int p)
{
	fac[0] = 1;
	for(int i = 1; i < p; i++)
		fac[i] = fac[i - 1] * i % p;
		
	inv[p - 1] = powermod(fac[p - 1], p - 2, p);
	for(int i = p - 2; i >= 0; i--)
		inv[i] = inv[i + 1] * (i + 1) % p;
	assert(inv[0] == 1);
}
LL lucas(LL x,LL y,LL p)
{
	if(!(y >= 0 && y <= x)) return 0;
	
	if(x < p) return fac[x] * inv[y] % p * inv[x - y] % p;
	
	return lucas(x % p, y % p, p) * lucas(x / p, y / p, p) % p;
}
