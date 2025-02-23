## Code Signing Steps

Follow these steps to sign your executable using SignTool.

### 1. Set Up the Password
```powershell
$password = ConvertTo-SecureString -String "MyStrongPassword!" -Force -AsPlainText
```

### 2. Retrieve Certificate Thumbprint
```powershell
Get-ChildItem Cert:\CurrentUser\My
```
Identify the correct certificate thumbprint from the output.

### 3. Export the Certificate
```powershell
Export-PfxCertificate -Cert "Cert:\CurrentUser\My\7F773C6B3363F38BE236E8283B46A02453E97F12" -FilePath C:\Users\rabdo\myshellcodesigner.pfx -Password $password
```

### 4. Navigate to SignTool Directory
```powershell
cd C:\Users\rabdo\source\SignTool\Releases\SignTool-10.0.26100.8-x64
```

### 5. Sign the Executable
```powershell
.\signtool.exe sign /f C:\Users\rabdo\myshellcodesigner.pfx /p MyStrongPassword! /fd SHA256 /tr http://timestamp.digicert.com /td SHA256 C:\Users\rabdo\source\malware_x64.exe
```

### Notes:
- Ensure you have the correct certificate thumbprint before exporting.
- Adjust paths based on your actual file locations.
- This will timestamp the signature using **DigiCert's timestamp server**.

