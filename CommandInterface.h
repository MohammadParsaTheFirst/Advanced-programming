#ifndef COMMAND_INTERFACE_H
#define COMMAND_INTERFACE_H

#include <string>
#include <vector>
#include <memory>

// Forward declarations
class Circuit;

class CommandInterface {
public:
    CommandInterface();
    void processCommand(const std::string& command);

private:
    std::shared_ptr<Circuit> currentCircuit;
    std::vector<std::string> splitCommand(const std::string& input);

    double parseSpiceValue(const std::string& valueStr);

    void addResistor(const std::vector<std::string>& tokens);
    void addCapacitor(const std::vector<std::string>& tokens);
    void addInductor(const std::vector<std::string>& tokens);
    void addVoltageSource(const std::vector<std::string>& tokens);
    void addCurrentSource(const std::vector<std::string>& tokens);
    void addVCVS(const std::vector<std::string>& tokens);
    void addCCVS(const std::vector<std::string>& tokens);
    // Add similar for VCCS and CCCS

    void handleSpiceComponent(const std::vector<std::string>& tokens);
    void handleRename(const std::vector<std::string>& tokens);
    void handleLoad(const std::vector<std::string>& tokens);
    void handleAdd(const std::vector<std::string>& tokens);
    void handleList(const std::vector<std::string>& tokens);

    void analyze();
    void printHelp();
};

#endif // COMMAND_INTERFACE_H
