cmake_minimum_required(VERSION 3.9)

add_executable(tfhe-hamming-exec hamming-tfhe.cxx)
target_link_libraries(tfhe-hamming-exec common tfhe_bit_exec)

add_executable(tfhe-hamming-encrypt encrypt.cxx)
target_link_libraries(tfhe-hamming-encrypt common tfhe_bit_exec)

add_executable(tfhe-hamming-decrypt decrypt.cxx)
target_link_libraries(tfhe-hamming-decrypt common tfhe_bit_exec)

add_custom_target(tfhe-hamming
  DEPENDS
    tfhe-hamming-exec
    tfhe-hamming-encrypt
    tfhe-hamming-decrypt
    tfhe
)

set(APPS_DIR ${CMAKE_BINARY_DIR}/apps)
configure_file("run.sh.in" "run.sh" @ONLY)
