# TODO - Future Features & Backlog

## Known Limitations

### Current State
- Environment variables can be copied but setenv/unsetenv builtins need integration
- Pipelines work for single pipe but multi-command pipelines need improvement
- Heredoc not yet implemented
- Quote handling not yet implemented
- Variable expansion not yet implemented

## Planned Features

### High Priority
- [ ] Robust tokenizer with quote and operator support
- [ ] AST-based parser for proper precedence
- [ ] Complete redirection support (>, >>, <, <<)
- [ ] Multi-command pipeline execution
- [ ] Variable expansion ($VAR, $?, $$)
- [ ] Quote handling (single and double)

### Medium Priority
- [ ] Alias system (alias/unalias builtins)
- [ ] Command history (history builtin, !!, !n)
- [ ] Line editing improvements (arrow keys, Ctrl-A/E/K/U)
- [ ] Beautiful colored prompt
- [ ] Help builtin

### Low Priority (Bonus)
- [ ] Job control (& fg bg jobs)
- [ ] Backtick command substitution
- [ ] Advanced globbing (*, ?, [...])
- [ ] Tab completion
- [ ] Signal handling improvements (Ctrl-C, Ctrl-Z)
- [ ] Configuration file (~/.myshrc)

## Technical Debt
- [ ] Memory leak fixes in tokenizer
- [ ] FD leak prevention in pipelines
- [ ] Better error messages
- [ ] Code reorganization into subdirectories
- [ ] More comprehensive test coverage

## Documentation Needed
- [ ] UX customization guide (docs/UX.md)
- [ ] Architecture documentation
- [ ] API documentation for functions
- [ ] Examples and tutorials
