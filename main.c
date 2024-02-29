#include"shell.h"
/**
 * main - Entry point
 * @ac: argument count
 * @av: argument vector
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	Data_sl Data_sh;
	(void) ac;

	signal(SIGINT, hundel_ctrd);
	set_data(&Data_sh, av);
	shell_loop(&Data_sh);
	free_data(&Data_sh);
	if (Data_sh.status < 0)
		return (255);
	return (Data_sh.status);
}
