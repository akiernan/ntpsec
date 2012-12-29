/**  -*- buffer-read-only: t -*- vi: set ro:
 *  
 *  DO NOT EDIT THIS FILE   (usage-txt.h)
 *  
 *  It has been AutoGen-ed  December 27, 2012 at 12:59:03 PM by AutoGen 5.17.0pre12
 *  From the definitions    usage-txt.def
 *  and the template file   usage-txt.tpl
 *  @file usage-txt.h
 *
 *  This file handles all the bookkeeping required for tracking all the little
 *  tiny strings used by the AutoOpts library.  There are 146
 *  of them.  This is not versioned because it is entirely internal to the
 *  library and accessed by client code only in a very well-controlled way:
 *  they may substitute translated strings using a procedure that steps through
 *  all the string pointers.
 *
 *  Copyright (C) 1992-2012 Bruce Korb, all rights reserved.
 *  This is free software. It is licensed for use, modification and
 *  redistribution under the terms of the
 *  GNU Lesser General Public License, version 3 or later
 *     <http://gnu.org/licenses/lgpl.html>
 *
 *  AutoOpts is free software: you can redistribute it and/or modify it
 *  under the terms of the GNU Lesser General Public License as published
 *  by the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  AutoOpts is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *  See the GNU Lesser General Public License for more details.
 *  
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.";
 */
#ifndef AUTOOPTS_USAGE_TXT_H_GUARD
#define AUTOOPTS_USAGE_TXT_H_GUARD 1

/*
 *  One structure to hold all the pointers to all the translatable strings.
 */
typedef struct {
  int           field_ct;
  char *        utpz_GnuBoolArg;
  char *        utpz_GnuFileArg;
  char *        utpz_GnuKeyArg;
  char *        utpz_GnuKeyLArg;
  char *        utpz_GnuNumArg;
  char *        utpz_GnuStrArg;
  char *        utpz_GnuTimeArg;
  char const *  apz_str[91];
} usage_text_t;

/*
 *  Declare the global structure with all the pointers to translatable
 *  strings and the text array containing untranslatable strings.
 */
extern usage_text_t option_xlateable_txt;
extern char const option_lib_text[4660];

#if defined(AUTOOPTS_INTERNAL)
/*
 *  Provide a mapping from a short name to either the text directly
 *  (for untranslatable strings), or to pointers to the text, rendering
 *  them translatable.
 */
