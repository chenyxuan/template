void build_sa(int m)
{
	static int cur[maxn], t0[maxn], t1[maxn];
	int *x = t0, *y = t1;
	
	for(int i = 1; i <= m; i++) cur[i] = 0;
	for(int i = 1; i <= n; i++) cur[x[i] = s[i]]++;
	for(int i = 1; i <= m; i++) cur[i] += cur[i - 1];
	for(int i = n; i >= 1; i--) sa[cur[x[i]]--] = i;
	
	for(int k = 1; k <= n; k<<=1)
	{
		int p = 0;
		
		for(int i = n - k + 1; i <= n; i++) y[++p] = i;
		for(int i = 1; i <= n; i++)
			if(sa[i] > k) y[++p] = sa[i] - k;
		
		for(int i = 1; i <= m; i++) cur[i] = 0;
		for(int i = 1; i <= n; i++) cur[x[y[i]]]++;
		for(int i = 1; i <= m; i++) cur[i] += cur[i - 1];
		for(int i = n; i >= 1; i--) sa[cur[x[y[i]]]--] = y[i];
		
		std::swap(x, y);
		
		x[sa[1]] = 1;
		p = 1;
		
		for(int i = 2; i <= n; i++)
		{
			x[sa[i]] = ++p;
			
			if(sa[i] + k <= n && sa[i - 1] + k <= n)
				if(y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k])
				{
					x[sa[i]] = --p;
				}
		}

		m = p;
	}
}
void build_height()
{
	int k = 0;
	
	for(int i = 1; i <= n; i++) rank[sa[i]] = i;
	for(int i = 1; i <= n; i++)
	{
		if(k != 0) k--;
		
		if(rank[i] == 1) continue;
		
		int j = sa[rank[i] - 1];
		while(s[j + k] == s[i + k]) k++;
		height[rank[i]] = k;
	}
}
