#include<iostream>
#include<String>
using namespace std;
char Plaintext[100];
char Ciphertext[100];
int main()
{
	int i=0,j=0,key_numble[20]={0},len,len_P,m,n,x=0,k,v=-1;
	string key;
	cout<<endl<<endl<<"	---------------��ӭʹ��Column permutation�ӽ���ϵͳ---------------"<<endl<<endl;
	while(v!=0)
	{
		if(v!=-1)
			cout<<endl<<endl<<"�����������:��"<<endl;
		fflush(stdin);
		getchar();
		system ("cls");
		cout<<endl<<endl<<"	---------------ʹ��Column permutation��������1---------------"<<endl;
		cout<<"	---------------ʹ��Column permutation��������2---------------"<<endl;
		cout<<"	---------------       �˳���������0           ---------------"<<endl<<"	";
		cin>>v;
		while(v!=0&&v!=1&&v!=2)
		{
			cout<<"��������������룺";
			cin>>v;
		}
		if(v==1||v==2)
		{
			cout<<"����keyword��"<<endl;
			cin>>key;
			len=key.size();
			for(i=0;i<len;i++)												//key��ĸ˳��
			{
				key_numble[i]=1;
				for(j=0;j<len;j++)
					if(key[i]>key[j])
						key_numble[i]++;
			}
			for(i=0;i<len;i++)												//key�������ͬ��ĸ
			{
				for(j=i+1;j<len;j++)
						if(key[i]==key[j])
							key_numble[j]++;
			}
		}
		if(v==1)
		{
			cout<<"����Plaintext��"<<endl;
			cin>>Plaintext;
			len_P=strlen(Plaintext);
			m=len_P/len;
			n=len_P%len;
			if(n!=0)														//�����ַ���������"x"���
			{
				m++;
				for(i=0;i<len-n;i++)
					Plaintext[len_P++]='x';
			}
			//---------Column permutation encryption���Ĵ���---------
			for(i=0;i<len;i++)
			{
				k=key_numble[i]-1;
				for(j=0;j<m;j++)
					Ciphertext[x++]=Plaintext[j*len+k];
			}
			cout<<endl<<"keyword˳��Ϊ��";
			for(i=0;i<len;i++)
				cout<<key_numble[i]<<" ";
			cout<<endl<<endl<<"���ܳɹ�������Ϊ��"<<endl<<Ciphertext<<endl;
		}
		else if(v==2)
		{
			cout<<"����Ciphertext��"<<endl;
			cin>>Ciphertext;
			len_P=strlen(Ciphertext);
			m=len_P/len;
			n=len_P%len;
			if(n!=0)														//�����ַ���������"x"���
			{
				m++;
				for(i=0;i<len-n;i++)
					Ciphertext[len_P++]='x';
			}
			//---------����---------
			x=0;
			for(i=0;i<len;i++)
			{
				k=key_numble[i]-1;
				for(j=0;j<m;j++)
					Plaintext[j*len+k]=Ciphertext[x++];
			}
			cout<<endl<<"keyword˳��Ϊ��";
			for(i=0;i<len;i++)
				cout<<key_numble[i]<<" ";
			cout<<endl<<endl<<"���ܳɹ�������Ϊ��"<<endl<<Plaintext<<endl;
		}
	}
	cout<<endl<<endl<<"��ӭʹ��:��"<<endl;
	return 0;
}
