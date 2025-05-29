#include <iostream>
#include "e3int.h"
#include "../../src/e3key.h"

using SecureInt = TypeUint<64>;

int main()
{
  // == inputs ====
  SecureInt x = _18369602397145053886_Ep;
  SecureInt y = _1311768467463790320_Ep;
  SecureInt one = _1_Ep;

  // == //END inputs ====
  SecureInt count = _0_Ep;

  for (int i = 0; i < 64; i++) {
    count += ((x >> i) ^ (y >> i)) & one;
  }

  std::cout << e3::decrypt(count) << '\n';
}
