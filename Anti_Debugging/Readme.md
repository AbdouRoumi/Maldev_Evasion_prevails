
# **Anti-Debugging: IsDebuggerPresent Technique**  

## 📌 Overview  
This simple example demonstrates **anti-debugging** using `IsDebuggerPresent()`. The goal is to detect if a **debugger** is attached to the process and modify behavior accordingly.  

📌 **Important Note:**  
This technique is **not the most effective** since `IsDebuggerPresent()` is easily detectable. Advanced malware avoids this approach in favor of **PEB-based** or **timing-based** detection techniques.  

## 🛠 How It Works  
- If a **debugger is attached**, the malware will execute **safe behavior**, pretending to be legitimate.  
- If **no debugger is detected**, the malware will execute **malicious behavior**.  

### 🔍 **Behavior**  
| Debugger Attached? | Output Behavior |
|--------------------|----------------|
| ✅ Yes  | Prints `[-] a Debugger is present`, displays a harmless message box. |
| ❌ No   | Prints `[+] No Debugger detected`, executes the malicious behavior. |

## 🔧 Requirements  
- **Windows OS**  
- **Visual Studio / MinGW** (to compile the code)  

## 💻 Compilation & Execution  
### Compile using **Visual Studio Developer Command Prompt**:  
```bash
cl anti_debugging.c /Fe:anti_debugging.exe
```
### Compile using **MinGW (GCC)**:  
```bash
gcc anti_debugging.c -o anti_debugging.exe -Wall
```
### Run the Executable:  
```bash
anti_debugging.exe
```

## 🚀 Advanced Techniques  
For **better anti-debugging methods**, refer to:  
- **Process Environment Block (PEB) checks**  
- **NtQueryInformationProcess() API**  
- **Timing-based detection**  

🔗 Check out the **MalwareEvasionTechniques** repository for more advanced evasion strategies!  
