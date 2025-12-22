#include "../includes/ft_ls.h"

static void	list_directory(const char *path, t_options *opts)
{
	t_file	*files;

	files = read_directory(path, opts);
	if (!files)
		return ;
	sort_files(&files, opts);
	display_files(files, opts);
	if (opts->flags & FLAG_REC)
	{
		t_file *curr = files;
		write(1, "\n", 1);
		while (curr)
		{
			if (S_ISDIR(curr->stat.st_mode))
				list_recursive(curr->path, opts);
			curr = curr->next;
		}
	}
	file_free(files);
}

int	main(int argc, char **argv)
{
	t_options	opts;
	int			i;

	if (!parse_options(argc, argv, &opts))
		return (1);
	if (opts.arg_index >= argc)
	{
		list_directory(".", &opts);
	}
	else
	{
		i = opts.arg_index;
		while (i < argc)
		{
			if (argc - opts.arg_index > 1)
			{
				write(1, argv[i], ft_strlen(argv[i]));
				write(1, ":\n", 2);
			}
			list_directory(argv[i], &opts);
			if (i < argc - 1)
				write(1, "\n", 1);
			i++;
		}
	}
	return (0);
}
