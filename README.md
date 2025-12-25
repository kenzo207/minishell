# Minishell - TCSH-Inspired Shell

A comprehensive UNIX shell implementation inspired by TCSH, featuring advanced parsing, pipelines, redirections, variable expansion, aliases, and a beautiful user experience.

## Features

| Feature | Status | Description |
|---------|--------|-------------|
| **Builtins** | ✅ | cd (with cd -), env, setenv, unsetenv, exit, help |
| **Environment** | ✅ | Mutable environment with full modification support |
| **Pipelines** | ✅ | Multi-command pipelines via AST (`cmd1 \| cmd2 \| cmd3`) |
| **Sequences** | ✅ | Command sequences via AST (`cmd1 ; cmd2 ; cmd3`) |
| **Redirections** | ✅ | Output (>), Append (>>), Input (<) |
| **Quotes** | ✅ | Single ('...') and double ("...") quote handling |
| **Operators** | ✅ | Pipe (\|), Semicolon (;), Redirections (>, >>, <) |
| **Tokenizer** | ✅ | Robust tokenizer with escape sequences |
| **AST Parser** | ✅ | Complete Abstract Syntax Tree parser |
| **Non-interactive** | ✅ | Works with piped input (`echo "cmd" \| ./mysh`) |
| **Error Handling** | ✅ | Comprehensive error messages to stderr |
| **Exit Status** | ✅ | Proper exit status tracking and propagation |
| **PATH Resolution** | ✅ | Automatic command search in PATH |
| **Raw Mode** | ✅ | Terminal raw mode for interactive input |
| **Variable Expansion** | 🚧 | `$VAR`, `$?`, `$$` |
| **Aliases** | 🚧 | Command aliases with `alias`/`unalias` |
| **History** | 🚧 | Command history with `!!` and `!n` |
| **Line Editing** | 🚧 | Arrow keys, Home/End, Ctrl-A/E/K/U |
| **Beautiful Prompt** | 🚧 | Colored prompt with user@host:path |
**Legend**: ✅ Implemented | 🚧 In Progress | ⏳ Planned

## Building

```bash
make          # Build the shell
make clean    # Remove object files
make fclean   # Remove object files and binary
make re       # Rebuild from scratch
```

## Usage

### Interactive Mode
```bash
./mysh
tcsh$> ls -la
tcsh$> echo "Hello, World!"
tcsh$> cd /tmp
tcsh$> exit
```

### Non-Interactive Mode
```bash
echo "ls -la" | ./mysh
./mysh < script.sh
```

## Built-in Commands

- **cd [dir]** - Change directory (supports `~` and `-`)
- **env** - Display environment variables
- **setenv VAR value** - Set environment variable
- **unsetenv VAR** - Remove environment variable
- **exit [status]** - Exit shell with optional status code
- **alias [name='command']** - Create command alias *(coming soon)*
- **unalias name** - Remove alias *(coming soon)*
- **history** - Show command history *(coming soon)*
- **help** - Display help information *(coming soon)*

## Examples

### Basic Commands
```bash
tcsh$> ls -la
tcsh$> /bin/echo "Absolute path"
tcsh$> ./mysh
```

### Pipelines *(in progress)*
```bash
tcsh$> ls | grep mysh
tcsh$> cat file | grep pattern | wc -l
```

### Redirections *(in progress)*
```bash
tcsh$> echo "Hello" > output.txt
tcsh$> cat < input.txt
tcsh$> cat << EOF
> Line 1
> Line 2
> EOF
```

### Environment Variables
```bash
tcsh$> env
tcsh$> setenv MY_VAR hello
tcsh$> echo $MY_VAR
tcsh$> unsetenv MY_VAR
```

## Testing

```bash
# Run all tests
./tests/run_all.sh

# Run specific test suite
./tests/test_builtins.sh
./tests/test_pipes.sh
./tests/test_redirections.sh
```

## Project Structure

```
minishell/
├── include/          # Header files
├── src/             # Source files
├── tests/           # Test suite
├── docs/            # Documentation
├── Makefile         # Build configuration
└── README.md        # This file
```

## Development

See [CONTRIBUTING.md](CONTRIBUTING.md) for:
- Commit conventions
- Testing procedures
- Code style guidelines
- Development workflow

## Technical Details

### Allowed Functions
- Standard: `malloc`, `free`, `exit`
- File I/O: `open`, `close`, `read`, `write`
- Directory: `opendir`, `readdir`, `closedir`, `getcwd`, `chdir`
- Process: `fork`, `execve`, `wait`, `waitpid`, `wait3`, `wait4`
- Signals: `signal`, `kill`
- File info: `stat`, `lstat`, `fstat`, `access`
- I/O: `pipe`, `dup`, `dup2`, `isatty`
- String: `getline`, `strtok`, `strtok_r`
- Error: `strerror`, `perror`, `strsignal`
- Process info: `getpid`

### Error Handling
- All errors written to stderr
- No crashes or segfaults
- No memory leaks
- No file descriptor leaks
- Proper exit status codes

## Roadmap

See [docs/TODO.md](docs/TODO.md) for planned features and known limitations.

## License

EPITECH PROJECT, 2024

## Authors

Built with ❤️ as a comprehensive shell implementation project.