#define zAO_Alloc             (option_xlateable_txt.apz_str[  0])
#define zAO_Bad               (option_xlateable_txt.apz_str[  1])
#define zAO_Big               (option_xlateable_txt.apz_str[  2])
#define zAO_Err               (option_xlateable_txt.apz_str[  3])
#define zAO_Realloc           (option_xlateable_txt.apz_str[  4])
#define zAO_Sml               (option_xlateable_txt.apz_str[  5])
#define zAO_Strdup            (option_xlateable_txt.apz_str[  6])
#define zAO_Ver               (option_xlateable_txt.apz_str[  7])
#define zAO_Woops             (option_xlateable_txt.apz_str[  8])
#define zAliasRange           (option_xlateable_txt.apz_str[  9])
#define zAll                  (option_xlateable_txt.apz_str[ 10])
#define zAlt                  (option_lib_text + 547)
#define zAmbigKey             (option_xlateable_txt.apz_str[ 11])
#define zAmbigList            (option_xlateable_txt.apz_str[ 12])
#define zAmbigOptStr          (option_xlateable_txt.apz_str[ 13])
#define zAmbiguous            (option_xlateable_txt.apz_str[ 14])
#define zArgsMust             (option_xlateable_txt.apz_str[ 15])
#define zAtMost               (option_xlateable_txt.apz_str[ 16])
#define zAuto                 (option_xlateable_txt.apz_str[ 17])
#define zBadPipe              (option_xlateable_txt.apz_str[ 18])
#define zBadVerArg            (option_xlateable_txt.apz_str[ 19])
#define zCantFmt              (option_xlateable_txt.apz_str[ 20])
#define zCantSave             (option_xlateable_txt.apz_str[ 21])
#define zCfgAO_Flags          (option_xlateable_txt.apz_str[ 22])
#define zCfgProg              (option_xlateable_txt.apz_str[ 23])
#define zDefaultOpt           (option_xlateable_txt.apz_str[ 24])
#define zDis                  (option_xlateable_txt.apz_str[ 25])
#define zDisabledErr          (option_xlateable_txt.apz_str[ 26])
#define zDisabledOpt          (option_lib_text + 1225)
#define zDisabledWhy          (option_xlateable_txt.apz_str[ 27])
#define zEnab                 (option_lib_text + 1270)
#define zEquiv                (option_xlateable_txt.apz_str[ 28])
#define zErrOnly              (option_xlateable_txt.apz_str[ 29])
#define zExamineFmt           (option_xlateable_txt.apz_str[ 30])
#define zFSErrOptLoad         (option_xlateable_txt.apz_str[ 31])
#define zFSErrReadFile        (option_xlateable_txt.apz_str[ 32])
#define zFSOptErrFopen        (option_xlateable_txt.apz_str[ 33])
#define zFSOptErrMayExist     (option_xlateable_txt.apz_str[ 34])
#define zFSOptErrMustExist    (option_xlateable_txt.apz_str[ 35])
#define zFSOptErrNoExist      (option_xlateable_txt.apz_str[ 36])
#define zFSOptErrOpen         (option_xlateable_txt.apz_str[ 37])
#define zFSOptError           (option_xlateable_txt.apz_str[ 38])
#define zFileCannotExist      (option_lib_text + 1605)
#define zFileMustExist        (option_lib_text + 1636)
#define zFiveSpaces           (option_lib_text + 1663)
#define zFlagOkay             (option_xlateable_txt.apz_str[ 39])
#define zFmtFmt               (option_lib_text + 1772)
#define zForkFail             (option_xlateable_txt.apz_str[ 40])
#define zFreopenFail          (option_xlateable_txt.apz_str[ 41])
#define zGenshell             (option_xlateable_txt.apz_str[ 42])
#define zGnuBoolArg           (option_xlateable_txt.utpz_GnuBoolArg)
#define zGnuBreak             (option_lib_text + 1970)
#define zGnuFileArg           (option_xlateable_txt.utpz_GnuFileArg)
#define zGnuKeyArg            (option_xlateable_txt.utpz_GnuKeyArg)
#define zGnuKeyLArg           (option_xlateable_txt.utpz_GnuKeyLArg)
#define zGnuNestArg           (option_lib_text + 1976)
#define zGnuNumArg            (option_xlateable_txt.utpz_GnuNumArg)
#define zGnuOptArg            (option_lib_text + 1982)
#define zGnuOptFmt            (option_lib_text + 1989)
#define zGnuStrArg            (option_xlateable_txt.utpz_GnuStrArg)
#define zGnuTimeArg           (option_xlateable_txt.utpz_GnuTimeArg)
#define zIllOptChr            (option_xlateable_txt.apz_str[ 43])
#define zIllOptStr            (option_xlateable_txt.apz_str[ 44])
#define zIllVendOptStr        (option_xlateable_txt.apz_str[ 45])
#define zIntRange             (option_xlateable_txt.apz_str[ 46])
#define zInvalOptDesc         (option_xlateable_txt.apz_str[ 47])
#define zInvalOptName         (option_xlateable_txt.apz_str[ 48])
#define zLowerBits            (option_xlateable_txt.apz_str[ 49])
#define zMembers              (option_lib_text + 2267)
#define zMisArg               (option_xlateable_txt.apz_str[ 50])
#define zMultiEquiv           (option_xlateable_txt.apz_str[ 51])
#define zMust                 (option_lib_text + 2404)
#define zNeedOne              (option_xlateable_txt.apz_str[ 52])
#define zNoArg                (option_xlateable_txt.apz_str[ 53])
#define zNoArgs               (option_xlateable_txt.apz_str[ 54])
#define zNoCreat              (option_xlateable_txt.apz_str[ 55])
#define zNoFlags              (option_xlateable_txt.apz_str[ 56])
#define zNoKey                (option_xlateable_txt.apz_str[ 57])
#define zNoLim                (option_lib_text + 2705)
#define zNoPreset             (option_lib_text + 2738)
#define zNoResetArg           (option_xlateable_txt.apz_str[ 58])
#define zNoRq_NoShrtTtl       (option_xlateable_txt.apz_str[ 59])
#define zNoRq_ShrtTtl         (option_xlateable_txt.apz_str[ 60])
#define zNoStat               (option_xlateable_txt.apz_str[ 61])
#define zNoState              (option_xlateable_txt.apz_str[ 62])
#define zNone                 (option_xlateable_txt.apz_str[ 63])
#define zNotCmdOpt            (option_xlateable_txt.apz_str[ 64])
#define zNotDate              (option_xlateable_txt.apz_str[ 65])
#define zNotDef               (option_xlateable_txt.apz_str[ 66])
#define zNotDuration          (option_xlateable_txt.apz_str[ 67])
#define zNotEnough            (option_xlateable_txt.apz_str[ 68])
#define zNotFile              (option_xlateable_txt.apz_str[ 69])
#define zNotNumber            (option_xlateable_txt.apz_str[ 70])
#define zNrmOptFmt            (option_lib_text + 3264)
#define zNumberOpt            (option_lib_text + 3272)
#define zOnlyOne              (option_xlateable_txt.apz_str[ 71])
#define zOptsOnly             (option_lib_text + 3345)
#define zOutputFail           (option_xlateable_txt.apz_str[ 72])
#define zPathFmt              (option_xlateable_txt.apz_str[ 73])
#define zPlsSendBugs          (option_xlateable_txt.apz_str[ 74])
#define zPreset               (option_lib_text + 3461)
#define zPresetFile           (option_lib_text + 3497)
#define zPresetIntro          (option_xlateable_txt.apz_str[ 75])
#define zProhib               (option_lib_text + 3591)
#define zRange                (option_lib_text + 3617)
#define zRangeAbove           (option_lib_text + 3630)
#define zRangeErr             (option_xlateable_txt.apz_str[ 76])
#define zRangeExact           (option_lib_text + 3710)
#define zRangeLie             (option_xlateable_txt.apz_str[ 77])
#define zRangeOnly            (option_xlateable_txt.apz_str[ 78])
#define zRangeOr              (option_lib_text + 3789)
#define zRangeScaled          (option_lib_text + 3795)
#define zRangeUpto            (option_lib_text + 3841)
#define zReorder              (option_xlateable_txt.apz_str[ 79])
#define zReqFmt               (option_xlateable_txt.apz_str[ 80])
#define zReqOptFmt            (option_lib_text + 3977)
#define zReqThese             (option_xlateable_txt.apz_str[ 81])
#define zReq_NoShrtTtl        (option_xlateable_txt.apz_str[ 82])
#define zReq_ShrtTtl          (option_xlateable_txt.apz_str[ 83])
#define zResetNotConfig       (option_xlateable_txt.apz_str[ 84])
#define zSepChars             (option_xlateable_txt.apz_str[ 85])
#define zSetMemberSettings    (option_xlateable_txt.apz_str[ 86])
#define zShrtGnuOptFmt        (option_lib_text + 4367)
#define zSixSpaces            (option_lib_text + 4370)
#define zStdBoolArg           (option_lib_text + 4377)
#define zStdBreak             (option_lib_text + 4381)
#define zStdFileArg           (option_lib_text + 4389)
#define zStdKeyArg            (option_lib_text + 4393)
#define zStdKeyLArg           (option_lib_text + 4397)
#define zStdNestArg           (option_lib_text + 4401)
#define zStdNoArg             (option_lib_text + 4405)
#define zStdNumArg            (option_lib_text + 4409)
#define zStdOptArg            (option_lib_text + 4413)
#define zStdReqArg            (option_lib_text + 4417)
#define zStdStrArg            (option_lib_text + 4421)
#define zStdTimeArg           (option_lib_text + 4425)
#define zTabHyp               (option_lib_text + 4429)
#define zTabHypAnd            (option_lib_text + 4436)
#define zTabout               (option_lib_text + 4448)
#define zThreeSpaces          (option_lib_text + 4456)
#define zTooLarge             (option_xlateable_txt.apz_str[ 87])
#define zTwoSpaces            (option_lib_text + 4500)
#define zUpTo                 (option_lib_text + 4503)
#define zValidKeys            (option_xlateable_txt.apz_str[ 88])
#define zVendIntro            (option_xlateable_txt.apz_str[ 89])
#define zVendOptsAre          (option_xlateable_txt.apz_str[ 90])

  /*
   *  First, set up the strings.  Some of these are writable.  These are all in
   *  English.  This gets compiled into libopts and is distributed here so that
   *  xgettext (or equivalents) can extract these strings for translation.
   */
