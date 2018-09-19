#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int sigma_size=26;

struct Node{
    Node *L,*R;
    char ch;
    int flag;
    Node(){
        L=R=NULL;
        ch=flag=0;
    }
};

Node *root;

void Init()
{
    root=new Node();
}

void Insert(char *s)
{
    int len=strlen(s);
    Node *now=root;

    for(int i=0;i<len;i++)
    {
    	Node *j,*pre;
    	if(now->L==NULL)
    	{
    		now->L=new Node();
        	now->L->ch=s[i];
		}
        for(j=now->L;j;j=j->R)
        {
        	pre=j;
			if(j->ch==s[i])
        		break;
		}
        if(pre->ch!=s[i])
        {
        	pre->R=new Node();
        	pre->R->ch=s[i];
        	j=pre->R;
        }
        now=j;
        now->flag++;
    }
}

int Query(char *s)
{
    int len=strlen(s);
    Node *now=root;

    for(int i=0;i<len;i++)
    {
		Node *j;
        for(j=now->L;j;j=j->R)
        	if(j->ch==s[i])
        		break;
        if(j==NULL)
            return 0;
        now=j;
    }
    return now->flag;
}

int main()
{
    char s[20];
    Init();
    while(gets(s),strcmp(s,""))
        Insert(s);
    while(gets(s)!=NULL)
        printf("%d\n",Query(s));
    return 0;
}
