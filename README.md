# 📘 Compiler Design Programs

This repository contains a collection of programs and tools developed for Compiler Design. It includes everything from lexical analysis to syntax analysis and parser construction. Each program demonstrates a specific concept or component of a compiler.

## 📁 Contents

### 🔤 String & Token Analysis
- ✅ **String Function Analyzer** – A program to analyze standard string functions.
- ✅ **Token Counter** – Counts the total number of tokens in a given code.
- ✅ **Token Specifier** – Identifies and lists all tokens in a code sample.

### 📚 Symbol Table
- ✅ **Symbol Table in C** – Implements a basic symbol table with insert and lookup functionality.

### 🔍 Lexical Analysis
- ✅ **Lexical Analyzer in C** – Recognizes basic patterns from C language (keywords, identifiers, etc.).
- ✅ **Lexical Analyzer using LEX Tool** – Implementation of a lexer using the LEX tool.
- ✅ **Dynamic Stack in C** – Stack implementation using dynamic memory allocation, useful for parsing tasks.

### 📐 Parsing Techniques

#### 🔮 Predictive Parsing
- ✅ **Predictive Parser (Non-Recursive Descent)** – Implements a predictive parser based on a given grammar.

#### 🔁 Recursive Descent
- ✅ **Recursive Descent Parser in C** – Parses based on a given context-free grammar (CFG).

#### 📊 Automata
- ✅ **NFA Construction** – Constructs a Non-Deterministic Finite Automata from a regular expression.

#### 🎯 Grammar Analysis
- ✅ **First & Follow Set Calculator** – Computes FIRST and FOLLOW sets for a given CFG.

### 🧩 Parser Design
- ✅ **SLR Parser**
- ✅ **LALR Parser**
- ✅ **Shift-Reduce Parser**

### 🛠️ Lex and YACC Projects
- ✅ **YACC: Infix to Postfix Converter** – Converts infix expressions to postfix using YACC.
- ✅ **Lex & Yacc in LLVM** – A minimal compiler front-end using LLVM, Lex and Yacc.

## 🚀 Getting Started

1. Clone the repository:
   ```bash
   git clone https://github.com/Karansehgal0611/CompilerPractice.git
   cd CompilerPractice.git
   ```
2. Compile and run any .c file using GCC:
   ```bash
   gcc filename.c -o output
    ./output
   ```
3. For LEX/YACC programs:
  ```bash
    lex file.l
    yacc -d file.y
    gcc lex.yy.c y.tab.c -o output
    ./output
  ```

## 📌 Prerequisites
- GCC or any C compiler
- Flex (for lex programs)
- Bison or YACC (for yacc programs)
- LLVM (for advanced LLVM integration programs)

## Author 
Karan Sehgal
