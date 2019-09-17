#include "libft/libft.h"

int main()
{
    char *str;
    // open("qwe", O_RDONLY);
    while(get_next_line(0, &str))
    {
        ft_putendl(str);
        free(str);
        str = NULL;
    }
    // close(3);
    if (str)
        free(str);
    return (0);
}
