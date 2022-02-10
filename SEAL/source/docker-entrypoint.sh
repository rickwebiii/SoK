#!/bin/bash

EVAL_BUILD_DIR=/root/eval/build
cd $EVAL_BUILD_DIR || (echo "Could not switch to ${EVAL_BUILD_DIR}" && exit)

function upload_files() {
    TARGET_DIR=$1
    shift
    for item in "$@"; do
        aws s3 cp $item ${S3_URL}/${S3_FOLDER}/${TARGET_DIR}/
    done  
}

function run_benchmark() {
    cd $EVAL_BUILD_DIR
    echo "t_keygen,t_input_encryption,t_computation,t_decryption" > $OUTPUT_FILENAME
    RUN=1
    if [ -z "${NUM_RUNS}" ]
    then
        echo "Cannot continue as NUM_RUNS is undefined!"
        exit 1
    fi
    while (( $RUN <= $NUM_RUNS ))
    do
        RUN=$(( $RUN + 1))
        ./$1
    done
}

function run_microbenchmark() {
    cd $EVAL_BUILD_DIR
    # echo "t_mul_ct_ct,t_mul_ct_ct_inplace,t_mul_ct_pt,t_mul_ct_pt_inplace,t_add_ct_ct,t_add_ct_ct_inplace,t_add_ct_pt,t_add_ct_pt_inplace,t_enc_sk,t_enc_pk,t_dec,t_rot" > $OUTPUT_FILENAME
    RUN=1
    if [ -z "${NUM_RUNS}" ]
    then
        echo "Cannot continue as NUM_RUNS is undefined!"
        exit 1
    fi
    while (( $RUN <= $NUM_RUNS ))
    do
        RUN=$(( $RUN + 1))
        ./$1
    done
}

# Chi-Squared BFV with manual params, reusing subexpressions, etc (OPT)
export OUTPUT_FILENAME=seal_bfv_chi_squared_opt.csv
run_benchmark chi_squared_opt

# Chi-Squared BFV with seal params, not reusing subexpressions, etc (NAIVE)
export OUTPUT_FILENAME=seal_bfv_chi_squared_naive.csv
run_benchmark chi_squared_naive

# Chi-Squared BFV Batched
export OUTPUT_FILENAME=seal_bfv_batched_chi_squared.csv
run_benchmark chi_squared_batched

# Kernel BFV
export OUTPUT_FILENAME=seal_bfv_kernel.csv
run_benchmark kernel

# Kernel BFV batched
export OUTPUT_FILENAME=seal_batched_bfv_kernel.csv
run_benchmark kernel_batched
