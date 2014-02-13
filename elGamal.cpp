/*
 *  elGamal.cpp
 *
 *  Created by Eric Mariasis on 12/4/12
 *
 */

#include <iostream>
#include <gmpxx.h>
using namespace std;

gmp_randstate_t rstate;

gmp_randclass r1(gmp_randinit_default);

struct GCDstruct {
  mpz_class d, X, Y;
};

GCDstruct eGCD( mpz_class a, mpz_class b );

mpz_class modInv( mpz_class N, mpz_class a );

mpz_class modExp( mpz_class N, mpz_class a, mpz_class b );

int isPrime( mpz_class N, int t );

GCDstruct eGCD( mpz_class a, mpz_class b ) {
  GCDstruct newGCD;

  mpz_class r = a % b;
  if ( r == 0 )
    return (GCDstruct){ b, 0, 1 };
  mpz_class q = (a-r)/b;
  newGCD = eGCD( b, r );
  return (GCDstruct){ newGCD.d, newGCD.Y, newGCD.X - (newGCD.Y * q) };
}

mpz_class modInv( mpz_class N, mpz_class a ) {
        GCDstruct tmpGCD = eGCD( a, N );
        if (tmpGCD.d != 1 ) {
 cout << a << " is not invertible mod " << N << endl;
                  return -1;
        }
        else {
          mpz_class retval = tmpGCD.X % N;
          if ( retval >= 0 ) return retval;
          return retval + N;
        }
}

mpz_class modExp( mpz_class N, mpz_class a, mpz_class b ) {
        if ( b == 0 ) { return 1; };
        if ( b == 1 ) { return a % N; };
        if ( (b%2) == 0 ) {
          mpz_class t = modExp( N, a, b/2 );
          return (t*t) % N;
        };
        mpz_class t = modExp( N, a, (b-1)/2 );
        return (a*t*t) % N;
}
int isPrime( mpz_class N, int t ) {
        int Nsize = (int) mpz_sizeinbase( N.get_mpz_t(), 2);
        mpz_class randa;
        for (int i=0; i<t; i++) {
          randa = r1.get_z_bits( Nsize + 1 );
          randa = 1 + (randa % (N-1) );
          GCDstruct gcdNa = eGCD( randa, N );
          if ( gcdNa.d != 1 ) { return 0; };
          mpz_class aToTheNminus1 = modExp( N, randa, N-1 );
          if ( aToTheNminus1 != 1 ) { return 0; };
        }
        return 1;
}

mpz_class tothepower(mpz_class base, mpz_class i)
{
  mpz_class j;
  mpz_class result = 1;
  for(j = 0; j < i; j++)
    {
      result = result * base;
 }
  return result;
}

int main (void)
{
  //Gen
  r1.seed(5);
  mpz_class big = 2;
  for(mpz_class i = 0; i < 100; i++)
    {
      big = big * 2;
      //big number to pass to modExp so that it is easy to raise a
      //number to a power
    }
  big = big * big * big;
  mpz_class g;
  mpz_class gmid;
  mpz_class m;
  mpz_class n;
  mpz_class p;
 mpz_class q;
  cout << "Please enter the number of bits you want to use: " << endl;
  cin >> n;
  cout << "Please enter a message encoded as an integer: " << endl;
  cin >> m;
  int j = 0;
  while(j < 1)
    {
      mpz_class i = r1.get_z_bits(n);
      i = i + 1;
      if(isPrime(i, 20) == 1)
        {
          q = (i - 1) / 2;
          if(isPrime(q, 20) == 1)
            {
              p = i;
              cout << "P is: ";
              cout << p << endl;
              cout << "Q is: ";
              cout << q << endl;
              j++;
  }
        }
    }
  mpz_class N = p;
  int Nsize = (int) mpz_sizeinbase( N.get_mpz_t(), 2);
  mpz_class randa;
  randa = r1.get_z_bits( Nsize + 1 ); //generate random value
  randa = 1 + (randa % (N-1) );
  gmid = modExp(p, randa, 1); //get random value mod p
  g = gmid * gmid; //square result of (value mod p)
  cout << "G is: ";
  cout << g << endl;
  int k = 0;
  mpz_class x;
  while(k < 1)
    {
      randa = r1.get_z_bits( Nsize + 1 ); //generate random value
      randa = 1 + (randa % (N-1) );
      if(randa < p)
        {
          x = randa; //select random value of x that is within Zp
 cout << "X is: ";
          cout << x << endl;
          k++;
        }
    }
  mpz_class h;
  h = modExp(big, g, x);
  cout << "H is: ";
  cout << h << endl;
  //Encryption
  mpz_class y;
  int a = 0;
  while(a < 1)
    {
      randa = r1.get_z_bits( Nsize + 1 ); //generate random value
      randa = 1 + (randa % (N-1) );
      if(randa < p)
        {
          y = randa; //select random value of y that is within Zp
          cout << "Y is: ";
          cout << y << endl;
  a++;
        }
    }
  mpz_class c1;
  mpz_class c2;
  c1 = modExp(big, g, y);
  c2 = modExp(big, h, y) * m;
  cout << "C1 is: ";
  cout << c1 << endl;
  cout << "C2 is: ";
  cout << c2 << endl;
  //Decryption
  mpz_class dec;
  dec = c2 / modExp(big, c1, x);
  cout << "M is: ";
  cout << dec << endl;
  return 0;
}

