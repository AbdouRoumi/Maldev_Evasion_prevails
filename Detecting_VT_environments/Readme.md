# Windows Malware with Anti-VM Techniques

## Overview
This program is a Windows-based executable that contains a shellcode payload with basic anti-virtual machine (anti-VM) detection techniques. The program checks for various system characteristics that indicate execution in a virtualized environment before proceeding to execute the shellcode.

## Features
- **Encoded Shellcode Execution**: The program includes an encoded shellcode payload, which is decoded using an XOR operation before execution.
- **Anti-VM Checks**: It detects virtualization by checking:
  - **CPU Count**: Exits if fewer than 2 CPUs are detected.
  - **RAM Size**: Exits if less than 2GB of RAM is available.
  - **HDD Size**: Exits if the primary disk size is below a threshold.
  - **MAC Address Filtering**: Checks for known MAC addresses associated with virtualization software (VMware, VirtualBox, Hyper-V, Parallels, QEMU) and exits if found.
- **User Interaction**: Displays a message box with a question to engage with the user.
- **Shellcode Execution**: Allocates memory, copies the decoded shellcode, and executes it in a new thread.

## How It Works
1. The program first checks the number of processors and available memory.
2. It retrieves and evaluates the size of the primary hard disk.
3. It examines the MAC address of network adapters to detect virtualized environments.
4. If the system passes these checks, it prompts the user with a message box.
5. If the program determines that it is running in a non-VM environment, it proceeds to execute the shellcode.

## Prerequisites
- Windows operating system.
- A compiler supporting Windows API calls (e.g., MinGW, Microsoft Visual Studio).

## Compilation
To compile the program, use a compiler such as MinGW or MSVC:
```sh
cl /EHsc /MD /DYNAMICBASE /NXCOMPAT malware.cpp /link psapi.lib iphlpapi.lib
```

## Usage
1. Compile the source code to an executable.
2. Run the executable on a Windows system.
3. If executed in a VM, the program will exit before executing the shellcode.

## Security & Ethical Considerations
- **Educational Use Only**: This code is intended for research and learning purposes.
- **Legal Compliance**: Running malware on unauthorized systems is illegal. Ensure you have explicit permission before testing this code.
- **Detection Evasion**: The anti-VM techniques are common methods used by malware to avoid detection in sandboxed environments.

## Notes
- The shellcode is XOR-encoded with a key (`0xAA`) and must be decoded before execution.
- The message box prompt (`"Do you love ESTIN?"`) is an example of a social engineering trick that can be modified.
- Further obfuscation techniques can be added to make analysis harder for security researchers.

## Disclaimer
This program is for educational and research purposes only. The author is not responsible for any misuse of this code.

