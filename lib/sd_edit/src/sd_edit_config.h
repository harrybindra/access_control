#include <leb.h>
#include <SdFat.h>
#include "FS.h"
#include <ac_system_tasks.h>
#include <json_edit_config.h>
#include <time_config.h>

#ifndef SD_EDIT_CONFIG_H
#define SD_EDIT_CONFIG_H
class sd_edit_config
{
private:
    /* data */
public:
    void start_sd();
    void make_schedule(String user_json_oject);

    bool exists_schedule(String name);
    String list_schedule();
    bool is_allow_to_enter(String id_name);

};
#endif