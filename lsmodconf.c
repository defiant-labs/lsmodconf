#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "modules.h"


#define CONF_PRE "CONFIG_"
#define LINE_MAX 500
#define NAME_MAX 50


void lsmod_name(char* input_line, char* mod_name) {
  int i = 0;
  while (input_line[i] != ' ') {
    mod_name[i] = input_line[i];
    i++;
  }
  mod_name[i] = '\0';
}

void config_name(char* mod_name, char* conf_name) {
  int i = 0;
  int ilen = sizeof(modules) / sizeof(Module);
  Module* conf_mod = NULL;

  while (i < ilen) {
    if (strcmp(modules[i].mod_name, mod_name) == 0) {
      conf_mod = &modules[i];
      strcpy(conf_name, CONF_PRE);
      strcat(conf_name, (*conf_mod).conf_name);
      return;
    }

    i++;
  }
}

int main(int argc, char** argv) {
  char mod_line[LINE_MAX];
  char conf_line[LINE_MAX];

  while (fgets(mod_line, LINE_MAX, stdin) != NULL) {
    char mod_name[NAME_MAX] = "";
    char conf_name[NAME_MAX] = "";

    lsmod_name(mod_line, mod_name);

    // Ignore the first line of lsmod's output
    if (strcmp(mod_name, "Module") == 0)
      continue;

    config_name(mod_name, conf_name);

    // Handle unknown module names
    if (conf_name[0] == '\0') {
      printf("# Module %s is unknown\n", mod_name);
      continue;
    }

    char conf_name_from_line[NAME_MAX];
    unsigned short matched = 0;

    FILE* conf_file = fopen(argv[1], "r");
    while (fgets(conf_line, LINE_MAX, conf_file) != NULL) {
      strcpy(conf_name_from_line, conf_line);
      conf_name_from_line[strlen(conf_name)] = '\0';
      if (strcmp(conf_name_from_line, conf_name) == 0
          && conf_line[strlen(conf_name)] == '=') {
        printf("%s", conf_line);
        matched = 1;
      }
    }
    fclose(conf_file);

    if (matched)
      continue;

    conf_file = fopen(argv[1], "r");
    while (fgets(conf_line, LINE_MAX, conf_file) != NULL) {
      strcpy(conf_name_from_line, "# ");
      strcat(conf_name_from_line, conf_name);
      strcat(conf_name_from_line, " is not set\n");
      if (strcmp(conf_name_from_line, conf_line) == 0) {
        printf("%s", conf_line);
        matched = 1;
      }
    }
    fclose(conf_file);

    if (matched)
      continue;

    printf("# Config string %s for module %s could not be found\n", conf_name,
              mod_name);
  }
}
