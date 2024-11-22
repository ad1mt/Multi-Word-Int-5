
const
	Multi_X5_maxi = Multi_X2_maxi + 1;
	Multi_X5_maxi_x2 = Multi_X2_maxi_x2 + 2;
	Multi_X5_size = Multi_X2_size + 1;

var

X2_Last_Divisor,
X2_Last_Dividend,
X2_Last_Quotient,
X2_Last_Remainder	:Multi_Int_X2;

type

(* Multi_Int_X5 FOR INTERNAL USE ONLY! *)

Multi_Int_X5	=	record
					private
						M_Value			:array[0..Multi_X5_maxi] of MULTI_INT_1W_U;
						Negative_flag	:T_Multi_UBool;
						Overflow_flag	:boolean;
						Defined_flag	:boolean;
					public
						function Negative:boolean;
						class operator :=(const v1:MULTI_INT_2W_U):Multi_Int_X5;
						class operator :=(const v1:Multi_Int_X2):Multi_Int_X5;
						class operator >=(const v1,v2:Multi_Int_X5):Boolean;
						class operator >(const v1,v2:Multi_Int_X5):Boolean;
						class operator *(const v1,v2:Multi_Int_X5):Multi_Int_X5;
						class operator -(const v1,v2:Multi_Int_X5):Multi_Int_X5;
					end;


procedure ShiftUp_NBits_Multi_Int_X5(Var v1:Multi_Int_X5; NBits:MULTI_INT_1W_U); forward;
procedure ShiftDown_MultiBits_Multi_Int_X5(Var v1:Multi_Int_X5; NBits:MULTI_INT_1W_U); forward;
function To_Multi_Int_X2(const v1:Multi_Int_X5):Multi_Int_X2; forward; overload;

{
******************************************
Multi_Int_X2
******************************************
}

function ABS_greaterthan_Multi_Int_X2(const v1,v2:Multi_Int_X2):Boolean;
begin
if	(v1.M_Value[3] > v2.M_Value[3])
then begin Result:=TRUE; exit; end
else
	if	(v1.M_Value[3] < v2.M_Value[3])
	then begin Result:=FALSE; exit; end
	else
		if	(v1.M_Value[2] > v2.M_Value[2])
		then begin Result:=TRUE; exit; end
		else
			if	(v1.M_Value[2] < v2.M_Value[2])
			then begin Result:=FALSE; exit; end
			else
				if	(v1.M_Value[1] > v2.M_Value[1])
				then begin Result:=TRUE; exit; end
				else
					if	(v1.M_Value[1] < v2.M_Value[1])
					then begin Result:=FALSE; exit; end
					else
						if	(v1.M_Value[0] > v2.M_Value[0])
						then begin Result:=TRUE; exit; end
						else begin Result:=FALSE; exit; end;
end;


(******************************************)
function ABS_lessthan_Multi_Int_X2(const v1,v2:Multi_Int_X2):Boolean;
begin
if	(v1.M_Value[3] < v2.M_Value[3])
then begin Result:=TRUE; exit; end
else
	if	(v1.M_Value[3] > v2.M_Value[3])
	then begin Result:=FALSE; exit; end
	else
		if	(v1.M_Value[2] < v2.M_Value[2])
		then begin Result:=TRUE; exit; end
		else
			if	(v1.M_Value[2] > v2.M_Value[2])
			then begin Result:=FALSE; exit; end
			else
				if	(v1.M_Value[1] < v2.M_Value[1])
				then begin Result:=TRUE; exit; end
				else
					if	(v1.M_Value[1] > v2.M_Value[1])
					then begin Result:=FALSE; exit; end
					else
						if	(v1.M_Value[0] < v2.M_Value[0])
						then begin Result:=TRUE; exit; end
						else begin Result:=FALSE; exit; end;
end;


(******************************************)
function ABS_equal_Multi_Int_X2(const v1,v2:Multi_Int_X2):Boolean;
begin
Result:=TRUE;
if	(v1.M_Value[0] <> v2.M_Value[0])
then Result:=FALSE
else
	if	(v1.M_Value[1] <> v2.M_Value[1])
	then Result:=FALSE
	else
		if	(v1.M_Value[2] <> v2.M_Value[2])
		then Result:=FALSE
		else
			if	(v1.M_Value[3] <> v2.M_Value[3])
			then Result:=FALSE;
end;


(******************************************)
function ABS_notequal_Multi_Int_X2(const v1,v2:Multi_Int_X2):Boolean;				{$ifdef inline_functions_level_1} inline; {$endif}
begin
Result:= (not ABS_equal_Multi_Int_X2(v1,v2));
end;


(******************************************)
function nlz_words_X2(m:Multi_Int_X2):MULTI_INT_1W_U;
var
i,n		:Multi_int32;
fini	:boolean;

begin
n:= 0;
i:= Multi_X2_maxi;
fini:= false;
repeat
	if	(i < 0) then fini:= true
	else if	(m.M_Value[i] <> 0) then fini:= true
	else
		begin
		INC(n);
		DEC(i);
		end;
until fini;
Result:= n;
end;


(******************************************)
function nlz_MultiBits_X2(const v1:Multi_Int_X2):MULTI_INT_1W_U;
var	w	:MULTI_INT_1W_U;
begin
if	(Not v1.Defined_flag)
then
	begin
	Result:= 0;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	end;

w:= nlz_words_X2(v1);
if (w <= Multi_X2_maxi)
then Result:= nlz_bits(v1.M_Value[Multi_X2_maxi-w]) + (w * MULTI_INT_1W_SIZE)
else Result:= (w * MULTI_INT_1W_SIZE);
end;


(******************************************)
function Multi_Int_X2.Defined:boolean;									{$ifdef inline_functions_level_1} inline; {$endif}
begin
Result:= self.Defined_flag;
end;


(******************************************)
function Multi_Int_X2.Overflow:boolean;									{$ifdef inline_functions_level_1} inline; {$endif}
begin
Result:= self.Overflow_flag;
end;


(******************************************)
function Overflow(const v1:Multi_Int_X2):boolean; overload;				{$ifdef inline_functions_level_1} inline; {$endif}
begin
Result:= v1.Overflow_flag;
end;


(******************************************)
function Multi_Int_X2.Negative:boolean;									{$ifdef inline_functions_level_1} inline; {$endif}
begin
Result:= self.Negative_flag;
end;


(******************************************)
function Negative(const v1:Multi_Int_X2):boolean; overload;				{$ifdef inline_functions_level_1} inline; {$endif}
begin
Result:= v1.Negative_flag;
end;


(******************************************)
function Abs(const v1:Multi_Int_X2):Multi_Int_X2; overload;				{$ifdef inline_functions_level_1} inline; {$endif}
begin
Result:= v1;
Result.Negative_flag:= Multi_UBool_FALSE;

if	(Not v1.Defined_flag)
then
	begin
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	end;
end;


(******************************************)
function Defined(const v1:Multi_Int_X2):boolean; overload; 				{$ifdef inline_functions_level_1} inline; {$endif}
begin
Result:= v1.Defined_flag;
end;


(******************************************)
function Multi_Int_X2_Odd(const v1:Multi_Int_X2):boolean; 
var	bit1_mask	:MULTI_INT_1W_U;

begin
bit1_mask:= $1;

if ((v1.M_Value[0] and bit1_mask) = bit1_mask)
then Result:= TRUE
else Result:= FALSE;

if	(Not v1.Defined_flag)
then
	begin
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	end;

end;


(******************************************)
function Odd(const v1:Multi_Int_X2):boolean; overload;					{$ifdef inline_functions_level_1} inline; {$endif}
begin
Result:= Multi_Int_X2_Odd(v1);
end;


(******************************************)
function Multi_Int_X2_Even(const v1:Multi_Int_X2):boolean; 
var	bit1_mask	:MULTI_INT_1W_U;
begin

bit1_mask:= $1;

if ((v1.M_Value[0] and bit1_mask) = bit1_mask)
then Result:= FALSE
else Result:= TRUE;

if	(Not v1.Defined_flag)
then
	begin
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	end;

end;


(******************************************)
function Even(const v1:Multi_Int_X2):boolean; overload;					{$ifdef inline_functions_level_1} inline; {$endif}
begin
Result:= Multi_Int_X2_Even(v1);
end;


{$ifdef 32bit}
(******************************************)
procedure ShiftUp_NBits_Multi_Int_X2(Var v1:Multi_Int_X2; NBits:MULTI_INT_1W_U);
var	carry_bits_1,
	carry_bits_2,
	carry_bits_mask,
	NBits_max,
	NBits_carry	:MULTI_INT_1W_U;

	procedure INT_1W_U_shl(var v1:MULTI_INT_1W_U; const nbits:MULTI_INT_1W_U); 
	var carry_bits_mask_2w	:MULTI_INT_2W_U;
	begin
	carry_bits_mask_2w:= v1;
	carry_bits_mask_2w:= (carry_bits_mask_2w << NBits);
	v1:= MULTI_INT_1W_U(carry_bits_mask_2w and MULTI_INT_1W_U_MAXINT);
	end;

begin
if NBits > 0 then
begin

carry_bits_mask:= $FFFF;
NBits_max:= MULTI_INT_1W_SIZE;
NBits_carry:= (NBits_max - NBits);
INT_1W_U_shl(carry_bits_mask, NBits_carry);

if NBits <= NBits_max then
	begin
	carry_bits_1:= ((v1.M_Value[0] and carry_bits_mask) >> NBits_carry);
	INT_1W_U_shl(v1.M_Value[0], NBits);

	carry_bits_2:= ((v1.M_Value[1] and carry_bits_mask) >> NBits_carry);
	INT_1W_U_shl(v1.M_Value[1], NBits);
	v1.M_Value[1]:= (v1.M_Value[1] OR carry_bits_1);

	carry_bits_1:= ((v1.M_Value[2] and carry_bits_mask) >> NBits_carry);
	INT_1W_U_shl(v1.M_Value[2], NBits);
	v1.M_Value[2]:= (v1.M_Value[2] OR carry_bits_2);

	INT_1W_U_shl(v1.M_Value[3], NBits);
	v1.M_Value[3]:= (v1.M_Value[3] OR carry_bits_1);
	end;
end;

end;
{$endif}

{$ifdef 64bit}
(******************************************)
procedure ShiftUp_NBits_Multi_Int_X2(Var v1:Multi_Int_X2; NBits:MULTI_INT_1W_U);
var	carry_bits_1,
	carry_bits_2,
	carry_bits_mask,
	NBits_max,
	NBits_carry	:MULTI_INT_1W_U;
begin
if NBits > 0 then
	begin

	carry_bits_mask:= $FFFFFFFF;
	NBits_max:= MULTI_INT_1W_SIZE;
	NBits_carry:= (NBits_max - NBits);

	carry_bits_mask:= (carry_bits_mask << NBits_carry);

	if NBits <= NBits_max then
		begin
		carry_bits_1:= ((v1.M_Value[0] and carry_bits_mask) >> NBits_carry);
		v1.M_Value[0]:= (v1.M_Value[0] << NBits);

		carry_bits_2:= ((v1.M_Value[1] and carry_bits_mask) >> NBits_carry);
		v1.M_Value[1]:= ((v1.M_Value[1] << NBits) OR carry_bits_1);

		carry_bits_1:= ((v1.M_Value[2] and carry_bits_mask) >> NBits_carry);
		v1.M_Value[2]:= ((v1.M_Value[2] << NBits) OR carry_bits_2);

		v1.M_Value[3]:= ((v1.M_Value[3] << NBits) OR carry_bits_1);
		end;
	end;

end;
{$endif}


(******************************************)
procedure ShiftUp_NWords_Multi_Int_X2(Var v1:Multi_Int_X2; NWords:MULTI_INT_1W_U);
var	n	:MULTI_INT_1W_U;
begin
if	(NWords > 0) then
	if	(NWords <= Multi_X2_maxi) then
		begin
		n:= NWords;
		while (n > 0) do
			begin
			v1.M_Value[3]:= v1.M_Value[2];
			v1.M_Value[2]:= v1.M_Value[1];
			v1.M_Value[1]:= v1.M_Value[0];
			v1.M_Value[0]:= 0;
			DEC(n);
			end;
		end
	else
		begin
		v1.M_Value[0]:= 0;
		v1.M_Value[1]:= 0;
		v1.M_Value[2]:= 0;
		v1.M_Value[3]:= 0;
		end;
end;


{******************************************}
procedure ShiftUp_MultiBits_Multi_Int_X2(Var v1:Multi_Int_X2; NBits:MULTI_INT_1W_U);
var
NWords_count,
NBits_count		:MULTI_INT_1W_U;

begin
if	(Not v1.Defined_flag)
then
	begin
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

if (NBits > 0) then
	begin
	if (NBits >= MULTI_INT_1W_SIZE) then
		begin
		NWords_count:= (NBits DIV MULTI_INT_1W_SIZE);
		NBits_count:= (NBits MOD MULTI_INT_1W_SIZE);
		ShiftUp_NWords_Multi_Int_X2(v1, NWords_count);
		end
	else NBits_count:= NBits;
	ShiftUp_NBits_Multi_Int_X2(v1, NBits_count);
	end;
end;


(******************************************)
procedure ShiftDown_NBits_Multi_Int_X2(Var v1:Multi_Int_X2; NBits:MULTI_INT_1W_U);
var	carry_bits_1,
	carry_bits_2,
	carry_bits_mask,
	NBits_max,
	NBits_carry	:MULTI_INT_1W_U;
begin

if NBits > 0 then
	begin
	{$ifdef 32bit}
	carry_bits_mask:= $FFFF;
	{$endif}
	{$ifdef 64bit}
	carry_bits_mask:= $FFFFFFFF;
	{$endif}

	NBits_max:= MULTI_INT_1W_SIZE;
	NBits_carry:= (NBits_max - NBits);
	carry_bits_mask:= (carry_bits_mask >> NBits_carry);

	if NBits <= NBits_max then
		begin
		carry_bits_1:= ((v1.M_Value[3] and carry_bits_mask) << NBits_carry);
		v1.M_Value[3]:= (v1.M_Value[3] >> NBits);

		carry_bits_2:= ((v1.M_Value[2] and carry_bits_mask) << NBits_carry);
		v1.M_Value[2]:= ((v1.M_Value[2] >> NBits) OR carry_bits_1);

		carry_bits_1:= ((v1.M_Value[1] and carry_bits_mask) << NBits_carry);
		v1.M_Value[1]:= ((v1.M_Value[1] >> NBits) OR carry_bits_2);

		v1.M_Value[0]:= ((v1.M_Value[0] >> NBits) OR carry_bits_1);
		end;
	end;

end;


(******************************************)
procedure ShiftDown_NWords_Multi_Int_X2(Var v1:Multi_Int_X2; NWords:MULTI_INT_1W_U);
var	n	:MULTI_INT_1W_U;
begin
if	(NWords > 0) then
	if	(NWords <= Multi_X2_maxi) then
		begin
		n:= NWords;
		while (n > 0) do
			begin
			v1.M_Value[0]:= v1.M_Value[1];
			v1.M_Value[1]:= v1.M_Value[2];
			v1.M_Value[2]:= v1.M_Value[3];
			v1.M_Value[3]:= 0;
			DEC(n);
			end;
		end
	else
		begin
		v1.M_Value[0]:= 0;
		v1.M_Value[1]:= 0;
		v1.M_Value[2]:= 0;
		v1.M_Value[3]:= 0;
		end;
