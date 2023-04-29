#include "shell.h"

/**
 * print_alias - prints the value of an alias, if it exists
 * @name: name of the alias to print
 * @args: parameter struct containing the alias list
 */

void print_alias(char *name, arg_t *args)
{
	unsigned int len = 0;
	list_t *ptr = args->alias_head;

	len = _strlen(name);
	while (ptr)
	{
		if (_strcmp_n(name, ptr->str, len - 1) == 0)
			_printf("%s=\'%s\'\n", ptr->str, ptr->val);
		ptr = ptr->next;
	}
	args->status = 0;
}

/**
 * print_all_aliases - prints all aliases in the alias list
 * @args: parameter struct containing the alias list
 */
void print_all_aliases(arg_t *args)
{
	print_list_alias(args->alias_head);
	args->status = 0;
}

/**
 * print_list_alias - prints the name and value of each alias in a linked list
 * @head: pointer to the head of the linked list
 *
 * This function iterates through the linked list of aliases and print the name
 * and value of each alias to stdout.
*/
void print_list_alias(list_t *head)
{
	if (head)
	{
		print_list_alias(head->next);
		if (head->str != NULL)
			_printf("%s=\'%s\'\n", head->str, head->val);
	}
}
