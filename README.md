# Huffman-Archivator

## This application implements the Huffman algorithm for compressing and decompressing files

Huffman algorithm : https://www.geeksforgeeks.org/greedy-algorithms-set-3-huffman-coding/


The input is recieved from the command line. The first parameter indicates which operation to perform. 
Possible operations are as follows:

**-Pack**
Compressing. In this case, after the command is given a path to the directory which needs to be processed
and the name of the archive file which needs to be created.
For example:
> Archive.exe -Pack C:\Test C:\Temp\myfile.arc

**-Unpack** 
Decompressing. In this case, after the command is given a path to an existing archive 
and a path to the directory in which it needs to be unpacked. 
For example:
> Archive.exe -Unpack C:\Temp\myfile.arc C:\AnotherDirectory\

**-List**
Shows the content of an archive. In this case, after the command is given a path to an exising archive.
As output we get a list of the names of all files and directories contained in it.
For example:
> Archive.exe -List C:\Temp\myfile.arc
