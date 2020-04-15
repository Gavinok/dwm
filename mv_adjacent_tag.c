void
tagtoleft(const Arg *arg) {


	/* if (scratchpad_last_showed != NULL) */
	/* 	scratchpad_show (); */
	

	if(selmon->sel != NULL
	&& __builtin_popcount(selmon->tagset[selmon->seltags] & TAGMASK) == 1
	&& selmon->tagset[selmon->seltags] > 1) {
		selmon->sel->tags >>= 1;
		focus(NULL);
		arrange(selmon);
	}
}

void
tagtoright(const Arg *arg) {

	/* if (scratchpad_last_showed != NULL) */
	/* 	scratchpad_show (); */

	if(selmon->sel != NULL
	&& __builtin_popcount(selmon->tagset[selmon->seltags] & TAGMASK) == 1
	&& selmon->tagset[selmon->seltags] & (TAGMASK >> 1)) {
		selmon->sel->tags <<= 1;
		focus(NULL);
		arrange(selmon);
	}
}

void
wintotag(const Arg *arg){
 if ( arg->i >=1 )   
     tagtoleft(0);
 else
     tagtoright(0);
}
