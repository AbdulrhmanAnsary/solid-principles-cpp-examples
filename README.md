# SOLID Principles C++ Examples

This repository contains examples that demonstrates the applications of the SOLID principles in C++.

## Overview

The example code illustrates the following SOLID principles:

1. **Single Responsibility Principle (SRP):**
   - Each class has one unique responsibility.
   - Changes in functionality affect only one class.

2. **Open/Closed Principle (OCP):**
   - Classes are designed to be open for extension but closed for modification.
   - New functionality is added by extending the class (via interfaces or inheritance) rather than modifying the existing code.

3. **Liskov Substitution Principle (LSP):**
   - Derived classes can replace their base classes without affecting the correctness of the program.
   - All subclasses maintain the behavior expected from the base class.

4. **Interface Segregation Principle (ISP):**
   - Create small, focused interfaces instead of large, general-purpose ones.
   - Clients only depend on the methods they actually need.

5. **Dependency Inversion Principle (DIP):**
   - High-level modules depend on abstractions rather than concrete implementations.
   - Dependency injection is used to decouple high-level and low-level modules.

## How to Compile and Run

Ensure you have a C++ compiler that supports C++11 or later. For example, using `g++`:

```bash
g++ -std=c++11 notificationService.cpp -o notificationService
./notificationService
```

## Contributing

Feel free to open issues or pull requests if you have suggestions for improvements or additional examples.

## License

This project is licensed under the MIT License. See the [LICENSE](/LICENSE) file for details.
