#include <iostream>
#include <stdlib.h> 
#include <time.h>
using namespace std;//RSA�㷨������� 
typedef struct  RSA_PARAM_Tag { 
    unsigned __int64    p, q;   //������������������ܽ�������     
	unsigned __int64    f;      //f=(p-1)*(q-1)����������ܽ�������     
	unsigned __int64    n, e;   //���ף�n=p*q��gcd(e,f)=1 
    unsigned __int64    d;      //˽�ף�e*d=1 (mod f)��gcd(n,d)=1 
    unsigned __int64	s;      //�鳤������2^s<=n������s����log2(n) 
} RSA_PARAM;									 
const static long	g_PrimeTable[]= {3,5,7,11,13,17,
	19,23,29,31,37,41,
	43,47,53,59,61,67,71,73,79,83,89,97};		//С������
const static long	g_PrimeCount=sizeof(g_PrimeTable) / sizeof(long);


const unsigned __int64  multiplier=12747293821; 
const unsigned __int64  adder=1343545677842234541;//������� 
class    RandNumber 
{
private: 
    unsigned __int64    randSeed;
public: 
    RandNumber(unsigned __int64 s=0); 
    unsigned __int64    Random(unsigned __int64 n);
};

RandNumber::RandNumber(unsigned __int64 s) 
{ 
    if(!s)
	{ 
        randSeed= (unsigned __int64)time(NULL);
	}
	else
	{ 
        randSeed=s;
	}
} 

unsigned __int64 RandNumber::Random(unsigned __int64 n)
{ 
    randSeed=multiplier * randSeed + adder;
	return randSeed % n; 
}
static RandNumber   g_Rnd;				/* ģ�����㣬����ֵ x=a*b mod n */ 

inline unsigned __int64 MulMod(unsigned __int64 a, 
							   unsigned __int64 b, 
							   unsigned __int64 n)
{ 
    return a * b % n;
}

/* ģ�����㣬����ֵ x=base^pow mod n */ 
unsigned __int64 PowMod(unsigned __int64 &base, 
						unsigned __int64 &pow, 
						unsigned __int64 &n)
{ 
    unsigned __int64    a=base, b=pow, c=1;
	while(b)
	{ 
        while(!(b & 1))
		{ 
            b>>=1;        /*a=a * a % n;    //�������������Դ���64λ��������
							����������a*a��a>=2^32ʱ�Ѿ���������
								���ʵ�ʴ���Χû��64λ*/
			a=MulMod(a, a, n); 
        }
		b--;			//c=a * c % n;  ����Ҳ�����������64λ������Ϊ
						//	����32λ������֪�Ƿ���Խ���������         
		c=MulMod(a, c, n);
	}    
	return c;
}

/* Rabin-Miller�������ԣ�ͨ�����Է���1�����򷵻�0�� n�Ǵ��������� 
ע�⣺ͨ�����Բ���һ������������������ͨ�����Եĸ�����1/4 */ 

long RabinMillerKnl(unsigned __int64 &n)
{ 

//	cout<<"i'm in RabinMillerKnl\n";		//������Ϣ


    unsigned __int64    b, m, j, v, i;
	m=n - 1; 
    j=0;			//0���ȼ����m��j��ʹ��n-1=m*2^j������m����������j�ǷǸ�����
	while(!(m & 1))
	{ 

        ++j;
		m>>=1; 
    }								//1�����ȡһ��b��2<=b<n-1 
    b=2 + g_Rnd.Random(n - 3);    //2������v=b^m mod n
	v=PowMod(b, m, n);				//3�����v==1��ͨ������
	if(v == 1)
	{ 
        return 1;
	}								//4����i=1 
    i=1;					//5�����v=n-1��ͨ������
	while(v != n - 1)
	{ 
							//6�����i==l��������������
		if(i == j)
		{ 
            return 0; 
        }				 //7��v=v^2 mod n��i=i+1
		
		unsigned _int64 squ=2;
		v=PowMod(v, squ, n);		//X����2�Ļ�Ϊ��һ������   
        
		++i;			 //8��ѭ����5
	}

//	cout<<"i'm going out RabinMillerKnl\n";			//������Ϣ


	return 1;
}

/* Rabin-Miller�������ԣ�ѭ�����ú���loop�� ȫ��ͨ������1�����򷵻�0 */ 
long RabinMiller(unsigned __int64 &n, long loop) { 
    //����С����ɸѡһ�Σ����Ч��

//	cout<<"i'm in RabinMiller\n";				//������Ϣ


	for(long i=0; i < g_PrimeCount; i++)
	{ 
        if(n % g_PrimeTable[i] == 0)
		{ 
            return 0;
		} 
    }				//ѭ������Rabin-Miller����loop�Σ�
					//ʹ�÷�����ͨ�����Եĸ��ʽ�Ϊ(1/4)^loop
	for(long i=0; i < loop; i++)
	{ 
        if(!RabinMillerKnl(n))
		{ 
            return 0;
		} 
    }
	return 1;
}

/* �������һ��bitsλ(������λ)�����������32λ */ 
unsigned __int64 RandomPrime(char bits)
{ 

//	cout<<"i'm in RandomPrime\n";				//������Ϣ


    unsigned __int64    base;
	do
	{ 
        base= (unsigned long)1 << (bits - 1);	   //��֤���λ��1 
        
//		cout<<base<<"\t";					//������Ϣ

		base+=g_Rnd.Random(base);			    //�ټ���һ�������
		base|=1;							 //��֤���λ��1������֤������ 
    } while(!RabinMiller(base, 30));    //�������������ղ���30��
	return base;				//ȫ��ͨ����Ϊ������
}

