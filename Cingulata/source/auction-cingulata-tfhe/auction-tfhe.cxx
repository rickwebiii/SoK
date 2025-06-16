/*
    (C) Copyright 2019 CEA LIST. All Rights Reserved.
    Contributor(s): Cingulata team (formerly Armadillo team)

    This software is governed by the CeCILL-C license under French law and
    abiding by the rules of distribution of free software.  You can  use,
    modify and/ or redistribute the software under the terms of the CeCILL-C
    license as circulated by CEA, CNRS and INRIA at the following URL
    "http://www.cecill.info".

    As a counterpart to the access to the source code and  rights to copy,
    modify and redistribute granted by the license, users are provided only
    with a limited warranty  and the software's author,  the holder of the
    economic rights,  and the successive licensors  have only  limited
    liability.

    The fact that you are presently reading this means that you have had
    knowledge of the CeCILL-C license and that you accept its terms.
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

/* local includes */
#include <bit_exec/decorator/attach.hxx>
#include <bit_exec/decorator/stat.hxx>
#include <ci_context.hxx>
#include <ci_fncs.hxx>
#include <ci_int.hxx>
#include <int_op_gen/size.hxx>
#include <tfhe_bit_exec.hxx>
#include <int_op_gen/mult_depth.hxx>

/* namespaces */
using namespace std;
using namespace cingulata;

#define SEX_FIELD 0
#define ANTECEDENT_FIELD 1
#define SMOKER_FIELD 2
#define DIABETES_FIELD 3
#define PRESSURE_FIELD 4

#define COUNT 8

int main() {
  /* Set context to tfhe bit executor and size minimized integer
   * operations */
  CiContext::set_config(
      make_shared<decorator::Attach<TfheBitExec, decorator::Stat<IBitExecFHE>>>(
          "tfhe.pk", TfheBitExec::Public),
      make_shared<IntOpGenSize>());

  // Declares variables for conditions with each 8 bit.
  vector<CiInt> bids;

  // Fills conditions with values from file.
  for (int i = 0; i < COUNT; i++) {
    stringstream ss;
    ss << "bids" << i;
    string str;
    ss >> str;

    bids.push_back(CiInt{CiInt::u16});
    bids[i].read(str.c_str());
  }

  CiInt maxBid = bids[0];
  CiInt maxIdx{CiInt::u16v(0)};
  
  for (int i = 1; i < COUNT; i++) {
    CiBit gt = bids[i] > maxBid;

    maxBid = select(gt, bids[i], maxBid);
    maxIdx = select(gt, CiInt::u16v(i), maxIdx);
  }

  maxBid.write("maxBid");
  maxIdx.write("maxIdx");

  CiContext::get_bit_exec_t<decorator::Stat<IBitExecFHE>>()->print();
}
