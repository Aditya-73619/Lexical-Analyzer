# 🔍 Lexical Analyzer in C

## 📌 Overview

This project implements a **Lexical Analyzer (Lexer)** using the C programming language. Lexical analysis is the first phase of a compiler, where source code is scanned and converted into meaningful tokens.

The analyzer reads a C source file character by character, identifies tokens according to lexical rules, and classifies them into categories such as keywords, identifiers, constants, operators, and special symbols.

It also validates command-line arguments and reports errors for invalid tokens or operators encountered during analysis.

---

## 🚀 Features

- Identifies **C keywords** such as `int`, `char`, `if`, and `return`.
- Recognizes **identifiers**, including variable and function names.
- Detects **integer and floating-point constants**.
- Identifies **operators** used in expressions.
- Recognizes **special symbols** such as `;`, `,`, `(`, and `)`.
- Handles **string literals**.
- Reads a source filename through command-line arguments.
- Validates input arguments before starting lexical analysis.
- Reports invalid operators and invalid tokens.
- Displays the result of the lexical analysis process.

---

## 🛠️ Technologies Used

- C Programming
- GCC Compiler
- File Handling
- Character-by-Character Parsing
- Lexical Analysis and Tokenization
- Command-Line Argument Handling (`argc` and `argv`)
- Header Files and Modular Programming
- Error Handling

---

## 📂 Project Structure

```text
Lexical-Analyzer/
├── Src/
│   ├── main.c
│   ├── lexer.c
│   ├── lexer.h
│   └── types.h
├── Example/
│   └── sample.c
└── README.md
```

- `main.c` — Entry point of the program; validates the argument count and initiates lexical analysis.
- `lexer.c` — Implements the lexical analysis logic.
- `lexer.h` — Contains lexer-related declarations.
- `types.h` — Defines data types and related definitions used by the project.
- `sample.c` — Example C source file to analyze.

---

## ⚙️ How to Run

### Prerequisites

- GCC compiler
- Linux or macOS terminal, or a compatible environment

### 1. Navigate to the source directory

```bash
cd Src
```

### 2. Compile the program

```bash
gcc main.c lexer.c -o lexer
```

### 3. Run the analyzer

Pass the C source file as a command-line argument:

```bash
./lexer ../Example/sample.c
```

Replace `sample.c` with the path to the C source file you want to analyze.

**Important:** The program expects exactly one command-line argument: the input C source filename.

---

## 🧩 Token Types

The lexer classifies supported input into categories such as:

| Token Type | Examples |
|---|---|
| Keyword | `int`, `return`, `if` |
| Identifier | `main`, `count`, `total` |
| Integer Constant | `10`, `42`, `100` |
| Floating-Point Constant | `3.14`, `2.5` |
| Operator | `+`, `-`, `=`, `*` |
| Special Symbol | `;`, `,`, `(`, `)` |
| String Literal | `"Hello World"` |

The exact tokens recognized depend on the lexical rules implemented in the source code.

---

## 💻 Sample Input

Consider the following C program saved as `sample.c`:

```c
int main()
{
    int num = 10;
    return num;
}
```

The lexer reads this file and identifies the supported tokens, such as `int`, `main`, `(`, `)`, `num`, `=`, `10`, and `return`.

When lexical analysis completes successfully, the program prints:

```text
Analysis is Success
```

The program reports an error if the command-line arguments are invalid or if the lexer encounters an invalid token or operator.

---

## 🧠 Concepts Practiced

- Fundamentals of Compiler Design
- Lexical Analysis and Tokenization
- Character Processing in C
- File Handling
- Structures, Enumerations, and User-Defined Types
- Header Files and Modular Programming
- Command-Line Argument Validation
- Error Detection and Handling


---


## 👨‍💻 Author

**Aditya Gupta**

This project helped me strengthen my understanding of C programming, tokenization, file handling, and the fundamentals of compiler design by implementing a lexical analyzer from scratch.
