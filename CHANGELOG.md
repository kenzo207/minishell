# Changelog

All notable changes to this project will be documented in this file.

## [Unreleased]

### Added
- Initial project setup with .gitignore
- CHANGELOG.md for tracking changes
- CONTRIBUTING.md with development guidelines
- Environment management functions (copy_env, my_setenv_full, my_unsetenv)
- Shell state structure for mutable environment
- Non-interactive mode support (no prompt if stdin is not TTY)
- Test infrastructure (test_builtins.sh, test_execution.sh, run_all.sh)
- docs/TODO.md for backlog tracking
- setenv/unsetenv builtins with full environment modification
- exit builtin with status code support
- cd - (previous directory) support with OLDPWD
- help builtin with comprehensive documentation
- **Robust tokenizer with quote and operator support**
- **Complete AST parser (command, pipeline, sequence nodes)**
- **AST executor with redirection support**
- **Output redirection (>)**
- **Append redirection (>>)**
- **Input redirection (<)**
- **Pipeline execution via AST**
- **Sequence execution via AST**
- RESUME_FINAL.md comprehensive summary

### Changed
- Updated main.c to copy environment on startup
- Improved prompt display (only show if TTY)
- Fixed read_command_line to check isatty before enabling raw mode
- Updated entire execution chain to use shell_state_t
- Enhanced cd builtin with better error messages (ENOTDIR, ENOENT, EACCES)
- **Replaced legacy parsing with tokenizer → parser → AST → executor chain**
- **Simplified main shell loop using AST execution**

### Fixed
- Fixed input.c raw mode lifecycle (enable/disable on each read)
- Fixed EOF handling (Ctrl-D) in input
- Fixed parsing logic errors in my_clean and has_special_chars
- Fixed env.c pointer initialization (NULL instead of '\0')
- Removed mysterious funt() call from execution.c
- Fixed non-interactive mode (shell now works with piped input)
- Fixed help builtin recognition in move() function
- Fixed duplicate type definitions in tokenizer.c and ast.c
- Fixed PATH parsing in AST executor

### Removed

---

## Format
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
