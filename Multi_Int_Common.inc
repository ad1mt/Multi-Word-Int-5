
var
i, Force_recompile				:MULTI_INT_1W_U;

(******************************************)
procedure	T_Multi_UBool.Init(v:Multi_UBool_Values);
begin
if (v = Multi_UBool_TRUE) then B_Value:= Multi_UBool_TRUE
else if (v = Multi_UBool_FALSE) then B_Value:= Multi_UBool_FALSE
else B_Value:= Multi_UBool_UNDEF;
end;

function	T_Multi_UBool.ToStr:string;
begin
if (B_Value = Multi_UBool_TRUE) then Result:= 'TRUE'
else if (B_Value = Multi_UBool_FALSE) then Result:= 'FALSE'
else Result:= 'UNDEFINED';
end;

class operator T_Multi_UBool.:=(v:Multi_UBool_Values):T_Multi_UBool;
begin
Result.B_Value:= v;
end;

class operator T_Multi_UBool.:=(v:T_Multi_UBool):Multi_UBool_Values;
begin
Result:= v.B_Value;
end;

class operator T_Multi_UBool.:=(v:Boolean):T_Multi_UBool;
begin
if v then Result.B_Value:= Multi_UBool_TRUE
else Result.B_Value:= Multi_UBool_FALSE;
end;

class operator T_Multi_UBool.:=(v:T_Multi_UBool):Boolean;
begin
if (v.B_Value = Multi_UBool_TRUE) then Result:= TRUE
else Result:= FALSE;
end;

class operator T_Multi_UBool.=(v1,v2:T_Multi_UBool):Boolean;
begin
if (v1.B_Value = v2.B_Value) then Result:= TRUE
else Result:= FALSE;
end;

class operator T_Multi_UBool.<>(v1,v2:T_Multi_UBool):Boolean;
begin
if (v1.B_Value <> v2.B_Value) then Result:= TRUE
else Result:= FALSE;
end;

class operator T_Multi_UBool.<=(v1,v2:T_Multi_UBool):Boolean;
begin
if (v1.B_Value <= v2.B_Value) then Result:= TRUE
else Result:= FALSE;
end;

class operator T_Multi_UBool.<(v1,v2:T_Multi_UBool):Boolean;
begin
if (v1.B_Value < v2.B_Value) then Result:= TRUE
else Result:= FALSE;
end;

class operator T_Multi_UBool.>=(v1,v2:T_Multi_UBool):Boolean;
begin
if (v1.B_Value >= v2.B_Value) then Result:= TRUE
else Result:= FALSE;
end;

class operator T_Multi_UBool.>(v1,v2:T_Multi_UBool):Boolean;
begin
if (v1.B_Value > v2.B_Value) then Result:= TRUE
else Result:= FALSE;
end;

class operator T_Multi_UBool.or(v1,v2:T_Multi_UBool):Boolean;
begin
if	(v1.B_Value = Multi_UBool_TRUE)
or	(v2.B_Value = Multi_UBool_TRUE)
then Result:= TRUE
else Result:= FALSE;
end;

class operator T_Multi_UBool.or(v1:T_Multi_UBool;v2:Boolean):Boolean;
begin
if	(v1.B_Value = Multi_UBool_TRUE)
or	(v2)
then Result:= TRUE
else Result:= FALSE;
end;

class operator T_Multi_UBool.or(v1:Boolean;v2:T_Multi_UBool):Boolean;
begin
if	(v1)
or	(v2.B_Value = Multi_UBool_TRUE)
then Result:= TRUE
else Result:= FALSE;
end;

class operator T_Multi_UBool.and(v1,v2:T_Multi_UBool):Boolean;
begin
if	(v1.B_Value = Multi_UBool_TRUE)
and	(v2.B_Value = Multi_UBool_TRUE)
then Result:= TRUE
else Result:= FALSE;
end;

class operator T_Multi_UBool.and(v1:T_Multi_UBool;v2:Boolean):Boolean;
begin
if	(v1.B_Value = Multi_UBool_TRUE)
and	(v2)
then Result:= TRUE
else Result:= FALSE;
end;

class operator T_Multi_UBool.and(v1:Boolean; v2:T_Multi_UBool):Boolean;
begin
if	(v1)
and	(v2.B_Value = Multi_UBool_TRUE)
then Result:= TRUE
else Result:= FALSE;
end;

class operator T_Multi_UBool.not(v1:T_Multi_UBool):Boolean;
begin
if	(v1.B_Value = Multi_UBool_TRUE) then Result:= FALSE
else if (v1.B_Value = Multi_UBool_FALSE) then Result:= TRUE
else Result:= FALSE;
end;

class operator T_Multi_UBool.not(v1:T_Multi_UBool):T_Multi_UBool;
begin
if	(v1.B_Value = Multi_UBool_TRUE) then Result:= Multi_UBool_FALSE
else if (v1.B_Value = Multi_UBool_FALSE) then Result:= Multi_UBool_TRUE
else Result:= Multi_UBool_UNDEF;
end;


{$ifdef 32bit}
(******************************************)
function nlz_bits(P_x:MULTI_INT_1W_U):MULTI_INT_1W_U;
var
n		:Multi_int32;
x,t		:MULTI_INT_1W_U;
begin
if (P_x = 0) then Result:= 16
else
	begin
	x:= P_x;
	n:= 0;
	t:=(x and MULTI_INT_1W_U(65280));
	if	(t = 0) then begin n:=(n + 8); x:=(x << 8); end;

	t:=(x and MULTI_INT_1W_U(61440));
	if	(t = 0) then begin n:=(n + 4); x:=(x << 4); end;

	t:=(x and MULTI_INT_1W_U(49152));
	if	(t = 0) then begin n:=(n + 2); x:=(x << 2); end;

	t:=(x and MULTI_INT_1W_U(32768));
	if	(t = 0) then begin n:=(n + 1); end;
	Result:= n;
	end;
end;

{$endif}


{$ifdef 64bit}
(******************************************)
function nlz_bits(x:MULTI_INT_1W_U):MULTI_INT_1W_U;
var	n	:Multi_int32;
begin
if (x = 0) then Result:= 32
else
	begin
	n:= 1;
	if	((x >> 16) = 0) then begin n:=(n + 16); x:=(x << 16); end;
	if	((x >> 24) = 0) then begin n:=(n + 8); x:=(x << 8); end;
	if	((x >> 28) = 0) then begin n:=(n + 4); x:=(x << 4); end;
	if	((x >> 30) = 0) then begin n:=(n + 2); x:=(x << 2); end;
	n:= (n - (x >> 31));
	Result:= n;
	end;
end;
{$endif}
