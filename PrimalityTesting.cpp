//Built up using user arithmetric's 'Is a number prime?' kata and tests on CodeWars.
//Primality tests based on L. Lovasz and K. Vesztergombi (1999) Discrete Mathematics Lecture Notes, Yale University, Spring 1999
//Available at https://cims.nyu.edu/~regev/teaching/discrete_math_fall_2005/dmbook.pdf (see p69 - 72)

#include <cmath>
#include <cstdlib>
#include <vector>
#include <iostream>


class polynomial {
public:
    int base;
    int power;
    int constant;

    polynomial(int iBase, int iPower, int iConstant) {
        base = iBase;
        power = iPower;
        constant = iConstant;
    }

};

bool isPrime(int num) {
    //Corner Cases
    if (num <= 1) { return false; }
    if (num == 2) { return true; }
    if (num == 3) { return true; }
    if (num % 2 == 0) { return false; }

    std::cout << "Testing " << num << std::endl;

    //Run Primarlity Test arbitrary number of times
    for (int i = 0; i < 3; i++) {

        //Using Rabin and Miller Test (kind of... Much less efficient than actual Rabin and Miller algorithm):
        //Choose int base in range 0 <= base <= num - 1
        int testNum = std::rand() % num;

        //Break into factors
        std::vector<polynomial> factors = { polynomial(testNum, 1, 0), polynomial(testNum, num - 1, -1) };
        while (true) {
            int lowestFactorPower = factors.back().power;
            if (lowestFactorPower % 2 == 0 && lowestFactorPower != 2) {
                factors.pop_back();
                factors.push_back(polynomial(testNum, lowestFactorPower / 2, 1));
                factors.push_back(polynomial(testNum, lowestFactorPower / 2, -1));
                continue;
            }

            break;
        }

        //Test divisbility of each factor
        bool factorIsDivisible = false;

        //Reverse to start with smallest factors
        std::reverse(factors.begin(), factors.end());
        for (auto i : factors) {
            std::cout << "Testing divisbility of " << i.base << "^" << i.power << " + " << i.constant << std::endl;

            //Compute polynomial efficiently      
            long currentPower = 1;
            int targetPower = i.power;
            long runningTotal = i.base;

            //Double power / square num...
            while (currentPower * 2 < targetPower) {
                currentPower *= 2;
                runningTotal = runningTotal * runningTotal;
                if (runningTotal > num) { runningTotal = runningTotal % num; }
            }

            //std::cout << "Left squaring w/ power " << currentPower << std::endl;

            //+1 to power / *base num...
            while (currentPower < targetPower) {
                currentPower += 1;
                runningTotal *= i.base;
                if (runningTotal > num) { runningTotal = runningTotal % num; }
                //std::cout << "running number is now " << runningTotal << ", current power is " << currentPower << std::endl;
            }

            //Check is result is divisble by input num
            if ((runningTotal + i.constant) % num == 0) {
                factorIsDivisible = true;
                break;
            }
        }

        if (!factorIsDivisible) { return false; }

        //End Test loop
    }


    return true;
}

//Alt - Fermat Prime Test. Does not catch Carmichael numbers
/*
  //Create base in range 2, n-2
  int testBase = std::rand() % (num + 1);
  if (testBase < 2) {testBase = 2;}
  if (num - testBase <= 2) {testBase = num - 2;}
  std::cout << "With base " << testBase << std::endl;
  //Fermat's Primality Test: Does n|2^(n−1) − 1 hold?
  //Build up the final power, using only remainders whenever it growns greater than num
  int currentPower = 1;
  int targetPower = num - 1;
  int testNumber = testBase;

  //Double power / square num...
  while (currentPower * 2 < targetPower) {
    currentPower *= 2;
    testNumber = testNumber * testNumber;
    if (testNumber > num) {testNumber = testNumber % num;}
  }


  //+1 to power / *base num...
  while (currentPower < targetPower) {
    currentPower += 1;
    testNumber *= testBase;
    if (testNumber > num) {testNumber = testNumber % num;}
  std::cout << "test number is now " << testNumber << ", current power is " << currentPower << std::endl;
  }

  testNumber -= 1;

  std::cout << "Which comes to " << testNumber << std::endl;

  if (testNumber % num != 0) {return false;}
*/

int main(){
    //Put test here vv
    std::cout << isPrime(1826473961) << std::endl;
}