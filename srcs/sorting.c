#include "../includes/ft_ls.h"

static int	compare_name(t_file *a, t_file *b)
{
	return (ft_strcmp(a->name, b->name) > 0);
}

static int	compare_time(t_file *a, t_file *b)
{
	if (a->stat.st_mtime == b->stat.st_mtime)
		return (ft_strcmp(a->name, b->name) > 0);
	return (a->stat.st_mtime < b->stat.st_mtime);
}

static void	swap_files(t_file *a, t_file *b)
{
	char		*temp_name;
	char		*temp_path;
	struct stat	temp_stat;

	temp_name = a->name;
	temp_path = a->path;
	temp_stat = a->stat;
	a->name = b->name;
	a->path = b->path;
	a->stat = b->stat;
	b->name = temp_name;
	b->path = temp_path;
	b->stat = temp_stat;
}

void	sort_files(t_file **head, t_options *opts)
{
	t_file	*curr;
	t_file	*next;
	int		swapped;

	if (!head || !*head)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		curr = *head;
		while (curr && curr->next)
		{
			next = curr->next;
			if ((opts->flags & FLAG_T) && compare_time(curr, next))
			{
				swap_files(curr, next);
				swapped = 1;
			}
			else if (!(opts->flags & FLAG_T) && compare_name(curr, next))
			{
				swap_files(curr, next);
				swapped = 1;
			}
			curr = curr->next;
		}
	}
	if (opts->flags & FLAG_R)
		reverse_list(head);
}

void	reverse_list(t_file **head)
{
	t_file	*prev;
	t_file	*curr;
	t_file	*next;

	if (!head || !*head)
		return ;
	prev = NULL;
	curr = *head;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*head = prev;
}
