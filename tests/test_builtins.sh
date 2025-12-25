#!/bin/bash
# Basic builtin tests for minishell

SHELL="./mysh"
PASS=0
FAIL=0

echo "=== Testing Builtins ==="

# Test 1: env command
echo -n "Test 1: env command... "
if echo "env" | $SHELL | grep -q "PATH"; then
    echo "PASS"
    ((PASS++))
else
    echo "FAIL"
    ((FAIL++))
fi

# Test 2: cd command
echo -n "Test 2: cd /tmp... "
if echo -e "cd /tmp\npwd" | $SHELL 2>&1 | grep -q "/tmp"; then
    echo "PASS"
    ((PASS++))
else
    echo "FAIL"
    ((FAIL++))
fi

# Test 3: exit command
echo -n "Test 3: exit command... "
if echo "exit" | $SHELL > /dev/null 2>&1; then
    echo "PASS"
    ((PASS++))
else
    echo "FAIL"
    ((FAIL++))
fi

# Summary
echo ""
echo "=== Summary ==="
echo "Passed: $PASS"
echo "Failed: $FAIL"

if [ $FAIL -eq 0 ]; then
    exit 0
else
    exit 1
fi
