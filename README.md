# Trojan
A simple virus(Trojan) aka client-server application written in C for Windows.

## Server(victim)
  * Copies itself(Trojan) to _%SYSTEM%_
  * Writes to the register(_"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"_)

## Client(hacker)

Use cmd:
```
Client [ip] [command] [command arguments]
```

For example:
```
Client 127.0.0.1 message HelloWorld!
```

**Functions List**

|Function             |Enabled|
|---------------------|-------|
|RemoteDesctopView    |      -|
|RemoteKeyboardControl|      -|
|RemoteMouseControl   |      -|
|RemoteCmdLineAccess  |      -|
|MessageBox           |      +|
|FileEncryption       |      -|
|CopyingFiles         |      -|
|InputBlocking        |      -|
|SoundPlaying         |      -|
