/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 15;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */
static const char *fonts[]          = { "Liberation Mono:pixelsize=13:antialias=true:autohint=true" , "Font Awesome 5 Free:size=9" };
static const char dmenufont[]       = "monospace-10";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor    scratch key */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1,        0  },
	{ "firefox",  NULL,       NULL,       1 << 8,       0,           -1,        0  },
	{ "zoom",     NULL,      "Polls",     0,            1,           -1,        0  },
	{ NULL,       NULL,   "scratchpad",   0,            1,           -1,       's' },
	{ NULL,       NULL,   "calculator",   0,            1,           -1,       'c' },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

static const unsigned int deltamv   = 20; /* deltamvmv = the amount of pixels each movement will be by */
#include "mv.c"
#include "focusmv.c"

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* static const char scratchpadname[] = "scratchpad"; */
/* static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL }; */

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

/* TODO: force dmenu to the right monitor   <05-06-20 Gavin Jaeger-Freeborn>*/
/* TODO: add appropriate gaps to dmenu <05-06-20 Gavin Jaeger-Freeborn>*/
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-p", ">>", NULL };
static const char *termcmd[]  = { "/bin/sh", "-c", "${TERMINAL}", NULL };


static const char *barmenu[]       =  {"bar",            NULL   };

static const char *shot[]          =  {"windowshot.sh",  "-c",  NULL          };
static const char *dmenushot[]     =  {"windowshot.sh",  NULL    };             
static const char *nm[]            =  {"dmenu_connection_manager.sh", NULL };

static const char term[]           =  { "st"};
static const char exec[]           =  { "-e" };
/*First arg only serves to match against key in rules*/
static const char *scratchpadcmd[] =  {"s", term,             "-t",  "scratchpad", NULL}; 
static const char *calc[]          =  {"c", term,             "-t",  "calculator", "-e",  "R", NULL}; 
static const char *email[]         =  { term, "-t", "neomutt", exec, "launch_once.sh", "neomutt", NULL };
static const char *mixer[]         =  { term, exec, "cm", NULL };
static const char *mute[]          =  { "cm", "mute", NULL };
static const char *vdown[]         =  { "cm", "down", "5", NULL };
static const char *vup[]           =  { "cm", "up", "5", NULL };
static const char *ldown[]         =  { "cl", "down", "7", NULL };
static const char *lup[]           =  { "cl", "up", "7", NULL };
static const char *search[]        =  { "ducksearch", NULL };
static const char *browser[]       =  { "/bin/sh", "-c", "ducksearch \"google-chrome-stable \"" , NULL };
static const char *plumb[]         =  { "/bin/sh", "-c", "${PLUMBER} -c", NULL };
static const char *clip[]          =  { "clipmenu", NULL };
static const char *killit[]        =  { "dmenu-killall", NULL };
static const char *power[]         =  { "power_menu.sh", NULL };
static const char *tutoral[]       =  { "tutorialvids", NULL };
static const char *rotate[]        =  { "rotate_screen", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             			XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_u,      togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                    	XK_c,      togglescratch,  {.v = calc } },
	/* { MODKEY,                       XK_u,  	   togglescratch,  {.v = scratchpadcmd } }, */
	/* { MODKEY|ShiftMask,             XK_u, 	   spawn,  		   {.v = scratchpadcmd } }, */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_j,      mv,       	   {.i = -2} },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_k,      mv,       	   {.i = +2} },
	{ MODKEY,                       XK_a,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_s,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      focusmv,        {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      mv,       	   {.i = 1} },
	{ MODKEY,             XK_bracketright, 	   setmfact,       {.f = +0.05} },
	{ MODKEY,             XK_bracketleft,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      focusmv,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_l,      mv,       	   {.i = -1} },
	{ MODKEY,                       XK_v,	   zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,             			XK_q,      killclient,     {0} },
	{ MODKEY,             	XK_BackSpace, 	   killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,  	   setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_z,  	   togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = +5 } },

	{ 0,                            0x1008ff11, spawn,         {.v = vdown } },
	{ 0,                            0x1008ff13, spawn,         {.v = vup } },
	{ 0,                            0x1008ff12, spawn,         {.v = mute } },
	{ 0,                            0x1008ff7f, spawn,         {.v = rotate } },
	{ MODKEY,                       XK_equal,  spawn,          {.v = nm }   },
	{ 0,                            XK_Print,  spawn,          {.v = shot } },
	{ MODKEY,                       XK_Print,  spawn,          {.v = dmenushot } },
	{ 0,             				XK_Menu,   spawn,          {.v = (const char*[]){ "exit 0",  NULL }} },

	{ MODKEY,                       XK_y,      spawn,          {.v = mixer } },
	{ MODKEY|ShiftMask,             XK_t,      spawn,          {.v = tutoral } },
	{ MODKEY,                       XK_e,      spawn,          {.v = email } },
	{ MODKEY,                       XK_w,      spawn,          {.v = search } },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = browser } },
	{ MODKEY|ControlMask,           XK_q,      spawn,          {.v = killit } },
	{ ShiftMask|MODKEY,             XK_t,      spawn,          {.v = tutoral } },
	{ MODKEY|ShiftMask,             XK_x,      spawn,          {.v = power } },
	{ MODKEY,                       XK_p,      spawn,          {.v = clip } },

	{ MODKEY|ControlMask,           XK_f,      spawn,          {.v = vup } },
	{ MODKEY|ControlMask,           XK_d,      spawn,          {.v =  lup } },
	{ MODKEY|ControlMask,           XK_s,      spawn,          {.v = ldown } },
	{ MODKEY|ControlMask,           XK_a,      spawn,          {.v = vdown } },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkStatusText,        0,              Button3,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkStatusText,        0,              Button1,        spawn,          {.v = barmenu } },
	{ ClkRootWin, 		    0,              Button1,      	spawn,          {.v = barmenu } },
	{ ClkClientWin, 		ShiftMask,      Button3,      	spawn,          {.v = plumb } },
};

