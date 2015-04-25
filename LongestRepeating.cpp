#include <iostream>
#include <math.h>
/* CODE TO FIND LONGEST REPEATING DECIMAL FOR NUMBER WITH 1 IN NUMERATOR AND <= 1000 IN DENOMINATOR */
struct factor
{
  double base;
  double exp;
};

bool isPrime(double x)
{
  for(double i = 2; i <= sqrt(x); i++)
    {
      if(fmod(x, i) == 0)
        {
          return false;
        }
    }
  return true;
}

double getExponentForPrime(double num, double prime)
{
  double exp = 0.0;
  double product = 1.0;
  while(product <= num)
    {
      product *= prime;
      if(fmod(num, product) == 0)
        {
          exp++;
        }
      else{
        break;
      }
    }
  return exp;
}

struct factor * getPrimeFactorization(double num, struct factor * factors)
{
  if(isPrime(num))
    {
 factors[(int)num].base = num;
      factors[(int)num].exp = 1.0;
    }
  for(double base = 2; base <= sqrt(num); base++)
    {
      if(fmod(num, base) == 0.0)
        {
          if(isPrime(base))
            {
              factors[(int)base].base = base;
              factors[(int)base].exp = getExponentForPrime(num, base);
      }
          if(isPrime(num / base) && num/base != base)
            {
              factors[(int)(num/base)].base = num/base;
              factors[(int)(num/base)].exp = 1.0;
            }
        }
    }
  return factors;
}

double getDigitsForPrime(double prime)
{
  double ctr = 0.0;
  double ans = 1.0;
  double ans_ctr = 0.0;
  while(ans_ctr != 1.0)
    {
      ctr++;
      ans = ans * 10.0;
      ans = fmod(ans, prime);
      if(ans == 1.0)
        {
          ans_ctr++;
        }
    }
  return ctr;
}

bool coprimeToTen(double num)
{
  if(fmod(num, 2.0) == 0.0 || fmod(num, 5.0) == 0.0)
    {
      return false;
    }
  return true;
}

double carmichaelSmall(struct factor fact)
{
  if(fact.base == 2.0 && fact.exp > 2.0)
    {
      return pow(2.0, fact.exp - 2.0);
    }
  return pow(fact.base, fact.exp - 1.0) * (fact.base - 1.0);
}

double lcm(double a, double b)
{
  if(a == 1.0){return b;}
  if(b == 1.0){return a;}
  struct factor a_facts[(int)a + 1];
  struct factor b_facts[(int)b + 1];
  for(double i = 0; i <= a+1; i++)
    {
      a_facts[(int)i].base = 0;
      a_facts[(int)i].exp = 0.0;
    }
  for(double i = 0; i <= b+1; i++)
    {
      b_facts[(int)i].base = 0;
      b_facts[(int)i].exp = 0.0;
    }
  getPrimeFactorization(a, a_facts);
  getPrimeFactorization(b, b_facts);
  double LCM = 1.0;
  double min = a + 1.0;
  double max = b + 1.0;
  if(a > b)
    {
      min = b + 1.0;
      max = a + 1.0;
    }
  for(double i = 0; i < min; i++)
  {
      if(a_facts[(int)i].base != 0.0 || b_facts[(int)i].base != 0.0)
        {
          if(a_facts[(int)i].exp > b_facts[(int)i].exp)
            {
              LCM *= pow(a_facts[(int)i].base, a_facts[(int)i].exp);
            }
          else
            {
              LCM *= pow(b_facts[(int)i].base, b_facts[(int)i].exp);
            }
        }
  }
   for(double i = min; i < max; i++)
    {
      if(max == a+1 && a_facts[(int)i].base != 0)
        {
          LCM *= pow(a_facts[(int)i].base, a_facts[(int)i].exp);
        }
      else if(max == b + 1 && b_facts[(int)i].base != 0)
        {
          LCM *= pow(b_facts[(int)i].base, b_facts[(int)i].exp);
        }
      else
        {
      if(max == a+1 && a_facts[(int)i].base != 0)
        {
          LCM *= pow(a_facts[(int)i].base, a_facts[(int)i].exp);
        }
      else if(max == b + 1 && b_facts[(int)i].base != 0)
        {
          LCM *= pow(b_facts[(int)i].base, b_facts[(int)i].exp);
        }
      else
        {
          LCM *= 1.0;
        }
    }
  return LCM;
}

double carmichael(double num)
{
  double LCM = 1.0;
  struct factor factors[(int)num + 1];
  for(double i = 0; i <= num; i++)
    {
      factors[(int)i].base = 0;
      factors[(int)i].exp = 0.0;
    }
  getPrimeFactorization(num, factors);
  for(double i = 0; i <= num; i++)
    {
      if(factors[(int)i].base != 0)
        {
          LCM *= lcm(LCM, carmichaelSmall(factors[(int)i]));
        }
    }
  return LCM;
}

double getRepeatingDigs(double num)
{
  if(num <= 2.0 || num == 5.0)
    {
      return 0.0;
    }
  if(num == 9.0)
    {
      return 1.0;
    }
  if(isPrime(num))
    {
      return getDigitsForPrime(num);
    }
  if(coprimeToTen(num))
    {
      double LCM = 1.0;
      struct factor factors[(int)num + 1];
      for(double i = 0; i <= num; i++)
        {
          factors[(int)i].base = 0;
          factors[(int)i].exp = 0.0;
        }
      getPrimeFactorization(num, factors);
      for(double i = 0; i <= num; i++)
        {
       if(factors[(int)i].base != 0)
            {
              double period = pow(factors[(int)i].base, factors[(int)i].exp - 1.0) * getRepeatingDigs(i);
              LCM = lcm(period, LCM);
            }
        }
      return LCM;
    }
  struct factor factors[(int)num + 1];
  for(double i = 0; i <= num; i++)
    {
      factors[(int)i].base = 0;
      factors[(int)i].exp = 0.0;
    }
  getPrimeFactorization(num, factors);
  double divisor = 1.0;
  if(factors[2].base != 0)
    {
      divisor *= pow(factors[2].base, factors[2].exp);
    }
  if(factors[5].base != 0)
 {
      divisor *= pow(factors[5].base, factors[5].exp);
    }
  return getRepeatingDigs(num / divisor);
}

int main()
{
  double max_i = -1.0;
  double max_r = 0.0;
  double cur_r;
  for(double i = 1; i < 1000; i++)
    {
      cur_r = getRepeatingDigs(i);
      if(cur_r > max_r)
        {
          max_i = i;
          max_r = cur_r;
        }
    }
  std::cout << std::fixed << max_i << " has " << max_r << " repeating digs" << std::endl;
}