#include <scew/scew.h>

static int const indent_size = 4;

void
print_justify(unsigned int indent)
{
    int i = 0;

    for (i = 0; i < indent * indent_size; i++)
    {
        printf(" ");
    }
}

void
print_attributes(scew_element const* element)
{
    int i = 0;
    scew_attribute const* attribute = NULL;

    if (element != NULL)
    {
        for (i = 0; i < scew_get_attribute_count(element); i++)
        {
            attribute = scew_get_attribute(element, i);
            printf(" %s=\"%s\"", scew_get_attribute_name(attribute),
                   scew_get_attribute_value(attribute));
        }
    }
}

void
print_element(scew_element const* element, unsigned int indent)
{
    int i = 0;
    XML_Char const* contents;

    if (element != NULL)
    {
        print_justify(indent);
        printf("<%s", scew_get_element_name(element));
        print_attributes(element);
        printf(">\n");

        for (i = 0; i < scew_get_element_count(element); i++)
        {
            print_element(scew_get_element(element, i), indent + 1);
        }

        contents = scew_get_element_contents(element);
        if (contents != NULL)
        {
            print_justify(indent);
            printf("%s\n", scew_get_element_contents(element));
        }

        print_justify(indent);
        printf("</%s>\n", scew_get_element_name(element));
    }
}

int
main(int argc, char** argv)
{
    int i = 0;
    int count = 0;
    scew_parser* parser;
    scew_element** list;

    if (argc < 2)
    {
        printf("usage: scew_print file.xml\n");
        return EXIT_FAILURE;
    }

    parser = scew_parser_create();

    if (!scew_load_file(parser, argv[1]))
    {
        printf("unable to open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    print_element(scew_get_root(parser), 0);

    scew_parser_free(parser);
}
