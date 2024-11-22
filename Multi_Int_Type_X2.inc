
const

(* Do not change these values *)

	Multi_X2_maxi = 3;
	Multi_X2_maxi_x2 = 7;
	Multi_X2_size = Multi_X2_maxi + 1;

	Multi_X3_maxi = 5;
	Multi_X3_maxi_x2 = 11;
	Multi_X3_size = Multi_X3_maxi + 1;

	Multi_X4_maxi = 7;
	Multi_X4_maxi_x2 = 15;
	Multi_X4_size = Multi_X4_maxi + 1;


const
	Multi_INT8_MAXINT = 127;
	Multi_INT8_MAXINT_1 = 128;
	Multi_INT8U_MAXINT = 255;
	Multi_INT8U_MAXINT_1 = 256;
	Multi_INT16_MAXINT = 32767;
	Multi_INT16_MAXINT_1 = 32768;
	Multi_INT16U_MAXINT = 65535;
	Multi_INT16U_MAXINT_1 = 65536;
	Multi_INT32_MAXINT = 2147483647;
	Multi_INT32_MAXINT_1 = 2147483648;
	Multi_INT32U_MAXINT = 4294967295;
	Multi_INT32U_MAXINT_1 = 4294967296;
	Multi_INT64_MAXINT = 9223372036854775807;
	Multi_INT64_MAXINT_1 = 9223372036854775808;
	Multi_INT64U_MAXINT = 18446744073709551615;
	Multi_INT64U_MAXINT_1 = 18446744073709551616;

	MULTI_SINGLE_TYPE_PRECISION_DIGITS	= 7;
	MULTI_REAL_TYPE_PRECISION_DIGITS	= 15;
	MULTI_DOUBLE_TYPE_PRECISION_DIGITS	= 15;

type
	Multi_int8u = byte;
	Multi_int8 = shortint;
	Multi_int16 = smallint;
	Multi_int16u = word;
	Multi_int32 = longint;
	Multi_int32u = longword;
	Multi_int64u = QWord;
	Multi_int64 = int64;

{$ifdef 32bit}
const
	MULTI_INT_1W_SIZE		= 16;
	MULTI_INT_2W_SIZE		= 32;
	MULTI_INT_4W_SIZE		= 64;

	MULTI_INT_1W_S_MAXINT	= Multi_INT16_MAXINT;
	MULTI_INT_1W_S_MAXINT_1	= Multi_INT16_MAXINT_1;
	MULTI_INT_1W_U_MAXINT	= Multi_INT16U_MAXINT;
	MULTI_INT_1W_U_MAXINT_1	= Multi_INT16U_MAXINT_1;

	MULTI_INT_2W_S_MAXINT	= Multi_INT32_MAXINT;
	MULTI_INT_2W_S_MAXINT_1	= Multi_INT32_MAXINT_1;
	MULTI_INT_2W_U_MAXINT	= Multi_INT32U_MAXINT;
	MULTI_INT_2W_U_MAXINT_1	= Multi_INT32U_MAXINT_1;

	MULTI_INT_4W_S_MAXINT	= Multi_INT64_MAXINT;
	MULTI_INT_4W_S_MAXINT_1	= Multi_INT64_MAXINT_1;
	MULTI_INT_4W_U_MAXINT	= Multi_INT64U_MAXINT;
	MULTI_INT_4W_U_MAXINT_1	= Multi_INT64U_MAXINT_1;

type

	MULTI_INT_1W_S		= Multi_int16;
	MULTI_INT_1W_U		= Multi_int16u;
	MULTI_INT_2W_S		= Multi_int32;
	MULTI_INT_2W_U		= Multi_int32u;
	MULTI_INT_4W_S		= Multi_int64;
	MULTI_INT_4W_U		= Multi_int64u;

{$endif} // 32-bit

{$ifdef 64bit}
const
	MULTI_INT_1W_SIZE		= 32;
	MULTI_INT_2W_SIZE		= 64;

	MULTI_INT_1W_S_MAXINT	= Multi_INT32_MAXINT;
	MULTI_INT_1W_S_MAXINT_1	= Multi_INT32_MAXINT_1;
	MULTI_INT_1W_U_MAXINT	= Multi_INT32U_MAXINT;
	MULTI_INT_1W_U_MAXINT_1	= Multi_INT32U_MAXINT_1;

	MULTI_INT_2W_S_MAXINT	= Multi_INT64_MAXINT;
	MULTI_INT_2W_S_MAXINT_1	= Multi_INT64_MAXINT_1;
	MULTI_INT_2W_U_MAXINT	= Multi_INT64U_MAXINT;
	MULTI_INT_2W_U_MAXINT_1	= Multi_INT64U_MAXINT_1;

