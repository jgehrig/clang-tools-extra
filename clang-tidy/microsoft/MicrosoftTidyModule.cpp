//===--- MicrosoftTidyModule.cpp - clang-tidy ----------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"

namespace clang {
namespace tidy {
namespace microsoft {

class MicrosoftModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
  }
};

} // namespace microsoft

// Register the MicrosoftTidyModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<microsoft::MicrosoftModule>
    X("microsoft-module", "Adds microsoft coding style lint checks.");

// This anchor is used to force the linker to link in the generated object file
// and thus register the MicrosoftModule.
volatile int MicrosoftModuleAnchorSource = 0;

} // namespace tidy
} // namespace clang
