## Minibash

**minibash** is a simple, lightweight shell implementation, designed to mimic basic functionalities of a Unix shell like Bash. This project allows users to execute commands, navigate directories, and perform basic shell operations. It was developed as part of a learning exercise to understand the inner workings of a shell and how processes communicate with each other using pipes.

![minibash](https://fmi4cg1yoq.ufs.sh/f/cVtZuJ9vUYxcPdW7JWeImnXUrEdi95YpZczCFG0ajfDPQ8b4)

## Features
- **Command Execution:** Run commands and programs.
- **Pipe Handling:** Support for piping outputs between commands (|).
- **Redirection:** Handle input and output redirection (>, >>, <).
- **Environment Variables:** Ability to use and modify environment variables.
- **Exit Status:** Return an exit status based on the success or failure of commands.
- **Command Parsing:** Parse commands and handle arguments properly.

## Building

**Warning: It is important to have the readline Library installed using homebrew for it to work**

```bash
    git clone https://github.com/hek3er/minibash.git
    cd minibash
    make
    ./minibash
```

## Usage

```bash
    $ ./minibash
    minibash$ ls
    minibash$ echo "Hello, World!"
    minibash$ cat file.txt > output.txt
```