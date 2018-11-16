//===--- UniformInitializationCheck.h - clang-tidy --------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MICROSOFT_UNIFORMINITIALIZATIONCHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MICROSOFT_UNIFORMINITIALIZATIONCHECK_H

#include "../ClangTidy.h"

namespace clang {
namespace tidy {
namespace microsoft {

using ast_matchers::MatchFinder;

/// Ensure all FieldDecl and VarDecl nodes use modern list initialization
class UniformInitializationCheck : public ClangTidyCheck {
public:
  UniformInitializationCheck(StringRef Name, ClangTidyContext *Context)
      : ClangTidyCheck(Name, Context) {}

  void registerMatchers(MatchFinder *Finder) override;

  void check(const MatchFinder::MatchResult &Result) override;

  void fieldDeclCheck(const MatchFinder::MatchResult &Result, const FieldDecl &MatchFieldDecl);

  void varDeclCheck(const MatchFinder::MatchResult &Result, const VarDecl &MatchedVarDecl);

  void addDiagnosticMessage(const MatchFinder::MatchResult &Result, const NamedDecl &declStatement,
      const Expr *initExpr, const std::string errorMessage);
};

} // namespace microsoft
} // namespace tidy
} // namespace clang

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MICROSOFT_UNIFORMINITIALIZATIONCHECK_H
