#!/bin/bash
# Basic execution tests for minishell

SHELL="./mysh"
PASS=0
FAIL=0

echo "=== Testing Command Execution ==="

# Test 1: Execute /bin/ls
echo -n "Test 1: /bin/ls... "
if echo "/bin/ls" | $SHELL > /dev/null 2>&1; then
    echo "PASS"
    ((PASS++))
else
    echo "FAIL"
    ((FAIL++))
fi

# Test 2: Execute ls via PATH
echo -n "Test 2: ls (via PATH)... "
if echo "ls" | $SHELL > /dev/null 2>&1; then
    echo "PASS"
    ((PASS++))
else
    echo "FAIL"
    ((FAIL++))
fi

# Test 3: Command not found
echo -n "Test 3: nonexistent command... "
if echo "nonexistentcommand123" | $SHELL 2>&1 | grep -q "Command not found"; then
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
