#pragma once

class Formula {};

class AtomicFormula : public Formula {};

class LogicalConnective : public Formula {};

class UnaryConnective : public LogicalConnective {};
class Negation : public UnaryConnective {};

class BinaryConnective : public LogicalConnective {};
class Conjunction : public BinaryConnective {};
class Disjunction : public BinaryConnective {};
class Implication : public BinaryConnective {};
class Equivalence : public BinaryConnective {};

class Quantifier : public Formula {};
class ForAll : public Quantifier {};
class Exists : public Quantifier {};

