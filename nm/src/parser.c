/*
** parser.c for parser in /nm/src/
**
** Made by Frederic ODDOU
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Mon Feb 13 15:58:18 2017 Frederic ODDOU
** Last update Sat Feb 18 21:22:54 2017 Frederic ODDOU
*/

#include <string.h>
#include <stdio.h>
#include "parser.h"
#include "nm.h"

t_flags_tab			g_flags_tab[] = {
  {"A", FLAG_PRINT_FILE_NAME, FLAG_NON_STRICT, NULL},
  {"o", FLAG_PRINT_FILE_NAME, FLAG_NON_STRICT, NULL},
  {"print-file-name", FLAG_PRINT_FILE_NAME, FLAG_STRICT,
   "Display the file name before the nm's value."},
  {"a", FLAG_DEBUG_SYMS, FLAG_NON_STRICT, NULL},
  {"debug-syms", FLAG_DEBUG_SYMS, FLAG_STRICT,
   "Display all symbols, even debugger-only symbols; normally \
these are not listed."},
  {"l", FLAG_LINE_NUMBER, FLAG_NON_STRICT, NULL},
  {"line-numbers", FLAG_LINE_NUMBER, FLAG_STRICT,
   "For each symbol, use debugging information to try to find a \
filename and line number."},
  {"n", FLAG_NUMERIC_SORT, FLAG_NON_STRICT, NULL},
  {"v", FLAG_NUMERIC_SORT, FLAG_NON_STRICT, NULL},
  {"numeric-sort", FLAG_NUMERIC_SORT, FLAG_STRICT,
   "Sort symbols numerically by their addresses, rather than alphabetically \
by their names."},
  {"p", FLAG_NO_SORT, FLAG_NON_STRICT, NULL},
  {"no-sort", FLAG_NO_SORT, FLAG_STRICT,
   "Do not bother to sort the symbols in any order; print them in the \
order encountered."},
  {"r", FLAG_REVERSE_SORT, FLAG_NON_STRICT, NULL},
  {"reverse-sort", FLAG_REVERSE_SORT, FLAG_STRICT,
   "Reverse the order of the sort (whether numeric or alphabetic); let \
the last come first."},
  {"S", FLAG_PRINT_SIZE, FLAG_NON_STRICT, NULL},
  {"print-size", FLAG_PRINT_SIZE, FLAG_STRICT,
   "Print both value and size of defined symbols for the \"bsd\" \
output style."},
  {"u", FLAG_UNDEFINED_ONLY, FLAG_NON_STRICT, NULL},
  {"undefined-only", FLAG_UNDEFINED_ONLY, FLAG_STRICT,
   "Display only undefined symbols (those external to each object file)."},
  {"defined-only", FLAG_DEFINED_ONLY, FLAG_STRICT,
   "Display only defined symbols for each object file."},
  {"", FLAG_NONE, FLAG_STRICT, ""},
};

static bool	parser_flags_arg_strict(char		*arg,
					t_flag		flags)
{
  int		i_tab;

  i_tab = 0;
  while (g_flags_tab[i_tab].id != FLAG_NONE)
    {
      if (g_flags_tab[i_tab].strict == FLAG_STRICT &&
	  !strcmp(arg, g_flags_tab[i_tab].flag))
	{
	  flags[g_flags_tab[i_tab].id] = 1;
	  return (true);
	}
      i_tab++;
    }
  return (false);
}

static bool	parser_flags_arg_non_strict(char	*arg,
					    t_flag	flags)
{
  int		i_tab;
  bool		is_ok;

  while (*arg)
    {
      is_ok = false;
      i_tab = 0;
      while (!is_ok && g_flags_tab[i_tab].id != FLAG_NONE)
	{
	  if (g_flags_tab[i_tab].strict == FLAG_NON_STRICT &&
	      !strncmp(arg, g_flags_tab[i_tab].flag, 1))
	    {
	      flags[g_flags_tab[i_tab].id] = 1;
	      is_ok = true;
	    }
	  i_tab++;
	}
      if (!is_ok)
	return (false);
      arg++;
    }
  return (true);
}

static bool	parser_flags_display_help()
{
  int		i_tab;

  i_tab = 0;
  printf("\033[32mUsage: %s [option(s)] [file(s)] (a.out by default)\033[0m\n",
	 g_prog_name);
  while (g_flags_tab[i_tab].id != FLAG_NONE)
    {
      printf("\033[31m");
      if (g_flags_tab[i_tab].strict == FLAG_STRICT)
	printf(" %s", F_STRICT_FORMAT);
      else if (g_flags_tab[i_tab].strict == FLAG_NON_STRICT)
	printf(" %s", F_N_STRICT_FORMAT);
      printf("%s\033[0m", g_flags_tab[i_tab].flag);
      if (g_flags_tab[i_tab].message != NULL)
	printf("\n\t\t%s", g_flags_tab[i_tab].message);
      printf("\n");
      i_tab++;
    }
  return (false);
}

bool		parser_flags(int			ac,
			     char			**av,
			     t_flag			flag)
{
  int		i;
  bool		is_ok;

  memset(flag, 0, FLAG_NONE);
  i = 1;
  while (i < ac)
    {
      is_ok = true;
      if (!strcmp("-h", av[i]) || !strcmp("--help", av[i]))
	return (parser_flags_display_help());
      else if (!strncmp(F_STRICT_FORMAT, av[i], L_F_STRICT_FORMAT))
	is_ok = parser_flags_arg_strict(&av[i][L_F_STRICT_FORMAT], flag);
      else if (!strncmp(F_N_STRICT_FORMAT, av[i], L_F_N_STRICT_FORMAT))
	is_ok = parser_flags_arg_non_strict(&av[i][L_F_N_STRICT_FORMAT], flag);
      if (!is_ok)
	{
	  fprintf(stderr, "%s: invalid option '%s'\n", g_prog_name, av[i]);
	  return (parser_flags_display_help());
	}
      i++;
    }
  return (true);
}
