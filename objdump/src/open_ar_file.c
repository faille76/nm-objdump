/*
** open_ar_file.c for ar file in /objdump/src/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sun Feb 19 03:15:58 2017 Frederic ODDOU
** Last update Tue Feb 21 01:18:07 2017 Fredoddou
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "objdump.h"

int			g_header_ar_size = 0;
char			*g_header_ar = NULL;

static bool		get_ar_hdr(int			fd,
				   struct ar_hdr	**ar)
{
  if (*ar == NULL)
    {
      if (!(*ar = calloc(1, SIZE_AR_STRUCT + 1)))
	return (false);
    }
  if (read(fd, *ar, SIZE_AR_STRUCT) != SIZE_AR_STRUCT)
    {
      free(*ar);
      *ar = NULL;
      return (false);
    }
  ((char *)*ar)[SIZE_AR_STRUCT] = 0;
  if (memcmp((*ar)->ar_fmag, MAGIC_AR_END, strlen(MAGIC_AR_END)))
    {
      free(*ar);
      *ar = NULL;
      return (false);
    }
  return (true);
}

static char		*get_flex_hdr(int		fd,
				      struct ar_hdr	*ar)
{
  if (g_header_ar != NULL)
    free(g_header_ar);
  g_header_ar_size = atoi(ar->ar_size);
  if (!(g_header_ar = calloc(1, sizeof(char) * g_header_ar_size + 1)))
    return (NULL);
  if ((read(fd, g_header_ar, g_header_ar_size)) != g_header_ar_size)
    {
      free(g_header_ar);
      return (NULL);
    }
  g_header_ar[g_header_ar_size] = '\0';
  return (g_header_ar);
}

static bool		confirm_ar_file(int		fd)
{
  struct ar_hdr		*ar;

  ar = NULL;
  if (!get_ar_hdr(fd, &ar))
    return (false);
  if (!(get_flex_hdr(fd, ar)))
    return (false);
  free(g_header_ar);
  g_header_ar = NULL;
  if (!get_ar_hdr(fd, &ar))
    return (false);
  if (!(get_flex_hdr(fd, ar)))
    return (false);
  free(ar);
  return (true);
}

static bool		get_file(int			fd,
				 t_flag			flags,
				 struct ar_hdr		*ar)
{
  t_objdump		objdump;
  bool			ret;

  objdump.size = atoi(ar->ar_size);
  objdump.name = ar->ar_name;
  get_name(&objdump);
  if (get_ehdr(&objdump, fd) && get_sym(&objdump))
    {
      ret = exec_objdump(&objdump, flags);
      free(objdump.ehdr);
      if (ret == false)
	{
	  free(ar);
	  return (false);
	}
      return (true);
    }
  return (false);
}

bool			get_each_file(int		fd,
				      t_flag		flags)
{
  struct ar_hdr		*ar;

  ar = NULL;
  if (!(confirm_ar_file(fd)))
    return (print_error("File format not recognized"));
  printf("In archive %s:\n", g_file_name);
  while (get_ar_hdr(fd, &ar))
    {
      if (!get_file(fd, flags, ar))
	{
	  free(g_header_ar);
	  g_header_ar = NULL;
	  return (false);
	}
    }
  free(g_header_ar);
  g_header_ar = NULL;
  return (true);
}
