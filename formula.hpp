#pragma once

// Base formula class
class Formula {};

// Term
class Term {};
class Variable : public Term {};
class Constant : public Term {};
class ComplexTerm : public Term {};

// Atomic Formula
class AtomicFormula : public Formula {};

// Logical Connective
class LogicalConnective : public Formula {};

class UnaryConnective : public LogicalConnective {};
class Negation : public UnaryConnective {};

class BinaryConnective : public LogicalConnective {};
class Conjunction : public BinaryConnective {};
class Disjunction : public BinaryConnective {};
class Implication : public BinaryConnective {};
class Equivalence : public BinaryConnective {};

// Quantifier
class Quantifier : public Formula {};
class ForAll : public Quantifier {};
class Exists : public Quantifier {};

