
#include <leb.h>
#include "json_edit_config.h"
#include <screen_compo.h>
#include <time_config.h>
#include <sd_edit_config.h>
#include <fingerprint_leb.h>
#ifndef AC_SYSTEM_TASKS_H  // If AC_SYSTEM_TASKS_H is not defined
#define AC_SYSTEM_TASKS_H 
class ac_system_tasks
{
private:
    /* data */
public:
    void restart(String perpous);
    void verification(String input);

};
#endif 