#pragma once

typedef struct {
    char *mod_name;  /* How the actual loaded kmod file name is seen in `lsmod` */
    char *conf_name; /* CONF_MODULE_NAME=y as appears in Linux kernel's .config */
} Module;