end;


{******************************************}
procedure ShiftDown_MultiBits_Multi_Int_X2(Var v1:Multi_Int_X2; NBits:MULTI_INT_1W_U);
var
NWords_count,
NBits_count		:MULTI_INT_1W_U;

begin
if	(Not v1.Defined_flag)
then
	begin
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

if (NBits >= MULTI_INT_1W_SIZE) then
	begin
	NWords_count:= (NBits DIV MULTI_INT_1W_SIZE);
	NBits_count:= (NBits MOD MULTI_INT_1W_SIZE);
	ShiftDown_NWords_Multi_Int_X2(v1, NWords_count);
	end
else NBits_count:= NBits;

ShiftDown_NBits_Multi_Int_X2(v1, NBits_count);
end;


{******************************************}
class operator Multi_Int_X2.shl(const v1:Multi_Int_X2; const NBits:MULTI_INT_1W_U):Multi_Int_X2;				{$ifdef inline_functions_level_1} inline; {$endif}
begin
Result:= v1;
ShiftUp_MultiBits_Multi_Int_X2(Result, NBits);
end;


{******************************************}
class operator Multi_Int_X2.shr(const v1:Multi_Int_X2; const NBits:MULTI_INT_1W_U):Multi_Int_X2;				{$ifdef inline_functions_level_1} inline; {$endif}
begin
Result:= v1;
ShiftDown_MultiBits_Multi_Int_X2(Result, NBits);
end;


(******************************************)
class operator Multi_Int_X2.<=(const v1,v2:Multi_Int_X2):Boolean;
begin
if	(Not v1.Defined_flag)
or	(Not v2.Defined_flag)
or	(v1.Overflow_flag)
or	(v2.Overflow_flag)
then
	begin
	Result:=FALSE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

Result:=FALSE;
if ( (v1.Negative_flag = FALSE) and (v2.Negative_flag = TRUE) )
then Result:=FALSE
else
	if ( (v1.Negative_flag = TRUE) and (v2.Negative_flag = FALSE) )
	then Result:=TRUE
	else
		if ( (v1.Negative_flag = FALSE) and (v2.Negative_flag = FALSE) )
		then Result:= (Not ABS_greaterthan_Multi_Int_X2(v1,v2) )
		else
			if ( (v1.Negative_flag = TRUE) and (v2.Negative_flag = TRUE) )
			then Result:= (Not ABS_lessthan_Multi_Int_X2(v1,v2));
end;


(******************************************)
class operator Multi_Int_X2.>=(const v1,v2:Multi_Int_X2):Boolean;
begin
if	(Not v1.Defined_flag)
or	(Not v2.Defined_flag)
or	(v1.Overflow_flag)
or	(v2.Overflow_flag)
then
	begin
	Result:=FALSE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

Result:=FALSE;
if ( (v1.Negative_flag = FALSE) and (v2.Negative_flag = TRUE) )
then Result:=TRUE
else
	if ( (v1.Negative_flag = TRUE) and (v2.Negative_flag = FALSE) )
	then Result:=FALSE
	else
		if ( (v1.Negative_flag = FALSE) and (v2.Negative_flag = FALSE) )
		then Result:= (Not ABS_lessthan_Multi_Int_X2(v1,v2) )
		else
			if ( (v1.Negative_flag = TRUE) and (v2.Negative_flag = TRUE) )
			then Result:= (Not ABS_greaterthan_Multi_Int_X2(v1,v2) );
end;


(******************************************)
class operator Multi_Int_X2.>(const v1,v2:Multi_Int_X2):Boolean;
begin
if	(Not v1.Defined_flag)
or	(Not v2.Defined_flag)
or	(v1.Overflow_flag)
or	(v2.Overflow_flag)
then
	begin
	Result:=FALSE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

Result:=FALSE;
if ( (v1.Negative_flag = FALSE) and (v2.Negative_flag = TRUE) )
then Result:=TRUE
else
	if ( (v1.Negative_flag = TRUE) and (v2.Negative_flag = FALSE) )
	then Result:=FALSE
	else
		if ( (v1.Negative_flag = FALSE) and (v2.Negative_flag = FALSE) )
		then Result:= ABS_greaterthan_Multi_Int_X2(v1,v2)
		else
			if ( (v1.Negative_flag = TRUE) and (v2.Negative_flag = TRUE) )
			then Result:= ABS_lessthan_Multi_Int_X2(v1,v2);
end;


(******************************************)
class operator Multi_Int_X2.<(const v1,v2:Multi_Int_X2):Boolean;
begin
if	(Not v1.Defined_flag)
or	(Not v2.Defined_flag)
or	(v1.Overflow_flag)
or	(v2.Overflow_flag)
then
	begin
	Result:=FALSE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

Result:=FALSE;
if ( (v1.Negative_flag = TRUE) and (v2.Negative_flag = FALSE) )
then Result:=TRUE
else
	if ( (v1.Negative_flag = FALSE) and (v2.Negative_flag = FALSE) )
	then Result:= ABS_lessthan_Multi_Int_X2(v1,v2)
	else
		if ( (v1.Negative_flag = TRUE) and (v2.Negative_flag = TRUE) )
		then Result:= ABS_greaterthan_Multi_Int_X2(v1,v2);
end;


(******************************************)
class operator Multi_Int_X2.=(const v1,v2:Multi_Int_X2):Boolean;
begin
if	(Not v1.Defined_flag)
or	(Not v2.Defined_flag)
or	(v1.Overflow_flag)
or	(v2.Overflow_flag)
then
	begin
	Result:=FALSE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

Result:= TRUE;
if ( v1.Negative_flag <> v2.Negative_flag )
then Result:= FALSE
else Result:= ABS_equal_Multi_Int_X2(v1,v2);
end;


(******************************************)
class operator Multi_Int_X2.<>(const v1,v2:Multi_Int_X2):Boolean;
begin
if	(Not v1.Defined_flag)
or	(Not v2.Defined_flag)
or	(v1.Overflow_flag)
or	(v2.Overflow_flag)
then
	begin
	Result:=FALSE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

Result:= FALSE;
if ( v1.Negative_flag <> v2.Negative_flag )
then Result:= TRUE
else Result:= (not ABS_equal_Multi_Int_X2(v1,v2));
end;


(******************************************)
procedure ansistring_to_Multi_Int_X2_v1(const v1:ansistring; out mi:Multi_Int_X2); 
var
	i,b,c,e		:MULTI_INT_2W_U;
	M_Val		:array[0..Multi_X2_maxi] of MULTI_INT_2W_U;
	Signeg,
	Zeroneg		:boolean;
begin
Multi_Int_ERROR:= FALSE;

mi.Overflow_flag:=FALSE;
mi.Defined_flag:= TRUE;
mi.Negative_flag:= FALSE;
Signeg:= FALSE;
Zeroneg:= FALSE;

M_Val[0]:= 0;
M_Val[1]:= 0;
M_Val[2]:= 0;
M_Val[3]:= 0;

if	(length(v1) > 0) then
	begin
	b:=low(ansistring);
	e:=b + MULTI_INT_2W_U(length(v1)) - 1;
	if	(v1[b] = '-') then
		begin
		Signeg:= TRUE;
		INC(b);
		end;

	c:= b;
	while (c <= e) do
		begin
		try	i:=strtoint(v1[c]);
			except
				on EConvertError do
					begin
					Multi_Int_ERROR:= TRUE;
					mi.Overflow_flag:=TRUE;
					mi.Defined_flag:= FALSE;
					if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
						begin
						Raise;
						end;
					end;
			end;
 		if mi.Defined_flag = FALSE then exit;
		M_Val[0]:=(M_Val[0] * 10) + i;
		M_Val[1]:=(M_Val[1] * 10);
		M_Val[2]:=(M_Val[2] * 10);
		M_Val[3]:=(M_Val[3] * 10);

		if	M_Val[0] > MULTI_INT_1W_U_MAXINT then
			begin
			M_Val[1]:=M_Val[1] + (M_Val[0] DIV MULTI_INT_1W_U_MAXINT_1);
			M_Val[0]:=(M_Val[0] MOD MULTI_INT_1W_U_MAXINT_1);
			end;

		if	M_Val[1] > MULTI_INT_1W_U_MAXINT then
			begin
			M_Val[2]:=M_Val[2] + (M_Val[1] DIV MULTI_INT_1W_U_MAXINT_1);
			M_Val[1]:=(M_Val[1] MOD MULTI_INT_1W_U_MAXINT_1);
			end;

		if	M_Val[2] > MULTI_INT_1W_U_MAXINT then
			begin
			M_Val[3]:=M_Val[3] + (M_Val[2] DIV MULTI_INT_1W_U_MAXINT_1);
			M_Val[2]:=(M_Val[2] MOD MULTI_INT_1W_U_MAXINT_1);
			end;

		if	M_Val[3] > MULTI_INT_1W_U_MAXINT then
			begin
			Multi_Int_ERROR:= TRUE;
			mi.Defined_flag:=FALSE;
			mi.Overflow_flag:=TRUE;
			if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
				begin
				Raise EIntOverflow.create('Overflow');
				end;
			exit;
			end;

		Inc(c);
		end;
	end;

mi.M_Value[0]:= M_Val[0];
mi.M_Value[1]:= M_Val[1];
mi.M_Value[2]:= M_Val[2];
mi.M_Value[3]:= M_Val[3];

if	(M_Val[0] = 0)
and	(M_Val[1] = 0)
and	(M_Val[2] = 0)
and	(M_Val[3] = 0)
then Zeroneg:= TRUE;

if Zeroneg then mi.Negative_flag:= Multi_UBool_FALSE
else if Signeg then mi.Negative_flag:= Multi_UBool_TRUE
else mi.Negative_flag:= Multi_UBool_FALSE;
end;


{$ifdef 32bit}
(******************************************)
procedure MULTI_INT_4W_S_to_Multi_Int_X2(const v1:MULTI_INT_4W_S; out mi:Multi_Int_X2); 
var
v	:MULTI_INT_4W_U;
begin
mi.Overflow_flag:=FALSE;
mi.Defined_flag:=TRUE;
v:= Abs(v1);

v:= v1;
mi.M_Value[0]:= MULTI_INT_1W_U(v MOD MULTI_INT_1W_U_MAXINT_1);
v:= (v div MULTI_INT_1W_U_MAXINT_1);
mi.M_Value[1]:= MULTI_INT_1W_U(v MOD MULTI_INT_1W_U_MAXINT_1);
v:= (v div MULTI_INT_1W_U_MAXINT_1);
mi.M_Value[2]:= MULTI_INT_1W_U(v MOD MULTI_INT_1W_U_MAXINT_1);
v:= (v div MULTI_INT_1W_U_MAXINT_1);
mi.M_Value[3]:= v;

if (v1 < 0) then mi.Negative_flag:= Multi_UBool_TRUE
else mi.Negative_flag:= Multi_UBool_FALSE;

end;


(******************************************)
class operator Multi_Int_X2.:=(const v1:MULTI_INT_4W_S):Multi_Int_X2;				{$ifdef inline_functions_level_1} inline; {$endif}
begin
MULTI_INT_4W_S_to_Multi_Int_X2(v1,Result);
end;


(******************************************)
procedure MULTI_INT_4W_U_to_Multi_Int_X2(const v1:MULTI_INT_4W_U; out mi:Multi_Int_X2); 
var
v	:MULTI_INT_4W_U;
begin
mi.Overflow_flag:=FALSE;
mi.Defined_flag:=TRUE;
mi.Negative_flag:= Multi_UBool_FALSE;

v:= v1;
mi.M_Value[0]:= MULTI_INT_1W_U(v MOD MULTI_INT_1W_U_MAXINT_1);
v:= (v div MULTI_INT_1W_U_MAXINT_1);
mi.M_Value[1]:= MULTI_INT_1W_U(v MOD MULTI_INT_1W_U_MAXINT_1);
v:= (v div MULTI_INT_1W_U_MAXINT_1);
mi.M_Value[2]:= MULTI_INT_1W_U(v MOD MULTI_INT_1W_U_MAXINT_1);
v:= (v div MULTI_INT_1W_U_MAXINT_1);
mi.M_Value[3]:= v;

end;


(******************************************)
class operator Multi_Int_X2.:=(const v1:MULTI_INT_4W_U):Multi_Int_X2;
begin
MULTI_INT_4W_U_to_Multi_Int_X2(v1,Result);
end;
{$endif}


(******************************************)
procedure MULTI_INT_2W_S_to_Multi_Int_X2(const v1:MULTI_INT_2W_S; out mi:Multi_Int_X2); 
begin
mi.Overflow_flag:=FALSE;
mi.Defined_flag:=TRUE;
mi.M_Value[2]:= 0;
mi.M_Value[3]:= 0;

if (v1 < 0) then
	begin
	mi.Negative_flag:= Multi_UBool_TRUE;
	mi.M_Value[0]:= (ABS(v1) MOD MULTI_INT_1W_U_MAXINT_1);
	mi.M_Value[1]:= (ABS(v1) DIV MULTI_INT_1W_U_MAXINT_1);
	end
else
	begin
	mi.Negative_flag:= Multi_UBool_FALSE;
	mi.M_Value[0]:= (v1 MOD MULTI_INT_1W_U_MAXINT_1);
	mi.M_Value[1]:= (v1 DIV MULTI_INT_1W_U_MAXINT_1);
	end;

end;


(******************************************)
class operator Multi_Int_X2.:=(const v1:MULTI_INT_2W_S):Multi_Int_X2;				{$ifdef inline_functions_level_1} inline; {$endif}
begin
MULTI_INT_2W_S_to_Multi_Int_X2(v1,Result);
end;


(******************************************)
procedure MULTI_INT_2W_U_to_Multi_Int_X2(const v1:MULTI_INT_2W_U; out mi:Multi_Int_X2); 
begin
mi.Overflow_flag:=FALSE;
mi.Defined_flag:=TRUE;
mi.Negative_flag:= Multi_UBool_FALSE;

mi.M_Value[0]:= (v1 MOD MULTI_INT_1W_U_MAXINT_1);
mi.M_Value[1]:= (v1 DIV MULTI_INT_1W_U_MAXINT_1);
mi.M_Value[2]:= 0;
mi.M_Value[3]:= 0;
end;


(******************************************)
class operator Multi_Int_X2.:=(const v1:MULTI_INT_2W_U):Multi_Int_X2;				{$ifdef inline_functions_level_1} inline; {$endif}
begin
MULTI_INT_2W_U_to_Multi_Int_X2(v1,Result);
end;


(******************************************)
class operator Multi_Int_X2.:=(const v1:Multi_Int_X2):Single;
var
R,V,M		:Single;
i			:MULTI_INT_1W_U;
finished	:boolean;
begin
if	(Not v1.Defined_flag)
then
	begin
	Multi_Int_ERROR:= TRUE;
	Result:=0;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

