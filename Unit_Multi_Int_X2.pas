UNIT Unit_Multi_Int_X2;

(******************************************************************************)
// This code is public domain.
// No copyright.
// No license.
// No warranty.
// If you want to take this code and copyright it yourself, feel free.
(******************************************************************************)

{$MODE OBJFPC}
{$MODESWITCH ADVANCEDRECORDS}
{$LONGSTRINGS ON}
{$MODESWITCH NESTEDCOMMENTS+}
{$warn 6058 off}
{$warn 5025 off}

(* USER OPTIONAL DEFINES *)

// This should be changed to 32bit if you wish to override the default/detected setting
// E.g. if your compiler is 64bit but you want to generate code for 32bit integers,
// you would remove the "{$define 64bit}" and replace it with "{$define 32bit}"
// In 99.9% of cases, you should leave this to default, unless you have problems
// running the code in a 32bit or ARM environment.
// E.g:
// {$DEFINE 32BIT}
// or
{$DEFINE 64BIT}


// This makes procedures and functions inlined
{$define inline_functions_level_1}


// This enables assertion-type code that is
// designed to be enabled only while unit testing
{$define assertion_code_enabled}


(* END OF USER OPTIONAL DEFINES *)

// Do not remove these defines

{$IFDEF 32BIT}
	{$WARNING 32BIT OVERRIDE}
{$ELSE}
	{$IFDEF 64BIT}
		{$WARNING 64BIT OVERRIDE}
	{$ELSE}
		{$IFDEF CPU64}
			{$DEFINE 64BIT}
			{$NOTE 64BIT ENVIRONMENT DETECTED}
		{$ELSE} {$IFDEF CPU32}
		  	{$DEFINE 32BIT}
			{$NOTE 32BIT ENVIRONMENT DETECTED}
		{$ELSE}
			{$FATAL Could not detect 32bit vs 64bit CPU}
		{$ENDIF}
		{$ENDIF}
	{$ENDIF}
{$ENDIF}


// This define is essential to make exceptions work correctly
// for floating-point operations on Intel 32 bit CPU's.

{$IFDEF 64BIT}
	{$IFDEF CPU32}
		{$SAFEFPUEXCEPTIONS ON}
		{$WARNING 64BIT OVERRIDE IN 32BIT ENVIRONMENT DETECTED}
		{$WARNING SETTING SAFEFPUEXCEPTIONS ON}
	{$ENDIF}
{$ELSE}
	{$IFDEF 32BIT}
		{$SAFEFPUEXCEPTIONS ON}
	{$ENDIF}
{$ENDIF}

INTERFACE

uses	sysutils
,		strutils
,       math
;

const
	version = '5.00.00';

{$include Multi_Int_Type_X2.inc}

IMPLEMENTATION

{$include Multi_Int_Common.inc}

{$include Multi_Int_Implement_X2.inc}

