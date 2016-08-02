#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/* λ�ýṹ����¼��ĸ��Key matrix�е�λ�� */
#define NUM_OF_LETTERS 26
#define MAX_BUFF 1024
#define ch2id(ch) ((ch) - 'A') /* id����ĸ��A..Z�е�λ��(��ĸAΪ0) */
#define id2ch(id) ((id) + 'A') /* id��Ӧ����ĸ */

typedef struct tag_Position
{
  int x;
  int y;
} Position;
typedef char CharPair[2];

typedef struct tag_KeyMatrix
{
  Position auxMap[NUM_OF_LETTERS]; /* ��ĸ��λ�õĸ���ӳ��� */
  char letters[5][5];
} KeyMatrix;
void getKeyMatrix(char* key, KeyMatrix* m);
void setPair(char ch1, char ch2, CharPair pair);
/* ���ַ���p�л�ȡ1����ĸ(��������ĸQ���ظ���һ����ĸʱ������X)
 * ���ػ����ĸ���λ�ã�����NULL���ʾȫ����� */
char* getPairFromString(char* p, CharPair pair);
/* ת����ĸ�ԣ�d=1��ʾ������ת�����룬d=-1��ʾ������ת������ */
void getTransformPair(KeyMatrix* m, CharPair in, CharPair out, int d);
void encrypt(KeyMatrix* m, char* in, char* out, int len);
void decrypt(KeyMatrix* m, char* in, char* out, int len);
char *Playfair(char *plaintext,char *key,int count);


int main()
{
    int choose;
    char plaintext[100];
    char ciphertext[100];
    char key[100];
    printf("��ѡ��1������ 2������\n");
    scanf("%d",&choose);
    if(choose==1)
    {
        printf("��������Կ��");
        scanf("%s",key);
        printf("������Ҫ���ܵ����ģ�");
        scanf("%s",plaintext);
        Playfair(plaintext,key,1);
    }

    else if(choose==2)
    {
        printf("��������Կ��");
        scanf("%s",key);
        printf("������Ҫ���ܵ����ģ�");
        scanf("%s",ciphertext);
        Playfair(ciphertext,key,2);
    }
    else
        printf("������ѡ��");

}

/* ��ĸletter��Ӧ��λ�� */
Position* positionOfLetter(KeyMatrix* m, char letter)
{
  return &m->auxMap[ch2id(letter)];
}
/* ��¼letter��Ӧ��λ�� */
void setPosition(KeyMatrix* m, char letter, int x, int y)
{
  Position* p = positionOfLetter(m, letter);
  m->letters[y][x] = letter;
  p->x = x;
  p->y = y;
}
/* ����key����Key matrix */
void getKeyMatrix(char* key, KeyMatrix* m)
{
  int usedChars[NUM_OF_LETTERS]; /* ��¼�Ѿ�ʹ�ù�����ĸ */
  int i = 0, k,j;
  char upch;
  memset(usedChars, 0, sizeof(usedChars));
  /* ��key�еĳ�Q�����ĸ���ظ�����Key matrix */
  for (j=0;key[j]!='\0';j++)
  {
    upch = toupper(key[j]);
    if(isalpha(key[j]) && upch != 'J' && !usedChars[upch - 'A'])
    {
      usedChars[ch2id(upch)] = 1;
      setPosition(m, upch, i%5, i/5);
      i++;
    }
  }
  /* ��û��ʹ�õ���ĸ˳������ʣ�µ�λ�� */
  for(k=0; k<NUM_OF_LETTERS; k++)
  {
    if (usedChars[k] == 0 && id2ch(k) != 'J')
    {
      setPosition(m, id2ch(k), i%5, i/5);
      i++;
    }
  }
}
/* ȡ��Key matrix��x��y�е���ĸ */
char getLetter(KeyMatrix* m, int x, int y)
{
  return m->letters[y%5][x%5];
}
/* ��ĸ�� */