Multi_Int_ERROR:= FALSE;
finished:= FALSE;
M:= MULTI_INT_1W_U_MAXINT_1;
R:=	v1.M_Value[0];
i:= 1;
while	(i <= Multi_X2_maxi)
and		(not Multi_Int_ERROR)
do
	begin
	if	(not finished)
	then
		begin
			V:= v1.M_Value[i];
			try begin
				V:= (V * M);
				R:= R + V;
				end
			except Multi_Int_ERROR:= TRUE;
			end; // except
			if V.IsInfinity
			or single.IsInfinity(R) then
				Multi_Int_ERROR:= TRUE;

			if (Multi_Int_ERROR) then
				begin
				finished:= TRUE;
				if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
					begin
					Raise EIntOverflow.create('Overflow');
					end;
				end;

			V:= MULTI_INT_1W_U_MAXINT_1;
			try M:= (M * V);
			except finished:= TRUE;
			end; // except
			if single.IsInfinity(M) then 
				finished:= TRUE;
		end
	else
		begin
		if	(v1.M_Value[i] > 0) then
			begin
			Multi_Int_ERROR:= TRUE;
			if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
				begin
				Raise EIntOverflow.create('Overflow');
				end;
			end;
		end;
	Inc(i);
	end;

if v1.Negative_flag then R:= (- R);
Result:= R;
end;


(******************************************)
class operator Multi_Int_X2.:=(const v1:Multi_Int_X2):Real;
var
	R,V,M	:Real;
	i		:MULTI_INT_1W_U;
finished	:boolean;
begin
if	(Not v1.Defined_flag)
then
	begin
	Multi_Int_ERROR:= TRUE;
	Result:=0;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

Multi_Int_ERROR:= FALSE;
finished:= FALSE;
M:= MULTI_INT_1W_U_MAXINT_1;

R:=	v1.M_Value[0];
i:= 1;
while	(i <= Multi_X2_maxi)
and		(not Multi_Int_ERROR)
do
	begin
	if	(not finished)
	then
		begin
			V:= v1.M_Value[i];
			try begin
				V:= (V * M);
				R:= R + V;
				end
			except Multi_Int_ERROR:= TRUE;
			end; // except
			{
			if single.IsInfinity(V)
			or single.IsInfinity(R) then
				Multi_Int_ERROR:= TRUE;
			}

			if (Multi_Int_ERROR) then
				begin
				finished:= TRUE;
				if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
					begin
					Raise EIntOverflow.create('Overflow');
					end;
				end;

			V:= MULTI_INT_1W_U_MAXINT_1;
			try M:= (M * V);
			except finished:= TRUE;
			end; // except
			{
			if single.IsInfinity(M) then 
				finished:= TRUE;
			}
		end
	else
		begin
		if	(v1.M_Value[i] > 0) then
			begin
			Multi_Int_ERROR:= TRUE;
			if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
				begin
				Raise EIntOverflow.create('Overflow');
				end;
			end;
		end;
	Inc(i);
	end;

if v1.Negative_flag then R:= (- R);
Result:= R;
end;


(******************************************)
class operator Multi_Int_X2.:=(const v1:Multi_Int_X2):Double;
var
	R,V,M	:Double;
	i		:MULTI_INT_1W_U;
finished	:boolean;
begin
if	(Not v1.Defined_flag)
then
	begin
	Multi_Int_ERROR:= TRUE;
	Result:=0;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

Multi_Int_ERROR:= FALSE;
finished:= FALSE;
M:= MULTI_INT_1W_U_MAXINT_1;

R:=	v1.M_Value[0];
i:= 1;
while	(i <= Multi_X2_maxi)
and		(not Multi_Int_ERROR)
do
	begin
	if	(not finished)
	then
		begin
			V:= v1.M_Value[i];
			try begin
				V:= (V * M);
				R:= R + V;
				end
			except Multi_Int_ERROR:= TRUE;
			end; // except
			if double.IsInfinity(V)
			or double.IsInfinity(R) then
				Multi_Int_ERROR:= TRUE;

			if (Multi_Int_ERROR) then
				begin
				finished:= TRUE;
				if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
					begin
					Raise EIntOverflow.create('Overflow');
					end;
				end;

			V:= MULTI_INT_1W_U_MAXINT_1;
			try M:= (M * V);
			except finished:= TRUE;
			end; // except
			if double.IsInfinity(M) then 
				finished:= TRUE;
		end
	else
		begin
		if	(v1.M_Value[i] > 0) then
			begin
			Multi_Int_ERROR:= TRUE;
			if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
				begin
				Raise EIntOverflow.create('Overflow');
				end;
			end;
		end;
	Inc(i);
	end;

if v1.Negative_flag then R:= (- R);
Result:= R;
end;


{$ifdef 32bit}

(******************************************)
class operator Multi_Int_X2.:=(const v1:Multi_Int_X2):MULTI_INT_4W_S;
var		R	:MULTI_INT_4W_U;
begin
Multi_Int_ERROR:= FALSE;
if	(Not v1.Defined_flag)
then
	begin
	Result:=0;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

if	(v1 > MULTI_INT_4W_U_MAXINT)
or	(v1 < (-MULTI_INT_4W_U_MAXINT_1))
then
	begin
	Result:=0;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Overflow');
		end;
	exit;
	end;

R:=	MULTI_INT_4W_U(v1.M_Value[3]);
R:=	(R * MULTI_INT_1W_U_MAXINT_1) + MULTI_INT_4W_U(v1.M_Value[2]);
R:=	(R * MULTI_INT_1W_U_MAXINT_1) + MULTI_INT_4W_U(v1.M_Value[1]);
R:=	(R * MULTI_INT_1W_U_MAXINT_1) + MULTI_INT_4W_U(v1.M_Value[0]);

if v1.Negative_flag
then Result:= MULTI_INT_4W_S(-R)
else Result:= MULTI_INT_4W_S(R);
end;



(******************************************)
class operator Multi_Int_X2.:=(const v1:Multi_Int_X2):MULTI_INT_4W_U;
var		R	:MULTI_INT_4W_U;
begin
Multi_Int_ERROR:= FALSE;
if	(Not v1.Defined_flag)
then
	begin
	Result:=0;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

if	(v1 > MULTI_INT_4W_U_MAXINT)
or	(v1.Negative_flag)
then
	begin
	Result:=0;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Overflow');
		end;
	exit;
	end;

R:=	MULTI_INT_4W_U(v1.M_Value[3]);
R:=	(R * MULTI_INT_1W_U_MAXINT_1) + MULTI_INT_4W_U(v1.M_Value[2]);
R:=	(R * MULTI_INT_1W_U_MAXINT_1) + MULTI_INT_4W_U(v1.M_Value[1]);
R:=	(R * MULTI_INT_1W_U_MAXINT_1) + MULTI_INT_4W_U(v1.M_Value[0]);

Result:= (R);
end;

{$endif}


{******************************************}
class operator Multi_Int_X2.:=(const v1:Multi_Int_X2):MULTI_INT_2W_S;
var	R	:MULTI_INT_2W_U;
begin
Multi_Int_ERROR:= FALSE;
if	(Not v1.Defined_flag)
then
	begin
	Multi_Int_ERROR:= TRUE;
	Result:=0;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

R:= (MULTI_INT_2W_U(v1.M_Value[0]) + (MULTI_INT_2W_U(v1.M_Value[1]) * MULTI_INT_1W_U_MAXINT_1));

if	(R > MULTI_INT_2W_S_MAXINT)
or	(v1.M_Value[2] <> 0)
or	(v1.M_Value[3] <> 0)
then
	begin
	Result:=0;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Overflow');
		end;
	exit;
	end;

if v1.Negative_flag
then Result:= MULTI_INT_2W_S(-R)
else Result:= MULTI_INT_2W_S(R);
end;


{******************************************}
class operator Multi_Int_X2.:=(const v1:Multi_Int_X2):MULTI_INT_2W_U;
var	R	:MULTI_INT_2W_U;
begin
Multi_Int_ERROR:= FALSE;
if	(Not v1.Defined_flag)
then
	begin
	Result:=0;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

R:= (MULTI_INT_2W_U(v1.M_Value[1]) << MULTI_INT_1W_SIZE);
R:= (R OR MULTI_INT_2W_U(v1.M_Value[0]));

if	(v1.M_Value[2] <> 0)
or	(v1.M_Value[3] <> 0)
then
	begin
	Result:=0;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Overflow');
		end;
	exit;
	end;
Result:= R;
end;


{******************************************}
class operator Multi_Int_X2.:=(const v1:Multi_Int_X2):MULTI_INT_1W_S;
var	R	:MULTI_INT_2W_U;
begin
Multi_Int_ERROR:= FALSE;
if	(Not v1.Defined_flag)
then
	begin
	Result:=0;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

R:= (MULTI_INT_2W_U(v1.M_Value[0]) + (MULTI_INT_2W_U(v1.M_Value[1]) * MULTI_INT_1W_U_MAXINT_1));

if	(R > MULTI_INT_1W_S_MAXINT)
or	(v1.M_Value[2] <> 0)
or	(v1.M_Value[3] <> 0)
then
	begin
	Result:=0;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Overflow');
		end;
	exit;
	end;

if v1.Negative_flag
then Result:= MULTI_INT_1W_S(-R)
else Result:= MULTI_INT_1W_S(R);
end;


{******************************************}
class operator Multi_Int_X2.:=(const v1:Multi_Int_X2):MULTI_INT_1W_U;
var	R	:MULTI_INT_2W_U;
begin
Multi_Int_ERROR:= FALSE;
if	(Not v1.Defined_flag)
or	(v1.Negative_flag = Multi_UBool_TRUE)
then
	begin
	Result:=0;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

R:= (v1.M_Value[0] + (v1.M_Value[1] * MULTI_INT_1W_U_MAXINT_1));
if	(R > MULTI_INT_1W_U_MAXINT)
or	(v1.M_Value[2] <> 0)
or	(v1.M_Value[3] <> 0)
then
	begin
	Result:=0;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Overflow');
		end;
	exit;
	end;

Result:= MULTI_INT_1W_U(R);
end;


{******************************************}
class operator Multi_Int_X2.:=(const v1:Multi_Int_X2):Multi_int8u;
begin
Multi_Int_ERROR:= FALSE;
if	(Not v1.Defined_flag)
or	(v1.Negative_flag = Multi_UBool_TRUE)
then
	begin
	Result:=0;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

if (v1.M_Value[0] > Multi_INT8U_MAXINT)
or	(v1.M_Value[1] <> 0)
or	(v1.M_Value[2] <> 0)
or	(v1.M_Value[3] <> 0)
then
	begin
	Multi_Int_ERROR:= TRUE;
	Result:=0;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Overflow');
		end;
	exit;
	end;

Result:= Multi_int8u(v1.M_Value[0]);
end;


{******************************************}
class operator Multi_Int_X2.:=(const v1:Multi_Int_X2):Multi_int8;
begin
Multi_Int_ERROR:= FALSE;
if	(Not v1.Defined_flag)
or	(v1.Negative_flag = Multi_UBool_TRUE)
then
	begin
	Result:=0;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

if (v1.M_Value[0] > Multi_INT8_MAXINT)
or	(v1.M_Value[1] <> 0)
or	(v1.M_Value[2] <> 0)
or	(v1.M_Value[3] <> 0)
then
	begin
	Multi_Int_ERROR:= TRUE;
	Result:=0;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Overflow');
		end;
	exit;
	end;

Result:= Multi_int8(v1.M_Value[0]);
end;


(******************************************)
procedure bin_to_Multi_Int_X2(const v1:ansistring; out mi:Multi_Int_X2); 
var
	n,b,c,e	:MULTI_INT_2W_U;
	bit			:MULTI_INT_1W_S;
	M_Val		:array[0..Multi_X2_maxi] of MULTI_INT_2W_U;
	Signeg,
	Zeroneg,
	M_Val_All_Zero		:boolean;
begin
Multi_Int_ERROR:= FALSE;

mi.Overflow_flag:=FALSE;
mi.Defined_flag:= TRUE;
mi.Negative_flag:= FALSE;
Signeg:= FALSE;
Zeroneg:= FALSE;

n:=0;
while (n <= Multi_X2_maxi)
do begin M_Val[n]:= 0; inc(n); end;

if	(length(v1) > 0) then
	begin
	b:=low(ansistring);
	e:=b + MULTI_INT_2W_U(length(v1)) - 1;
	if	(v1[b] = '-') then
		begin
		Signeg:= TRUE;
		INC(b);
		end;

	c:= b;
	while (c <= e) do
		begin
		bit:= (ord(v1[c]) - ord('0'));
		if	(bit > 1)
		or	(bit < 0)
		then
			begin
			Multi_Int_ERROR:= TRUE;
			mi.Overflow_flag:=TRUE;
			mi.Defined_flag:= FALSE;
			if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
				Raise EInterror.create('Invalid binary digit');
			exit;
			end;

		M_Val[0]:=(M_Val[0] * 2) + bit;
		n:=1;
		while (n <= Multi_X2_maxi) do
			begin
			M_Val[n]:=(M_Val[n] * 2);
			inc(n);
			end;

		n:=0;
		while (n < Multi_X2_maxi) do
			begin
			if	M_Val[n] > MULTI_INT_1W_U_MAXINT then
				begin
				M_Val[n+1]:=M_Val[n+1] + (M_Val[n] DIV MULTI_INT_1W_U_MAXINT_1);
				M_Val[n]:=(M_Val[n] MOD MULTI_INT_1W_U_MAXINT_1);
				end;

			inc(n);
			end;

		if	M_Val[n] > MULTI_INT_1W_U_MAXINT then
			begin
			mi.Defined_flag:=FALSE;
			mi.Overflow_flag:=TRUE;
			Multi_Int_ERROR:= TRUE;
			if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
				begin
				Raise EIntOverflow.create('Overflow');
				end;
			exit;
			end;
		Inc(c);
		end;
	end;

M_Val_All_Zero:= TRUE;
n:=0;
while (n <= Multi_X2_maxi) do
	begin
	mi.M_Value[n]:= M_Val[n];
	if M_Val[n] > 0 then M_Val_All_Zero:= FALSE;
	inc(n);
	end;
if M_Val_All_Zero then Zeroneg:= TRUE;

if Zeroneg then mi.Negative_flag:= Multi_UBool_FALSE
else if Signeg then mi.Negative_flag:= Multi_UBool_TRUE
else mi.Negative_flag:= Multi_UBool_FALSE;
end;


(******************************************)
procedure FromBin(const v1:ansistring; out mi:Multi_Int_X2); overload;				{$ifdef inline_functions_level_1} inline; {$endif}
begin
Bin_to_Multi_Int_X2(v1,mi);
end;


(******************************************)
function Multi_Int_X2.FromBin(const v1:ansistring):Multi_Int_X2;				{$ifdef inline_functions_level_1} inline; {$endif}
begin
bin_to_Multi_Int_X2(v1,Result);
end;


(******************************************)
procedure Multi_Int_X2_to_bin(const v1:Multi_Int_X2; out v2:ansistring; LZ:T_Multi_Leading_Zeros); 
var
	s		:ansistring = '';
	n		:MULTI_INT_1W_S;
begin
if	(Not v1.Defined_flag)
then
	begin
	v2:='UNDEFINED';
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;
if	(v1.Overflow_flag)
then
	begin
	v2:='OVERFLOW';
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Overflow');
		end;
	exit;
	end;

