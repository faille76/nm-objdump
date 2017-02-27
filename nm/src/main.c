/*
** main.c for main in /nm/src/
**
** Made by Frederic ODDOU
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Mon Feb 13 14:12:40 2017 Frederic ODDOU
** Last update Fri Feb 24 08:24:19 2017 Frederic ODDOU
*/

#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include "parser.h"
#include "nm.h"

char *g_prog_name = NULL;
char *g_file_name = NULL;
enum e_architecture g_architecture = A64BITS;

static int		exec_file_name(t_flag	flags,
				       char	*name,
				       int	file)
{
  int			fd;
  struct stat		buf;

  g_file_name = name;
  if ((fd = open(g_file_name, O_RDONLY)) <= 0)
    {
      fprintf(stderr, "%s: '%s': No such file\n", g_prog_name, g_file_name);
      return (1);
    }
  if (fstat(fd, &buf) || S_ISDIR(buf.st_mode))
    {
      close(fd);
      fprintf(stderr, "%s: Warning: '%s' is not an ordinary file\n",
	      g_prog_name, g_file_name);
      return (1);
    }
  if (!open_file(flags, file, fd))
    {
      close(fd);
      return (1);
    }
  close(fd);
  return (0);
}

static int		count_file(int		ac,
				   char		**av)
{
  int			file;

  file = 0;
  while (--ac)
    {
      if (strncmp(F_N_STRICT_FORMAT, av[ac], L_F_N_STRICT_FORMAT))
	file++;
    }
  return (file);
}

static int		exec_file(int		ac,
				  char		**av,
				  t_flag	flags)
{
  int			i;
  int			error;
  int			file;

  i = 1;
  error = 0;
  file = count_file(ac, av);
  while (i < ac)
    {
      if (strncmp(F_N_STRICT_FORMAT, av[i], L_F_N_STRICT_FORMAT))
	error += exec_file_name(flags, av[i], file);
      i++;
    }
  if (!file)
    error += exec_file_name(flags, "a.out", file);
  return (error);
}

int			main(int		ac,
			     char		**av)
{
  char			flags[FLAG_NONE];

  g_prog_name = av[0];
  if (!parser_flags(ac, av, flags))
    return (EXIT_FAILURE);
  if (exec_file(ac, av, flags))
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