/* ŷ����÷������Լ�� */ 
unsigned __int64 EuclidGcd(unsigned __int64 &p, unsigned __int64 &q)
{ 

//	cout<<"\ni'm in EuclidGcd\n";				//������Ϣ

	unsigned __int64    a=p > q ? p : q;
	unsigned __int64    b=p < q ? p : q;
	unsigned __int64    t;     if(p == q)
	{ 
        return p;   //������ȣ����Լ�����Ǳ���
	}
	else
	{ 
        while(b)    //շת�������gcd(a,b)=gcd(b,a-qb)
		{ 
            a=a % b;
			t=a;
			a=b; 
            b=t; 
        }
		return a;
	}
}



/* ��֪a��b����x������a*x =1 (mod b) �൱�����a*x-b*y=1����С������ */ 
unsigned __int64 Euclid(unsigned __int64 &a, unsigned __int64 &b)
{ 

//	cout<<"i'm in Euclid for \"ni yuan\"\n";				//������Ϣ


	unsigned __int64    m, e, i, j, x, y;
	long                xx, yy;
	m=b;
	e=a;
	x=0;
	y=1;
	xx=1;
	yy=1;
	while(e)
	{ 
        i=m / e;
		j=m % e;
		m=e;
		e=j;
		j=y;
		y*=i; 
        if(xx == yy)
		{ 
            if(x > y)
			{ 
                y=x - y;
			}
			else
			{ 
                y-=x;
				yy=0;
			}
		}
		else
		{ 
            y+=x;
			xx=1 - xx;
			yy=1 - yy;
		}
		x=j;
	}
	if(xx == 0)
	{ 
        x=b - x;
	}
	return x;
}

/* �������һ��RSA���ܲ��� */ 

RSA_PARAM RsaGetParam(void)
{ 

//	cout<<"i'm in RsaGetParam\n";					//������Ϣ


    RSA_PARAM           Rsa={ 0 };
	unsigned __int64    t; 
    Rsa.p=RandomPrime(16);          //���������������
	Rsa.q=RandomPrime(16);

//	cout<<"get two prime p and q\n"<<Rsa.p<<"\t"<<Rsa.q;	//������Ϣ


	Rsa.n=Rsa.p * Rsa.q;
    Rsa.f=(Rsa.p - 1) * (Rsa.q - 1);
	do
	{ 
        Rsa.e=g_Rnd.Random(65536);  //С��2^16��65536=2^16 
        Rsa.e|=1;                   //��֤���λ��1������֤��������
									//��fһ����ż����Ҫ���أ�ֻ�������� 
    } while(EuclidGcd(Rsa.e, Rsa.f) != 1);
	Rsa.d=Euclid(Rsa.e, Rsa.f);
	Rsa.s=0; 
    t=Rsa.n >> 1;
	while(t)
	{ 
        Rsa.s++;                    //s=log2(n)
		t>>=1; 
    }

//	cout<<"i'm going out RsaGetParam\n";					//������Ϣ

	return Rsa;
}

/* ���������ղ��� */ 
void TestRM(void) { 
    unsigned long   k=0; 
    
	cout << " - Rabin-Miller prime check.\n" << endl;		//������Ϣ 
    
	for(unsigned __int64 i=4197900001; i < 4198000000; i+=2)
	{ 
        if(RabinMiller(i, 30))
		{ 
            k++; 
            cout << i << endl;
		} 
    }
	
	cout << "Total: " << k << endl;						//������Ϣ

}

/* RSA���ܽ��� */ 
void TestRSA(void) { 

//	cout<<"i'm in TestRSA\n";						//������Ϣ
    
	RSA_PARAM           r;
	
	cout<<"���������ģ�\n";						//������Ϣ
    
	char                pSrc[100];

	scanf("%s",pSrc);

	const unsigned long n=strlen(pSrc);		//X��ԭ����sizeof��pSrc��

	cout<<"���ĵĳ���Ϊ��"<<n<<endl;

    unsigned char       *q, pDec[100];		//X��ԭ����n ��n������100
	unsigned __int64    pEnc[100];
	r=RsaGetParam(); 
    cout << "p=" << r.p << endl;
	cout << "q=" << r.q << endl; 
    cout << "f=(p-1)*(q-1)=" << r.f << endl;
	cout << "n=p*q=" << r.n << endl;
	cout << "e=" << r.e << endl;
	cout << "d=" << r.d << endl;
	cout << "s=" << r.s << endl; 
    cout << "Source:" << pSrc << endl;
	q= (unsigned char *)pSrc;
	cout << "Encode:";
	
	unsigned _int64 t;
    
	for(unsigned long i=0; i < n; i++)
	{ 

		t=(unsigned _int64)q[i];			//Xͬ��ΪPowMod��ֵ��������
		
		pEnc[i]=PowMod(t, r.e, r.n);
		cout << hex << pEnc[i] << " ";
	}
	cout << endl;
	cout << "Decode:"; 

	unsigned long i=0;

    for(i=0; i < n; i++)
	{ 
        pDec[i]=PowMod(pEnc[i], r.d, r.n); 
        cout << hex << (unsigned long)pDec[i] << " ";
	}

	pDec[i]='\0';

	cout << endl; 
    cout << (char *)pDec << endl;
}
/* */ 
int main(void)
{ 
    TestRSA();
	system("pause");
	return 0;
} 