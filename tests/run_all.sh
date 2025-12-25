#!/bin/bash
# Master test runner

echo "======================================"
echo "  Minishell Test Suite"
echo "======================================"
echo ""

TOTAL_PASS=0
TOTAL_FAIL=0

# Run builtin tests
if [ -f tests/test_builtins.sh ]; then
    bash tests/test_builtins.sh
    if [ $? -eq 0 ]; then
        ((TOTAL_PASS++))
    else
        ((TOTAL_FAIL++))
    fi
    echo ""
fi

# Run execution tests
if [ -f tests/test_execution.sh ]; then
    bash tests/test_execution.sh
    if [ $? -eq 0 ]; then
        ((TOTAL_PASS++))
    else
        ((TOTAL_FAIL++))
    fi
    echo ""
fi

# Final summary
echo "======================================"
echo "  Final Results"
echo "======================================"
echo "Test suites passed: $TOTAL_PASS"
echo "Test suites failed: $TOTAL_FAIL"
echo ""

if [ $TOTAL_FAIL -eq 0 ]; then
    echo "✓ All tests passed!"
    exit 0
else
    echo "✗ Some tests failed"
    exit 1
fi
