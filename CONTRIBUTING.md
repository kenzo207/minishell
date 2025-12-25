# Contributing to Minishell

## Project Structure

```
minishell/
├── include/          # Header files
│   ├── shell.h      # Main shell structures and functions
│   └── my.h         # Utility functions
├── src/             # Source files
│   ├── main.c       # Entry point
│   ├── parsing.c    # Tokenizer and parser
│   ├── execution.c  # Command execution and pipelines
│   ├── builtins.c   # Built-in commands
│   ├── env.c        # Environment management
│   ├── input.c      # Line reading and editing
│   ├── utils.c      # Utility functions
│   └── errors.c     # Error handling
├── tests/           # Test suite
└── docs/            # Documentation
```

## Commit Conventions

We follow a strict commit message format for clarity and traceability:

### Format
```
<type>: <short description>

[optional body]
```

### Types
- `init:` - Initial setup and configuration
- `feat:` - New features
- `fix:` - Bug fixes
- `parser:` - Parser improvements
- `exec:` - Execution engine changes
- `builtin:` - Built-in command changes
- `tests:` - Test additions/changes
- `docs:` - Documentation updates
- `ux:` - User experience improvements
- `refactor:` - Code refactoring

### Examples
```
init: add .gitignore for build artifacts
feat: implement heredoc redirection (<<)
fix: correct pipe FD leaks in execution
parser: add quote handling to tokenizer
builtin: add alias command
tests: add pipeline integration tests
docs: update README with features table
ux: implement colored prompt
refactor: extract cd logic to separate function
```

## Commit Frequency

**CRITICAL**: Make **atomic commits** frequently (every 10-30 minutes or after each small unit of work).

- Each commit should be small, isolated, and testable
- After each commit, run `make re` minimum
- Update CHANGELOG.md for significant commits

## Testing

### Build Test
```bash
make re
```
Must complete without errors.

### Running Tests
```bash
# Run all tests
./tests/run_all.sh

# Run specific test suite
./tests/test_builtins.sh
./tests/test_pipes.sh
./tests/test_redirections.sh
```

### Adding Tests
1. Create test script in `tests/` directory
2. Make it executable: `chmod +x tests/test_name.sh`
3. Add to `tests/run_all.sh`
4. Test should return 0 on success, non-zero on failure

## Code Style

- Use clear, descriptive variable names
- Add comments for complex logic
- Keep functions focused and small
- Handle errors gracefully (no crashes, no leaks)
- All errors go to stderr
- Free all allocated memory
- Close all file descriptors

## Debugging

### Memory Leaks
```bash
valgrind --leak-check=full --show-leak-kinds=all ./mysh
```

### FD Leaks
```bash
# While mysh is running
ls -la /proc/$(pgrep mysh)/fd
```

### Build with Debug Symbols
```bash
gcc -g -O0 $(SRCS) -o mysh
gdb ./mysh
```

## Development Workflow

1. **Understand the task** - Read requirements carefully
2. **Plan the change** - Think about impact and dependencies
3. **Implement** - Write clean, focused code
4. **Test** - Run `make re` and relevant tests
5. **Commit** - Use proper commit message format
6. **Update CHANGELOG** - Add entry for significant changes
7. **Repeat** - Keep commits small and frequent

## Questions?

Check the documentation in `docs/` or examine existing code for patterns.
