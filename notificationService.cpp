/*
Below is a simple, step-by-step summary of the SOLID principles and how to apply them:

1. Single Responsibility Principle (SRP):
    Identify each class’s one unique responsibility.
    Ensure that every class has only one reason to change.

2. Open/Closed Principle (OCP):
    Design classes so they are open to extension (e.g., via inheritance or interfaces) but closed to modification.
    Add new functionality by extending the class rather than altering existing code.

3. Liskov Substitution Principle (LSP):
    Ensure that any subclass can replace its parent class without breaking the application.
    Maintain the expected behavior defined by the base class in all derived classes.

4. Interface Segregation Principle (ISP):
    Create small, focused interfaces rather than large, general-purpose ones.
    Clients should only depend on the methods they actually need.

5. Dependency Inversion Principle (DIP):
    Depend on abstractions (interfaces or abstract classes) rather than on concrete implementations.
    Use techniques like dependency injection to decouple high-level modules from low-level modules.

By following these steps, you ensure that your code is modular, maintainable, and easily extendable.
*/


// Below is the same example code, with inline comments explaining each SOLID principle:

#include <iostream>
#include <memory>
#include <string>

// -------------------------------------------
// 1. Single Responsibility Principle (SRP)
// -------------------------------------------
// This class is solely responsible for formatting messages.
// Its only job is to prepare a formatted notification message,
// without handling sending or logging.
class MessageFormatter
{
  public:
    std::string formatMessage(const std::string &recipient, const std::string &content)
    {
        return "Dear " + recipient + ", " + content;
    }
};

// -------------------------------------------
// 2. Open/Closed Principle (OCP)
// -------------------------------------------
// We define an abstract interface INotifier to generalize the process of sending notifications.
// This allows us to extend notification types (like email or SMS) without modifying existing code.
class INotifier
{
  public:
    virtual void send(const std::string &message) = 0;
    virtual ~INotifier() = default;
};

// Email notification implementation
class EmailNotifier : public INotifier
{
  public:
    void send(const std::string &message) override
    {
        std::cout << "Sending Email: " << message << std::endl;
    }
};

// SMS notification implementation
class SMSNotifier : public INotifier
{
  public:
    void send(const std::string &message) override
    {
        std::cout << "Sending SMS: " << message << std::endl;
    }
};

// -------------------------------------------
// 3. Liskov Substitution Principle (LSP)
// -------------------------------------------
// Any derived class (like EmailNotifier or SMSNotifier) can be used wherever an INotifier is expected,
// without changing the behavior of the client code.
void notifyUser(INotifier &notifier, const std::string &message)
{
    notifier.send(message);
}

// -------------------------------------------
// 4. Interface Segregation Principle (ISP)
// -------------------------------------------
// We define a separate interface for logging functionalities,
// so classes that don't need logging are not forced to implement it.
class ILogger
{
  public:
    virtual void log(const std::string &info) = 0;
    virtual ~ILogger() = default;
};

class ConsoleLogger : public ILogger
{
  public:
    void log(const std::string &info) override
    {
        std::cout << "Logging: " << info << std::endl;
    }
};

// -------------------------------------------
// 5. Dependency Inversion Principle (DIP)
// -------------------------------------------
// Here we create a NotificationService that depends on abstractions (INotifier and ILogger)
// instead of concrete implementations. Dependencies are injected via the constructor.
class NotificationService
{
  private:
    std::unique_ptr<INotifier> notifier; // depends on the abstraction
    std::unique_ptr<ILogger> logger;     // depends on the abstraction
    MessageFormatter formatter;          // responsible only for formatting (SRP)
  public:
    // Dependencies are injected through the constructor
    NotificationService(std::unique_ptr<INotifier> notifier, std::unique_ptr<ILogger> logger)
        : notifier(std::move(notifier)), logger(std::move(logger)) {}

    void sendNotification(const std::string &recipient, const std::string &content)
    {
        // Use the MessageFormatter to prepare the message
        std::string message = formatter.formatMessage(recipient, content);
        // Send the notification using the provided notifier (could be EmailNotifier, SMSNotifier, etc.)
        notifier->send(message);
        // Log the event using the provided logger
        logger->log("Notification sent to " + recipient);
    }
};

int main()
{
    // Example 1: Using EmailNotifier
    auto emailNotifier = std::make_unique<EmailNotifier>();
    auto consoleLogger = std::make_unique<ConsoleLogger>();

    NotificationService service(std::move(emailNotifier), std::move(consoleLogger));
    service.sendNotification("John", "Your order has been shipped!");

    // Example 2: Using SMSNotifier (we can easily switch the notifier without modifying NotificationService)
    auto smsNotifier = std::make_unique<SMSNotifier>();
    NotificationService service2(std::move(smsNotifier), std::make_unique<ConsoleLogger>());
    service2.sendNotification("Alice", "Your appointment is confirmed!");

    return 0;
}