# Trojan
A simple virus(Trojan) aka client-server application written in C++ for Windows.

## Server(victim)
  * Copies itself(Trojan) to _%SYSTEM%_
  * Writes to the register(_"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"_)
  * Keylogger
  * Sniffer(in future)

## Client Console(hacker)

Use cmd:
```
Client [server_ip] [port] 
```

For example:
```
Client 127.0.0.1 1234
```

## Functions List

|Function                |Enabled|Name   |Args               |Notes            |
|------------------------|-------|-------|-------------------|-----------------|
|MessageBox              |   +   |message|\<str>             |str.length <= 128|
|RemoteDesktopView       |   -   |       |                   |                 |
|ViewWebcam              |   -   |       |                   |                 |
|RemoteKeyboardControlOn |   +   |kbon   |\<key>             |all opt          |
|RemoteKeyboardControlOff|   +   |kboff  |null               |                 |
|RemoteMouseControlOn    |   +   |mon    |\<x> \<y> \<button>|all opt          |
|RemoteMouseControlOff   |   +   |moff   |null               |                 |
|RemoteCmdLineAccess     |   +   |cmd    |\<str>             |str.length <= 128|
|FileEncryption          |   -   |       |                   |                 |
|ImportingFiles          |   -   |       |                   |                 |
|ExportingFiles          |   -   |       |                   |                 |
|InputBlockingOn         |   +   |bion   |null               |                 |
|InputBlockingOff        |   +   |bioff  |null               |                 |
|SoundPlaying            |      -|       |                   |                 |
