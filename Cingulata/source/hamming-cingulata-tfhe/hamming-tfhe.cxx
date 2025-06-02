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

#define SIZE 1

int main() {
  /* Set context to tfhe bit executor and size minimized integer
   * operations */
  CiContext::set_config(
      make_shared<decorator::Attach<TfheBitExec, decorator::Stat<IBitExecFHE>>>(
          "tfhe.pk", TfheBitExec::Public),
      make_shared<IntOpGenSize>());

  vector<CiInt> x;
  vector<CiInt> y;

    // Fills conditions with values from file.
  for (int i = 0; i < SIZE; i++) {
    stringstream ss;
    ss << "x" << i;
    string str;
    ss >> str;

    x.push_back(CiInt{CiInt::u8});
    x[i].read(str.c_str());
  }

  for (int i = 0; i < SIZE; i++) {
    stringstream ss;
    ss << "y" << i;
    string str;
    ss >> str;

    y.push_back(CiInt{CiInt::u8});
    y[i].read(str.c_str());
  }

  CiInt count{CiInt::u8v(0)};
  CiInt one{CiInt::u8v(1)};

  for (int i = 0; i < SIZE; i++) {
    CiInt x_xor_y = x[i] ^ y[i];

    for (int j = 0; j < 8; j++) {
      count += (x_xor_y >> j) & one;
    }
  }

  count.write("count");

  CiContext::get_bit_exec_t<decorator::Stat<IBitExecFHE>>()->print();
}
