/*
** open_ar_file.c for ar file in /home/fredoddou/Documents/Epitech/B4-Unix-System-Programming/PSU_2016_nmobjdump/nm/src/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sun Feb 19 03:15:58 2017 Frederic ODDOU
** Last update Sun Feb 19 04:34:10 2017 Fredoddou
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "nm.h"

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
  t_nm			nm;
  bool			ret;

  nm.size = atoi(ar->ar_size);
  nm.name = ar->ar_name;
  get_name(&nm);
  if (get_ehdr(&nm, fd) && get_sym(&nm))
    {
      if (!flags[FLAG_PRINT_FILE_NAME])
	printf("\n%s:\n", nm.name);
      ret = exec_nm(&nm, flags);
      free(nm.ehdr);
      free(nm.list);
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