type

	MULTI_INT_1W_S		= Multi_int32;
	MULTI_INT_1W_U		= Multi_int32u;
	MULTI_INT_2W_S		= Multi_int64;
	MULTI_INT_2W_U		= Multi_int64u;

{$endif} // 64-bit

type

T_HWORDS_OR_DDIGITS		=	(HALF_WORDS,DEC_DIGITS);

T_Multi_Leading_Zeros	=	(Multi_Keep_Leading_Zeros, Multi_Trim_Leading_Zeros);

T_Multi_32bit_or_64bit	=	(Multi_undef, Multi_32bit, Multi_64bit);

Multi_UBool_Values		= 	(Multi_UBool_TRUE,Multi_UBool_FALSE,Multi_UBool_UNDEF);

T_Multi_UBool	=	record
					private
						B_Value		:Multi_UBool_Values;
					public
						procedure	Init(v:Multi_UBool_Values); inline;
						function	ToStr:string; inline;
						class operator :=(v:boolean):T_Multi_UBool; inline;
						class operator :=(v:T_Multi_UBool):Boolean; inline;
						class operator :=(v:Multi_UBool_Values):T_Multi_UBool; inline;
						class operator :=(v:T_Multi_UBool):Multi_UBool_Values; inline;
						class operator =(v1,v2:T_Multi_UBool):Boolean; inline;
						class operator <>(v1,v2:T_Multi_UBool):Boolean; inline;
						class operator <=(v1,v2:T_Multi_UBool):Boolean; inline;
						class operator <(v1,v2:T_Multi_UBool):Boolean; inline;
						class operator >=(v1,v2:T_Multi_UBool):Boolean; inline;
						class operator >(v1,v2:T_Multi_UBool):Boolean; inline;
						class operator or(v1,v2:T_Multi_UBool):Boolean; inline;
						class operator or(v1:T_Multi_UBool;v2:Boolean):Boolean; inline;
						class operator or(v1:Boolean; v2:T_Multi_UBool):Boolean; inline;
						class operator and(v1,v2:T_Multi_UBool):Boolean; inline;
						class operator and(v1:T_Multi_UBool;v2:Boolean):Boolean; inline;
						class operator and(v1:Boolean; v2:T_Multi_UBool):Boolean; inline;
						class operator not(v1:T_Multi_UBool):Boolean; inline;
						class operator not(v1:T_Multi_UBool):T_Multi_UBool; inline;
					end;

