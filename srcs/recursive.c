#include "../includes/ft_ls.h"

static void	process_directory(const char *path, t_options *opts, int print_path)
{
	t_file	*files;

	if (print_path)
	{
		write(1, path, ft_strlen(path));
		write(1, ":\n", 2);
	}
	files = read_directory(path, opts);
	if (!files)
		return ;
	sort_files(&files, opts);
	display_files(files, opts);
	if (opts->flags & FLAG_REC)
	{
		t_file *curr = files;
		while (curr)
		{
			if (S_ISDIR(curr->stat.st_mode))
			{
				write(1, "\n", 1);
				list_recursive(curr->path, opts);
			}
			curr = curr->next;
		}
	}
	file_free(files);
}

void	list_recursive(const char *path, t_options *opts)
{
	process_directory(path, opts, 1);
}
