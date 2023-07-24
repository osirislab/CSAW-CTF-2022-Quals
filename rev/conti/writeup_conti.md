# Conti writeup - Rev category

```json
{
  "name": "Conti",
  "category": "rev",
  "author": "awesome10billion, k3ma5",
  "description": "Can you recover my files :( my grandson downloaded a binary from a .pcap to send to a consultant...",
  "flag": "flag{Cyb3r_Pun4_!$_n0W1}"
  "type": "dynamic",
  "initial": "200"
  "minimum": "50"
  "decay": "75"
  "box": "rev.chal.csaw.io"
  "internal_port":"5000"
  "files": [ "Conti.exe","encryptedFiles.zip" ],
  }
 ```
 # Description
 In this challange, we extracted a binary from a .pcap file to be reversed engineered. We also provide the encrypted files in a zip file.
 
 # Deployment
 
 None
 
 # Flag
 The obtained flag is: "flag{Cyb3r_Pun4_!$_n0W1}"

 # Solution
1. launch conti.exe, notice it crashed with a .net style crash log
2. open with dnspy, realize it is a binary, open with exeinfope, strips ContiA8~Rip.dll which contains valid .net build info
3. reverse Encrypt function using dnspy, realize it is using Cha7539Engine class (salsa20 in reality since it is only using inherited functions init and processbytes), made a .net executor that imports ContiA8~Rip.dll and invoke function on EXTEN files
4. Read manifesto.pdf

total time was around 30 min max

# Alt Solution
By dropping the files into "encryptThese" and run Conti.exe again, it will process the files and automatically decrypt without further purposing. 

# Update
This has been patched in the current version of `Conti.exe`
