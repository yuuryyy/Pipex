# 🚰 pipex

*Because the shell pipe `|` is too mainstream.* **pipex** is a UNIX logic project at 1337 (42 Network) that challenges you to recreate the exact behavior of the standard shell pipe operator using C.

---

## 📖 About The Project

In a standard UNIX shell, the `|` operator takes the standard output of one command and connects it to the standard input of the next. 

The goal of this project is to build a program that handles this data stream redirection manually. You must read from an input file, process the data through a first command, pipe the result into a second command, and finally output the result to a specified file.

### 🎯 Core Objectives
* Master **Inter-Process Communication (IPC)** using the `pipe()` function.
* Understand process creation and management using `fork()`.
* Manipulate standard file descriptors (`stdin`, `stdout`) using `dup2()`.
* Safely execute shell commands using `execve()` and parse system environment variables (the `$PATH`).
* Prevent zombie processes and manage memory flawlessly.

---

## ⚙️ How It Works

The program must be executed with exactly four arguments:
```bash
./pipex file1 cmd1 cmd2 file2
```

This execution must behave *exactly* the same as the following shell command:
```bash
< file1 cmd1 | cmd2 > file2
```

### The Underlying Mechanics:
1. **Open Files:** `file1` is opened in read-only mode, and `file2` is opened in write/truncate mode.
2. **Create a Pipe:** A data channel is created using `pipe()`, generating two file descriptors (a read end and a write end).
3. **First Child Process:** The program forks. The child redirects its standard input to `file1` and its standard output to the write end of the pipe, then executes `cmd1`.
4. **Second Child Process:** The program forks again. This child redirects its standard input to the read end of the pipe and its standard output to `file2`, then executes `cmd2`.
5. **Parent Process:** The parent waits for the children to finish execution to prevent zombie processes.

---

## 🛠️ Getting Started

### Prerequisites
* A standard C compiler (`cc`, `gcc`, or `clang`)
* `make` utility

### Installation & Compilation

1. Clone the repository:
   ```bash
   git clone git@github.com:yuuryyy/Pipex.git
   cd Pipex
   ```

2. Compile the executable:
   ```bash
   make
   ```

### Makefile Rules
* `make` / `make all`: Compiles the `pipex` executable.
* `make clean`: Removes the compiled `.o` object files.
* `make fclean`: Removes the object files and the executable.
* `make re`: Runs `fclean` followed by `all`.

---

## 💻 Usage & Examples

Run the program by specifying an input file, two commands, and an output file.

**Example 1: Word Count**
```bash
# Using pipex:
./pipex infile "ls -l" "wc -l" outfile

# Equivalent to:
< infile ls -l | wc -l > outfile
```

**Example 2: Grep and Output**
```bash
# Using pipex:
./pipex infile "grep Hello" "awk '{print $1}'" outfile

# Equivalent to:
< infile grep Hello | awk '{print $1}' > outfile
```

*(Note: Ensure your `infile` exists and you have the correct read/write permissions for the execution directory).*

---
*Developed by Youssra Chagri at 1337 (UM6P).*
