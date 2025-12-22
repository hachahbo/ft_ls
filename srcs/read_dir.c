#include "../includes/ft_ls.h"

static int	should_skip(const char *name, t_options *opts)
{
	if (name[0] == '.')
	{
		if (!(opts->flags & FLAG_A))
			return (1);
		if (ft_strcmp(name, ".") == 0 || ft_strcmp(name, "..") == 0)
			return (1);
	}
	return (0);
}

t_file	*read_directory(const char *path, t_options *opts)
{
	DIR				*dir;
	struct dirent	*entry;
	t_file			*files;
	t_file			*new_file;

	dir = opendir(path);
	if (!dir)
	{
		error_msg(path, NULL);
		return (NULL);
	}
	files = NULL;
	entry = readdir(dir);
	while (entry)
	{
		if (!should_skip(entry->d_name, opts))
		{
			new_file = file_new(entry->d_name, path);
			if (new_file)
				file_add(&files, new_file);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (files);
}
