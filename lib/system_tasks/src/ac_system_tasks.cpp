
#include <ac_system_tasks.h>

void ac_system_tasks::restart(String perpous)
{
    Serial.println(perpous);
    // make loge
    ESP.restart();
}