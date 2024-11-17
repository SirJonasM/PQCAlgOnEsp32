# Set the library name (optional but recommended for clarity)
add_library(pqclean STATIC
    cbd.c
    fips202.c
    indcpa.c
    kem.c
    ntt.c
    poly.c
    polyvec.c
    randombytes.c
    reduce.c
    symmetric-shake.c
    verify.c
)

# Specify include directories
target_include_directories(pqclean PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
