#pragma once

#include <string>

/* This header abstracts some basics escape codes, 
   you can nest the commands as you need 	*/ 

/* reset format */
const std::string RESc	 	=	"\033[0m";

/* TEXT COLOR  */
/* codes */
const std::string BLACKc 	=	"\033[30m";
const std::string REDc 		=	"\033[31m";
const std::string GREENc 	=	"\033[32m";
const std::string YELLOWc 	=	"\033[33m";
const std::string BLUEc 	=	"\033[34m";
const std::string MAGENTAc 	=	"\033[35m";
const std::string CYANc 	=	"\033[36m";
const std::string WHITEc 	=	"\033[37m";

/* macros */
#define WHITE(x)	WHITEc + x + RESc
#define RED(x)		REDc + x + RESc
#define GREEN(x)	GREENc + x + RESc
#define YELLOW(x)	YELLOWc + x + RESc
#define BLUE(x)		BLUEc + x + RESc
#define MAGENTA(x)	MAGENTAc + x + RESc
#define CYAN(x)		CYANc + x + RESc
#define WHITE(x)	WHITEc + x + RESc

/* BACKGROUND COLORS */
/* codes */
const std::string bBLACKc 	=	"\033[40m";
const std::string bREDc 	=	"\033[41m";
const std::string bGREENc 	=	"\033[42m";
const std::string bYELLOWc 	=	"\033[43m";
const std::string bBLUEc 	=	"\033[44m";
const std::string bMAGENTAc	=	"\033[45m";
const std::string bCYANc 	=	"\033[46m";
const std::string bWHITEc 	=	"\033[47m";

/* macros */
#define bWHITE(x)	bWHITEc + x + RESc
#define bRED(x)		bREDc + x + RESc
#define bGREEN(x)	bGREENc + x + RESc
#define bYELLOW(x)	bYELLOWc + x + RESc
#define bBLUE(x)	bBLUEc + x + RESc
#define bMAGENTA(x)	bMAGENTAc + x + RESc
#define bCYAN(x)	bCYANc + x + RESc
#define bWHITE(x)	bWHITEc + x + RESc

/* EFFECTS */
/* codes */
const std::string BOLDc		=	"\033[1m";
const std::string UNDERLINEc	=	"\033[4m";
const std::string SLOW_BLINKc	=	"\033[5m";
const std::string RAPID_BLINKc	=	"\033[6m";
const std::string FRAMEDc	=	"\033[51m";

/* macros */
#define BOLD(x)		BOLDc + x + RESc
#define UNDERLINE(x)	UNDERLINEc + x + RESc
#define SLOW_BLINK(x)	SLOW_BLINKc + x + RESc
#define RAPID_BLINK(x)	RAPID_BLINKc + x + RESc
#define FRAMED(x)	FRAMEDc + x + RESc

/* CURSOSR CONTROL */
/* codes */
const std::string CLEAR		=	"\033[2J";
const std::string HIDE_CURSOR	=	"\033[?25l";
const std::string SHOW_CURSOR	=	"\033[?25h";
#define GOTO(l, c)	"\033[" + std::to_string(l) + ";" + std::to_string(c) + "H"



