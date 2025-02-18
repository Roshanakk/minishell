# Minishell

Minishell is a simple Unix shell implementation, the goal of this project is to create a functional shell that can execute commands, manage processes, and handle various shell features while demonstrating proficiency in system calls and process management.

<br>

## Features

- **Command Execution:** Execute both built-in and external commands.
- **Environment Variables:** Access and modify environment variables.
- **Input/Output Redirection:** Redirect input and output to and from files.
- **Pipes:** Connect commands using pipes to enable command chaining.
- **Signal Handling:** Gracefully handle signals like SIGINT.

<br>

## Run the project

```bash
git clone <link of the repo>
cd minishell
make
./minishell
```
 Welcome to our cute little shell !
<br><br>

## Usage
You can now run commands. Here are a few examples :
- Run a built-in command :


```bash
echo "Hi, stranger!"
```
- Redirect output to a file:
```bash
echo "Never gonna give you up" > rick_astley.txt
```

- Pipe commands :
```bash
cat rick_astley.txt | grep "never gonna let you down"
```

- Use heredoc :
```bash
cat << EOF
Oooooh
EOF
```