static char       eng_zGnuBoolArg[]  = "=T/F";
static char       eng_zGnuFileArg[]  = "=file";
static char       eng_zGnuKeyArg[]   = "=KWd";
static char       eng_zGnuKeyLArg[]  = "=Mbr";
static char       eng_zGnuNumArg[]   = "=num";
static char       eng_zGnuStrArg[]   = "=str";
static char       eng_zGnuTimeArg[]  = "=Tim";
char const option_lib_text[4660] =
/*     0 */ "malloc of %d bytes failed\n\0"
/*    27 */ "AutoOpts function called without option descriptor\n\0"
/*    79 */ "\tThis exceeds the compiled library version:  \0"
/*   125 */ "Automated Options Processing Error!\n"
            "\t%s called AutoOpts function with structure version %d:%d:%d.\n\0"
/*   224 */ "realloc of %d bytes at 0x%p failed\n\0"
/*   260 */ "\tThis is less than the minimum library version:  \0"
/*   310 */ "strdup of %d byte string failed\n\0"
/*   343 */ "Automated Options version %s\n"
            "\tcopyright (c) 1999-2012 by Bruce Korb - all rights reserved\n\0"
/*   434 */ "AutoOpts lib error: defaulted to option with optional arg\n\0"
/*   493 */ "(AutoOpts bug):  Aliasing option is out of range.\0"
/*   543 */ "all\0"
/*   547 */ "\t\t\t\t- an alternate for %s\n\0"
/*   574 */ "%s error:  the keyword `%s' is ambiguous for %s\n\0"
/*   623 */ "  The following options match:\n\0"
/*   655 */ "%s: ambiguous option name: %s (matches %d options)\n\0"
/*   707 */ "  %s%s\n\0"
/*   715 */ "%s: Command line arguments required\n\0"
/*   752 */ "%d %s%s options allowed\n\0"
/*   777 */ "version, usage and configuration options:\0"
/*   819 */ "Error %d (%s) from the pipe(2) syscall\n\0"
/*   859 */ "ERROR: version option argument '%c' invalid.  Use:\n"
            "\t'v' - version only\n"
            "\t'c' - version and copyright\n"
            "\t'n' - version and copyright notice\n\0"
