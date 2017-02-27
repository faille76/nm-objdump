/*
** parser.c for parser in /objdump/src/
**
** Made by Frederic ODDOU
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Mon Feb 13 15:58:18 2017 Frederic ODDOU
** Last update Mon Feb 20 20:19:36 2017 Frederic ODDOU
*/

#include <string.h>
#include <stdio.h>
#include "parser.h"
#include "objdump.h"

t_flags_tab			g_flags_tab[] = {
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