n:= MULTI_INT_1W_SIZE;
s:= '';

s:= s
	+   IntToBin(v1.M_Value[3],n)
	+   IntToBin(v1.M_Value[2],n)
	+   IntToBin(v1.M_Value[1],n)
	+   IntToBin(v1.M_Value[0],n)
	;

if (LZ = Multi_Trim_Leading_Zeros) then Removeleadingchars(s,['0']);
if	(v1.Negative_flag = Multi_UBool_TRUE) then s:='-' + s;
if	(s = '') then s:= '0';
v2:=s;
end;


(******************************************)
function Multi_Int_X2.Tobin(const LZ:T_Multi_Leading_Zeros):ansistring;				{$ifdef inline_functions_level_1} inline; {$endif}
begin
Multi_Int_X2_to_bin(self, Result, LZ);
end;


(******************************************)
procedure Multi_Int_X2_to_hex(const v1:Multi_Int_X2; out v2:ansistring; LZ:T_Multi_Leading_Zeros); 
var
	s		:ansistring = '';
	n		:Multi_int32u;
begin
if	(Not v1.Defined_flag)
then
	begin
	v2:='UNDEFINED';
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;
if	(v1.Overflow_flag)
then
	begin
	v2:='OVERFLOW';
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Overflow');
		end;
	exit;
	end;

n:= (MULTI_INT_1W_SIZE div 4);
s:= '';

s:= s
	+   IntToHex(v1.M_Value[3],n)
	+   IntToHex(v1.M_Value[2],n)
	+   IntToHex(v1.M_Value[1],n)
	+   IntToHex(v1.M_Value[0],n)
	;

if	(LZ = Multi_Trim_Leading_Zeros) then Removeleadingchars(s,['0']);
if	(v1.Negative_flag = Multi_UBool_TRUE) then s:='-' + s;
if	(s = '') then s:= '0';
v2:=s;
end;


(******************************************)
function Multi_Int_X2.ToHex(const LZ:T_Multi_Leading_Zeros):ansistring;				{$ifdef inline_functions_level_1} inline; {$endif}
begin
Multi_Int_X2_to_hex(self, Result, LZ);
end;


(*******************v2*********************)
procedure hex_to_Multi_Int_X2(const v1:ansistring; var mi:Multi_Int_X2);
var
	b,bi,bs,i,
	L,p,s,w		:MULTI_INT_2W_S;
	v			:MULTI_INT_2W_U;
	hex_substr	:ansistring;
	Signeg,
	Zeroneg,
	All_Zero	:boolean;

begin
mi.Overflow_flag:=FALSE;
mi.Defined_flag:= TRUE;
mi.Negative_flag:= FALSE;
mi:= 0;

if	(length(v1) = 0) then exit;

Zeroneg:= FALSE;
Signeg:= FALSE;

w:= (MULTI_INT_1W_SIZE div 4);

bi:= low(ansistring);
b:= 0;
if	(v1[bi] = '-') then
	begin
	Signeg:= TRUE;
	INC(b);
	end;
bs:= (bi + b);

L:= (length(v1) - b);
s:= (L div w);
if	((L mod w) > 0) then Inc(s);
if (s > Multi_X2_size) then
	begin
	mi.Overflow_flag:= TRUE;
	mi.Defined_flag:= FALSE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		Raise EIntOverflow.create('Overflow');
	exit;
	end;

All_Zero:= TRUE;
i:= 0;
L:= w;
p:= (bi + length(v1) - w);
repeat
	if	(p < bs) then
		begin
	    L:= (w - (bs - p));
		p:= bs;
		end;
	if	(L > 0) then
		begin
		hex_substr:= AnsiMidStr(v1,p,L);
		try
			v:= Hex2Dec64(hex_substr);
			except
				Multi_Int_ERROR:= TRUE;
				mi.Overflow_flag:=TRUE;
				mi.Defined_flag:= FALSE;
				if Multi_Int_RAISE_EXCEPTIONS_ENABLED then Raise;
				exit;
			end;
		mi.M_Value[i]:= v;
		if v <> 0 then All_Zero:= FALSE;
		p:= (p - w);
		Inc(i);
		end;
until L = 0;

if All_Zero then Zeroneg:= TRUE;

if Zeroneg then mi.Negative_flag:= Multi_UBool_FALSE
else if Signeg then mi.Negative_flag:= Multi_UBool_TRUE
else mi.Negative_flag:= Multi_UBool_FALSE;

end;


(******************************************)
procedure FromHex(const v1:ansistring; out v2:Multi_Int_X2); overload;				{$ifdef inline_functions_level_1} inline; {$endif}
begin
hex_to_Multi_Int_X2(v1,v2);
end;


(******************************************)
function Multi_Int_X2.FromHex(const v1:ansistring):Multi_Int_X2;				{$ifdef inline_functions_level_1} inline; {$endif}
begin
hex_to_Multi_Int_X2(v1,Result);
end;


(********************v2********************)
procedure Multi_Int_X2_to_ansistring(const v1:Multi_Int_X2; out v2:ansistring); 
var
	s,ts	:ansistring;
	M_Val	:array[0..Multi_X3_maxi] of MULTI_INT_2W_U;
	wf,wl	:MULTI_INT_2W_S;
begin
if	(Not v1.Defined_flag)
then
	begin
	v2:='UNDEFINED';
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;
if	(v1.Overflow_flag)
then
	begin
	v2:='OVERFLOW';
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Overflow');
		end;
	exit;
	end;

{$ifdef 64bit}
wf:= 1000000000; wl:= 9;
{$endif}
{$ifdef 32bit}
wf:= 10000; wl:= 4;
{$endif}

s:= '';

M_Val[0]:= v1.M_Value[0];
M_Val[1]:= v1.M_Value[1];
M_Val[2]:= v1.M_Value[2];
M_Val[3]:= v1.M_Value[3];

repeat

	M_Val[2]:= M_Val[2] + (MULTI_INT_1W_U_MAXINT_1 * (M_Val[3] MOD wf));
	M_Val[3]:= (M_Val[3] DIV wf);

	M_Val[1]:= M_Val[1] + (MULTI_INT_1W_U_MAXINT_1 * (M_Val[2] MOD wf));
	M_Val[2]:= (M_Val[2] DIV wf);

	M_Val[0]:= M_Val[0] + (MULTI_INT_1W_U_MAXINT_1 * (M_Val[1] MOD wf));
	M_Val[1]:= (M_Val[1] DIV wf);

	ts:= inttostr(M_Val[0] MOD wf);
	ts:= AddChar('0',ts,wl);
	s:= ts + s;
	M_Val[0]:= (M_Val[0] DIV wf);

until	(0=0)
and		(M_Val[0] = 0)
and		(M_Val[1] = 0)
and		(M_Val[2] = 0)
and		(M_Val[3] = 0)
;

s:= TrimLeftSet(s, ['0']);
if (s = '') then s:= '0';

if	(v1.Negative_flag = Multi_UBool_TRUE) then s:='-' + s;

v2:=s;
end;


(******************************************)
function Multi_Int_X2.ToStr:ansistring;								{$ifdef inline_functions_level_1} inline; {$endif}
begin
Multi_Int_X2_to_ansistring(self, Result);
end;


(******************************************)
class operator Multi_Int_X2.:=(const v1:Multi_Int_X2):ansistring;				{$ifdef inline_functions_level_1} inline; {$endif}
begin
Multi_Int_X2_to_ansistring(v1, Result);
end;


(******************************************)
class operator Multi_Int_X2.xor(const v1,v2:Multi_Int_X2):Multi_Int_X2;
begin
if	(Not v1.Defined_flag)
or	(Not v2.Defined_flag)
then
	begin
	Result:=0;
	Result.Defined_flag:= FALSE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;
if	(v1.Overflow_flag or v2.Overflow_flag)
then
	begin
	Result:= 0;
	Result.Overflow_flag:=TRUE;
	Result.Defined_flag:=FALSE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EIntOverflow.create('Overflow');
		end;
	exit;
	end;

Result.M_Value[0]:= (v1.M_Value[0] xor v2.M_Value[0]);
Result.M_Value[1]:= (v1.M_Value[1] xor v2.M_Value[1]);
Result.M_Value[2]:= (v1.M_Value[2] xor v2.M_Value[2]);
Result.M_Value[3]:= (v1.M_Value[3] xor v2.M_Value[3]);
Result.Defined_flag:=TRUE;
Result.Overflow_flag:= FALSE;

Result.Negative_flag:= Multi_UBool_FALSE;
if	(v1.Negative <> v2.Negative)
then Result.Negative_flag:= Multi_UBool_TRUE;
end;


(******************************************)
class operator Multi_Int_X2.or(const v1,v2:Multi_Int_X2):Multi_Int_X2;
begin
if	(Not v1.Defined_flag)
or	(Not v2.Defined_flag)
then
	begin
	Result:=0;
	Result.Defined_flag:= FALSE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

Result.M_Value[0]:= (v1.M_Value[0] or v2.M_Value[0]);
Result.M_Value[1]:= (v1.M_Value[1] or v2.M_Value[1]);
Result.M_Value[2]:= (v1.M_Value[2] or v2.M_Value[2]);
Result.M_Value[3]:= (v1.M_Value[3] or v2.M_Value[3]);
Result.Defined_flag:=TRUE;
Result.Overflow_flag := FALSE;

Result.Negative_flag:= Multi_UBool_FALSE;
if v1.Negative and v2.Negative
then Result.Negative_flag:= Multi_UBool_TRUE;
end;


(******************************************)
class operator Multi_Int_X2.and(const v1,v2:Multi_Int_X2):Multi_Int_X2;
begin
if	(Not v1.Defined_flag)
or	(Not v2.Defined_flag)
then
	begin
	Result:=0;
	Result.Defined_flag:= FALSE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

Result.M_Value[0]:= (v1.M_Value[0] and v2.M_Value[0]);
Result.M_Value[1]:= (v1.M_Value[1] and v2.M_Value[1]);
Result.M_Value[2]:= (v1.M_Value[2] and v2.M_Value[2]);
Result.M_Value[3]:= (v1.M_Value[3] and v2.M_Value[3]);
Result.Defined_flag:=TRUE;
Result.Overflow_flag := FALSE;

Result.Negative_flag:= Multi_UBool_FALSE;
if v1.Negative and v2.Negative
then Result.Negative_flag:= Multi_UBool_TRUE;
end;


(******************************************)
class operator Multi_Int_X2.not(const v1:Multi_Int_X2):Multi_Int_X2;
begin
if	(Not v1.Defined_flag)
then
	begin
	Result:=0;
	Result.Defined_flag:= FALSE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

Result.M_Value[0]:= (not v1.M_Value[0]);
Result.M_Value[1]:= (not v1.M_Value[1]);
Result.M_Value[2]:= (not v1.M_Value[2]);
Result.M_Value[3]:= (not v1.M_Value[3]);
Result.Defined_flag:=TRUE;
Result.Overflow_flag := FALSE;

Result.Negative_flag:=  Multi_UBool_TRUE;
if v1.Negative
then Result.Negative_flag:= Multi_UBool_FALSE;
end;


(********************v2********************)
procedure add_Multi_Int_X2(const v1,v2:Multi_Int_X2; var Result:Multi_Int_X2);
var
	TV,CV	:MULTI_INT_2W_S;
	all_zero:boolean;
begin
Result.Overflow_flag:=FALSE;
Result.Defined_flag:=TRUE;
Result.Negative_flag:=Multi_UBool_UNDEF;

all_zero:= TRUE;
CV:= 0;

TV:=(MULTI_INT_2W_U(v1.M_Value[0]) + MULTI_INT_2W_U(v2.M_Value[0]));
if (TV <> 0) then all_zero:= FALSE;
if	(TV > MULTI_INT_1W_U_MAXINT) then
	begin
	Result.M_Value[0]:= (TV - MULTI_INT_1W_U_MAXINT_1);
	CV:= 1;
	end
else
	begin
	Result.M_Value[0]:= TV;
	CV:= 0;
	end;

TV:=(MULTI_INT_2W_U(v1.M_Value[1]) + MULTI_INT_2W_U(v2.M_Value[1]) + CV);
if (TV <> 0) then all_zero:= FALSE;
if	(TV > MULTI_INT_1W_U_MAXINT) then
	begin
	Result.M_Value[1]:= (TV - MULTI_INT_1W_U_MAXINT_1);
	CV:= 1;
	end
else
	begin
	Result.M_Value[1]:= TV;
	CV:= 0;
	end;

TV:=(MULTI_INT_2W_U(v1.M_Value[2]) + MULTI_INT_2W_U(v2.M_Value[2]) + CV);
if (TV <> 0) then all_zero:= FALSE;
if	(TV > MULTI_INT_1W_U_MAXINT) then
	begin
	Result.M_Value[2]:= (TV - MULTI_INT_1W_U_MAXINT_1);
	CV:= 1;
	end
else
	begin
	Result.M_Value[2]:= TV;
	CV:= 0;
	end;

TV:=(MULTI_INT_2W_U(v1.M_Value[3]) + MULTI_INT_2W_U(v2.M_Value[3]) + CV);
if (TV <> 0) then all_zero:= FALSE;
if	(TV > MULTI_INT_1W_U_MAXINT) then
	begin
	Result.Defined_flag:= FALSE;
	Result.Overflow_flag:=TRUE;
	end
else
	Result.M_Value[3]:= TV;

if all_zero then Result.Negative_flag:=Multi_UBool_FALSE;

end;


(********************v2********************)
procedure subtract_Multi_Int_X2(const v1,v2:Multi_Int_X2; var Result:Multi_Int_X2);
var
	TV,CV	:MULTI_INT_2W_S;
	all_zero:boolean;
begin
Result.Overflow_flag:=FALSE;
Result.Defined_flag:=TRUE;
Result.Negative_flag:=Multi_UBool_UNDEF;

all_zero:= TRUE;
CV:= 0;

TV:=(v1.M_Value[0] - v2.M_Value[0]);
if (TV <> 0) then all_zero:= FALSE;
if	TV < 0 then
	begin
	Result.M_Value[0]:= (TV + MULTI_INT_1W_U_MAXINT_1);
	CV:= -1;
	end
else
	begin
	Result.M_Value[0]:= TV;
	CV:= 0;
	end;

TV:=(v1.M_Value[1] - v2.M_Value[1] + CV);
if (TV <> 0) then all_zero:= FALSE;
if	TV < 0 then
	begin
	Result.M_Value[1]:= (TV + MULTI_INT_1W_U_MAXINT_1);
	CV:= -1;
	end
else
	begin
	Result.M_Value[1]:= TV;
	CV:= 0;
	end;

TV:=(v1.M_Value[2] - v2.M_Value[2] + CV);
if (TV <> 0) then all_zero:= FALSE;
if	TV < 0 then
	begin
	Result.M_Value[2]:= (TV + MULTI_INT_1W_U_MAXINT_1);
	CV:= -1;
	end
else
	begin
	Result.M_Value[2]:= TV;
	CV:= 0;
	end;