/* ���� */
void encrypt(KeyMatrix* m, char* in, char* out, int len)
{
  char* p = in;
  int i = 0;
  CharPair pair={0, 0}, replacedPair;

  while ( (p = getPairFromString(p, pair)) != 0 )
  {
    if (i+2 > len)
      break;
    getTransformPair(m, pair, replacedPair, 1);
    out[i]   = replacedPair[0];
    out[i+1] = replacedPair[1];
    i+=2;
  }
  out[i] = '\0';
  for(i=0;i<strlen(out);i++)
  {
      printf("%c",out[i]);
  }
}
/* ���� */
void decrypt(KeyMatrix* m, char* in, char* out, int len)
{
  int i = 0;
  CharPair pair, replacedPair;

  while ( in[i] != 0 )
  {
    if (i+2 > len)
      break;
    pair[0] = in[i];
    pair[1] = in[i+1];

    pair[0]=toupper(pair[0]);
    pair[1]=toupper(pair[1]);

    getTransformPair(m, pair, replacedPair, -1);
    out[i]   = replacedPair[0];
    out[i+1] = replacedPair[1];
    i+=2;
  }
  out[i] = '\0';
  for(i=0;i<strlen(out);i++)
  {
      printf("%c",out[i]);
  }
}
void setPair(char ch1, char ch2, CharPair pair)
{
  pair[0] = ch1;
  pair[1] = ch2;
}
/* ���������ܵķ���ĸ�ַ�����ĸQ */
char* skipNocrypt(char* p)
{

  while (*p != '\0' && (!isalpha(*p) || *p == 'J' || *p == 'j'))
    *p='I';
  return p;
}
char* getPairFromString(char* p, CharPair pair)
{
  char upch1, upch2;
  if (*p == '\0')
    return NULL;

  p = skipNocrypt(p);
  upch1 = toupper(*p);
  if (pair[1] == upch1) /* �ϴλ�õ����һ����ĸ(pair[1])����͵�һ��ĸ��ͬ������X�ָ� */
  {
    upch2 = upch1;
    upch1 = 'X';
  }
  else
  {
    char* q = skipNocrypt(p+1);
    upch2 = toupper(*q);
    if (upch1 == upch2 || upch2 == '\0') /* ������ĸ��ͬ�򵥳�һ����ĸ������X */
      upch2 = 'X';
    else
      p = q; /* ���������ĸ����ȡ�ˣ�ָ��pָ���һ����ĸ */
  }
  setPair(upch1, upch2, pair);
  return p+1;
}
void getTransformPair(KeyMatrix* m, CharPair in, CharPair out, int d)
{
  Position* p0 = positionOfLetter(m, in[0]);
  Position* p1 = positionOfLetter(m, in[1]);
  out[0] = in[0];
  out[1] = in[1];
  if (p0->x == p1->x) /* ������ĸ��ͬһ�У�ת��Ϊͬ�е�ƫ��d����ĸ */
    setPair(
      getLetter(m, p0->x, p0->y+d),
      getLetter(m, p1->x, p1->y+d),
      out
    );
  else if (p0->y == p1->y) /* ��ͬһ�У�ת��Ϊͬ�е�ƫ��d����ĸ */
    setPair(
      getLetter(m, p0->x+d, p0->y),
      getLetter(m, p1->x+d, p1->y),
      out
    );
  else /* ��ͬ�в�ͬ�У�ת������������ͬ�������꽻���ĺ����ĸ�� */
    setPair(
      getLetter(m, p1->x, p0->y),
      getLetter(m, p0->x, p1->y),
      out
    );
}
char *Playfair(char *plaintext,char *key,int count)
{
    int i,j;
    KeyMatrix m;
	char encryptBuff[MAX_BUFF], decryptBuff[MAX_BUFF];
	getKeyMatrix(key, &m);
	printf("���ɵ�m����Ϊ��\n");
	for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            printf("%c",m.letters[i][j]);
        }
        printf("\n");
    }
	switch(count)
	{
	case 1:
		encrypt(&m, plaintext, encryptBuff, MAX_BUFF);

		return encryptBuff;
	case 2:
		decrypt(&m, plaintext, decryptBuff, MAX_BUFF);
		return decryptBuff;
	default:
		return NULL;
	}
}