/*   996 */ "ERROR:  %s option conflicts with the %s option\n\0"
/*  1044 */ "%s(optionSaveState): error: cannot allocate %d bytes\n\0"
/*  1098 */ "auto-options\0"
/*  1111 */ "program\0"
/*  1119 */ "\t\t\t\t- default option for unnamed options\n\0"
/*  1161 */ "\t\t\t\t- disabled as --%s\n\0"
/*  1185 */ "%s: The ``%s'' option has been disabled\0"
/*  1225 */ " --- %-14s %s\n\0"
/*  1240 */ "This option has been disabled\0"
/*  1270 */ "\t\t\t\t- enabled by default\n\0"
/*  1296 */ "-equivalence\0"
/*  1309 */ "ERROR:  only \0"
/*  1323 */ " - examining environment variables named %s_*\n\0"
/*  1370 */ "File error %d (%s) opening %s for loading options\n\0"
/*  1421 */ "fs error %d (%s) reading file %s\n\0"
/*  1455 */ "fopen-ing file\0"
/*  1470 */ "stat-ing for directory\0"
/*  1493 */ "stat-ing for regular file\0"
/*  1519 */ "stat-ing for non-existant file\0"
/*  1550 */ "open-ing file\0"
/*  1564 */ "fs error %d (%s) on %s %s for option %s\n\0"
/*  1605 */ "\t\t\t\t- file must not pre-exist\n\0"
/*  1636 */ "\t\t\t\t- file must pre-exist\n\0"
/*  1663 */ "     \0"
/*  1669 */ "Options are specified by doubled hyphens and their name or by a single\n"
            "hyphen and the flag character.\n\0"
/*  1772 */ "%%-%ds %%s\n\0"
/*  1784 */ "fs error %d (%s) on fork - cannot obtain %s usage\n\0"
/*  1835 */ "fs error %d (%s) on freopen\n\0"
/*  1864 */ "\n"
            "= = = = = = = =\n\n"
            "This incarnation of genshell will produce\n"
            "a shell script to parse the options for %s:\n\n\0"
/*  1970 */ "\n"
            "%s\n\n\0"
/*  1976 */ "=Cplx\0"
/*  1982 */ "[=arg]\0"
/*  1989 */ "--%2$s%1$s\0"
/*  2000 */ "%s: illegal option -- %c\n\0"
/*  2026 */ "%s: illegal option -- %s\n\0"
/*  2052 */ "%s: unknown vendor extension option -- %s\n\0"
/*  2095 */ "  or an integer from %d through %d\n\0"
/*  2131 */ "AutoOpts ERROR:  invalid option descriptor for %s\n\0"
/*  2182 */ "%s: invalid option name: %s\n\0"
/*  2211 */ "  or an integer mask with any of the lower %d bits set\n\0"
/*  2267 */ "\t\t\t\t- is a set membership option\n\0"
/*  2301 */ "%s: option `%s' requires an argument\n\0"
/*  2339 */ "Equivalenced option '%s' was equivalenced to both\n"
            "\t'%s' and '%s'\0"
