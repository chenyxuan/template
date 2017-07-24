TrieNode *NewNode()
{
    return T + (++tot);
}

void insert(char *t,TrieNode *now)
{
    if(!(*t)) 
    {
        now->end = true;
        return;
    }

    TrieNode *&next = now->p[(*t) - 'A'];

    if(!next) next = NewNode();
    insert(t + 1, next);
}

void init()
{
    read(n), read(m);

    root = NewNode(); 

    for(int i = 1; i <= n; i++)
    {
        scanf("%s",c);
        insert(c, root);
    }
}


void build()
{
    std::queue<TrieNode*>line;

    root->fail = root;

    for(int i = 0; i < size; i++)
        if(root->p[i])
        {
            root->p[i]->fail = root;
            line.push(root->p[i]);
        }
        else
            root->p[i] = root;  

    while(!line.empty())
    {
        TrieNode *x = line.front();
        line.pop();

        for(int i = 0; i < size; i++)
        {
            if(x->p[i])
            {
                x->p[i]->fail = x->fail->p[i];
                line.push(x->p[i]); 
            }
            else
                x->p[i] = x->fail->p[i];
        }

        if(x->fail->end) x->end = true;
    }
}

