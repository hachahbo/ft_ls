#include "../includes/ft_ls.h"

t_file	*file_new(const char *name, const char *path)
{
	t_file	*new;
	char	*full_path;
	char	*temp;

	new = malloc(sizeof(t_file));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	if (!new->name)
	{
		free(new);
		return (NULL);
	}
	temp = ft_strjoin(path, "/");
	full_path = ft_strjoin(temp, name);
	free(temp);
	new->path = full_path;
	if (lstat(full_path, &new->stat) == -1)
	{
		free(new->name);
		free(new->path);
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

void	file_add(t_file **head, t_file *new)
{
	t_file	*curr;

	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	curr = *head;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}

void	file_free(t_file *head)
{
	t_file	*temp;

	while (head)
	{
		temp = head->next;
		free(head->name);
		free(head->path);
		free(head);
		head = temp;
	}
}

int	file_count(t_file *head)
{
	int	count;

	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}