/*  2404 */ "\t\t\t\t- must appear between %d and %d times\n\0"
/*  2447 */ "ERROR:  The %s option is required\n\0"
/*  2482 */ "%s: option `%s' cannot have an argument\n\0"
/*  2523 */ "%s: Command line arguments not allowed\n\0"
/*  2563 */ "error %d (%s) creating %s\n\0"
/*  2590 */ "Options are specified by single or double hyphens and their name.\n\0"
/*  2657 */ "%s error:  `%s' does not match any %s keywords\n\0"
/*  2705 */ "\t\t\t\t- may appear multiple times\n\0"
/*  2738 */ "\t\t\t\t- may not be preset\n\0"
/*  2763 */ "The 'reset-option' option requires an argument\n\0"
/*  2811 */ "   Arg Option-Name    Description\n\0"
/*  2846 */ "  Flg Arg Option-Name    Description\n\0"
/*  2884 */ "error %d (%s) stat-ing %s\n\0"
/*  2911 */ "%s(optionRestore): error: no saved option state\n\0"
/*  2960 */ "none\0"
/*  2965 */ "'%s' is not a command line option\n\0"
/*  3000 */ "%s error:  `%s' is not a recognizable date/time\n\0"
/*  3049 */ "'%s' not defined\n\0"
/*  3067 */ "%s error:  `%s' is not a recognizable time duration\n\0"
/*  3120 */ "ERROR:  The %s option must appear %d times\n\0"
/*  3164 */ "error:  cannot load options from non-regular file %s\n\0"
/*  3218 */ "%s error:  `%s' is not a recognizable number\n\0"
/*  3264 */ " %3s %s\0"
/*  3272 */ "The '-#<number>' option may omit the hash char\n\0"
/*  3320 */ "one %s%s option allowed\n\0"
/*  3345 */ "All arguments are named options.\n\0"
/*  3379 */ "Write failure to output file\0"
/*  3408 */ " - reading file %s\0"
/*  3427 */ "\n"
            "please send bug reports to:  %s\n\0"
/*  3461 */ "\t\t\t\t- may NOT appear - preset only\n\0"
/*  3497 */ "#  preset/initialization file\n"
            "#  %s#\n\0"
/*  3535 */ "\n"
            "The following option preset mechanisms are supported:\n\0"
/*  3591 */ "prohibits these options:\n\0"
/*  3617 */ "%s%ld to %ld\0"
/*  3630 */ "%sgreater than or equal to %ld\0"
/*  3661 */ "%s error:  %s option value %ld is out of range.\n\0"
/*  3710 */ "%s%ld exactly\0"
/*  3724 */ "%sIt must lie in one of the ranges:\n\0"
/*  3761 */ "%sIt must be in the range:\n\0"
/*  3789 */ ", or\n\0"
/*  3795 */ "%sis scalable with a suffix: k/K/m/M/g/G/t/T\n\0"
/*  3841 */ "%sless than or equal to %ld\0"
/*  3869 */ "Operands and options may be intermixed.  They will be reordered.\n\0"
/*  3935 */ "ERROR:  %s option requires the %s option\n\0"
/*  3977 */ " %3s %-14s %s\0"
/*  3991 */ "requires these options:\n\0"
/*  4016 */ "   Arg Option-Name   Req?  Description\n\0"
/*  4056 */ "  Flg Arg Option-Name   Req?  Description\n\0"
/*  4099 */ "The --reset-option has not been configured.\n\0"
/*  4144 */ "-_^\0"
/*  4148 */ "or you may use a numeric representation.  Preceding these with a '!' will\n"
            "clear the bits, specifying 'none' will clear all bits, and 'all' will set them\n"
            "all.  Multiple entries may be passed as an option argument list.\n\0"
/*  4367 */ "%s\0"
/*  4370 */ "      \0"
/*  4377 */ "T/F\0"
/*  4381 */ "\n"
            "%s\n\n"
            "%s\0"
/*  4389 */ "Fil\0"
/*  4393 */ "KWd\0"
/*  4397 */ "Mbr\0"
/*  4401 */ "Cpx\0"
/*  4405 */ "no \0"
/*  4409 */ "Num\0"
/*  4413 */ "opt\0"
/*  4417 */ "YES\0"
/*  4421 */ "Str\0"
/*  4425 */ "Tim\0"
/*  4429 */ "\t\t\t\t- \0"
/*  4436 */ "\t\t\t\t-- and \0"
/*  4448 */ "\t\t\t\t%s\n\0"
/*  4456 */ "   \0"
/*  4460 */ "%s error:  %s exceeds %s keyword count\n\0"
/*  4500 */ "  \0"
/*  4503 */ "\t\t\t\t- may appear up to %d times\n\0"
/*  4536 */ "The valid \"%s\" option keywords are:\n\0"
/*  4573 */ "The next option supports vendor supported extra options:\0"
/*  4630 */ "These additional options are:";

/*
 *  Now, define (and initialize) the structure that contains
 *  the pointers to all these strings.
 *  Aren't you glad you don't maintain this by hand?
 */
