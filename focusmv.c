/**
 * @author      : Gavin Jaeger-Freeborn (gavinfreeborn@gmail.com)
 * @file        : focusmv.c
 * @created     : Fri 27 Dec 2019 07:53:40 PM MST
 */

// +1=right
// -1=left

#include "focus_adjacent_tab.c"
void
focusmv(const Arg *arg) 
{
	int axis = arg->i;
	if (mons->next){ /* if only one monitor */
		focusmon(arg); /* switch workspaces instead of monitors */
		return;
	}
	if (axis == 1){
		viewtoright(arg);
	}else{
		viewtoleft(arg);
	}
}

