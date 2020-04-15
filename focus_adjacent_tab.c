void
viewtoleft(const Arg *arg) {

	if(__builtin_popcount(selmon->tagset[selmon->seltags] & TAGMASK) == 1 /* if one tag is focused */
	&& selmon->tagset[selmon->seltags] > 1) {
		selmon->seltags ^= 1; /* toggle sel tagset */
		selmon->tagset[selmon->seltags] = selmon->tagset[selmon->seltags ^ 1] >> 1;
		focus(NULL);
		arrange(selmon);
	}
}

void
viewtoright(const Arg *arg) {

	/* hidescratch(); */

	if(__builtin_popcount(selmon->tagset[selmon->seltags] & TAGMASK) == 1  /* if one tag is focused */
	&& selmon->tagset[selmon->seltags] & (TAGMASK >> 1)) {
		selmon->seltags ^= 1; /* toggle sel tagset */
		selmon->tagset[selmon->seltags] = selmon->tagset[selmon->seltags ^ 1] << 1;
		focus(NULL);
		arrange(selmon);
	}
}
