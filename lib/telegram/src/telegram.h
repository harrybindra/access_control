#include <leb.h>
#include <sd_edit_config.h>


class telegram
{
private:

public:
void send_text(String text ,String object="{}",bool update=true);
void remove_mass(int mass_id);

String get_last_mass();
void conand_map(String comand);
};

