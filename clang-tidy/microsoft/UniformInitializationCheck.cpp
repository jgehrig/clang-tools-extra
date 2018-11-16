//===--- UniformInitializationCheck.cpp - clang-tidy ----------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "UniformInitializationCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Lex/Lexer.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace microsoft {

void UniformInitializationCheck::registerMatchers(MatchFinder *Finder) {
  // This rule only applies to C++11 or greater
  if (!getLangOpts().CPlusPlus11) {
    return;
  }

  // Check all variable and class member variable declarations
  Finder->addMatcher(varDecl().bind("variable"), this);
  Finder->addMatcher(fieldDecl().bind("member variable"), this);
}

void UniformInitializationCheck::check(const MatchFinder::MatchResult &Result) {
  if (const auto *MatchedVarDecl = Result.Nodes.getNodeAs<VarDecl>("variable")) {
    varDeclCheck(Result, *MatchedVarDecl);
  }
  else if (const auto *MatchedFieldDecl= Result.Nodes.getNodeAs<FieldDecl>("member variable")) {
    fieldDeclCheck(Result, *MatchedFieldDecl);
  }
}

void UniformInitializationCheck::fieldDeclCheck(const MatchFinder::MatchResult &Result, const FieldDecl &MatchedFieldDecl) {
  if (MatchedFieldDecl.getInClassInitStyle() == InClassInitStyle::ICIS_ListInit) {
    return;
  }

  const std::string errorMessage { "class member variable '%0' does not use uniform initialization" };
  const Expr *initExpr { MatchedFieldDecl.getInClassInitializer() };

  addDiagnosticMessage(Result, MatchedFieldDecl, initExpr, errorMessage);
}

void UniformInitializationCheck::varDeclCheck(const MatchFinder::MatchResult &Result, const VarDecl &MatchedVarDecl) {
  // Variables declared but not defined do not need uniform initialization
  if (MatchedVarDecl.isThisDeclarationADefinition() == VarDecl::DefinitionKind::DeclarationOnly) {
    return;
  }

  // This variable already uses uniform initialization
  if (MatchedVarDecl.isDirectInit()) {
    return;
  }

  const std::string errorMessage { "variable '%0' does not use uniform initialization" };
  const Expr *initExpr { MatchedVarDecl.getInit() };

  addDiagnosticMessage(Result, MatchedVarDecl, initExpr, errorMessage);
  }

void UniformInitializationCheck::addDiagnosticMessage(
    const MatchFinder::MatchResult &Result,
    const NamedDecl &declStatement,
    const Expr *initExpr,
    const std::string errorMessage) {

  // Display error message, with variable name
  // NOTE: errorMessage must contain "'%0'", on which a substitution for declStatement is performed
  auto Diag = diag(declStatement.getLocation(), errorMessage) << declStatement.getNameAsString();

  // Variable already contains a default value
  if (initExpr) {
    const std::string initExpressionText{ Lexer::getSourceText(
        CharSourceRange::getTokenRange(initExpr->getSourceRange()), *Result.SourceManager,
        Result.Context->getLangOpts()) };

    const SourceRange rangeVariableToExpression { declStatement.getLocation(), initExpr->getEndLoc() };

    const std::string fixedStatementUniformInit { declStatement.getNameAsString() + " { " + initExpressionText + " }" };

    Diag << FixItHint::CreateReplacement(rangeVariableToExpression, fixedStatementUniformInit);
  }
  // Variable does not already have a default value
  else {
    SourceLocation BeginLoc { declStatement.getLocation() };
    SourceLocation EndLoc { declStatement.getEndLoc() };
    const std::string varDeclText { Lexer::getSourceText(CharSourceRange::getTokenRange(BeginLoc, EndLoc), *Result.SourceManager, Result.Context->getLangOpts()) };

    Diag << FixItHint::CreateInsertion(declStatement.getLocation().getLocWithOffset(varDeclText.size()), " {}");
  }
}

} // namespace microsoft
} // namespace tidy
} // namespace clang