TV:=(v1.M_Value[3] - v2.M_Value[3] + CV);
if (TV <> 0) then all_zero:= FALSE;
if	TV < 0 then
	begin
	Result.Defined_flag:= FALSE;
	Result.Overflow_flag:=TRUE;
	end
else
	Result.M_Value[3]:= TV;

if all_zero then Result.Negative_flag:=Multi_UBool_FALSE;

end;


(*******************v6*********************)
procedure multiply_Multi_Int_X2(const v1,v2:Multi_Int_X2; var Result:Multi_Int_X2); overload;
var
// zf		:boolean;
tv		:MULTI_INT_2W_U;
i,j,h	:MULTI_INT_2W_S;

begin
if	(Not v1.Defined_flag)
or	(Not v2.Defined_flag)
then
	begin
	Result.Defined_flag:= FALSE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;
if	(v1.Overflow_flag or v2.Overflow_flag)
then
	begin
	Result.Overflow_flag:=TRUE;
	Result.Defined_flag:=TRUE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EIntOverflow.create('Overflow');
		end;
	exit;
	end;

Result:= 0;
Result.Overflow_flag:=FALSE;
Result.Defined_flag:=TRUE;
Result.Negative_flag:=Multi_UBool_UNDEF;

i:=0; repeat Result.M_Value[i]:= 0; INC(i); until (i > Multi_X2_maxi);

Result.Overflow_flag:= FALSE;
Result.Defined_flag:= TRUE;
Result.Negative_flag:= Multi_UBool_UNDEF;

// main loopy
h:= 0;
i:= 0;
j:= 0;
repeat
	if (v2.M_Value[j] <> 0) then
    	begin
		repeat
			if	(v1.M_Value[i] <> 0)
			then
				begin
				h:= (i+j);
				if (h > Multi_X2_maxi) then
					begin
					Result.Overflow_flag:=TRUE;
					exit;
					end;
                tv:= MULTI_INT_2W_U(Result.M_Value[h]) + (MULTI_INT_2W_U(v1.M_Value[i]) * MULTI_INT_2W_U(v2.M_Value[j]));
				Result.M_Value[h]:= (tv MOD MULTI_INT_1W_U_MAXINT_1);
                tv:= (tv DIV MULTI_INT_1W_U_MAXINT_1);
				while (tv > 0) do
					begin
					Inc(h);
					if (h > Multi_X2_maxi) then
						begin
						Result.Overflow_flag:=TRUE;
						exit;
						end;
	                tv:= (tv + Result.M_Value[h]);
					Result.M_Value[h]:= (tv MOD MULTI_INT_1W_U_MAXINT_1);
					tv:= (tv DIV MULTI_INT_1W_U_MAXINT_1);
					end;
				end;
			INC(i);
		until (i > Multi_X2_maxi);
		i:=0;
        end;
	INC(j);
until (j > Multi_X2_maxi);

if	(v1.Negative_flag = v2.Negative_flag)
then Result.Negative_flag:= Multi_UBool_FALSE
else Result.Negative_flag:=Multi_UBool_TRUE;

end;


(*******************v2*********************)
procedure ansistring_to_Multi_Int_X2(const v1:ansistring; var mi:Multi_Int_X2);
var
	b,bi,bs,e,n,
	L,p,w,wf		:MULTI_INT_1W_S;
	v				:MULTI_INT_2W_U;
	dec_substr		:ansistring;
	Signeg,
	All_Zero,
	first_time		:boolean;
	tm				:Multi_Int_X2;

begin
mi.Overflow_flag:=FALSE;
mi.Defined_flag:= TRUE;
mi.Negative_flag:= FALSE;
mi:= 0;

if	(length(v1) = 0) then exit;

Signeg:= FALSE;

{$ifdef 64bit}
w:= 9; wf:= 1000000000;
{$endif}
{$ifdef 32bit}
w:= 4; wf:= 10000;
{$endif}

bi:= low(ansistring);
b:= 0;
if	(v1[bi] = '-') then
	begin
	Signeg:= TRUE;
	INC(b);
	end;
bs:= (bi + b);

L:= (length(v1) - b);
e:= (length(v1) + bi - 1);

All_Zero:= TRUE;
first_time:= TRUE;
L:= w;
p:= bs;
repeat
	if	((p + w) > e) then
	    L:= (e - p + 1);
	if	(L > 0) then
		begin
		dec_substr:= AnsiMidStr(v1,p,L);
		try
			v:= StrToInt64(dec_substr);
			except
				Multi_Int_ERROR:= TRUE;
				mi.Defined_flag:= FALSE;
				if Multi_Int_RAISE_EXCEPTIONS_ENABLED then Raise;
				exit;
			end;
		if first_time then
			begin
			first_time:= FALSE;
			add_Multi_Int_X2(mi,v,tm);
			if (tm.Overflow_flag = TRUE) then
				begin
				mi.Defined_flag:= FALSE;
				Multi_Int_ERROR:= TRUE;
				if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
					Raise EIntOverflow.create('Overflow');
				end;
			mi:= tm;
			end
		else
			begin
			if (L < w) then
				begin
				wf:= 1;
				for n:=1 to L do
					wf:= (wf * 10);
				end;
            multiply_Multi_Int_X2(mi,wf,tm);
			if (tm.Overflow_flag = TRUE) then
				begin
				Multi_Int_ERROR:= TRUE;
				if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
					Raise EIntOverflow.create('Overflow');
				end;

			add_Multi_Int_X2(tm,v,mi);
			if (mi.Overflow_flag = TRUE) then
				begin
				Multi_Int_ERROR:= TRUE;
				if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
					Raise EIntOverflow.create('Overflow');
				end;

			end;
		if Multi_Int_ERROR then exit;
		if v <> 0 then All_Zero:= FALSE;
		p:= (p + w);
		end;
until L < w;

mi.Defined_flag:= TRUE;
if All_Zero then mi.Negative_flag:= Multi_UBool_FALSE
else if Signeg then mi.Negative_flag:= Multi_UBool_TRUE
else mi.Negative_flag:= Multi_UBool_FALSE;

end;


(******************************************)
class operator Multi_Int_X2.:=(const v1:ansistring):Multi_Int_X2;				{$ifdef inline_functions_level_1} inline; {$endif}
begin
ansistring_to_Multi_Int_X2(v1,Result);
end;


(******************************************)
// WARNING Float to Multi_Int type conversion loses some precision
class operator Multi_Int_X2.:=(const v1:Single):Multi_Int_X2;
var
R			:Multi_Int_X2;
R_FLOATREC	:TFloatRec;
begin
Multi_Int_ERROR:= FALSE;

FloatToDecimal(R_FLOATREC, v1, MULTI_SINGLE_TYPE_PRECISION_DIGITS, 0);
ansistring_to_Multi_Int_X2(AddCharR('0',AnsiLeftStr(R_FLOATREC.digits,(MULTI_SINGLE_TYPE_PRECISION_DIGITS-1)),R_FLOATREC.Exponent), R);

if (R.Overflow) then
	begin
	Multi_Int_ERROR:= TRUE;
	Result.Defined_flag:= FALSE;
	Result.Negative_flag:= Multi_UBool_UNDEF;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EIntOverflow.create('Overflow');
		end;
	exit;
	end;

if (R_FLOATREC.Negative) then R.Negative_flag := TRUE;
Result:= R;
end;


(******************************************)
// WARNING Float to Multi_Int type conversion loses some precision
class operator Multi_Int_X2.:=(const v1:Real):Multi_Int_X2;
var
R			:Multi_Int_X2;
R_FLOATREC	:TFloatRec;
begin
Multi_Int_ERROR:= FALSE;

FloatToDecimal(R_FLOATREC, v1, MULTI_REAL_TYPE_PRECISION_DIGITS, 0);
ansistring_to_Multi_Int_X2(AddCharR('0',AnsiLeftStr(R_FLOATREC.digits,(MULTI_REAL_TYPE_PRECISION_DIGITS-1)),R_FLOATREC.Exponent), R);

if (R.Overflow) then
	begin
	Multi_Int_ERROR:= TRUE;
	Result.Defined_flag:= FALSE;
	Result.Negative_flag:= Multi_UBool_UNDEF;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EIntOverflow.create('Overflow');
		end;
	exit;
	end;

if (R_FLOATREC.Negative) then R.Negative_flag := TRUE;
Result:= R;
end;


(******************************************)
// WARNING Float to Multi_Int type conversion loses some precision
class operator Multi_Int_X2.:=(const v1:Double):Multi_Int_X2;
var
R			:Multi_Int_X2;
R_FLOATREC	:TFloatRec;

begin
Multi_Int_ERROR:= FALSE;

FloatToDecimal(R_FLOATREC, v1, MULTI_DOUBLE_TYPE_PRECISION_DIGITS, 0);
ansistring_to_Multi_Int_X2(AddCharR('0',AnsiLeftStr(R_FLOATREC.digits,(MULTI_DOUBLE_TYPE_PRECISION_DIGITS-1)),R_FLOATREC.Exponent), R);

if (R.Overflow) then
	begin
	Multi_Int_ERROR:= TRUE;
	Result.Defined_flag:= FALSE;
	Result.Negative_flag:= Multi_UBool_UNDEF;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EIntOverflow.create('Overflow');
		end;
	exit;
	end;

if (R_FLOATREC.Negative) then R.Negative_flag := TRUE;
Result:= R;
end;


(******************************************)
class operator Multi_Int_X2.inc(const v1:Multi_Int_X2):Multi_Int_X2;
Var	Neg	:Multi_UBool_Values;
	v2	:Multi_Int_X2;
begin
if	(Not v1.Defined_flag)
then
	begin
	Result:=0;
	Result.Defined_flag:= v1.Defined_flag;
	Result.Overflow_flag:= v1.Overflow_flag;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

if	(v1.Overflow_flag)
then
	begin
	Result:= 0;
	Multi_Int_ERROR:= TRUE;
	Result.Defined_flag:= v1.Defined_flag;
	Result.Overflow_flag:= v1.Overflow_flag;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EIntOverflow.create('Overflow');
		end;
	exit;
	end;

Neg:=Multi_UBool_UNDEF;
v2:= 1;

if	(v1.Negative_flag = FALSE)
then
	begin
	add_Multi_Int_X2(v1,v2,Result);
	Neg:= v1.Negative_flag;
	end
else
	begin
	if	ABS_greaterthan_Multi_Int_X2(v1,v2)
	then
		begin
		subtract_Multi_Int_X2(v1,v2,Result);
		Neg:= Multi_UBool_TRUE;
		end
	else
		begin
		subtract_Multi_Int_X2(v2,v1,Result);
		Neg:= Multi_UBool_FALSE;
		end;
	end;

if (Result.Overflow_flag = TRUE) then
	begin
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		Raise EIntOverflow.create('Overflow');
	end;

if	(Result.Negative_flag = Multi_UBool_UNDEF) then Result.Negative_flag:= Neg;
end;


(******************************************)
class operator Multi_Int_X2.+(const v1,v2:Multi_Int_X2):Multi_Int_X2;
Var	Neg:T_Multi_UBool;
begin
if	(Not v1.Defined_flag)
or	(Not v2.Defined_flag)
then
	begin
	Result:=0;
	Result.Defined_flag:= FALSE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

if	(v1.Overflow_flag or v2.Overflow_flag)
then
	begin
	Multi_Int_ERROR:= TRUE;
	Result:= 0;
	Result.Overflow_flag:=TRUE;
	Result.Defined_flag:=TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EIntOverflow.create('Overflow');
		end;
	exit;
	end;

Neg:=Multi_UBool_UNDEF;

if	(v1.Negative_flag = v2.Negative_flag)
then
	begin
	add_Multi_Int_X2(v1,v2,Result);
	Neg:= v1.Negative_flag;
	end
else
	if	((v1.Negative_flag = FALSE) and (v2.Negative_flag = TRUE))
	then
		begin
		if	ABS_greaterthan_Multi_Int_X2(v2,v1)
		then
			begin
			subtract_Multi_Int_X2(v2,v1,Result);
			Neg:= Multi_UBool_TRUE;
			end
		else
			begin
			subtract_Multi_Int_X2(v1,v2,Result);
			Neg:= Multi_UBool_FALSE;
			end;
		end
	else
		begin
		if	ABS_greaterthan_Multi_Int_X2(v1,v2)
		then
			begin
			subtract_Multi_Int_X2(v1,v2,Result);
			Neg:= Multi_UBool_TRUE;
			end
		else
			begin
			subtract_Multi_Int_X2(v2,v1,Result);
			Neg:= Multi_UBool_FALSE;
			end;
		end;

if (Result.Overflow_flag = TRUE) then
	begin
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		Raise EIntOverflow.create('Overflow');
	end;

if	(Result.Negative_flag = Multi_UBool_UNDEF) then Result.Negative_flag:= Neg;
end;


(******************************************)
class operator Multi_Int_X2.dec(const v1:Multi_Int_X2):Multi_Int_X2;
Var	Neg	:Multi_UBool_Values;
	v2	:Multi_Int_X2;
begin
if	(Not v1.Defined_flag)
then
	begin
	Result:=0;
	Result.Defined_flag:= v1.Defined_flag;
	Result.Overflow_flag:= v1.Overflow_flag;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

if	(v1.Overflow_flag)
then
	begin
	Multi_Int_ERROR:= TRUE;
	Result:= 0;
	Result.Defined_flag:= v1.Defined_flag;
	Result.Overflow_flag:= v1.Overflow_flag;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EIntOverflow.create('Overflow');
		end;
	exit;
	end;

Neg:=Multi_UBool_UNDEF;
v2:= 1;

if	(v1.Negative_flag = FALSE) then
	begin
	if	ABS_greaterthan_Multi_Int_X2(v2,v1)
	then
		begin
		subtract_Multi_Int_X2(v2,v1,Result);
		Neg:=Multi_UBool_TRUE;
		end
	else
		begin
		subtract_Multi_Int_X2(v1,v2,Result);
		Neg:=Multi_UBool_FALSE;
		end
	end
else (* v1 is Negative_flag *)
	begin
	add_Multi_Int_X2(v1,v2,Result);
	Neg:=Multi_UBool_TRUE;
	end;

if (Result.Overflow_flag = TRUE) then
	begin
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		Raise EIntOverflow.create('Overflow');
	end;

if	(Result.Negative_flag = Multi_UBool_UNDEF) then Result.Negative_flag:= Neg;
end;


(******************************************)
class operator Multi_Int_X2.-(const v1,v2:Multi_Int_X2):Multi_Int_X2;
Var	Neg:Multi_UBool_Values;
begin
if	(Not v1.Defined_flag)
or	(Not v2.Defined_flag)
then
	begin
	Result:=0;
	Result.Defined_flag:= FALSE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

if	(v1.Overflow_flag or v2.Overflow_flag)
then
	begin
	Multi_Int_ERROR:= TRUE;
	Result:= 0;
	Result.Overflow_flag:=TRUE;
	Result.Defined_flag:=TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EIntOverflow.create('Overflow');
		end;
	exit;
	end;

Neg:=Multi_UBool_UNDEF;

