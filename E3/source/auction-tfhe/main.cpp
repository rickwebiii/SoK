#include <iostream>
#include "e3int.h"
#include "../../src/e3key.h"

using SecureByte = TypeUint<16>;

#define COUNT 2

int main()
{
  // == inputs ====
  // FEEDF00D'CAFEBABE
  std::vector<SecureByte> bids = { _0_Ep, _1_Ep, _2_Ep, _3_Ep, _4_Ep, _5_Ep, _6_Ep, _7_Ep, _8_Ep, _9_Ep, _10_Ep, _11_Ep, _12_Ep, _13_Ep, _14_Ep, _15_Ep, _16_Ep, _17_Ep, _18_Ep, _19_Ep, _20_Ep, _21_Ep, _22_Ep, _23_Ep, _24_Ep, _25_Ep, _26_Ep, _27_Ep, _28_Ep, _29_Ep, _30_Ep, _31_Ep };

  // == //END inputs ====
  SecureByte max = bids[0];
  SecureByte max_idx = _0_Ep;

  for (int i = 1; i < COUNT; i++) {
    auto gt = bids[i] > max;

    max = gt.mux(bids[i], max);
    max_idx = gt.mux(bids[i], max_idx);
  }

  std::cout << e3::decrypt(max) << '\n';
  std::cout << e3::decrypt(max_idx) << '\n';
}