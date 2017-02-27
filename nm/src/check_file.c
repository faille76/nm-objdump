/*
** check_file.c for check file in /nm/src/
**
** Made by Frederic ODDOU
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Tue Feb 14 11:33:25 2017 Frederic ODDOU
** Last update Fri Feb 24 12:50:18 2017 Frederic ODDOU
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "nm.h"

bool		get_sym(t_nm		*nm)
{
  if (g_architecture == A32BITS)
    {
      nm->shdr = (Elf64_Shdr *)((char *)nm->ehdr +
		  ((Elf32_Ehdr *)nm->ehdr)->e_shoff);
      return (get_sym32(nm));
    }
  nm->shdr = (Elf64_Shdr *)((char *)nm->ehdr + nm->ehdr->e_shoff);
  return (get_sym64(nm));
}

bool		get_ehdr(t_nm		*nm,
			 int		fd)
{
  g_architecture = A64BITS;
  if (nm->size < (int)sizeof(Elf64_Ehdr))
    return (print_error("File format not recognized"));
  if (!(nm->ehdr = malloc(nm->size + 1)))
    return (false);
  if (read(fd, nm->ehdr, nm->size) != nm->size)
    return (print_error("File format not recognized"));
  ((char *)nm->ehdr)[nm->size] = 0;
  if (memcmp(nm->ehdr->e_ident, MAGIC_ELF, strlen(MAGIC_ELF)))
    return (print_error("File format not recognized"));
  if (nm->ehdr->e_ident[EI_CLASS] == ELFCLASS32)
    g_architecture = A32BITS;
  return (true);
}

static bool		is_ar_file(int		fd)
{
  char			magic_ar[SARMAG];

  if (read(fd, magic_ar, SARMAG) != SARMAG)
    return (false);
  if (strncmp(magic_ar, MAGIC_AR, SARMAG))
    return (false);
  return (true);
}

static bool	get_non_ar_file(int		fd,
				t_flag		flags,
				int file)
{
  t_nm		nm;
  bool		ret;

  ret = false;
  memset(&nm, 0, sizeof(nm));
  if ((nm.size = lseek(fd, 0, SEEK_END)) == -1 || lseek(fd, 0, SEEK_SET) == -1)
    return (print_error("lseek failled"));
  if (get_ehdr(&nm, fd))
    {
      if (file > 1 && !flags[FLAG_PRINT_FILE_NAME])
	printf("\n%s:\n", g_file_name);
      if (get_sym(&nm))
	ret = exec_nm(&nm, flags);
    }
  free(nm.ehdr);
  free(nm.list);
  return (ret);
}

bool			open_file(t_flag	flags,
				  int		file,
				  int		fd)
{
  if (is_ar_file(fd))
    {
      if (file > 1)
	printf("\n%s:\n", g_file_name);
      return (get_each_file(fd, flags));
    }
  return (get_non_ar_file(fd, flags, file));
}
