#include "stdafx.h"

void register_mappers();
void register_mappers()
{
	register_optional_mappers();

	extern void register_vrc7_mapper();
	register_vrc7_mapper();

	extern void register_more_mappers();
	register_more_mappers();
}