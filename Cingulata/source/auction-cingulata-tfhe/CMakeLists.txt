cmake_minimum_required(VERSION 3.9)

add_executable(tfhe-auction-exec auction-tfhe.cxx)
target_link_libraries(tfhe-auction-exec common tfhe_bit_exec)

add_executable(tfhe-auction-encrypt encrypt.cxx)
target_link_libraries(tfhe-auction-encrypt common tfhe_bit_exec)

add_executable(tfhe-auction-decrypt decrypt.cxx)
target_link_libraries(tfhe-auction-decrypt common tfhe_bit_exec)

add_custom_target(tfhe-auction
  DEPENDS
    tfhe-auction-exec
    tfhe-auction-encrypt
    tfhe-auction-decrypt
    tfhe
)

set(APPS_DIR ${CMAKE_BINARY_DIR}/apps)
configure_file("run.sh.in" "run.sh" @ONLY)
