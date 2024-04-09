/* TODO: respect bar location */

void
max(const Arg *arg)
{
	if (!selmon->sel)
		return;

	Client* c = selmon->sel;
	Layout* l = selmon->lt[selmon->sellt]->arrange;
	/* if the client is not fullscreen, alone, or monocle */
	if (!c->isfullscreen && l != monocle && (nexttiled(c) || c->isfloating || l == NULL)){
		/* if arg is 0 use monocle size if 1 use fullscreen */
		if(selmon->showbar && (arg->i != 1)){
			if (sp != 0) {
				sp = vp = 0;
				updatebarspace(selmon);
			}
			setfullscreen(c, 2);
			return;
		}
		setfullscreen(c, 1);
	}
	else {
		if ((sp != sidepad) && !(l == monocle)) {
			sp = sidepad, vp = (topbar == 1) ? vertpad : - vertpad;
			updatebarspace(selmon);
		}
		setfullscreen(c, 0);
	}
}