if	(v1.Negative_flag = v2.Negative_flag)
then
	begin
	if	(v1.Negative_flag = TRUE) then
		begin
		if	ABS_greaterthan_Multi_Int_X2(v1,v2)
		then
			begin
			subtract_Multi_Int_X2(v1,v2,Result);
			Neg:=Multi_UBool_TRUE;
			end
		else
			begin
			subtract_Multi_Int_X2(v2,v1,Result);
			Neg:=Multi_UBool_FALSE;
			end
		end
	else	(* if	not Negative_flag then	*)
		begin
		if	ABS_greaterthan_Multi_Int_X2(v2,v1)
		then
			begin
			subtract_Multi_Int_X2(v2,v1,Result);
			Neg:=Multi_UBool_TRUE;
			end
		else
			begin
			subtract_Multi_Int_X2(v1,v2,Result);
			Neg:=Multi_UBool_FALSE;
			end
		end
	end
else (* v1.Negative_flag <> v2.Negative_flag *)
	begin
	if	(v2.Negative_flag = TRUE) then
		begin
		add_Multi_Int_X2(v1,v2,Result);
		Neg:=Multi_UBool_FALSE;
		end
	else
		begin
		add_Multi_Int_X2(v1,v2,Result);
		Neg:=Multi_UBool_TRUE;
		end
	end;

if (Result.Overflow_flag = TRUE) then
	begin
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		Raise EIntOverflow.create('Overflow');
	end;

if	(Result.Negative_flag = Multi_UBool_UNDEF) then Result.Negative_flag:= Neg;
end;


(******************************************)
class operator Multi_Int_X2.-(const v1:Multi_Int_X2):Multi_Int_X2; 				{$ifdef inline_functions_level_1} inline; {$endif}
begin
Result:= v1;
if	(v1.Negative_flag = Multi_UBool_TRUE) then Result.Negative_flag:= Multi_UBool_FALSE;
if	(v1.Negative_flag = Multi_UBool_FALSE) then Result.Negative_flag:= Multi_UBool_TRUE;
end;


(******************************************)
class operator Multi_Int_X2.*(const v1,v2:Multi_Int_X2):Multi_Int_X2;
var	  R:Multi_Int_X2;
begin
if	(Not v1.Defined_flag)
or	(Not v2.Defined_flag)
then
	begin
	Result:=0;
	Result.Defined_flag:= FALSE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

if	(v1.Overflow_flag or v2.Overflow_flag)
then
	begin
	Result:= 0;
	Result.Overflow_flag:=TRUE;
	Result.Defined_flag:=TRUE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EIntOverflow.create('Overflow');
		end;
	exit;
	end;

multiply_Multi_Int_X2(v1,v2,R);

if	(R.Negative_flag = Multi_UBool_UNDEF) then
	if	(v1.Negative_flag = v2.Negative_flag)
	then R.Negative_flag:= Multi_UBool_FALSE
	else R.Negative_flag:=Multi_UBool_TRUE;

Result:= R;

if	R.Overflow_flag then
	begin
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EIntOverflow.create('Overflow');
		end;
	end;
end;


(********************v3********************)
{ Function exp_by_squaring_iterative(TV, P) }

class operator Multi_Int_X2.**(const v1:Multi_Int_X2; const P:MULTI_INT_2W_S):Multi_Int_X2;
var
Y,TV,T,R	:Multi_Int_X2;
PT			:MULTI_INT_2W_S;
begin
PT:= P;
TV:= v1;
if	(PT < 0) then R:= 0
else if	(PT = 0) then R:= 1
else
	begin
	Y := 1;
	while (PT > 1) do
		begin
		if	odd(PT) then
			begin
			multiply_Multi_Int_X2(TV,Y, T);
			if	(T.Overflow_flag)
			then
				begin
				Multi_Int_ERROR:= TRUE;
				Result:= 0;
				Result.Defined_flag:= FALSE;
				Result.Overflow_flag:= TRUE;
				if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
					begin
					Raise EIntOverflow.create('Overflow');
					end;
				exit;
				end;
			if	(T.Negative_flag = Multi_UBool_UNDEF) then
				if	(TV.Negative_flag = Y.Negative_flag)
				then T.Negative_flag:= Multi_UBool_FALSE
				else T.Negative_flag:= Multi_UBool_TRUE;

			Y:= T;
			PT := PT - 1;
			end;
		multiply_Multi_Int_X2(TV,TV, T);
		if	(T.Overflow_flag)
		then
			begin
			Multi_Int_ERROR:= TRUE;
			Result:= 0;
			Result.Defined_flag:= FALSE;
			Result.Overflow_flag:= TRUE;
			if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
				begin
				Raise EIntOverflow.create('Overflow');
				end;
			exit;
			end;
		T.Negative_flag:= Multi_UBool_FALSE;

		TV:= T;
		PT := (PT div 2);
		end;
	multiply_Multi_Int_X2(TV,Y, R);
	if	(R.Overflow_flag)
	then
		begin
		Multi_Int_ERROR:= TRUE;
		Result:= 0;
		Result.Defined_flag:= FALSE;
		Result.Overflow_flag:= TRUE;
		if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
			begin
			Raise EIntOverflow.create('Overflow');
			end;
		exit;
		end;
	if	(R.Negative_flag = Multi_UBool_UNDEF) then
		if	(TV.Negative_flag = Y.Negative_flag)
		then R.Negative_flag:= Multi_UBool_FALSE
		else R.Negative_flag:= Multi_UBool_TRUE;
	end;

Result:= R;
end;


(********************v1********************)
procedure intdivide_taylor_warruth_X2(const P_dividend,P_dividor:Multi_Int_X2;out P_quotient,P_remainder:Multi_Int_X2);
label	AGAIN,FINISH;
var
dividor,
quotient,
dividend,
next_dividend	:Multi_Int_X5;

dividend_i,
dividend_i_1,
quotient_i,
dividor_i,
dividor_i_1,
dividor_non_zero_pos,
shiftup_bits_dividor,
i
				:MULTI_INT_1W_S;

adjacent_word_dividend,
adjacent_word_division,
word_division,
word_dividend,
word_carry,
adjacent_word_carry
				:MULTI_INT_2W_U;

finished		:boolean;

begin
dividend:= 0;
next_dividend:= 0;
dividor:= 0;
quotient:= 0;
P_quotient:= 0;
P_remainder:= 0;

if	(P_dividor = 0) then
	begin
	P_quotient.Defined_flag:= FALSE;
	P_quotient.Overflow_flag:= TRUE;
	P_remainder.Defined_flag:= FALSE;
	P_remainder.Overflow_flag:= TRUE;
	Multi_Int_ERROR:= TRUE;
    end
else if	(P_dividor = P_dividend) then
	begin
	P_quotient:= 1;
    end
else
	begin
	if	(Abs(P_dividor) > Abs(P_dividend)) then
		begin
	 	P_remainder:= P_dividend;
		goto FINISH;
	    end;

	dividor_non_zero_pos:= 0;
    i:= Multi_X2_maxi;
	while (i >= 0) do
		begin
		dividor.M_Value[i]:= P_dividor.M_Value[i];
		if	(dividor_non_zero_pos = 0) then
			if	(dividor.M_Value[i] <> 0) then
				dividor_non_zero_pos:= i;
		Dec(i);
		end;
	dividor.Negative_flag:= FALSE;

	// essential short-cut for single word dividor
	// the later code will fail if this case is not dealt with here

	if	(dividor_non_zero_pos = 0) then
		begin
		word_carry:= 0;
		i:= Multi_X2_maxi;
		while (i >= 0) do
			begin
			P_quotient.M_Value[i]:= (((word_carry * MULTI_INT_2W_U(MULTI_INT_1W_U_MAXINT_1)) + MULTI_INT_2W_U(P_dividend.M_Value[i])) div MULTI_INT_2W_U(P_dividor.M_Value[0]));
			word_carry:= (((word_carry * MULTI_INT_2W_U(MULTI_INT_1W_U_MAXINT_1)) + MULTI_INT_2W_U(P_dividend.M_Value[i])) - (MULTI_INT_2W_U(P_quotient.M_Value[i]) * MULTI_INT_2W_U(P_dividor.M_Value[0])));
			Dec(i);
			end;
		P_remainder.M_Value[0]:= word_carry;
		goto FINISH;
		end;

    dividend:= P_dividend;
	dividend.Negative_flag:= FALSE;

	shiftup_bits_dividor:= nlz_bits(dividor.M_Value[dividor_non_zero_pos]);
	if	(shiftup_bits_dividor > 0) then
		begin
		ShiftUp_NBits_Multi_Int_X5(dividend, shiftup_bits_dividor);
		ShiftUp_NBits_Multi_Int_X5(dividor, shiftup_bits_dividor);
		end;

	adjacent_word_carry:= 0;
	word_carry:= 0;
	dividor_i:= dividor_non_zero_pos;
	dividor_i_1:= (dividor_i - 1);
	dividend_i:= (Multi_X2_maxi + 1);
	finished:= FALSE;
	while (not finished) do
	    if (dividend_i >= 0) then
		    if (dividend.M_Value[dividend_i] = 0) then
				Dec(dividend_i)
			else finished:= TRUE
		else finished:= TRUE
		;
	quotient_i:= (dividend_i - dividor_non_zero_pos);

	while	(dividend >= 0)
	and		(quotient_i >= 0)
	do
		begin
		word_dividend:= ((word_carry * MULTI_INT_2W_U(MULTI_INT_1W_U_MAXINT_1)) + dividend.M_Value[dividend_i]);
        word_division:= (word_dividend div dividor.M_Value[dividor_i]);
        adjacent_word_carry:= (word_dividend mod dividor.M_Value[dividor_i]);

		if	(word_division > 0) then
			begin
			dividend_i_1:= (dividend_i - 1);
			if	(dividend_i_1 >= 0) then
				begin
				AGAIN:
				adjacent_word_dividend:= ((adjacent_word_carry * MULTI_INT_2W_U(MULTI_INT_1W_U_MAXINT_1)) + dividend.M_Value[dividend_i_1]);
                adjacent_word_division:= (dividor.M_Value[dividor_i_1] * word_division);
				if	(adjacent_word_division > adjacent_word_dividend)
				or	(word_division >= MULTI_INT_1W_U_MAXINT_1)
				then
					begin
					Dec(word_division);
					adjacent_word_carry:= adjacent_word_carry + dividor.M_Value[dividor_i];
					if (adjacent_word_carry < MULTI_INT_1W_U_MAXINT_1) then
						goto AGAIN;
					end;
				end;
			quotient:= 0;
			quotient.M_Value[quotient_i]:= word_division;
            next_dividend:= (dividend - (dividor * quotient));
			if Multi_Int_ERROR then
				begin
				P_quotient.Defined_flag:= FALSE;
				P_quotient.Overflow_flag:= TRUE;
				P_remainder.Defined_flag:= FALSE;
				P_remainder.Overflow_flag:= TRUE;
				exit;
				end;
			if (next_dividend.Negative) then
				begin
				Dec(word_division);
				quotient.M_Value[quotient_i]:= word_division;
	            next_dividend:= (dividend - (dividor * quotient));
				if Multi_Int_ERROR then
					begin
					P_quotient.Defined_flag:= FALSE;
					P_quotient.Overflow_flag:= TRUE;
					P_remainder.Defined_flag:= FALSE;
					P_remainder.Overflow_flag:= TRUE;
					exit;
					end;
				end;
			P_quotient.M_Value[quotient_i]:= word_division;
            dividend:= next_dividend;
            word_carry:= dividend.M_Value[dividend_i];
			end
		else
			begin
            word_carry:= word_dividend;
			end;

		Dec(dividend_i);
		quotient_i:= (dividend_i - dividor_non_zero_pos);
		end; { while }

	ShiftDown_MultiBits_Multi_Int_X5(dividend, shiftup_bits_dividor);
	P_remainder:= To_Multi_Int_X2(dividend);

FINISH:
	if	(P_dividend.Negative_flag = TRUE) and (P_remainder > 0)
	then
		P_remainder.Negative_flag:= TRUE;

	if	(P_dividend.Negative_flag <> P_dividor.Negative_flag)
	and	(P_quotient > 0)
	then
		P_quotient.Negative_flag:= TRUE;

	end;
end;


(******************************************)
class operator Multi_Int_X2.div(const v1,v2:Multi_Int_X2):Multi_Int_X2;
var
Remainder,
Quotient	:Multi_Int_X2;
begin
if	(Not v1.Defined_flag)
or	(Not v2.Defined_flag)
then
	begin
	Result:=0;
	Result.Defined_flag:= FALSE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

if	(v1.Overflow_flag or v2.Overflow_flag)
then
	begin
	Multi_Int_ERROR:= TRUE;
	Result:= 0;
	Result.Overflow_flag:=TRUE;
	Result.Defined_flag:=TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EIntOverflow.create('Overflow');
		end;
	exit;
	end;

// same values as last time

if	(X2_Last_Divisor = v2)
and	(X2_Last_Dividend = v1)
then
	Result:= X2_Last_Quotient
else	// different values than last time
	begin
	intdivide_taylor_warruth_X2(v1,v2,Quotient,Remainder);

	X2_Last_Divisor:= v2;
	X2_Last_Dividend:= v1;
	X2_Last_Quotient:= Quotient;
	X2_Last_Remainder:= Remainder;

	Result:= Quotient;
	end;

if	(X2_Last_Remainder.Overflow_flag)
or	(X2_Last_Quotient.Overflow_flag)
then
	begin
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EIntOverflow.create('Overflow');
		end;
	end;
end;


(******************************************)
class operator Multi_Int_X2.mod(const v1,v2:Multi_Int_X2):Multi_Int_X2;
var
Remainder,
Quotient	:Multi_Int_X2;
begin
if	(Not v1.Defined_flag)
or	(Not v2.Defined_flag)
then
	begin
	Result:=0;
	Result.Defined_flag:= FALSE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

if	(v1.Overflow_flag or v2.Overflow_flag)
then
	begin
	Multi_Int_ERROR:= TRUE;
	Result:= 0;
	Result.Overflow_flag:=TRUE;
	Result.Defined_flag:=TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EIntOverflow.create('Overflow');
		end;
	exit;
	end;

// same values as last time

if	(X2_Last_Divisor = v2)
and	(X2_Last_Dividend = v1)
then
	Result:= X2_Last_Remainder
else	// different values than last time
	begin
	intdivide_taylor_warruth_X2(v1,v2,Quotient,Remainder);

	X2_Last_Divisor:= v2;
	X2_Last_Dividend:= v1;
	X2_Last_Quotient:= Quotient;
	X2_Last_Remainder:= Remainder;

	Result:= Remainder;
	end;

if	(X2_Last_Remainder.Overflow_flag)
or	(X2_Last_Quotient.Overflow_flag)
then
	begin
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EIntOverflow.create('Overflow');
		end;
	end;
end;


(***********v2************)
procedure SqRoot(const v1:Multi_Int_X2; out VR,VREM:Multi_Int_X2);
var
D,D2		:MULTI_INT_2W_S;
HS,LS,TS	:ansistring;
H,L,
C,CC,
LPC,TC,
Q,R,T		:Multi_Int_X2;
finished	:boolean;

begin
if	(Not v1.Defined_flag)
then
	begin
	VR:= 0;
	VR.Defined_flag:= FALSE;
	VREM:= 0;
	VREM.Defined_flag:= FALSE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;
