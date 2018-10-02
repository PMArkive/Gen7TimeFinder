#ifndef SFMT_HPP
#define SFMT_HPP

#include <cstdint>

typedef uint64_t u64;
typedef uint32_t u32;

class SFMT
{

private:
    static const u32 CMSK1 = 0xdfffffef;
    static const u32 CMSK2 = 0xddfecb7f;
    static const u32 CMSK3 = 0xbffaffff;
    static const u32  CMSK4 = 0xbffffff6;
    static const int CSL1 = 18;
    static const int CSR1 = 11;
    static const int N32 = 624;
    const u32 parity[4] = { 0x1, 0x0, 0x0, 0x13c9e684 };
    u32 *sfmt = nullptr;
    u32 seed;
    u32 index;

    void initialize(u32 seed);
    void periodCertificaion();
    void shuffle();

public:
    SFMT(u32 seed, u32 frames = 0);
    ~SFMT() { delete[] sfmt; }
    void advanceFrames(u32 frames);
    u32 nextUInt();
    u64 nextULong();
    void setSeed(u64 seed);
    void setSeed(u64 seed, u32 frames);
    u64 getSeed();

};

#endif // SFMT_HPP
