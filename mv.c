// TODO
// add support for snapping 
//
/* #define MULTIMONITOR */
#include "mv_adjacent_tag.c"
void
movestack(const Arg *arg) {
	Client *c = NULL, *p = NULL, *pc = NULL, *i;

	if(arg->i < 0) {
		/* find the client after selmon->sel */
		for(c = selmon->sel->next; c && (!ISVISIBLE(c) || c->isfloating); c = c->next);
		if(!c)
			for(c = selmon->clients; c && (!ISVISIBLE(c) || c->isfloating); c = c->next);

	}
	else {
		/* find the client before selmon->sel */
		for(i = selmon->clients; i != selmon->sel; i = i->next)
			if(ISVISIBLE(i) && !i->isfloating)
				c = i;
		if(!c)
			for(; i; i = i->next)
				if(ISVISIBLE(i) && !i->isfloating)
					c = i;
	}
	/* find the client before selmon->sel and c */
	for(i = selmon->clients; i && (!p || !pc); i = i->next) {
		if(i->next == selmon->sel)
			p = i;
		if(i->next == c)
			pc = i;
	}

	/* swap c and selmon->sel selmon->clients in the selmon->clients list */
	if(c && c != selmon->sel) {
		Client *temp = selmon->sel->next==c?selmon->sel:selmon->sel->next;
		selmon->sel->next = c->next==selmon->sel?c:c->next;
		c->next = temp;

		if(p && p != c)
			p->next = c;
		if(pc && pc != selmon->sel)
			pc->next = selmon->sel;

		if(selmon->sel == selmon->clients)
			selmon->clients = c;
		else if(c == selmon->clients)
			selmon->clients = selmon->sel;

		arrange(selmon);
	}
}

// 1=x // 2=y 
// +1 would meen move left
// -2 would meen move down
void
mv(const Arg *arg) 
{
	Client *c;
	int axis = arg->i;
	if (!(c = selmon->sel))
		return;
	if (c->isfullscreen ) /* shrink from fullscreen */
		setfullscreen(c, 0);	
	if ((axis == 1) || (axis == -1)) {
		if(!c->isfloating && (selmon->lt[selmon->sellt]->arrange)){
		    if (!selmon->sel || !mons->next) /* if only one monitor */
		    	wintotag(arg); /* switch workspaces instead of monitors */
		    tagmon(arg);
		    return;
		}
		int delta = (deltamv * axis);
		XMoveWindow(dpy, c->win, (c->x - delta), c->y);
		c->oldx = c->x;
		c->x = c->oldx - delta;
		XWarpPointer(dpy, None, c->win, 
				0, 0, 0, 0, (c->w/2),(c->h/2));
	}
	else{
		if(!c->isfloating && (selmon->lt[selmon->sellt]->arrange)){
		    movestack(arg);
		    return;
		}
		int delta = (deltamv * (axis/2));
		XMoveWindow(dpy, c->win, c->x, (c->y - delta));
		c->oldy = c->y;
		c->y = c->oldy - delta;
		XWarpPointer(dpy, None, c->win, 
				0, 0, 0, 0, (c->w/2),(c->h/2));
	}
}

