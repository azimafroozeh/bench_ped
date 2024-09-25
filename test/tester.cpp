// ---------------------------------------------------------------------------
// cengine
// ---------------------------------------------------------------------------
#include "gtest/gtest.h"
#include "gflags/gflags.h"
#include "datablock/schemes/CSchemePool.hpp"
// ---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
   testing::InitGoogleTest(&argc, argv);
   // -------------------------------------------------------------------------------------
   gflags::ParseCommandLineFlags(&argc, &argv, true);
   cengine::db::CSchemePool::available_schemes = make_unique<cengine::db::SchemesCollection>();
   return RUN_ALL_TESTS();
}
// ---------------------------------------------------------------------------
