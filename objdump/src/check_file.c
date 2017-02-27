/*
** check_file.c for check file in /objdump/src/
**
** Made by Frederic ODDOU
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Tue Feb 14 11:33:25 2017 Frederic ODDOU
** Last update Fri Feb 24 15:40:43 2017 Frederic ODDOU
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "objdump.h"

bool		get_sym(t_objdump		*objdump)
{
  if (g_architecture == A32BITS)
    {
      objdump->shdr = (Elf64_Shdr *)((char *)objdump->ehdr +
		       ((Elf32_Ehdr *)objdump->ehdr)->e_shoff);
      return (get_sym32(objdump));
    }
  objdump->shdr = (Elf64_Shdr *)((char *)objdump->ehdr + objdump->ehdr->e_shoff);
  return (get_sym64(objdump));
}

bool		get_ehdr(t_objdump		*objdump,
			 int			fd)
{
  if (objdump->size < (int)sizeof(Elf64_Ehdr))
    return (print_error("File format not recognized"));
  if (!(objdump->ehdr = malloc(objdump->size + 1)))
    return (false);
  if (read(fd, objdump->ehdr, objdump->size) != objdump->size)
    return (print_error("File format not recognized"));
  ((char *)objdump->ehdr)[objdump->size] = 0;
  if (memcmp(objdump->ehdr->e_ident, MAGIC_ELF, strlen(MAGIC_ELF)))
    return (print_error("File format not recognized"));
  if (objdump->ehdr->e_ident[EI_CLASS] == ELFCLASS32)
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
				t_flag		flags)
{
  t_objdump		objdump;
  bool			ret;

  memset(&objdump, 0, sizeof(objdump));
  if ((objdump.size = lseek(fd, 0, SEEK_END)) == -1 ||
      lseek(fd, 0, SEEK_SET) == -1)
    return (print_error("lseek failled"));
  if (get_ehdr(&objdump, fd) && get_sym(&objdump))
    {
      objdump.name = g_file_name;
      ret = exec_objdump(&objdump, flags);
    }
  free(objdump.ehdr);
  return (ret);
}

bool			open_file(t_flag	flags,
				  int		fd)
{
  if (is_ar_file(fd))
    return (get_each_file(fd, flags));
  return (get_non_ar_file(fd, flags));
}