usage_text_t option_xlateable_txt = {
  98,
  eng_zGnuBoolArg, eng_zGnuFileArg, eng_zGnuKeyArg,  eng_zGnuKeyLArg,
  eng_zGnuNumArg,  eng_zGnuStrArg,  eng_zGnuTimeArg,
    {
    option_lib_text +    0, option_lib_text +   27, option_lib_text +   79,
    option_lib_text +  125, option_lib_text +  224, option_lib_text +  260,
    option_lib_text +  310, option_lib_text +  343, option_lib_text +  434,
    option_lib_text +  493, option_lib_text +  543, option_lib_text +  574,
    option_lib_text +  623, option_lib_text +  655, option_lib_text +  707,
    option_lib_text +  715, option_lib_text +  752, option_lib_text +  777,
    option_lib_text +  819, option_lib_text +  859, option_lib_text +  996,
    option_lib_text + 1044, option_lib_text + 1098, option_lib_text + 1111,
    option_lib_text + 1119, option_lib_text + 1161, option_lib_text + 1185,
    option_lib_text + 1240, option_lib_text + 1296, option_lib_text + 1309,
    option_lib_text + 1323, option_lib_text + 1370, option_lib_text + 1421,
    option_lib_text + 1455, option_lib_text + 1470, option_lib_text + 1493,
    option_lib_text + 1519, option_lib_text + 1550, option_lib_text + 1564,
    option_lib_text + 1669, option_lib_text + 1784, option_lib_text + 1835,
    option_lib_text + 1864, option_lib_text + 2000, option_lib_text + 2026,
    option_lib_text + 2052, option_lib_text + 2095, option_lib_text + 2131,
    option_lib_text + 2182, option_lib_text + 2211, option_lib_text + 2301,
    option_lib_text + 2339, option_lib_text + 2447, option_lib_text + 2482,
    option_lib_text + 2523, option_lib_text + 2563, option_lib_text + 2590,
    option_lib_text + 2657, option_lib_text + 2763, option_lib_text + 2811,
    option_lib_text + 2846, option_lib_text + 2884, option_lib_text + 2911,
    option_lib_text + 2960, option_lib_text + 2965, option_lib_text + 3000,
    option_lib_text + 3049, option_lib_text + 3067, option_lib_text + 3120,
    option_lib_text + 3164, option_lib_text + 3218, option_lib_text + 3320,
    option_lib_text + 3379, option_lib_text + 3408, option_lib_text + 3427,
    option_lib_text + 3535, option_lib_text + 3661, option_lib_text + 3724,
    option_lib_text + 3761, option_lib_text + 3869, option_lib_text + 3935,
    option_lib_text + 3991, option_lib_text + 4016, option_lib_text + 4056,
    option_lib_text + 4099, option_lib_text + 4144, option_lib_text + 4148,
    option_lib_text + 4460, option_lib_text + 4536, option_lib_text + 4573,
    option_lib_text + 4630
  } };
#endif /* AUTOOPTS_INTERNAL */

#ifdef XGETTEXT_SCAN_DO_NOT_COMPILE
do not compile this section.
/* TRANSLATORS: The following dummy function was crated solely so that
 * xgettext can extract the correct strings.  These strings are actually
 * referenced where the preceding "#line" directive states, though you
 * will not see the literal string there.  The literal string is defined
 * above and referenced via a #define name that redirects into the
 * "option_xlateable_txt" structure above.
 */
