
struct Node
{
	int go[size], suf;
	int len, num;

} Ma[maxn];

int ind, last, n;
char s[maxn];

bool check(int p,int l)
{
	return p - l - 1 > 0 && s[p - l - 1] == s[p];
}
void insert(int pos)
{
	int c = s[pos] - 'a';
	int cur = last;
	
	while(!check(pos, Ma[cur].len)) cur = Ma[cur].suf;
	
	if(!Ma[cur].go[c])
	{
		Ma[++ind].len = Ma[cur].len + 2;
		
		if(Ma[ind].len == 1) Ma[ind].suf = 2;
		else
		{
			int fi = Ma[cur].suf;
		
			while(!check(pos, Ma[fi].len)) fi = Ma[fi].suf;
		
			Ma[ind].suf = Ma[fi].go[c];
		}

		Ma[cur].go[c] = ind;
	}
	
	Ma[last = Ma[cur].go[c]].num++;
}
void init()
{
	Ma[1].len = -1, Ma[1].suf = 1;
	Ma[2].len = 0, Ma[2].suf = 1;
	ind = last = 2;
}
