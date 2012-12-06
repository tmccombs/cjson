#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include "json_types.h"

JSON_node *json_parse_file(FILE *f);
JSON json_parse_str(const char *input);

#endif