static void dummy_func(void) {
#line 51 "../autoopts.c"
  puts(_("malloc of %d bytes failed\n"));
#line 52 "../init.c"
  puts(_("AutoOpts function called without option descriptor\n"));
#line 85 "../init.c"
  puts(_("\tThis exceeds the compiled library version:  "));
#line 83 "../init.c"
  puts(_("Automated Options Processing Error!\n"
       "\t%s called AutoOpts function with structure version %d:%d:%d.\n"));
#line 64 "../autoopts.c"
  puts(_("realloc of %d bytes at 0x%p failed\n"));
#line 87 "../init.c"
  puts(_("\tThis is less than the minimum library version:  "));
#line 77 "../autoopts.c"
  puts(_("strdup of %d byte string failed\n"));
#line 122 "../version.c"
  puts(_("Automated Options version %s\n"
       "\tcopyright (c) 1999-2012 by Bruce Korb - all rights reserved\n"));
#line 585 "../find.c"
  puts(_("AutoOpts lib error: defaulted to option with optional arg\n"));
#line 53 "../alias.c"
  puts(_("(AutoOpts bug):  Aliasing option is out of range."));
#line 486 "../enum.c"
  puts(_("all"));
#line 228 "../enum.c"
  puts(_("%s error:  the keyword `%s' is ambiguous for %s\n"));
#line 104 "../find.c"
  puts(_("  The following options match:\n"));
#line 286 "../find.c"
  puts(_("%s: ambiguous option name: %s (matches %d options)\n"));
#line 107 "../find.c"
  puts(_("  %s%s\n"));
#line 112 "../find.c"
  puts(_("  %s%s\n"));
#line 157 "../check.c"
  puts(_("%s: Command line arguments required\n"));
#line 78 "../alias.c"
  puts(_("%d %s%s options allowed\n"));
#line 215 "../autoopts.c"
  puts(_("%d %s%s options allowed\n"));
#line 872 "../usage.c"
  puts(_("version, usage and configuration options:"));
#line 266 "../makeshell.c"
  puts(_("Error %d (%s) from the pipe(2) syscall\n"));
#line 162 "../version.c"
  puts(_("ERROR: version option argument '%c' invalid.  Use:\n"
       "\t'v' - version only\n"
       "\t'c' - version and copyright\n"
       "\t'n' - version and copyright notice\n"));
#line 56 "../check.c"
  puts(_("ERROR:  %s option conflicts with the %s option\n"));
#line 108 "../restore.c"
  puts(_("%s(optionSaveState): error: cannot allocate %d bytes\n"));
#line 593 "../configfile.c"
  puts(_("auto-options"));
#line 592 "../configfile.c"
  puts(_("program"));
#line 674 "../configfile.c"
  puts(_("program"));
#line 679 "../configfile.c"
  puts(_("program"));
#line 654 "../usage.c"
  puts(_("\t\t\t\t- default option for unnamed options\n"));
#line 569 "../usage.c"
  puts(_("\t\t\t\t- disabled as --%s\n"));
#line 210 "../find.c"
  puts(_("%s: The ``%s'' option has been disabled"));
#line 417 "../find.c"
  puts(_("%s: The ``%s'' option has been disabled"));
#line 839 "../usage.c"
  puts(_("This option has been disabled"));
#line 73 "../alias.c"
  puts(_("-equivalence"));
#line 210 "../autoopts.c"
  puts(_("-equivalence"));
#line 75 "../alias.c"
  puts(_("ERROR:  only "));
#line 212 "../autoopts.c"
  puts(_("ERROR:  only "));
#line 916 "../usage.c"
  puts(_(" - examining environment variables named %s_*\n"));
#line 1170 "../configfile.c"
  puts(_("File error %d (%s) opening %s for loading options\n"));
#line 98 "../text_mmap.c"
  puts(_("fs error %d (%s) reading file %s\n"));
#line 135 "../file.c"
  puts(_("fopen-ing file"));
#line 74 "../file.c"
  puts(_("stat-ing for directory"));
#line 86 "../file.c"
  puts(_("stat-ing for regular file"));
#line 48 "../file.c"
  puts(_("stat-ing for non-existant file"));
#line 108 "../file.c"
  puts(_("open-ing file"));
#line 47 "../file.c"
  puts(_("fs error %d (%s) on %s %s for option %s\n"));
#line 73 "../file.c"
  puts(_("fs error %d (%s) on %s %s for option %s\n"));
#line 85 "../file.c"
  puts(_("fs error %d (%s) on %s %s for option %s\n"));
#line 107 "../file.c"
  puts(_("fs error %d (%s) on %s %s for option %s\n"));
#line 134 "../file.c"
  puts(_("fs error %d (%s) on %s %s for option %s\n"));
#line 273 "../usage.c"
  puts(_("Options are specified by doubled hyphens and their name or by a single\n"
       "hyphen and the flag character.\n"));
#line 272 "../makeshell.c"
  puts(_("fs error %d (%s) on fork - cannot obtain %s usage\n"));
#line 802 "../makeshell.c"
  puts(_("fs error %d (%s) on freopen\n"));
#line 880 "../makeshell.c"
  puts(_("\n"
       "= = = = = = = =\n\n"
       "This incarnation of genshell will produce\n"
       "a shell script to parse the options for %s:\n\n"));
#line 456 "../find.c"
  puts(_("%s: illegal option -- %c\n"));
#line 106 "../reset.c"
  puts(_("%s: illegal option -- %c\n"));
#line 264 "../find.c"
  puts(_("%s: illegal option -- %s\n"));
#line 758 "../find.c"
  puts(_("%s: illegal option -- %s\n"));
#line 114 "../reset.c"
  puts(_("%s: illegal option -- %s\n"));
#line 328 "../find.c"
  puts(_("%s: unknown vendor extension option -- %s\n"));
#line 153 "../enum.c"
  puts(_("  or an integer from %d through %d\n"));
#line 163 "../enum.c"
  puts(_("  or an integer from %d through %d\n"));
#line 484 "../usage.c"
  puts(_("AutoOpts ERROR:  invalid option descriptor for %s\n"));
#line 805 "../usage.c"
  puts(_("AutoOpts ERROR:  invalid option descriptor for %s\n"));
#line 375 "../find.c"
  puts(_("%s: invalid option name: %s\n"));
#line 160 "../enum.c"
  puts(_("  or an integer mask with any of the lower %d bits set\n"));
#line 514 "../find.c"
  puts(_("%s: option `%s' requires an argument\n"));
#line 162 "../autoopts.c"
  puts(_("Equivalenced option '%s' was equivalenced to both\n"
       "\t'%s' and '%s'"));
#line 90 "../check.c"
  puts(_("ERROR:  The %s option is required\n"));
#line 620 "../find.c"
  puts(_("%s: option `%s' cannot have an argument\n"));
#line 147 "../check.c"
  puts(_("%s: Command line arguments not allowed\n"));
#line 510 "../save.c"
  puts(_("error %d (%s) creating %s\n"));
#line 275 "../usage.c"
  puts(_("Options are specified by single or double hyphens and their name.\n"));
#line 228 "../enum.c"
  puts(_("%s error:  `%s' does not match any %s keywords\n"));
#line 89 "../reset.c"
  puts(_("The 'reset-option' option requires an argument\n"));
#line 1031 "../usage.c"
  puts(_("   Arg Option-Name    Description\n"));
#line 967 "../usage.c"
  puts(_("  Flg Arg Option-Name    Description\n"));
#line 1025 "../usage.c"
  puts(_("  Flg Arg Option-Name    Description\n"));
#line 177 "../save.c"
  puts(_("error %d (%s) stat-ing %s\n"));
#line 231 "../save.c"
  puts(_("error %d (%s) stat-ing %s\n"));
#line 149 "../restore.c"
  puts(_("%s(optionRestore): error: no saved option state\n"));
#line 491 "../enum.c"
  puts(_("none"));
#line 252 "../autoopts.c"
  puts(_("'%s' is not a command line option\n"));
#line 110 "../time.c"
  puts(_("%s error:  `%s' is not a recognizable date/time\n"));
#line 126 "../save.c"
  puts(_("'%s' not defined\n"));
#line 49 "../time.c"
  puts(_("%s error:  `%s' is not a recognizable time duration\n"));
#line 89 "../check.c"
  puts(_("ERROR:  The %s option must appear %d times\n"));
#line 1180 "../configfile.c"
  puts(_("error:  cannot load options from non-regular file %s\n"));
#line 727 "../makeshell.c"
  puts(_("error:  cannot load options from non-regular file %s\n"));
#line 250 "../save.c"
  puts(_("error:  cannot load options from non-regular file %s\n"));
#line 149 "../numeric.c"
  puts(_("%s error:  `%s' is not a recognizable number\n"));
#line 80 "../alias.c"
  puts(_("one %s%s option allowed\n"));
#line 217 "../autoopts.c"
  puts(_("one %s%s option allowed\n"));
#line 177 "../makeshell.c"
  puts(_("Write failure to output file"));
#line 902 "../makeshell.c"
  puts(_("Write failure to output file"));
#line 232 "../usage.c"
  puts(_("Write failure to output file"));
#line 307 "../usage.c"
  puts(_("Write failure to output file"));
#line 168 "../version.c"
  puts(_("Write failure to output file"));
#line 701 "../usage.c"
  puts(_(" - reading file %s"));
#line 302 "../usage.c"
  puts(_("\n"
       "please send bug reports to:  %s\n"));
#line 106 "../version.c"
  puts(_("\n"
       "please send bug reports to:  %s\n"));
#line 128 "../version.c"
  puts(_("\n"
       "please send bug reports to:  %s\n"));
#line 673 "../usage.c"
  puts(_("\n"
       "The following option preset mechanisms are supported:\n"));
#line 914 "../usage.c"
  puts(_("\n"
       "The following option preset mechanisms are supported:\n"));
#line 54 "../numeric.c"
  puts(_("%s error:  %s option value %ld is out of range.\n"));
#line 62 "../numeric.c"
  puts(_("%sIt must lie in one of the ranges:\n"));
#line 62 "../numeric.c"
  puts(_("%sIt must be in the range:\n"));
#line 283 "../usage.c"
  puts(_("Operands and options may be intermixed.  They will be reordered.\n"));
#line 43 "../check.c"
  puts(_("ERROR:  %s option requires the %s option\n"));
#line 401 "../usage.c"
  puts(_("requires these options:\n"));
#line 1043 "../usage.c"
  puts(_("   Arg Option-Name   Req?  Description\n"));
#line 1037 "../usage.c"
  puts(_("  Flg Arg Option-Name   Req?  Description\n"));
#line 84 "../reset.c"
  puts(_("The --reset-option has not been configured.\n"));
#line 117 "../init.c"
  puts(_("-_^"));
#line 161 "../enum.c"
  puts(_("or you may use a numeric representation.  Preceding these with a '!' will\n"
       "clear the bits, specifying 'none' will clear all bits, and 'all' will set them\n"
       "all.  Multiple entries may be passed as an option argument list.\n"));
#line 194 "../enum.c"
  puts(_("%s error:  %s exceeds %s keyword count\n"));
#line 71 "../enum.c"
  puts(_("The valid \"%s\" option keywords are:\n"));
#line 876 "../usage.c"
  puts(_("The next option supports vendor supported extra options:"));
#line 512 "../usage.c"
  puts(_("These additional options are:"));
}
#endif /* XGETTEXT_SCAN_DO_NOT_COMPILE */
#endif /* AUTOOPTS_USAGE_TXT_H_GUARD */
