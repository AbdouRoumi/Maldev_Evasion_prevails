
#include <stdio.h>
#include <Windows.h>

//This technique is not a really good approach because calling IsDebuggerPresent is like asking security guard where is the cameras
//you can check MalwareEvasionTechniques Repo , the Anti_Debugging folder for more advanced techniques(Using Process Environment Block)

int main(void) {
	if (IsDebuggerPresent()) {
		puts("[-] a Debugger is present let's change what we do!");//here we put the behavior that we want while debugging
		MessageBoxW(NULL, L"just legitimate stuff", L"Nah you won't", MB_ICONEXCLAMATION | MB_HELP);
	}
	else {
		puts("[+] sa Debugger is not present let's do what we do!");//here we put normal behavior
		MessageBoxW(NULL, L"Malware here you're in a big trouble", L"Got u", MB_ICONEXCLAMATION | MB_HELP);
	}

	return EXIT_SUCCESS;
}