Multi_Int_X2	=	record
					private
						Overflow_flag	:boolean;
						Defined_flag	:boolean;
						Negative_flag	:T_Multi_UBool;
						M_Value			:array[0..Multi_X2_maxi] of MULTI_INT_1W_U;
					public
						function ToStr:ansistring;										{$ifdef inline_functions_level_1} inline; {$endif}
						function ToHex(const LZ:T_Multi_Leading_Zeros=Multi_Trim_Leading_Zeros):ansistring;
						function ToBin(const LZ:T_Multi_Leading_Zeros=Multi_Trim_Leading_Zeros):ansistring;
						function FromHex(const v1:ansistring):Multi_Int_X2;
						function FromBin(const v1:ansistring):Multi_Int_X2;
						function Overflow:boolean;										{$ifdef inline_functions_level_1} inline; {$endif}
						function Negative:boolean;										{$ifdef inline_functions_level_1} inline; {$endif}
						function Defined:boolean;										{$ifdef inline_functions_level_1} inline; {$endif}
						class operator :=(const v1:Multi_Int_X2):Multi_int8u;
						class operator :=(const v1:Multi_Int_X2):Multi_int8;
						class operator :=(const v1:Multi_Int_X2):MULTI_INT_1W_U;
						class operator :=(const v1:Multi_Int_X2):MULTI_INT_1W_S;
						class operator :=(const v1:Multi_Int_X2):MULTI_INT_2W_U;
						class operator :=(const v1:Multi_Int_X2):MULTI_INT_2W_S;
						class operator :=(const v1:MULTI_INT_2W_S):Multi_Int_X2;		{$ifdef inline_functions_level_1} inline; {$endif}
						class operator :=(const v1:MULTI_INT_2W_U):Multi_Int_X2;		{$ifdef inline_functions_level_1} inline; {$endif}
					{$ifdef 32bit}
						class operator :=(const v1:MULTI_INT_4W_S):Multi_Int_X2;		{$ifdef inline_functions_level_1} inline; {$endif}
						class operator :=(const v1:MULTI_INT_4W_U):Multi_Int_X2;		{$ifdef inline_functions_level_1} inline; {$endif}
						class operator :=(const v1:Multi_Int_X2):MULTI_INT_4W_S;		{$ifdef inline_functions_level_1} inline; {$endif}
						class operator :=(const v1:Multi_Int_X2):MULTI_INT_4W_U;		{$ifdef inline_functions_level_1} inline; {$endif}
					{$endif}
						class operator :=(const v1:ansistring):Multi_Int_X2;			{$ifdef inline_functions_level_1} inline; {$endif}
						class operator :=(const v1:Multi_Int_X2):ansistring;			{$ifdef inline_functions_level_1} inline; {$endif}
						class operator :=(const v1:Single):Multi_Int_X2;
						class operator :=(const v1:Real):Multi_Int_X2;
						class operator :=(const v1:Double):Multi_Int_X2;
						class operator :=(const v1:Multi_Int_X2):Single;
						class operator :=(const v1:Multi_Int_X2):Real;
						class operator :=(const v1:Multi_Int_X2):Double;
						class operator +(const v1,v2:Multi_Int_X2):Multi_Int_X2;
						class operator -(const v1,v2:Multi_Int_X2):Multi_Int_X2;
						class operator inc(const v1:Multi_Int_X2):Multi_Int_X2;
						class operator dec(const v1:Multi_Int_X2):Multi_Int_X2;
						class operator *(const v1,v2:Multi_Int_X2):Multi_Int_X2;		{$ifdef inline_functions_level_1} inline; {$endif}
						class operator div(const v1,v2:Multi_Int_X2):Multi_Int_X2;
						class operator mod(const v1,v2:Multi_Int_X2):Multi_Int_X2;
						class operator xor(const v1,v2:Multi_Int_X2):Multi_Int_X2;
						class operator or(const v1,v2:Multi_Int_X2):Multi_Int_X2;
						class operator and(const v1,v2:Multi_Int_X2):Multi_Int_X2;
						class operator not(const v1:Multi_Int_X2):Multi_Int_X2;
						class operator -(const v1:Multi_Int_X2):Multi_Int_X2;			{$ifdef inline_functions_level_1} inline; {$endif}
						class operator >(const v1,v2:Multi_Int_X2):Boolean;				{$ifdef inline_functions_level_1} inline; {$endif}
						class operator <(const v1,v2:Multi_Int_X2):Boolean;				{$ifdef inline_functions_level_1} inline; {$endif}
						class operator =(const v1,v2:Multi_Int_X2):Boolean;				{$ifdef inline_functions_level_1} inline; {$endif}
						class operator <>(const v1,v2:Multi_Int_X2):Boolean;			{$ifdef inline_functions_level_1} inline; {$endif}
						class operator >=(const v1,v2:Multi_Int_X2):Boolean;			{$ifdef inline_functions_level_1} inline; {$endif}
						class operator <=(const v1,v2:Multi_Int_X2):Boolean;			{$ifdef inline_functions_level_1} inline; {$endif}
						class operator **(const v1:Multi_Int_X2; const P:MULTI_INT_2W_S):Multi_Int_X2;
						class operator shr(const v1:Multi_Int_X2; const NBits:MULTI_INT_1W_U):Multi_Int_X2;
						class operator shl(const v1:Multi_Int_X2; const NBits:MULTI_INT_1W_U):Multi_Int_X2;
					end;


var
Multi_Int_RAISE_EXCEPTIONS_ENABLED	:boolean = TRUE;
Multi_Int_ERROR						:boolean = FALSE;
Multi_Int_X2_MAXINT					:Multi_Int_X2;

procedure Multi_Int_Reset_X2_Last_Divisor;
function Odd(const v1:Multi_Int_X2):boolean; overload;					{$ifdef inline_functions_level_1} inline; {$endif}
function Even(const v1:Multi_Int_X2):boolean; overload;					{$ifdef inline_functions_level_1} inline; {$endif}
function Abs(const v1:Multi_Int_X2):Multi_Int_X2; overload;					{$ifdef inline_functions_level_1} inline; {$endif}
function Negative(const v1:Multi_Int_X2):boolean; overload;					{$ifdef inline_functions_level_1} inline; {$endif}
procedure SqRoot(const v1:Multi_Int_X2; out VR,VREM:Multi_Int_X2); overload;	
procedure SqRoot(const v1:Multi_Int_X2; out VR:Multi_Int_X2); overload;	
function SqRoot(const v1:Multi_Int_X2):Multi_Int_X2; overload;	
procedure FromHex(const v1:ansistring; out v2:Multi_Int_X2); overload;	
procedure FromBin(const v1:ansistring; out mi:Multi_Int_X2); overload;	
procedure Hex_to_Multi_Int_X2(const v1:ansistring; var mi:Multi_Int_X2); overload;
procedure bin_to_Multi_Int_X2(const v1:ansistring; out mi:Multi_Int_X2); overload;	
