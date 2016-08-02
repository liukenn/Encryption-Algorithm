#include<iostream>
#include<String>
using namespace std;

int main()
{
	int i,j,v=-1,P_len;
	char Plaintext[100];
	char Ciphertext[100];
	string key;
	//---------------------Vigenere ��---------------------
	char a[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	char table[26][26];
	for(i=0;i<26;i++)
	{
		for(j=0;j<26;j++)
			table[i][j]=a[(i+j)%26];
	}
//	cout<<endl<<endl<<"	---------------��ӭʹ��Vigenere�ӽ���ϵͳ---------------"<<endl<<endl;
	while(v!=0)
	{
		if(v!=-1)
			cout<<"�����������:��"<<endl;
		fflush(stdin);
		getchar();
		system ("cls");
		cout<<endl<<endl<<"	---------------ʹ��Vigenere��������1---------------"<<endl;
		cout<<"	---------------ʹ��Vigenere��������2---------------"<<endl;
		cout<<"	---------------�˳���������0        ---------------"<<endl<<"	";
		cin>>v;
		while(v!=0&&v!=1&&v!=2)
		{
			cout<<"��������������룺";
			cin>>v;
		}
		if(v==1)
		{
			cout<<"����plaintext��"<<endl;
			cin>>Plaintext;
			P_len=strlen(Plaintext);
			cout<<"����key��"<<endl;
			cin>>key;
			cout<<endl<<"������ciphertext��"<<endl;
			i=0;
			//---------------------����---------------------
			while(i!=P_len)
			{
				cout<<table[(int)key[i%key.size()]-97][(int)Plaintext[i]-97];					//����Vigenere ��
				Ciphertext[i]=table[(int)key[i%key.size()]-97][(int)Plaintext[i]-97];
				i++;
			}
			cout<<endl;
		}
		else if(v==2)
		{
			cout<<"����Ciphertext��"<<endl;
			cin>>Ciphertext;
			P_len=strlen(Ciphertext);
			cout<<"����key��"<<endl;
			cin>>key;
			cout<<endl<<"������plaintext��"<<endl;
			i=0;
			j=0;
			//---------------------Vigenere ��---------------------
			while(j!=P_len)
			{
				if(Ciphertext[j]==table[(int)key[j%key.size()]-97][i])							//����Vigenere �������
				{
					cout<<table[0][i];
					j++;
					i=0;
				}
				else
					i++;
			}
			cout<<endl;
		}
		cout<<endl;
		cout<<endl;
	}
	cout<<"��ӭʹ��:��"<<endl;
	return 0;
}