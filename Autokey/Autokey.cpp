#include <iostream>
using namespace std;
void Autokey(char p[],char key[],int v);
int main()
{
	char p[100],key[20];
	cin>>p;
	cin>>key;
	Autokey(p,key,2);
	return 0;
}
void Autokey(char p[],char key[],int v)
{
	int i=0,j=0,P_len=strlen(p),k_len=strlen(key);
	char key_use[100];
	//---------------------Vigenere ��---------------------
	char a[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	char table[26][26];
	for(i=0;i<26;i++)
	{
		for(j=0;j<26;j++)
			table[i][j]=a[(i+j)%26];
	}
	//------------------------------------------
	if(v==1)
	{
		for(i=0;i<k_len;i++)
			key_use[i]=key[i];
		for(i=0;i<P_len-k_len;i++)
			key_use[i+k_len]=p[i];
		key_use[i+k_len]='\0';
		i=0;
		//---------------------����---------------------
		while(i!=P_len)
		{
			cout<<table[(int)key_use[i]-97][(int)p[i]-97];					//����Vigenere ��
			i++;
		}
		cout<<endl;	
	}
	else if(v==2)//---------------------����---------------------
	{
		for(i=0;i<k_len;i++)
			key_use[i]=key[i];
		i=0;
		j=0;
		while(j!=P_len)
		{
			if(p[j]==table[(int)key_use[j]-97][i])							//����Vigenere �������
			{
				cout<<table[0][i];
				key_use[k_len++]=table[0][i];
				j++;
				i=0;
			}
			else
				i++;
		}
		cout<<endl;
	}
}