if	(v1.Overflow_flag)
then
	begin
	VR:= 0;
	VR.Defined_flag:= FALSE;
	VREM:= 0;
	VREM.Defined_flag:= FALSE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EIntOverflow.create('Overflow');
		end;
	exit;
	end;

if	(v1.Negative_flag = Multi_UBool_TRUE)
then
	begin
	VR:= 0;
	VR.Defined_flag:= FALSE;
	VREM:= 0;
	VREM.Defined_flag:= FALSE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EIntOverflow.create('Overflow');
		end;
	exit;
	end;

VR.Defined_flag:= FALSE;
VREM.Defined_flag:= FALSE;

if	(v1 >= 100) then
	begin
	TS:= v1.ToStr;
	D:= length(TS);
	D2:= D div 2;
	if ((D mod 2)=0) then
		begin
		LS:= '1' + AddCharR('0','',D2-1);
		HS:= '1' + AddCharR('0','',D2);
		H:= HS;
		L:= LS;
		end
	else
		begin
		LS:= '1' + AddCharR('0','',D2);
		HS:= '1' + AddCharR('0','',D2+1);
		H:= HS;
		L:= LS;
		end;

	T:= (H-L);
	ShiftDown_MultiBits_Multi_Int_X2(T, 1);
	C:= (L+T);
	end
else
	begin
	C:= (v1 div 2);
	if	(C = 0) then C:= 1;
	end;

finished:= FALSE;
LPC:= v1;
repeat
	begin
	// CC:= ((C + (v1 div C)) div 2);
    intdivide_taylor_warruth_X2(v1, C, Q, R);
	if (Multi_Int_ERROR) then exit;

	CC:= (C + Q);
	if (Multi_Int_ERROR) then exit;

    ShiftDown_MultiBits_Multi_Int_X2(CC, 1);

	TC:= (C - CC);
	if (Multi_Int_ERROR) then exit;

	if	(ABS(TC) < 2) then
		begin
		if	(CC < LPC) then
			LPC:= CC
		else if (CC >= LPC) then
			finished:= TRUE
		end;
	C:= CC;
	end
until finished;

TC:= (LPC * LPC);
if (Multi_Int_ERROR) then exit;

VREM:= (v1 - TC);
if (Multi_Int_ERROR) then exit;

VR:= LPC;
VR.Negative_flag:= Multi_UBool_FALSE;
VREM.Negative_flag:= Multi_UBool_FALSE;

end;


(*************************)
procedure SqRoot(const v1:Multi_Int_X2; out VR:Multi_Int_X2);				{$ifdef inline_functions_level_1} inline; {$endif}
var	VREM:Multi_Int_X2;
begin
VREM:= 0;
sqroot(v1,VR,VREM);
end;


(*************************)
function SqRoot(const v1:Multi_Int_X2):Multi_Int_X2;						{$ifdef inline_functions_level_1} inline; {$endif}
var	VR,VREM:Multi_Int_X2;
begin
VREM:= 0;
sqroot(v1,VR,VREM);
Result:= VR;
end;


{
******************************************
Multi_Int_X5  INTERNAL USE ONLY!
******************************************
}


(******************************************)
function ABS_greaterthan_Multi_Int_X5(const v1,v2:Multi_Int_X5):Boolean;
begin
if	(v1.M_Value[4] > v2.M_Value[4])
then begin Result:=TRUE; exit; end
else
	if	(v1.M_Value[4] < v2.M_Value[4])
	then begin Result:=FALSE; exit; end
	else
		if	(v1.M_Value[3] > v2.M_Value[3])
		then begin Result:=TRUE; exit; end
		else
			if	(v1.M_Value[3] < v2.M_Value[3])
			then begin Result:=FALSE; exit; end
			else
				if	(v1.M_Value[2] > v2.M_Value[2])
				then begin Result:=TRUE; exit; end
				else
					if	(v1.M_Value[2] < v2.M_Value[2])
					then begin Result:=FALSE; exit; end
					else
						if	(v1.M_Value[1] > v2.M_Value[1])
						then begin Result:=TRUE; exit; end
						else
							if	(v1.M_Value[1] < v2.M_Value[1])
							then begin Result:=FALSE; exit; end
							else
								if	(v1.M_Value[0] > v2.M_Value[0])
								then begin Result:=TRUE; exit; end
								else begin Result:=FALSE; exit; end;
end;


(******************************************)
function ABS_lessthan_Multi_Int_X5(const v1,v2:Multi_Int_X5):Boolean;
begin
if	(v1.M_Value[4] < v2.M_Value[4])
then begin Result:=TRUE; exit; end
else
	if	(v1.M_Value[4] > v2.M_Value[4])
	then begin Result:=FALSE; exit; end
	else
		if	(v1.M_Value[3] < v2.M_Value[3])
		then begin Result:=TRUE; exit; end
		else
			if	(v1.M_Value[3] > v2.M_Value[3])
			then begin Result:=FALSE; exit; end
			else
				if	(v1.M_Value[2] < v2.M_Value[2])
				then begin Result:=TRUE; exit; end
				else
					if	(v1.M_Value[2] > v2.M_Value[2])
					then begin Result:=FALSE; exit; end
					else
						if	(v1.M_Value[1] < v2.M_Value[1])
						then begin Result:=TRUE; exit; end
						else
							if	(v1.M_Value[1] > v2.M_Value[1])
							then begin Result:=FALSE; exit; end
							else
								if	(v1.M_Value[0] < v2.M_Value[0])
								then begin Result:=TRUE; exit; end
								else begin Result:=FALSE; exit; end;
end;


(******************************************)
function Multi_Int_X5.Negative:boolean; 
begin
Result:= self.Negative_flag;
end;


(******************************************)
class operator Multi_Int_X5.>(const v1,v2:Multi_Int_X5):Boolean;
begin
if	(Not v1.Defined_flag)
or	(Not v2.Defined_flag)
or	(v1.Overflow_flag)
or	(v2.Overflow_flag)
then
	begin
	Result:=FALSE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

Result:=FALSE;
if ( (v1.Negative_flag = FALSE) and (v2.Negative_flag = TRUE) )
then Result:=TRUE
else
	if ( (v1.Negative_flag = TRUE) and (v2.Negative_flag = FALSE) )
	then Result:=FALSE
	else
		if ( (v1.Negative_flag = FALSE) and (v2.Negative_flag = FALSE) )
		then Result:= ABS_greaterthan_Multi_Int_X5(v1,v2)
		else
			if ( (v1.Negative_flag = TRUE) and (v2.Negative_flag = TRUE) )
			then Result:= ABS_lessthan_Multi_Int_X5(v1,v2);
end;


(******************************************)
class operator Multi_Int_X5.>=(const v1,v2:Multi_Int_X5):Boolean;
begin
if	(Not v1.Defined_flag)
or	(Not v2.Defined_flag)
or	(v1.Overflow_flag)
or	(v2.Overflow_flag)
then
	begin
	Result:=FALSE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

Result:=FALSE;
if ( (v1.Negative_flag = FALSE) and (v2.Negative_flag = TRUE) )
then Result:=TRUE
else
	if ( (v1.Negative_flag = TRUE) and (v2.Negative_flag = FALSE) )
	then Result:=FALSE
	else
		if ( (v1.Negative_flag = FALSE) and (v2.Negative_flag = FALSE) )
		then Result:= (Not ABS_lessthan_Multi_Int_X5(v1,v2) )
		else
			if ( (v1.Negative_flag = TRUE) and (v2.Negative_flag = TRUE) )
			then Result:= (Not ABS_greaterthan_Multi_Int_X5(v1,v2) );
end;


{$ifdef 32bit}
(******************************************)
procedure ShiftUp_NBits_Multi_Int_X5(Var v1:Multi_Int_X5; NBits:MULTI_INT_1W_U);
var	carry_bits_1,
	carry_bits_2,
	carry_bits_mask,
	NBits_max,
	NBits_carry	:MULTI_INT_1W_U;

	procedure INT_1W_U_shl(var v1:MULTI_INT_1W_U; const nbits:MULTI_INT_1W_U); 
	var carry_bits_mask_2w	:MULTI_INT_2W_U;
	begin
	carry_bits_mask_2w:= v1;
	carry_bits_mask_2w:= (carry_bits_mask_2w << NBits);
	v1:= MULTI_INT_1W_U(carry_bits_mask_2w and MULTI_INT_1W_U_MAXINT);
	end;

begin
if NBits > 0 then
begin

carry_bits_mask:= $FFFF;
NBits_max:= MULTI_INT_1W_SIZE;
NBits_carry:= (NBits_max - NBits);
INT_1W_U_shl(carry_bits_mask, NBits_carry);

if NBits <= NBits_max then
	begin
	carry_bits_1:= ((v1.M_Value[0] and carry_bits_mask) >> NBits_carry);
	INT_1W_U_shl(v1.M_Value[0], NBits);

	carry_bits_2:= ((v1.M_Value[1] and carry_bits_mask) >> NBits_carry);
	INT_1W_U_shl(v1.M_Value[1], NBits);
	v1.M_Value[1]:= (v1.M_Value[1] OR carry_bits_1);

	carry_bits_1:= ((v1.M_Value[2] and carry_bits_mask) >> NBits_carry);
	INT_1W_U_shl(v1.M_Value[2], NBits);
	v1.M_Value[2]:= (v1.M_Value[2] OR carry_bits_2);

	carry_bits_2:= ((v1.M_Value[3] and carry_bits_mask) >> NBits_carry);
	INT_1W_U_shl(v1.M_Value[3], NBits);
	v1.M_Value[3]:= (v1.M_Value[3] OR carry_bits_1);

	carry_bits_1:= ((v1.M_Value[4] and carry_bits_mask) >> NBits_carry);
	INT_1W_U_shl(v1.M_Value[4], NBits);
	v1.M_Value[4]:= (v1.M_Value[4] OR carry_bits_2);
	end;
end;

end;

{$endif}


{$ifdef 64bit}
(******************************************)
procedure ShiftUp_NBits_Multi_Int_X5(Var v1:Multi_Int_X5; NBits:MULTI_INT_1W_U);
var	carry_bits_1,
	carry_bits_2,
	carry_bits_mask,
	NBits_max,
	NBits_carry	:MULTI_INT_1W_U;

begin
if NBits > 0 then
begin

carry_bits_mask:= $FFFFFFFF;
NBits_max:= MULTI_INT_1W_SIZE;
NBits_carry:= (NBits_max - NBits);
carry_bits_mask:= (carry_bits_mask << NBits_carry);

if NBits <= NBits_max then
	begin
	carry_bits_1:= ((v1.M_Value[0] and carry_bits_mask) >> NBits_carry);
	v1.M_Value[0]:= (v1.M_Value[0] << NBits);

	carry_bits_2:= ((v1.M_Value[1] and carry_bits_mask) >> NBits_carry);
	v1.M_Value[1]:= ((v1.M_Value[1] << NBits) OR carry_bits_1);

	carry_bits_1:= ((v1.M_Value[2] and carry_bits_mask) >> NBits_carry);
	v1.M_Value[2]:= ((v1.M_Value[2] << NBits) OR carry_bits_2);

	carry_bits_2:= ((v1.M_Value[3] and carry_bits_mask) >> NBits_carry);
	v1.M_Value[3]:= ((v1.M_Value[3] << NBits) OR carry_bits_1);

	carry_bits_1:= ((v1.M_Value[4] and carry_bits_mask) >> NBits_carry);
	v1.M_Value[4]:= ((v1.M_Value[4] << NBits) OR carry_bits_2);
	end;
end;

end;

{$endif}


(******************************************)
procedure ShiftDown_NBits_Multi_Int_X5(Var v1:Multi_Int_X5; NBits:MULTI_INT_1W_U);
var	carry_bits_1,
	carry_bits_2,
	carry_bits_mask,
	NBits_max,
	NBits_carry	:MULTI_INT_1W_U;

begin
if NBits > 0 then
	begin

	{$ifdef 32bit}
	carry_bits_mask:= $FFFF;
	{$endif}
	{$ifdef 64bit}
	carry_bits_mask:= $FFFFFFFF;
	{$endif}

	NBits_max:= MULTI_INT_1W_SIZE;
	NBits_carry:= (NBits_max - NBits);
	carry_bits_mask:= (carry_bits_mask >> NBits_carry);

	if NBits <= NBits_max then
		begin

		carry_bits_2:= ((v1.M_Value[4] and carry_bits_mask) << NBits_carry);
		v1.M_Value[4]:= ((v1.M_Value[4] >> NBits));

		carry_bits_1:= ((v1.M_Value[3] and carry_bits_mask) << NBits_carry);
		v1.M_Value[3]:= ((v1.M_Value[3] >> NBits) OR carry_bits_2);

		carry_bits_2:= ((v1.M_Value[2] and carry_bits_mask) << NBits_carry);
		v1.M_Value[2]:= ((v1.M_Value[2] >> NBits) OR carry_bits_1);

		carry_bits_1:= ((v1.M_Value[1] and carry_bits_mask) << NBits_carry);
		v1.M_Value[1]:= ((v1.M_Value[1] >> NBits) OR carry_bits_2);

		v1.M_Value[0]:= ((v1.M_Value[0] >> NBits) OR carry_bits_1);

		end;
	end;

end;


(******************************************)
procedure ShiftDown_NWords_Multi_Int_X5(Var v1:Multi_Int_X5; NWords:MULTI_INT_1W_U);
var	n	:MULTI_INT_1W_U;
begin
if	(NWords > 0) then
	if	(NWords <= Multi_X5_maxi) then
		begin
		n:= NWords;
		while (n > 0) do
			begin
			v1.M_Value[0]:= v1.M_Value[1];
			v1.M_Value[1]:= v1.M_Value[2];
			v1.M_Value[2]:= v1.M_Value[3];
			v1.M_Value[3]:= v1.M_Value[4];
			v1.M_Value[4]:= 0;
			DEC(n);
			end;
		end
	else
		begin
		v1.M_Value[0]:= 0;
		v1.M_Value[1]:= 0;
		v1.M_Value[2]:= 0;
		v1.M_Value[3]:= 0;
		v1.M_Value[4]:= 0;
		end;
end;


{******************************************}
procedure ShiftDown_MultiBits_Multi_Int_X5(Var v1:Multi_Int_X5; NBits:MULTI_INT_1W_U);
var
NWords_count,
NBits_count		:MULTI_INT_1W_U;

begin
if	(Not v1.Defined_flag)
then
	begin
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

if (NBits >= MULTI_INT_1W_SIZE) then
	begin
	NWords_count:= (NBits DIV MULTI_INT_1W_SIZE);
	NBits_count:= (NBits MOD MULTI_INT_1W_SIZE);
	ShiftDown_NWords_Multi_Int_X5(v1, NWords_count);
	end
else NBits_count:= NBits;

ShiftDown_NBits_Multi_Int_X5(v1, NBits_count);
end;


(******************************************)
procedure MULTI_INT_2W_U_to_Multi_Int_X5(const v1:MULTI_INT_2W_U; out mi:Multi_Int_X5); 
begin
mi.Overflow_flag:=FALSE;
mi.Defined_flag:=TRUE;
mi.Negative_flag:= Multi_UBool_FALSE;

