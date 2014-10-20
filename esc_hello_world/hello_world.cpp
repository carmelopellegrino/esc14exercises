#include "libesc/libesc_api.h"

int main()
{
	esc_start_auto();

	int result = 1;
	return esc_finish(&result,1,ESC_TYPE_INT,ESC_ACCURACY_DEFAULT);
}
