#include "../includes/ft_ls.h"

void	display_files(t_file *files, t_options *opts)
{
	t_file	*curr;

	if (!files)
		return ;
	if (opts->flags & FLAG_L)
	{
		display_long_format(files, opts);
		return ;
	}
	curr = files;
	while (curr)
	{
		write(1, curr->name, ft_strlen(curr->name));
		write(1, "\n", 1);
		curr = curr->next;
	}
}
