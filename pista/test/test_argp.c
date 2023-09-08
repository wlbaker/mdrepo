#include<stdlib.h>
#include<argp.h>

// need to mention a version string.
const char *argp_program_version = "your-cool-app 1.0.0";

// documentation string that will be displayed in the help section.
static char doc[] = "documentation for your cool application :)";

// email address for bug reporting.
const char *argp_program_bug_address = "<your e-mail address>";

// argument list for doc. This will be displayed on --help
static char args_doc[] = "ARG1";

// cli argument availble options.
static struct argp_option options[] = {
    {"verbose", 'v', 0, 0, "Produce verbose output"},
    {"option1", 'o', "Option1", 0},
    {0}
};


// define a struct to hold the arguments.
struct arguments{
    int  verbose;
    char *args[1];
    char *option1;
};


// define a function which will parse the args.
static error_t parse_opt(int key, char *arg, struct argp_state *state){

    struct arguments *arguments = state->input;
    switch(key){

        case 'v':
            arguments->verbose = 1;
            break;
        case 'o':
            arguments->option1 = arg;
            break;

        case ARGP_KEY_ARG:
        
            // Too many arguments.
            if(state->arg_num > 1)
                argp_usage(state);
            arguments->args[state->arg_num] = arg;
            break;

        case ARGP_KEY_END:
            // Not enough arguments.
            if(state->arg_num < 1)
                argp_usage(state);
            break;

        default:
            return ARGP_ERR_UNKNOWN;
    }

    return 0;
}


// initialize the argp struct. Which will be used to parse and use the args.
static struct argp argp = {options, parse_opt, args_doc, doc};


int main(int argc, char *args[]){

    // create a new struct to hold arguments.
    struct arguments arguments;

    // set the default values for all of the args.
    arguments.verbose = 0;
    arguments.option1 = "";
    // arguments.option2 = "";

    // parse the cli arguments.
    argp_parse(&argp, argc, args, 0, 0, &arguments);

    printf("ARG1:    %s", arguments.args[0]);
    printf("\nVERBOSE: %s", arguments.verbose? "yes" : "no");
    printf("\nOption1: %s", arguments.option1);
    printf("\n");
}
