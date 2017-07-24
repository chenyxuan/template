void getNext(char *s,int len)
{
	next[0] = next[1] = 0;
	
	for(int i = 2; i <= len; i++)
	{
		int j = next[i - 1];
		
		while(j && s[i] != s[j + 1]) j = next[j];
		
		if(s[i] == s[j + 1]) j++;
		next[i] = j;
	}
}
int solve(char *s,int len,char *t,int tlen)
{
	int p = 0;
	int res = 0;
	
	for(int i = 1; i <= len; i++)
	{
		while(p && s[i] != t[p + 1]) p = next[p];
		
		if(s[i] == t[p + 1]) p++;
		
		if(p == tlen) res++, p = next[p];
	}
	
	return res;
}
