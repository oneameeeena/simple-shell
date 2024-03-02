#include"shell.h"
/**
 * func_helper_general - for help builtin
 * Return: void
 */
void func_helper_general(void)
{
	char *help = "$ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, help, _strlen(help));
	help =
	"Type 'help cmd_name' to find out more about the function 'cmd_name'.\n\n ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = " alias: alias [cmd_name=['str']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, help, _strlen(help));
	help =
	"[dir]\nexit: exit [n]\n  env: env [option] [cmd_name=value] [command ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "[args]]\n  setenv: setenv [variable] [value]\n  unset_env: ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "unset_env [variable]\n";
	write(STDOUT_FILENO, help, _strlen(help));
}
/**
 * func_helper_exit - Help for builint exit
 * Return: void
 */
void func_helper_exit(void)
{
	char *help = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "statusis that of the last command executed\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * func_helper - for builtin help.
 * Return: void
 */
void func_helper(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}
/**
 * func_helper_alias - for the builtin alias.
 * Return: void
 */
void func_helper_alias(void)
{
	char *help = "alias: alias [-p] [cmd_name[=value]...]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
}