mi.M_Value[0]:= (v1 MOD MULTI_INT_1W_U_MAXINT_1);
mi.M_Value[1]:= (v1 DIV MULTI_INT_1W_U_MAXINT_1);
mi.M_Value[2]:= 0;
mi.M_Value[3]:= 0;
mi.M_Value[4]:= 0;
end;


(******************************************)
class operator Multi_Int_X5.:=(const v1:MULTI_INT_2W_U):Multi_Int_X5;
begin
MULTI_INT_2W_U_to_Multi_Int_X5(v1,Result);
end;


(******************************************)
procedure Multi_Int_X2_to_Multi_Int_X5(const v1:Multi_Int_X2; out MI:Multi_Int_X5);
var
	n				:MULTI_INT_1W_U;
begin
MI.Overflow_flag:= v1.Overflow_flag;
MI.Defined_flag:= v1.Defined_flag;
MI.Negative_flag:= v1.Negative_flag;

if	(v1.Defined_flag = FALSE)
then
	begin
	Multi_Int_ERROR:= TRUE;
	MI.Defined_flag:= FALSE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

if	(v1.Overflow_flag = TRUE)
then
	begin
	Multi_Int_ERROR:= TRUE;
	MI.Overflow_flag:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Overflow');
		end;
	exit;
	end;

n:= 0;
while (n <= Multi_X2_maxi) do
	begin
	MI.M_Value[n]:= v1.M_Value[n];
	inc(n);
	end;

while (n <= Multi_X5_maxi) do
	begin
	MI.M_Value[n]:= 0;
	inc(n);
	end;
end;


(******************************************)
class operator Multi_Int_X5.:=(const v1:Multi_Int_X2):Multi_Int_X5;
begin
Multi_Int_X2_to_Multi_Int_X5(v1,Result);
end;


(******************************************)
function To_Multi_Int_X5(const v1:Multi_Int_X2):Multi_Int_X5;
begin
Multi_Int_X2_to_Multi_Int_X5(v1,Result);
end;


(******************************************)
function To_Multi_Int_X2(const v1:Multi_Int_X5):Multi_Int_X2; overload;
var n :MULTI_INT_1W_U;
begin
Result.Overflow_flag:= v1.Overflow_flag;
Result.Defined_flag:= v1.Defined_flag;
Result.Negative_flag:= v1.Negative_flag;

if	(v1.Defined_flag = FALSE)
then
	begin
	Result.Defined_flag:= FALSE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

if	(v1.Overflow_flag = TRUE)
or	(v1 > Multi_Int_X2_MAXINT)
then
	begin
	Result.Overflow_flag:= TRUE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Overflow');
		end;
	exit;
	end;

n:= 0;
while (n <= Multi_X2_maxi) do
	begin
	Result.M_Value[n]:= v1.M_Value[n];
	inc(n);
	end;
end;


(*******************v6*********************)
procedure multiply_Multi_Int_X5(const v1,v2:Multi_Int_X5; var Result:Multi_Int_X5); overload;
var
// zf		:boolean;
tv		:MULTI_INT_2W_U;
i,j,h	:MULTI_INT_2W_S;

begin
if	(Not v1.Defined_flag)
or	(Not v2.Defined_flag)
then
	begin
	Result.Defined_flag:= FALSE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;
if	(v1.Overflow_flag or v2.Overflow_flag)
then
	begin
	Result.Overflow_flag:=TRUE;
	Result.Defined_flag:=TRUE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EIntOverflow.create('Overflow');
		end;
	exit;
	end;

Result:= 0;
Result.Overflow_flag:=FALSE;
Result.Defined_flag:=TRUE;
Result.Negative_flag:=Multi_UBool_UNDEF;

i:=0; repeat Result.M_Value[i]:= 0; INC(i); until (i > Multi_X5_maxi);

Result.Overflow_flag:= FALSE;
Result.Defined_flag:= TRUE;
Result.Negative_flag:= Multi_UBool_UNDEF;

// main loopy
h:= 0;
i:= 0;
j:= 0;
repeat
	if (v2.M_Value[j] <> 0) then
    	begin
		repeat
			if	(v1.M_Value[i] <> 0)
			then
				begin
				h:= (i+j);
				if (h > Multi_X5_maxi) then
					begin
					Result.Overflow_flag:=TRUE;
					exit;
					end;
                tv:= MULTI_INT_2W_U(Result.M_Value[h]) + (MULTI_INT_2W_U(v1.M_Value[i]) * MULTI_INT_2W_U(v2.M_Value[j]));
				Result.M_Value[h]:= (tv MOD MULTI_INT_1W_U_MAXINT_1);
                tv:= (tv DIV MULTI_INT_1W_U_MAXINT_1);
				while (tv > 0) do
					begin
					Inc(h);
					if (h > Multi_X5_maxi) then
						begin
						Result.Overflow_flag:=TRUE;
						exit;
						end;
	                tv:= (tv + Result.M_Value[h]);
					Result.M_Value[h]:= (tv MOD MULTI_INT_1W_U_MAXINT_1);
					tv:= (tv DIV MULTI_INT_1W_U_MAXINT_1);
					end;
				end;
			INC(i);
		until (i > Multi_X5_maxi);
		i:=0;
        end;
	INC(j);
until (j > Multi_X5_maxi);

if	(v1.Negative_flag = v2.Negative_flag)
then Result.Negative_flag:= Multi_UBool_FALSE
else Result.Negative_flag:=Multi_UBool_TRUE;

end;


(******************************************)
class operator Multi_Int_X5.*(const v1,v2:Multi_Int_X5):Multi_Int_X5;
var	  R:Multi_Int_X5;
begin
if	(Not v1.Defined_flag)
or	(Not v2.Defined_flag)
then
	begin
	Result:=0;
	Result.Defined_flag:= FALSE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

if	(v1.Overflow_flag or v2.Overflow_flag)
then
	begin
	Result:= 0;
	Result.Overflow_flag:=TRUE;
	Result.Defined_flag:=TRUE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EIntOverflow.create('Overflow');
		end;
	exit;
	end;

multiply_Multi_Int_X5(v1,v2,R);

if	(R.Negative_flag = Multi_UBool_UNDEF) then
	if	(v1.Negative_flag = v2.Negative_flag)
	then R.Negative_flag:= Multi_UBool_FALSE
	else R.Negative_flag:=Multi_UBool_TRUE;

Result:= R;

if (Result.Overflow_flag = TRUE) then
	begin
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		Raise EIntOverflow.create('Overflow');
	end;

end;


(********************v2********************)
procedure add_Multi_Int_X5(const v1,v2:Multi_Int_X5; var Result:Multi_Int_X5);
var
	TV,CV	:MULTI_INT_2W_U;
	all_zero:boolean;
begin
Result.Overflow_flag:=FALSE;
Result.Defined_flag:=TRUE;
Result.Negative_flag:=Multi_UBool_UNDEF;

all_zero:= TRUE;
CV:= 0;

TV:=(MULTI_INT_2W_U(v1.M_Value[0]) + MULTI_INT_2W_U(v2.M_Value[0]));
if (TV <> 0) then all_zero:= FALSE;
if	(TV > MULTI_INT_1W_U_MAXINT) then
	begin
	Result.M_Value[0]:= (TV - MULTI_INT_1W_U_MAXINT_1);
	CV:= 1;
	end
else
	begin
	Result.M_Value[0]:= TV;
	CV:= 0;
	end;

TV:=(MULTI_INT_2W_U(v1.M_Value[1]) + MULTI_INT_2W_U(v2.M_Value[1]) + CV);
if (TV <> 0) then all_zero:= FALSE;
if	(TV > MULTI_INT_1W_U_MAXINT) then
	begin
	Result.M_Value[1]:= (TV - MULTI_INT_1W_U_MAXINT_1);
	CV:= 1;
	end
else
	begin
	Result.M_Value[1]:= TV;
	CV:= 0;
	end;

TV:=(MULTI_INT_2W_U(v1.M_Value[2]) + MULTI_INT_2W_U(v2.M_Value[2]) + CV);
if (TV <> 0) then all_zero:= FALSE;
if	(TV > MULTI_INT_1W_U_MAXINT) then
	begin
	Result.M_Value[2]:= (TV - MULTI_INT_1W_U_MAXINT_1);
	CV:= 1;
	end
else
	begin
	Result.M_Value[2]:= TV;
	CV:= 0;
	end;

TV:=(MULTI_INT_2W_U(v1.M_Value[3]) + MULTI_INT_2W_U(v2.M_Value[3]) + CV);
if (TV <> 0) then all_zero:= FALSE;
if	(TV > MULTI_INT_1W_U_MAXINT) then
	begin
	Result.M_Value[3]:= (TV - MULTI_INT_1W_U_MAXINT_1);
	CV:= 1;
	end
else
	begin
	Result.M_Value[3]:= TV;
	CV:= 0;
	end;

TV:=(MULTI_INT_2W_U(v1.M_Value[4]) + MULTI_INT_2W_U(v2.M_Value[4]) + CV);
if (TV <> 0) then all_zero:= FALSE;
if	(TV > MULTI_INT_1W_U_MAXINT) then
	begin
	Result.M_Value[4]:= (TV - MULTI_INT_1W_U_MAXINT_1);
	CV:= 1;
	end
else
	Result.M_Value[4]:= TV;


if all_zero then Result.Negative_flag:=Multi_UBool_FALSE;

end;


(********************v2********************)
procedure subtract_Multi_Int_X5(const v1,v2:Multi_Int_X5; var Result:Multi_Int_X5);
var
	TV,CV	:MULTI_INT_2W_S;
	all_zero:boolean;
begin
Result.Overflow_flag:=FALSE;
Result.Defined_flag:=TRUE;
Result.Negative_flag:=Multi_UBool_UNDEF;

all_zero:= TRUE;
CV:= 0;

TV:=(v1.M_Value[0] - v2.M_Value[0]);
if (TV <> 0) then all_zero:= FALSE;
if	TV < 0 then
	begin
	Result.M_Value[0]:= (TV + MULTI_INT_1W_U_MAXINT_1);
	CV:= -1;
	end
else
	begin
	Result.M_Value[0]:= TV;
	CV:= 0;
	end;

TV:=(v1.M_Value[1] - v2.M_Value[1] + CV);
if (TV <> 0) then all_zero:= FALSE;
if	TV < 0 then
	begin
	Result.M_Value[1]:= (TV + MULTI_INT_1W_U_MAXINT_1);
	CV:= -1;
	end
else
	begin
	Result.M_Value[1]:= TV;
	CV:= 0;
	end;

TV:=(v1.M_Value[2] - v2.M_Value[2] + CV);
if (TV <> 0) then all_zero:= FALSE;
if	TV < 0 then
	begin
	Result.M_Value[2]:= (TV + MULTI_INT_1W_U_MAXINT_1);
	CV:= -1;
	end
else
	begin
	Result.M_Value[2]:= TV;
	CV:= 0;
	end;

TV:=(v1.M_Value[3] - v2.M_Value[3] + CV);
if (TV <> 0) then all_zero:= FALSE;
if	TV < 0 then
	begin
	Result.M_Value[3]:= (TV + MULTI_INT_1W_U_MAXINT_1);
	CV:= -1;
	end
else
	begin
	Result.M_Value[3]:= TV;
	CV:= 0;
	end;

TV:=(v1.M_Value[4] - v2.M_Value[4] + CV);
if (TV <> 0) then all_zero:= FALSE;
if	TV < 0 then
	begin
	Result.M_Value[4]:= (TV + MULTI_INT_1W_U_MAXINT_1);
	CV:= -1;
	end
else
	Result.M_Value[4]:= TV;

if all_zero then Result.Negative_flag:=Multi_UBool_FALSE;

end;


(******************************************)
class operator Multi_Int_X5.-(const v1,v2:Multi_Int_X5):Multi_Int_X5;
Var	Neg:Multi_UBool_Values;
begin
if	(Not v1.Defined_flag)
or	(Not v2.Defined_flag)
then
	begin
	Result:=0;
	Result.Defined_flag:= FALSE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EInterror.create('Uninitialised variable');
		end;
	exit;
	end;

if	(v1.Overflow_flag or v2.Overflow_flag)
then
	begin
	Result:= 0;
	Result.Overflow_flag:=TRUE;
	Result.Defined_flag:=TRUE;
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		begin
		Raise EIntOverflow.create('Overflow');
		end;
	exit;
	end;

Neg:=Multi_UBool_UNDEF;

if	(v1.Negative_flag = v2.Negative_flag)
then
	begin
	if	(v1.Negative_flag = TRUE) then
		begin
		if	ABS_greaterthan_Multi_Int_X5(v1,v2)
		then
			begin
			subtract_Multi_Int_X5(v1,v2,Result);
			Neg:=Multi_UBool_TRUE;
			end
		else
			begin
			subtract_Multi_Int_X5(v2,v1,Result);
			Neg:=Multi_UBool_FALSE;
			end
		end
	else	(* if	not Negative_flag then	*)
		begin
		if	ABS_greaterthan_Multi_Int_X5(v2,v1)
		then
			begin
			subtract_Multi_Int_X5(v2,v1,Result);
			Neg:=Multi_UBool_TRUE;
			end
		else
			begin
			subtract_Multi_Int_X5(v1,v2,Result);
			Neg:=Multi_UBool_FALSE;
			end
		end
	end
else (* v1.Negative_flag <> v2.Negative_flag *)
	begin
	if	(v2.Negative_flag = TRUE) then
		begin
		add_Multi_Int_X5(v1,v2,Result);
		Neg:=Multi_UBool_FALSE;
		end
	else
		begin
		add_Multi_Int_X5(v1,v2,Result);
		Neg:=Multi_UBool_TRUE;
		end
	end;

if (Result.Overflow_flag = TRUE) then
	begin
	Multi_Int_ERROR:= TRUE;
	if Multi_Int_RAISE_EXCEPTIONS_ENABLED then
		Raise EIntOverflow.create('Overflow');
	end;

if	(Result.Negative_flag = Multi_UBool_UNDEF) then Result.Negative_flag:= Neg;
end;


procedure Multi_Int_Reset_X2_Last_Divisor;
begin
X2_Last_Divisor:= 0;
X2_Last_Dividend:= 0;
X2_Last_Quotient:= 0;
X2_Last_Remainder:= 0;
end;


begin

X2_Last_Divisor:= 0;
X2_Last_Dividend:= 0;
X2_Last_Quotient:= 0;
X2_Last_Remainder:= 0;

Multi_Int_X2_MAXINT:= 0;
i:=0;
while (i <= Multi_X2_maxi) do
	begin
	Multi_Int_X2_MAXINT.M_Value[i]:= MULTI_INT_1W_U_MAXINT;
	Inc(i);
	end;
Multi_Int_X2_MAXINT.Defined_flag:= TRUE;
Multi_Int_X2_MAXINT.Negative_flag:= FALSE;
Multi_Int_X2_MAXINT.Overflow_flag:= FALSE;

{
What is the point of Force_recompile ?
I have been getting problems where disabling/enabling the
{$define inline_functions_level_1} has not been picked-up
by the compiler. So whenever I change the define, I also
change the value assigned to T, which forces a re-compile.
}

Force_recompile:= 1;
end.
