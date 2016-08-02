#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Permutation_en(char *plaintext,char *key);
void Permutation_de(char *ciphertext,char *key);

int main()
{

    char key[100];
    char plaintext[100];
    char ciphertext[100];
    int choose;
    printf("permutation �����㷨��\n");
    printf("��ѡ��1������ 2������\n");
    scanf("%d",&choose);
    if(choose==1)
    {
        printf("��������Կ��");
        scanf("%s",key);
        printf("���������ģ�");
        scanf("%s",plaintext);
        Permutation_en(plaintext,key);
    }
    else if(choose==2)
    {
        printf("���������ģ�");
        scanf("%s",ciphertext);
        printf("��������Կ��");
        scanf("%s",key);
        Permutation_de(ciphertext,key);
    }
    else
        printf("����������ѡ��\n");

    return 0;
}

void Permutation_en(char *plaintext,char *key)
{

    int length,len,i,j,n;
    int num[10];
    char plaintextfinish[1000];
    char table[100][100];
    char table2[100][100];
    length=strlen(key);
    for(i=0;i<length;i++)
    {
        num[i]=1;   //��num[]��ֵΪ1
        for(j=0;j<length;j++)
        {
            if(key[j]<key[i])
            {
                num[i]++;
            }//��key[i]��key�������ַ��Ƚϣ��б�key[i]С��num[i]��+1
        }
        for(j=0;j<i;j++)
        {	if(key[j] == key[i])
                num[i]=num[i]+1;
        }	//����ͬ�ַ����ͰѺ����ַ�λ�õ�k[i]+1
    }
    int length_pl=strlen(plaintext);//���ĳ���
    int re=length_pl%length;        //��Ҫ���ϵĳ���
	int row;
	if(re!=0)
		row=((length_pl-re)/length+1);//����
	else
		row=length_pl/length;//����
    //���Ʋ���
    for(i=0;i<length_pl;i++)
    {
        plaintextfinish[i]=plaintext[i];
    }
    //�����ĳ��Ȳ�����Կ���ȵ�������������Ч�ַ�����
    if(re!=0)
    {
        for(i=0;i<(length-re);i++)
        {
            plaintextfinish[length_pl]='q';//����Ч�ַ���ȫ����
            length_pl++;//���ĳ���+1
        }
    }
    //ת��Ϊ��ά����
    for(i=0;i<row;i++)
    {
        for(j=0;j<length;j++)
        {
            len=i*length+j;
            table[i][j]=plaintextfinish[len];
        }
    }
    for(i=0;i<=length;i++)
    {
        for(j=0;j<length;j++)
        {
            if(num[j]==i+1)
            {
                for(n=0;n<len;n++)
                {
                    table2[n][i]=table[n][j];
                }
            }
        }
    }
    printf("����Ϊ:\n");
	for(i=0;i<row;i++)
	{
		for(j=0;j<length;j++)
		{
			printf("%c",table2[i][j]);
		}
	}
	printf("\n");
}
void Permutation_de(char *ciphertext,char *key)
{
    int i,j;
    int num[10];
    char table[100][100];
    char table2[100][100];
    int length=0;
    int length_ci;
    length=strlen(key);
    for(i=0;i<length;i++)
    {
        num[i]=1;   //��num[]��ֵΪ1
        for(j=0;j<length;j++)
        {
            if(key[j]<key[i])
            {
                num[i]++;
            }//��key[i]��key�������ַ��Ƚϣ��б�key[i]С��num[i]��+1
        }
        for(j=0;j<i;j++)
        {	if(key[j] == key[i])
                num[i]=num[i]+1;
        }
    }
    length_ci=strlen(ciphertext);//���ĳ���
    int row=length_ci/length;  //����
    for(i=0;i<length;i++)
    {
        for(j=0;j<row;j++)
        {
            table[j][i]=ciphertext[j*length+i];
        }
    }
    for(i=0;i<row;i++)
    {
        for(j=0;j<length;j++)
        {
            table2[i][j]=table[i][num[j]-1];
        }
    }
    printf("����Ϊ:\n");
    for(i=0;i<row;i++)
    {
        for(j=0;j<length;j++)
        {
                printf("%c",table2[i][j]);
        }
    }
}




