# nm-objdump
Epitech project: Nm is an unix program that list symbols and Objdump displays informations from object files.

<--------->

Usage: ./my_nm [option(s)] [file(s)] (a.out by default)	
 -A
 -o
 --print-file-name
 		Display the file name before the nm's value.
 -a
 --debug-syms
		Display all symbols, even debugger-only symbols; normally these are not listed.
 -l
 --line-numbers
		For each symbol, use debugging information to try to find a filename and line number.
 -n
 -v
 --numeric-sort
		Sort symbols numerically by their addresses, rather than alphabetically by their names.
 -p
 --no-sort
		Do not bother to sort the symbols in any order; print them in the order encountered.
 -r
 --reverse-sort
		Reverse the order of the sort (whether numeric or alphabetic); let the last come first.
 -S
 --print-size
		Print both value and size of defined symbols for the "bsd" output style.
 -u
 --undefined-only
		Display only undefined symbols (those external to each object file).
 --defined-only
		Display only defined symbols for each object file.
-h
--help
                Display the program help

<--------->

Usage: ./my_objdump [option(s)] [file(s)] (a.out by default)
-h
--help
                Display the program help
