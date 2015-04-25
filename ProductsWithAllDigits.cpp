#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <vector>

/* 
   CODE THAT PRINTS THE SUM OF ALL INTS Z WITH THE FOLLOWING PROPERTY:
   
   THERE EXISTS INTS X,Y IN THE EQUATION X*Y=Z, 
   WHERE EACH DIGIT BETWEEN 1 AND 9 APPEARS EXACTLY ONCE    
   IN THE ENTIRE EQUATION.
*/

bool checkPandigForFactor(double factor, double product)
{
  bool digs[10] = {true,false,false,false,false,false,false,false,false,false};
  double quot = product / factor;
  double factor_left = factor;
  double product_left = product;
  double quot_left = quot;
  while(factor_left != 0)
    {
      int dig = fmod(factor_left, 10);
      if(digs[dig])
        {
          return false;
        }
      digs[dig] = true;
      factor_left = (factor_left - dig) / 10;
    }
  while(product_left != 0)
    {
      int dig = fmod(product_left, 10);
      if(digs[dig])
        {
          return false;
        }
      digs[dig] = true;
      product_left = (product_left - dig) / 10;
    }
  while(quot_left != 0)
    {
      int dig = fmod(quot_left, 10);
      if(digs[dig])
        {
   return false;
        }
      digs[dig] = true;
      quot_left = (quot_left - dig) / 10;
    }
  for(int i = 0; i < 10; i++)
    {
      if(!digs[i])
        {
          return false;
        }
    }
  return true;
}

bool allDigsDifferent(double num)
{
  double rem = num;
  bool digs[10] = {false,false,false,false,false,false,false,false,false,false};
  while(rem != 0)
    {
      int dig = fmod(rem, 10);
      if(digs[dig])
        {
          return false;
        }
      digs[dig] = true;
      rem = (rem - dig) / 10;
    }
  return true;
}

bool hasPandigital(double num)
{
  for(double i = 1; i < sqrt(num); i++)
    {
      double quot = num / i;
      if(fmod(quot, 1) == 0)
        {
          bool isPand = checkPandigForFactor(i, num);
          if(isPand)
            {
              return true;
            }
        }
    }
  return false;
}

double getNextI(double num)
{
  double rem = num;
  double ctr = 0.0;
  while(rem != 0)
    {
      int dig = fmod(rem,10);
      if(fmod(fmod(rem,100), 11) == 0 && dig != 0)
        {
          return (rem+1) * pow(10,ctr);
        }
      ctr++;
      rem = (rem - dig)/10;
    }
  return num+1;
}

double getFinalSum()
{
  double sum = 0.0;
  double next_i;
  for(double i = 0; i < 10000; i = next_i)
    {
      if(allDigsDifferent(i))
        {
          if(hasPandigital(i))
            {
              sum += i;
            }
        }
      next_i = getNextI(i);
    }
  std::cout << "Final sum is " << sum << std::endl;
  return sum;
}

int main()
{
  getFinalSum();
}
