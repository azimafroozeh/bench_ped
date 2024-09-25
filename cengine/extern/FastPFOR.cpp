#include "FastPFOR.hpp"
#include <headers/blockpacking.h>
#include <headers/simdbinarypacking.h>
#include "Exceptions.hpp"

#include "headers/codecfactory.h"
#include "headers/deltautil.h"

// -------------------------------------------------------------------------------------
template<>
struct LemiereImpl<FastPForCodec::FPF>::impl {
    FastPForLib::CompositeCodec<FastPForLib::SIMDFastPFor<8>, FastPForLib::VariableByte> codec;
};
// -------------------------------------------------------------------------------------
template<>
struct LemiereImpl<FastPForCodec::FBP>::impl {
    FastPForLib::CompositeCodec<FastPForLib::FastBinaryPacking<32>, FastPForLib::VariableByte> codec;
};
// -------------------------------------------------------------------------------------
template<FastPForCodec Codec>
LemiereImpl<Codec>::LemiereImpl() : pImpl(new LemiereImpl<Codec>::impl) {}
// -------------------------------------------------------------------------------------
template<FastPForCodec Codec>
LemiereImpl<Codec>::~LemiereImpl() = default;
// -------------------------------------------------------------------------------------
template<FastPForCodec Codec>
u32 LemiereImpl<Codec>::compress(const data_t* src, u32 count, data_t* dest, SIZE& outsize) {
    auto& codec = this->pImpl->codec;
    codec.encodeArray(src, count, dest, outsize);
    return outsize;
}
// -------------------------------------------------------------------------------------
template<FastPForCodec Codec>
const typename LemiereImpl<Codec>::data_t* LemiereImpl<Codec>::decompress(const data_t* src, u32 count, data_t* dest, SIZE& outsize) {
    auto& codec = this->pImpl->codec;
    return codec.decodeArray(src, count, dest, outsize);
}
// -------------------------------------------------------------------------------------
template<FastPForCodec Codec>
void LemiereImpl<Codec>::applyDelta(data_t* src, size_t count) {
    using namespace FastPForLib;
    FastPForLib::Delta::deltaSIMD(src, count);
}
// -------------------------------------------------------------------------------------
template<FastPForCodec Codec>
void LemiereImpl<Codec>::revertDelta(data_t* src, size_t count) {
    using namespace FastPForLib;
    FastPForLib::Delta::inverseDeltaSIMD(src, count);
}
// -------------------------------------------------------------------------------------
template struct LemiereImpl<FastPForCodec::FPF>;
template struct LemiereImpl<FastPForCodec::FBP>;
// -------------------------------------------------------------------------------------
