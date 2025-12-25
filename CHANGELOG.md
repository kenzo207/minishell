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

### Changed
- Updated main.c to copy environment on startup
- Improved prompt display (only show if TTY)

### Fixed
- Fixed input.c raw mode lifecycle (enable/disable on each read)
- Fixed EOF handling (Ctrl-D) in input
- Fixed parsing logic errors in my_clean and has_special_chars
- Fixed env.c pointer initialization (NULL instead of '\0')
- Removed mysterious funt() call from execution.c

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
