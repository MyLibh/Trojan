# Trojan
A simple virus(Trojan) aka client-server application written in C++ for Windows.

## Server(victim)
  * Copies itself(Trojan) to _%SYSTEM%_
  * Writes to the register(_"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"_)
  * Keylogger
  * Sniffer(in future)

## Client(hacker)

Use cmd:
```
Client [server_ip] [port] 
```

For example:
```
Client 127.0.0.1 1234
```

## Functions List

|Function             |Enabled|
|---------------------|-------|
|MessageBox           |      -|
|RemoteDesktopView    |      -|
|ViewWebcam           |      -|
|RemoteKeyboardControl|      -|
|RemoteMouseControl   |      -|
|RemoteCmdLineAccess  |      -|
|FileEncryption       |      -|
|ImportingFiles       |      -|
|ExportingFiles       |      -|
|InputBlocking        |      -|
|SoundPlaying         |      -|
