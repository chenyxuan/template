
void FFT(complex *X,int n,int flag)
{
	for(int i = 0; i < n; i++)
	{
		int p = 0, t = i;
		
		for(int j = 1; j < n; j <<= 1)
			p <<= 1, p |= t & 1, t >>= 1;
		
		if(i < p) std::swap(X[i], X[p]);
	}
	
	for(int m = 2; m <= n; m <<= 1)
	{
		complex wm = complex(cos((double) 2 * pi * flag / m), sin((double) 2 * pi * flag / m));
	
		for(int i = 0; i < n; i += m)
		{ 
			complex wk = complex(1, 0);
			 
			for(int j = 0; j < (m >> 1); wk = wk * wm, j++)
			{
			    complex u = X[i + j], t = wk * X[i + j + (m >> 1)];
			    X[i + j] = u + t, X[i + j + (m >> 1)] = u - t;
			}
		}
	}

	if(flag == -1) for(int i = 0; i < n; i++) X[i] = X[i] / n;
}
