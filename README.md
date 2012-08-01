Automatic-Header-file-including
===============================

This program will include header files required in your program by scanning the entire program given as input.
This program is using the man page in linux to get the details about the header files,so it will include header files
that corresponds to the man page entry of the methods used in your program.
NOTE
1.This program will include the header files of a C program
2.This will ignore user defined methods.
3.A message will be printed on the shell if there is no header file corresponding to a method(it is annoying so 
  i will trying to avoid this later)

This program is not fully tested with all the cases.But it will work fine for moderate length codes.
Sometimes it may detect stack smashing errors while including headers like '# include <sys/types.h>' (for the meth
od socket)since it is declared in man page as ' #include <sys/types.h>          /* See NOTES */'. since there are 
some extra characters(/* see NOTES */) along with the header file.The code is simple and it requires further debugging
to solve all the problems.But for almost all programs this will work fine.