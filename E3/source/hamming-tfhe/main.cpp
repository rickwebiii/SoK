#include <iostream>
#include "e3int.h"
#include "../../src/e3key.h"

using SecureByte = TypeUint<8>;

#define SIZE 8

int main()
{
  // == inputs ====
  // FEEDF00D'CAFEBABE
  std::vector<SecureByte> x = { _254_Ep, _237_Ep, _240_Ep, _13_Ep, _202_Ep, _254_Ep, _186_Ep, _190_Ep };
  // 12345678'9ABCDEF0
  std::vector<SecureByte> y = { _18_Ep, _52_Ep, _86_Ep, _120_Ep, _154_Ep, _188_Ep, _222_Ep, _240_Ep };
  
  SecureByte one = _1_Ep;

  // == //END inputs ====
  SecureByte count = _0_Ep;
  
  for (int i = 0; i < SIZE; i++) {
    SecureByte x_xor_y = x[i] ^ y[i];

    for (int j = 0; j < 8; j++) {
      count += (x_xor_y >> i) & one;
    }
  }

  std::cout << e3::decrypt(count) << '\n';
}
