// Copyright (c) 2021, the YACCLAB contributors, as 
// shown by the AUTHORS file. All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef HEADER_BIT_SCANNER
#define HEADER_BIT_SCANNER

#if __cplusplus > 201703L
#include <version>
#endif

#if defined _MSC_VER
#include <intrin.h>
#define myBitScanForward32 _BitScanForward
#define myBitScanForward64 _BitScanForward64

#elif defined MY_PLATFORM_MACRO
// Define YacclabBitScanForward64 using the proper compiler intrinsic for your platform.
// Don't forget to open a pull request! :)

#elif defined __GNUC__ && (__GNUC__ > 3 || (__GNUC__ == 3 && (__GNUC_MINOR__ > 4 || (__GNUC_MINOR__ == 4 && __GNUC_PATCHLEVEL__ > 0))))
#include <stdint.h>
inline unsigned char myBitScanForward32(uint32_t* Index, uint32_t Mask) {
    if (!Mask) return 0;

    *Index = static_cast<uint32_t>(__builtin_ctzl(Mask));
    return 1;
}
inline unsigned char myBitScanForward64(uint32_t* Index, uint64_t Mask) {
    if (!Mask) return 0;

    *Index = static_cast<uint32_t>(__builtin_ctzll(Mask));
    return 1;
}

#elif defined __clang__ && (__clang_major__ >= 5)
#include <stdint.h>
inline unsigned char myBitScanForward32(uint32_t* Index, uint32_t Mask) {
    if (!Mask) return 0;

    *Index = static_cast<uint32_t>(__builtin_ctzl(Mask));
    return 1;
}
inline unsigned char myBitScanForward64(uint32_t* Index, uint64_t Mask) {
    if (!Mask) return 0;

    *Index = static_cast<uint32_t>(__builtin_ctzll(Mask));
    return 1;
}

#elif defined __cpp_lib_bitops
#include <bit>
#include <stdint.h>
inline unsigned char myBitScanForward32(uint32_t* Index, uint32_t Mask) {
    if (!Mask) return 0;

    *Index = static_cast<uint32_t>(std::countr_zero(Mask));
    return 1;
}
inline unsigned char myBitScanForward64(uint32_t* Index, uint64_t Mask) {
    if (!Mask) return 0;

    *Index = static_cast<uint32_t>(std::countr_zero(Mask));
    return 1;
}

#else
#include <stdexcept>
#include <stdint.h>
inline unsigned char myBitScanForward32(uint32_t* Index, uint64_t Mask) {
    throw std::runtime_error("myBitScanForward32 undefined."
        " Define it for your platform in \"BitScanner.h\","
        " or enable C++20 for the generic version.");
}
inline unsigned char myBitScanForward64(uint32_t* Index, uint64_t Mask) {
    throw std::runtime_error("myBitScanForward64 undefined."
        " Define it for your platform in \"BitScanner.h\","
        " or enable C++20 for the generic version.");
}
#endif
#endif