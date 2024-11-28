# Interactive FOL theorem prover
This is an interactive theorem prover for first-order logic (FOL) using natural deduction. It tries to imitate the Isabelle/HOL syntax of proving theorems using natural deduction rules.

## System requirements
The program is designed to run on the Linux operating system. To compile the program, one needs to have the `g++` C++ compiler and the `flex` and `bison` parsing tools installed on their system.

## Setup
The program is compiled by running the `make` command. This will build the `prover` application, which can then be run in the terminal.

## Usage
The application is run directly in the terminal:
```
./prover <formula_path>
```
where `<formula_path>` is the path to a file which contains the formula to be proven.

### Formula syntax

Below is the syntax for entering formulas in the interactive theorem prover.

#### Terms
- **Constants:**  
  Syntax: identifiers with lowercase initials  
  Examples: `a`, `b`, `c`, ...

- **Variables:**  
  Syntax: identifiers with uppercase initials  
  Examples: `X`, `Y`, `Z`, ...

- **Complex terms:**  
  Syntax: `symbol(term_list)`  
  Example (simple term): `f(X, Y)`  
  Example (more complex term): `g(X, c, h(X, Y, Z), Y)`  

#### Atomic Formulas
- **Boolean constants:**  `True`, `False`  

- **Predicates:**  
  Syntax: `symbol(term_list)`  
  Examples of simple predicates: `p`, `q`, `r`, ...  
  Examples of complex predicates: `p(X, Y)`, `q(X, f(Y, c))`, `r(X)`, ...

#### Logical Connectives
- **Negation (NOT):**  
  Syntax: `~ formula`  
  Example: `~ p(X)`

- **Conjunction (AND):**  
  Syntax: `formula & formula`  
  Example: `p(X) & q(X)`

- **Disjunction (OR):**  
  Syntax: `formula | formula`  
  Example: `p(X) | q(X)`

- **Implication:**  
  Syntax: `formula => formula`  
  Example: `(p(X) => q(X)) => r(X)`

- **Equivalence (IFF):**  
  Syntax: `formula <=> formula`  
  Example: `p(X) <=> q(X)`

#### Quantifiers
- **Universal quantification:**  
  Syntax: `! VAR . formula`  
  Example: `! X . (p(X) -> q(X))`

- **Existential quantification:**  
  Syntax: `? VAR . formula`  
  Example: `? X . p(X)`

#### Parentheses
- Use `()` to group subformulas explicitly.  
  Example: `(p(X) OR q(X)) AND r(X)`

#### Examples
Here are some example formulas:

1. `(p(X) AND q(X)) -> r(X)`
2. `FORALL X . (p(X) -> q(X))`
3. `EXISTS Y . (NOT p(Y) OR q(Y))`
4. `p(f(a, X)) -> q(a)`


### Example
```
Welcome!
Formula to prove:
((∀ X. (p(X) → q(X))) ∧ (∀ Y. (q(Y) → r(Y)))) → (∀ Z. (p(Z) → r(Z)))
Commands:
* apply - apply a natural deduction rule on current goal (for the list of available rules, see 'list')
* shift - rotate the assumptions of current goal (one position to the left)
* help - display this help message
* list - show list of natural deduction rules
* exit - stop the program

Goals to prove: 1
1. ((∀ X. (p(X) → q(X))) ∧ (∀ Y. (q(Y) → r(Y)))) → (∀ Z. (p(Z) → r(Z)))
> apply rule impI

Goals to prove: 1
1. (∀ X. (p(X) → q(X))) ∧ (∀ Y. (q(Y) → r(Y))) ⊢  ∀ Z. (p(Z) → r(Z))
> apply erule conjE

Goals to prove: 1
1. [∀ X. (p(X) → q(X)), ∀ Y. (q(Y) → r(Y))] ⊢  ∀ Z. (p(Z) → r(Z))
> apply rule allI

Goals to prove: 1
1. ∧ Z. [∀ X. (p(X) → q(X)), ∀ Y. (q(Y) → r(Y))] ⊢  p(Z) → r(Z)
> apply erule allE
Instantiate variable: Z

Goals to prove: 1
1. ∧ Z. [∀ Y. (q(Y) → r(Y)), p(Z) → q(Z)] ⊢  p(Z) → r(Z)
> apply erule allE
Instantiate variable: Z

Goals to prove: 1
1. ∧ Z. [p(Z) → q(Z), q(Z) → r(Z)] ⊢  p(Z) → r(Z)
> apply rule impI

Goals to prove: 1
1. ∧ Z. [p(Z) → q(Z), q(Z) → r(Z), p(Z)] ⊢  r(Z)
> apply erule impE

Goals to prove: 2
1. ∧ Z. [q(Z) → r(Z), p(Z)] ⊢  p(Z)
2. ∧ Z. [q(Z) → r(Z), p(Z), q(Z)] ⊢  r(Z)
> apply assumption

Goals to prove: 1
1. ∧ Z. [q(Z) → r(Z), p(Z), q(Z)] ⊢  r(Z)
> apply erule impE

Goals to prove: 2
1. ∧ Z. [p(Z), q(Z)] ⊢  q(Z)
2. ∧ Z. [p(Z), q(Z), r(Z)] ⊢  r(Z)
> apply assumption

Goals to prove: 1
1. ∧ Z. [p(Z), q(Z), r(Z)] ⊢  r(Z)
> apply assumption

No goals!
> done
```

## About
This project is part of a seminar paper for the course "Automated reasoning", a course on the master studies program at the Faculty of Mathematics, University of Belgrade.
