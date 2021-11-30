// 參考 : http://wen00072.github.io/blog/2013/12/29/using-getopt-parse-command-line-parameter/
// ./simple -a -b arg_b -c [arg_c]  [args]

#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char **argv)
{
    int cmd_opt = 0;

    while(1) {
        printf("process index: %d\n", optind);
        cmd_opt = getopt(argc, argv, "ab:c::");

        /* End condition always first */
        if (cmd_opt == -1)
            break;

        /* Print option when it is valid */
        if (cmd_opt != '?')
            fprintf(stderr, "option:-%c\n", cmd_opt);

        switch (cmd_opt) {
            case 'a':
                break;

            case 'b':
                fprintf(stderr, "option arg:%s\n", optarg);
                break;

            case 'c':
                if (optarg)
                    fprintf(stderr, "option arg:%s\n", optarg);
                break;


            /* Error handle: Mainly missing arg or illegal option */
            case '?':
                fprintf(stderr, "Illegal option:-%c\n", isprint(optopt) ? optopt : '#');
                break;

            default:
                fprintf(stderr, "Not supported option\n");
                break;
        }
    }

    /* Do we have args? */
    if (argc > optind)
        for (int i = optind; i < argc; i++)
            fprintf(stderr, "argv[%d] = %s\n", i, argv[i]);

    return 0;
}
