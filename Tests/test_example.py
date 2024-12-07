import example_module

# Simple test cases
print("Testing add function...")
assert example_module.add(3, 4) == 7, "Test failed: 3 + 4 should equal 7"
assert example_module.add(-1, 1) == 0, "Test failed: -1 + 1 should equal 0"
assert example_module.add(0, 0) == 0, "Test failed: 0 + 0 should equal 0"

print("All tests passed!")

# Example usage
result = example_module.add(10, 20)
print(f"10 + 20 = {result}")